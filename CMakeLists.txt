cmake_minimum_required(VERSION 3.9)

project(exchange-service)

include_directories(include)

add_library(exchange-service CurrencyNode.cpp RateLeaf.cpp RateReverse.cpp RateComposite.cpp SingleProcessStorage.cpp  ExchangeService.cpp)



