#include "RateComposite.h"

namespace umstel {
	
	RateComposite::RateComposite(const CurrencyNode::RatePtr firstRate, const CurrencyNode::RatePtr secondRate) {
		set(firstRate, secondRate);
	}

	void RateComposite::set(const Rate::PtrType firstRate, const Rate::PtrType secondRate) {
		_firstRate = firstRate;
		_secondRate = secondRate;
	}

	double RateComposite::get() {
		double result = _firstRate->get() * _secondRate->get();
		return result;
	}

	CurrencyNode & RateComposite::source() {
		return _firstRate->source();
	}

	CurrencyNode & RateComposite::dest() {
		return _secondRate->dest();
	}

	short RateComposite::rang() {
		return _firstRate->rang() + _secondRate->rang();
	}

	const string RateComposite::path() {
		return string("(") + _firstRate->path() + "*" + _secondRate->path() + ")";
	}

}