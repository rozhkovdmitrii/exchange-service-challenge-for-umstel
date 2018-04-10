#include "SingleProcessStorage.h"
#include "RateLeaf.h"
#include "RateComposite.h"
#include "RateReverse.h"
#include <memory>

namespace umstel {

	SingleProcessStorage * SingleProcessStorage::_instance = nullptr;
	SingleProcessStorage & SingleProcessStorage::instance() {
		if (_instance == nullptr)
			_instance = new SingleProcessStorage;
		return *_instance;
	}

	void SingleProcessStorage::set(const string & source, const string & dest, const double rate) {
		CurrencyNode & sourceNode = node(source);
		CurrencyNode & destNode = node(dest);
		setDirectRates(sourceNode, destNode, rate);
		setIndirectRates(sourceNode, destNode);
		setIndirectRates(destNode, sourceNode);
	}

	void SingleProcessStorage::setDirectRates(CurrencyNode & source, CurrencyNode & dest, const double rate) {
		CurrencyNode::RatePtr ratePtr = source.rateTo(dest);
		RateLeaf::PtrType rateLeafPtr(dynamic_pointer_cast<RateLeaf>(ratePtr));
		RateReverse::PtrType rateReversePtr(dynamic_pointer_cast<RateReverse>(ratePtr));
		RateComposite::PtrType rateCompositPtr(dynamic_pointer_cast<RateComposite>(ratePtr));

		if (rateLeafPtr) {
			rateLeafPtr->set(rate);
		} else if (rateReversePtr) {
			setDirectRates(dest, source, 1 / rate);
		} else if (!ratePtr || rateCompositPtr) {
			ratePtr = make_shared<RateLeaf>(source, dest, rate);
			source.setRate(dest, ratePtr);
			dest.setRate(source, make_shared<RateReverse>(ratePtr));
		}
	}

	void SingleProcessStorage::setIndirectRates(CurrencyNode & source, CurrencyNode & dest) {
		RatePtr origin = source.rateTo(dest);
		RatePtr reverse = dest.rateTo(source);
		auto resetNeighborRate = [&,this](RatePtr & neighborRate) {
			CurrencyNode & someNode = neighborRate->dest();
			if (reverse->equalBySourceDest(neighborRate))
				return;
			RatePtr sourceToSomeNode = source.rateTo(someNode);
			if (sourceToSomeNode && sourceToSomeNode->rang() <= neighborRate->rang() + origin->rang())
				return;
			if (!sourceToSomeNode) {
				sourceToSomeNode = make_shared<RateComposite>(origin, neighborRate);
				source.setRate(someNode, sourceToSomeNode);
				RatePtr someNodeToSource = make_shared<RateComposite>(someNode.rateTo(dest), reverse);
				someNode.setRate(source, someNodeToSource);
				setIndirectRates(source, someNode);
				setIndirectRates(someNode, source);
				return;
			}
			RateComposite::PtrType existingCompositePtr = dynamic_pointer_cast<RateComposite>(source.rateTo(someNode));
			existingCompositePtr->set(origin, neighborRate);
			existingCompositePtr = dynamic_pointer_cast<RateComposite>(someNode.rateTo(source));
			existingCompositePtr->set(someNode.rateTo(dest), reverse);
		};

		dest.forEachRate(resetNeighborRate);
	}

	pair<double, short> SingleProcessStorage::get(const string & first, const string & second) {
		CurrencyNode::RatePtr ratePtr = node(first).rateTo(second);
		return ratePtr ? pair<double, short>(ratePtr->get(), ratePtr->rang()) : pair<double, short>(0, 0);
	}

	const string SingleProcessStorage::path(const string & first, const string & second) {
		CurrencyNode::RatePtr ratePtr = node(first).rateTo(second);
		if (ratePtr)
			return ratePtr->path();
		const string noPath = "no rate";
		return noPath;
	}

	CurrencyNode & SingleProcessStorage::node(const string & name) {
		StorageType::iterator found = _nodes.find(name);
		if (found != _nodes.end())
			return found->second;
		StorageType::value_type newNode(name, CurrencyNode(name));
		return _nodes.insert(newNode).first->second;
	}
}