#include "RateLeaf.h"
#include <sstream>

namespace umstel {

	RateLeaf::RateLeaf(CurrencyNode & source, CurrencyNode & dest, const double rate) : _source(source), _dest(dest) {
		set(rate);
	}

	void RateLeaf::set(const double rate) {
		_rateValue = rate;
	}

	double RateLeaf::get() {
		return _rateValue;
	}

	CurrencyNode & RateLeaf::source() {
		return _source;
	}

	CurrencyNode & RateLeaf::dest() {
		return _dest;
	}

	short RateLeaf::rang() {
		return 1;
	}

	const string RateLeaf::path() {
		ostringstream oss;
		oss << "{" << _source.name() << "," << dest().name() << "," << _rateValue << "}";
		return oss.str();
	}
}