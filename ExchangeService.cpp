#include "ExchangeService.h"
#include "SingleProcessStorage.h"

namespace umstel {
	using namespace std;

	void setExchangeRate(const string & first_currency, const string & second_currency, const double exchange_rate) {
		SingleProcessStorage & instance = SingleProcessStorage::instance();
		instance.set(first_currency, second_currency, exchange_rate);
	}

	const double getExchangeRate(const string & first_currency, const string & second_currency) {
		SingleProcessStorage & instance = SingleProcessStorage::instance();
		return instance.get(first_currency, second_currency).first;
	}

	pair<double, short> _getExchangeRate(const string & first_currency, const string & second_currency) {
		SingleProcessStorage & instance = SingleProcessStorage::instance();
		return instance.get(first_currency, second_currency);
	}

	const string getExchangePath(const string & first_currency, const string & second_currency) {
		SingleProcessStorage & instance = SingleProcessStorage::instance();
		return instance.path(first_currency, second_currency);
	}

}