#pragma once
#include <string>
#include <memory>

namespace umstel {
	using namespace std;

	template<class NodeType>
	class Rate {
	
	public:
	
		typedef shared_ptr<Rate> PtrType;

		virtual double get() = 0;
		virtual short rang() = 0;

		virtual NodeType & source() = 0;
		virtual NodeType & dest() = 0;
		
		virtual const string path() = 0;
		bool equalBySourceDest(const PtrType rate) {
			return source().name() == rate->source().name() && dest().name() == rate->dest().name();
		}

	protected:

		Rate() = default;
		~Rate() = default;
		Rate(const Rate &) = default;
		Rate & operator=(const Rate &) = default;

	};
}
