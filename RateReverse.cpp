#include "RateReverse.h"

namespace umstel {

	RateReverse::RateReverse(Rate::PtrType ratePtr) : _directPtr(ratePtr) {}

	double RateReverse::get() {
		return 1 / _directPtr->get();
	}

	CurrencyNode & RateReverse::source() {
		return _directPtr->dest();
	}

	CurrencyNode & RateReverse::dest() {
		return _directPtr->source();
	}

	short RateReverse::rang() {
		return _directPtr->rang();
	}

	const string RateReverse::path() {
		return string("1/") + _directPtr->path();
	}

	CurrencyNode::RatePtr RateReverse::getDirect() const {
		return _directPtr;
	}
}

