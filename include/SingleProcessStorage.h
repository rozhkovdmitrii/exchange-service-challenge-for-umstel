#pragma once
#include "RateStorageBase.h"
#include "RateBase.h"
#include "CurrencyNode.h"

namespace umstel {
	using namespace std;

	class SingleProcessStorage {
		typedef map<const string, CurrencyNode> StorageType;
		typedef CurrencyNode::RatePtr RatePtr;
		SingleProcessStorage() = default;
		~SingleProcessStorage() = default;

	public:

		static SingleProcessStorage & instance();

		void set(const string & first, const string & second, const double rate);
		pair<double, short> get(const string & first, const string & second);
		const string path(const string & first, const string & second);
		CurrencyNode & node(const string & name);

	private:

		void setDirectRates(CurrencyNode & first, CurrencyNode & second, const double rate);
		void setIndirectRates(CurrencyNode & source, CurrencyNode & dest);

		StorageType _nodes;
		static SingleProcessStorage * _instance;
	};

}