

#include "std_lib_facilities_4.h"
#include "Banking.h"
#include "Chrono.h"

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


int prompt_menu ( ) {

	menu =  " What would you like to do? Plese enter:" 
			"1  - to add Money to the Bank,\n"
			"2  - to remove Money from the Bank,\n"
			"3  - to display how much total Money is in the Bank,\n"
			"4  - to add a new Patron to the Bank,\n"
			"5  - to check whether someone is already a Patron, and displaying their information, \n"
			"6  - to display a list of information about all Patron’s,\n"
			"7  - to make a deposit in USD by a Patron,\n"
			"8  - to make a withdrawal in USD by a Patron,\n"
			"9  - to display a list of information about all Patron’s that are overdrawn\n"
			"10 - to display a list of Transaction’s done by all Patron’s  \n"
			"11 - to quit the program\n";

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
		return prompt_for_currency();
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

}

void check_is_patron( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;
	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		cout << "Patron name: "<< patron.get_name() << endl << "Patron Number: " patron.get_account_number() << endl << "patron balance: " << patron.get_balance() << endl;
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

	double amount = prompt_for_double( "How much money should be deposited?" );

	bank.deposit( patron, amount );
}

void make_withdraw( International_Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	double amount = prompt_for_double( "How much money should be withdrawn?" );

	bank.deposit( patron, amount );
}

void display_overdrawn_patrons( International_Bank & bank )
{
	bank.display_overdrawn();
}

void display_transactions( International_Bank & bank )
{
	bank.display_transactions();
}

int main ( ) {

	International_Bank bank;

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
				break;

			default: 
				cout << "Invlid menu item!" << endl;

		}

	}

}



