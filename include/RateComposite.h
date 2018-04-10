#pragma once
#include "RateBase.h"
#include "CurrencyNode.h"
#include <memory>

namespace umstel {

	using namespace std;
	
	class RateComposite : public Rate<CurrencyNode> {
	
	public:
	
		typedef shared_ptr<RateComposite> PtrType;

		RateComposite() = delete;
		~RateComposite() = default;

		RateComposite(const  CurrencyNode::RatePtr firstRate, const CurrencyNode::RatePtr secondRate);
		
		void set(const Rate::PtrType firstRate, const Rate::PtrType secondRate);
		double get() override;

		CurrencyNode & source() override;
		CurrencyNode & dest() override;
		short rang() override;
		const string path() override;

	private:

		Rate::PtrType _firstRate;
		Rate::PtrType _secondRate;
	};
}
