#include "CurrencyNode.h"

namespace umstel {

	CurrencyNode::CurrencyNode(const string & currencyName) : _name(currencyName) {}
	
	void CurrencyNode::setRate(const CurrencyNode & destCurrency, RatePtr rate) {
		_rates[destCurrency.name()] = rate;
	}
	
	CurrencyNode::RatePtr CurrencyNode::rateTo(const CurrencyNode & destCurrency) const {
		auto rateItr = _rates.find(destCurrency.name());
		return rateItr == _rates.end() ? nullptr : rateItr->second;
	}

	const string & CurrencyNode::name() const {
		return _name;
	}

	bool CurrencyNode::operator==(const CurrencyNode & otherNode) const {
		return this == &otherNode;
	}
}


