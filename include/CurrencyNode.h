#pragma once
#include <map>
#include "RateBase.h"

namespace umstel {

	class CurrencyNode {
		typedef map<const string, Rate<CurrencyNode>::PtrType> RatesCollection;

	public:

		typedef Rate<CurrencyNode>::PtrType RatePtr;

		CurrencyNode() = default;
		~CurrencyNode() = default;
		CurrencyNode(const string & currencyName);
		
		void setRate(const CurrencyNode & destCurrency, RatePtr rate);
		RatePtr rateTo(const CurrencyNode & destCurrency) const;

		bool operator==(const CurrencyNode & otherNode) const;
		const string & name() const;

		template<class RateOperation>
		void forEachRate(RateOperation);

	private:

		RatesCollection _rates;
		const string _name;
	};

	template<class RateOperation>
	inline void CurrencyNode::forEachRate(RateOperation rateOperation) {
		for (RatesCollection::iterator itr = _rates.begin(); itr != _rates.end(); ++itr) {
			rateOperation(itr->second);
		}
	}

}

