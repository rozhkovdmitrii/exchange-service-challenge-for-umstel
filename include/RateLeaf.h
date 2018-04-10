#pragma once
#include "RateBase.h"
#include "CurrencyNode.h"

namespace umstel {
	
	class RateLeaf : public Rate<CurrencyNode> {
	
	public:

		typedef shared_ptr<RateLeaf> PtrType;

		RateLeaf() = delete;
		~RateLeaf() = default;
		RateLeaf(CurrencyNode & source, CurrencyNode & dest, const double rate);

		void set(const double rate);
		double get() override;

		CurrencyNode & source() override;
		CurrencyNode & dest() override;
		short rang() override;
		const string path() override;
	
	private:
	
		double _rateValue;
		CurrencyNode & _source;
		CurrencyNode & _dest;
	};
}
