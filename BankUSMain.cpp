

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
			"\t1  - to add Money of Currency type USD to the Bank,\n"
			"\t2  - to remove Money of Currency type USD from the Bank,\n"
			"\t3  - to display how much total Money in USD is in the Bank,\n"
			"\t4  - to add a new Patron to the Bank,\n"
			"\t5  - to check whether someone is already a Patron, and displaying their information, \n"
			"\t6  - to display a list of information about all Patron’s,\n"
			"\t7  - to make a deposit in USD by a Patron,\n"
			"\t8  - to make a withdrawal in USD by a Patron,\n"
			"\t9  - to display a list of information about all Patron’s that are overdrawn\n"
			"\t10 - to display a list of Transaction’s done by all Patron’s  \n"
			"\t11 - to quit the program\n";

	int selection = 0;
	while ( ( selection < 1 ) || ( selection > 11 ) ) {
		selection = prompt_for_int( menu );
	}

	cout << endl << endl;

	return selection;

}

void add_money_to_bank( Bank & bank )
{

	double amount = prompt_for_double("How much money would you like to add? (in USD): ");
	bank.add_money( amount );

}

void remove_money_from_bank( Bank & bank )
{
	double amount = prompt_for_double("How much money would you like to add? (in USD): ");
	bank.remove_money( amount );
}

void display_total_money( Bank & bank )
{
	cout << "The bank contains " << bank.total_money() << " dollars";
}

void add_new_patron( Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	int num = bank.patron_count();

	Patron patron( name, num, 0);

	cout << "Patron added as account number " << num;

	bank.add_patron( patron );

}

void check_is_patron( Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;
	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		cout << "Patron name: "<< patron.get_name() << endl << "Patron Number: " << patron.get_account_number() << endl << "patron balance: " << patron.get_balance() << endl << endl;
	} else {
		cout << name << " is not a patron here";
	}
}

void display_patron_information( Bank & bank )
{
	
	bank.display_patrons();
	
}

void make_deposit( Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	if(bank.is_patron(name)){
		Patron patron = bank.get_patron( name );
		double amount = prompt_for_double( "How much money should be deposited?" );
		bank.deposit( patron, amount );
	}
	else {
		cout << name << " is not a patron here";
	}
}

void make_withdraw( Bank & bank )
{
	cout << "Enter patron name (no spaces): ";
	string name;
	cin >> name;

	if(bank.is_patron(name)) {
		Patron patron = bank.get_patron( name );
		double amount = prompt_for_double( "How much money should be withdrawn?" );
		bank.withdraw( patron, amount );
	}
	else {
		cout << name << " is not a patron here";
	}

}

void display_overdrawn_patrons( Bank & bank )
{
	bank.display_overdrawn();
}

void display_transactions( Bank & bank )
{
	bank.display_transactions();
}

void quit( Bank & bank ) {
	bank.Save_to("TODO");
}

int main ( ) {

	Bank bank;

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
				cout << "Invalid menu item!" << endl;

		}

	}

}



