

#include "std_lib_facilities_4.h"
#include "Bank_Window.h"


using namespace Banking;
using namespace Graph_lib; // uncertain

void prompt_for_file ( International_Bank & bank, string bank_country )
// Description: Loads bank from file if prompted
// Precondition: cin is empty, 
// Postcondition: The Bank in country X may be loaded with file
{
	string load = "";
	while ( (load!="yes") && (load!="no") ) {
		string load = "";
		cout << "/n Would you like to load the data for the Bank in " << bank_country << " from a file? Input 'yes' or 'no': ";
		cin >> load;
	}

	if (load == "yes") {
		string save_file = "";
		cout << "Name of save file (no spaces): ";
		cin >> save_file;
		bank = International_Bank( save_file );
	}

}





int main ( ) {

	// Construct 5 Bank's in 5 countries
	International_Bank US ( Currency( "USD", 1.0) );
	International_Bank GB ( Currency( "GBP", 0.76) );
	International_Bank DE ( Currency( "EUR", 0.89) );
	International_Bank JP ( Currency( "JPY", 102.09) );
	International_Bank RU ( Currency( "RUB", 65.97) );

	// Queries user to load bank data from a file
	prompt_for_file(US,"the US");
	prompt_for_file(GB,"Great Britain");
	prompt_for_file(DE,"Germany");
	prompt_for_file(JP,"Japan");
	prompt_for_file(RU,"Russia");

	// Create a bank network
	Bank_Network network;
	network.add( US );
	network.add( GB );
	network.add( DE );
	network.add( JP );
	network.add( RU );

	// Construct a Bank_window for each Bank
	Bank_Window win_us ( network, US, "Bank of the US");
	Bank_Window win_gb ( network, GB, "Bank of Great Britain");
	Bank_Window win_de ( network, DE, "Bank of Germany");
	Bank_Window win_jp ( network, JP, "Bank of Japan");
	Bank_Window win_ru ( network, RU, "Bank of Russia");

}



