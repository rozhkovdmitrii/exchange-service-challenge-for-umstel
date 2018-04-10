#pragma once
#include "RateBase.h"
#include "CurrencyNode.h"

namespace umstel {

	class RateReverse : public Rate<CurrencyNode>{
	
	public:

		typedef shared_ptr<RateReverse> PtrType;

		RateReverse() = delete;
		~RateReverse() = default;
		RateReverse(Rate::PtrType ratePtr);

		double get() override;

		CurrencyNode & source() override;
		CurrencyNode & dest() override;
		short rang() override;
		const string path() override;

		Rate::PtrType getDirect() const;
	
	private:
	
		Rate::PtrType _directPtr;
	};
}

