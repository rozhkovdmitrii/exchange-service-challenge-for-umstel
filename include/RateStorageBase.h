#pragma once

#pragma once

#include <string>

namespace umstel {
	using namespace std;

	class RateStorageBase {
	protected:
		RateStorageBase() = default;
		~RateStorageBase() = default;
		RateStorageBase(const RateStorageBase &) = delete;
		RateStorageBase & operator=(const RateStorageBase &) = delete;
	public:
		virtual void set(const string & first, const string & second, const double rate) = 0;
		virtual pair<double, short> get(const string & first, const string & second) = 0;
	};

}
