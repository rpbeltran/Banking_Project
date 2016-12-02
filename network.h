
#include "Banking.h"

using namespace Banking;
using namespace Graph_lib;

struct Bank_Network {

	vector<Bank> banks;

	void add ( Bank bank) {

		banks.push_back( bank );
	}

};

