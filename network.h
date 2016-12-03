
#include "Banking.h"

using namespace Banking;
using namespace Graph_lib;

struct Bank_Network {

	vector<International_Bank> banks;

	void add ( International_Bank bank) {

		banks.push_back( bank );
	}

};
