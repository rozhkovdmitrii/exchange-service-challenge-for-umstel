#pragma once

#include <string>

namespace umstel {

	using namespace std;

	void setExchangeRate(const string & first_currency, const string & second_currency, const double exchange_rate);
	const double getExchangeRate(const string & first_currency, const string & second_currency);

	pair<double, short> _getExchangeRate(const string & first_currency, const string & second_currency);
	const string getExchangePath(const string & first_currency, const string & second_currency);

}