

#include "std_lib_facilities_4.h"
#include "Banking.h"

using namespace Banking;


int prompt_for_int ( string message )
// Description: Fetches the next int from cin, ignoring invalid (non-integer) inputs.
// Precondition: cin is empty
// Postcondition: Returns a valid int from user input
{
	cout << message;

	int input;	
	cin >> input;

	while(std::cin.fail()) {
	    std::cin.clear();
	    std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
	    std::cout << "Input invalid! Please keep your inputs numerical.\n" << message;
	    std::cin >> input;
	}

	return input;
}

int prompt_for_double ( string message )
// Description: Fetches the next int from cin, ignoring invalid (non-integer) inputs.
// Precondition: cin is empty
// Postcondition: Returns a valid int from user input
{
	cout << message;

	double input;	
	cin >> input;

	while(std::cin.fail()) {
	    std::cin.clear();
	    std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
	    std::cout << "Input invalid! Please keep your inputs numerical.\n" << message;
	    std::cin >> input;
	}

	return input;

}


int prompt_menu ( ) {

	string menu =  "\nWhat would you like to do? Plese enter:\n" 
			"\t1  - to add Money to the Bank,\n"
			"\t2  - to remove Money from the Bank,\n"
			"\t3  - to display how much total Money is in the Bank,\n"
			"\t4  - to add a new Patron to the Bank,\n"
			"\t5  - to check whether someone is already a Patron, and displaying their information, \n"
			"\t6  - to display a list of information about all Patron’s,\n"
			"\t7  - to make a deposit in by a Patron,\n"
			"\t8  - to make a withdrawal in by a Patron,\n"
			"\t9  - to display a list of information about all Patron’s that are overdrawn\n"
			"\t10 - to display a list of Transaction’s done by all Patron’s  \n"
			"\t11 - to quit the program\n";

	int selection = 0;
	while ( ( selection < 1 ) || ( selection > 11 ) ) {
		selection = prompt_for_int( menu );
	}

	return selection;

}

Currency prompt_for_currency( International_Bank & bank )
{
	string currency_name;
	cout << "Please enter your desired type of currency. Valid entries include: USD GBP EUR JPY RUB. ";
	cin  >> currency_name;

	if ( (currency_name!="USD")&&(currency_name!="GBP")&&(currency_name!="EUR")&&(currency_name!="JPY")&&(currency_name!="RUB") ){
		cout << "Invalid currency!" << endl;
		return prompt_for_currency( bank );
	}

	return bank.currency( currency_name );

}

void add_money_to_bank( International_Bank & bank )
{

	Currency currency = prompt_for_currency( bank );
	double amount = prompt_for_double("How much would you like to add?");
	bank.add_money( currency, amount );

}

void remove_money_from_bank( International_Bank & bank )
{
	Currency currency = prompt_for_currency( bank );
	double amount = prompt_for_double("How much would you like to remove?");
	bank.remove_money( currency, amount );
}

void display_total_money( International_Bank & bank )
{
	bank.display_total_money();
}

void add_new_patron( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	int num = bank.patron_count();

	Patron patron( name, num, 0);

	cout << "Patron added as account number " << num;

	bank.add_patron( patron );

}

void check_is_patron( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;
	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		cout << "Patron name: "<< patron.get_name() << endl << "Patron Number: " << patron.get_account_number() << endl << "patron balance: " << patron.get_balance() << endl;
	} else {
		cout << name << " is not a patron here";
	}
}

void display_patron_information( International_Bank & bank )
{
	
	bank.display_patrons();
	
}

void make_deposit( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		Currency currency = prompt_for_currency( bank );
		double amount = prompt_for_double( "How much money should be deposited?" );
		bank.deposit( patron, currency, amount );
	}
	else {
		cout << name << " is not a patron here";
	}
}

void make_withdraw( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		Currency currency = prompt_for_currency( bank );
		double amount = prompt_for_double( "How much money should be withdrawn?" );
		bank.withdraw( patron, currency, amount );
	}
	else {
		cout << name << " is not a patron here";
	}

}

void display_overdrawn_patrons( International_Bank & bank )
{
	bank.display_overdrawn();
}

void display_transactions( International_Bank & bank )
{
	bank.display_transactions();
}

Currency prompt_country() {

	string menu =  "\nWhat coutry are you in?\n" 
		"\t1  - United States\n"
		"\t2  - Great Britian\n"
		"\t3  - European Economic Community\n"
		"\t4  - Japan\n"
		"\t5  - Russia\n";


	int selection = 0;
	while ( ( selection < 1 ) || ( selection > 5 ) ) {
		selection = prompt_for_int( menu );
	}

	switch( selection ) {

		case 2 : return Currency( "GBP", .76 );

		case 3 : return Currency( "EUR", .89 );

		case 4 : return Currency( "JPY", 102.09 ); 

		case 5 : return Currency( "RUB", 65.97 );

	}

	return Currency( "USD", 1.0 );

}

void quit( Bank & bank ) {
	
	string save = "";
	while ( (save!="yes")&&(save!="no")){
		cout << "save to a file? Input 'yes' or 'no': ";
		cin >> save;
	}

	if (save == "yes") {
		string save_file = "";
		cout << "Name of save file (no spaces): ";
		cin >> save_file;
		bank.Save_to( save_file );
	}

}

int main ( ) {

	International_Bank bank ( Currency( "USD", 1) );

	string load = "";
	while ( (load!="yes")&&(load!="no")) {
		cout << "load from a file? Input 'yes' or 'no': ";
		cin >> load;
	}

	if (load == "yes") {
		string save_file = "";
		cout << "Name of save file (no spaces): ";
		cin >> save_file;
		bank = International_Bank( save_file );
	}

	else {
		Currency dc = prompt_country( );
		bank = International_Bank ( dc );
	}

	int option = 0;
	while ( option != 11 ) {

		option = prompt_menu();

		switch( option ) {
			
			case 1:
				add_money_to_bank( bank );
				break;

			case 2:
				remove_money_from_bank( bank );
				break;

			case 3:
				display_total_money( bank );
				break;

			case 4:
				add_new_patron( bank );
				break;

			case 5:
				check_is_patron( bank );
				break;

			case 6:
				display_patron_information( bank );
				break;

			case 7:
				make_deposit( bank );
				break;

			case 8:
				make_withdraw( bank );
				break;

			case 9:
				display_overdrawn_patrons( bank );
				break;

			case 10:
				display_transactions( bank );
				break;

			case 11: 
				quit( bank );
				break;

			default: 
				cout << "Invlid menu item!" << endl;

		}

	}

}



