

#include "std_lib_facilities_4.h"
#include "Banking.h"
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

using namespace Banking;
using namespace Graph_lib; // uncertain

void prompt_for_file ( International_Bank & bank, string bank_country )
// Description: Loads bank from file if prompted
// Precondition: cin is empty, 
// Postcondition: The Bank in country X may be loaded with file
{

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

void quit( Bank & bank ) {
	
	string save = "";
	while ( (save!="yes")&&(save!="no")){
		cout << "Save to a file? Input 'yes' or 'no': ";
		cin >> save;
	}

	if (save == "yes") {
		string save_file = "";
		cout << "Name of save file (no spaces): ";
		cin >> save_file;
		bank.Save_to( save_file );
	}

}

struct Bank_window : Graph_lib::Window {       // inherits from Window

  // constructor
	Bank_window(
		International_Bank bank,	// Each Bank_window requires a bank to execute functions on
		Point xy,            		// top lefthand corner
		int w,               		// width
		int h,               		// height
		const string& title);		// label

private:
	// data members
	International_Bank bank;                // shape to hold the DLL points

	// widgets:
	Menu main_menu;
	Button menu_button;

	// Widgets for add money (enclosed in {})
		{
			Text add_title;
			In_box add_amount;
			In_box add_currency;
			Button add_money;
		}
	// Remove money
		{
			Text remove_title;
			In_box remove_amount;
			In_box remove_currency;
			Button remove_money;
		}
	// Display money
		{
			Out_box display_usd;
			Out_box display_gbp;
			Out_box display_eur;
			Out_box display_jpy;
			Out_box display_rub;
		}
	// Add patron
		{
			In_box add_patron_name;
			Button add_patron;
		}
	// 


	// function members



// actions invoked by callbacks:


void quit();   // defined below

// callback functions; declared here and defined below.

static void cb_red(Address, Address);
static void cb_blue(Address, Address);
static void cb_black(Address, Address);
static void cb_menu(Address, Address);
static void cb_next(Address, Address);
static void cb_quit(Address, Address);
};

// constructor:

Bank_window::Bank_window(International_Bank bank, Point xy, int w, int h, const string& title) : 

	// initialization - start by calling constructor of base class 
	Window(xy,w,h,title),

	// initialize widgets (buttons, I/O boxes, and menus)
	// Add money (enclosed in {})
		{
			add_amount(
				Point(100,50),
				50, 20,
				"Amount:"),
			add_currency(
				Point(100,80),
				50, 20,
				"Currency:"),
			add_money(
				Point(100,110),
				70, 20,
				"Add",
				cb_add_money),
		}
	// Remove money
		{
			remove_amount(
				Point(100,50),
				50, 20,
				"Amount:"),
			remove_currency(
				Point(100,80),
				50, 20,
				"Currency:"),
			remove_money(
				Point(100,110),
				70, 20,
				"Remove",
				cb_remove_money),
		}
	// Display money
		{
			display_usd(
				Point(100,50),
				50, 20,
				"USD:"),
			display_gbp(
				Point(100,80),
				50, 20,
				"GBP:"),
			display_eur(
				Point(100,110),
				50, 20,
				"EUR:"),
			display_jpy(
				Point(100,140),
				50, 20,
				"JPY:"),
			display_rub(
				Point(100,170),
				50, 20,
				"RUB:"),
		}
	// Add patron
		{
			add_patron_name(
				Point(100,50),
				50, 20,
				"Name:"),
			add_patron(
				Point(100,80),
				70, 20,
				"Add",
				cb_add_patron),
		}
	// 



	// body of constructor follows
{

	// attach buttons and boxes to window




}

// ---------------------------- 
// callback function for quit button - boilerplate: 
// When the button is pressed, the system invokes the
// specified callback function.  First argument is address of the
// button (which we won't use, so we don't bother to name it).  Second
// argument, named pw, is address of the window containing the pressed
// button, i.e., address of our Bank_window object.  reference_to
// converts the address pw into a reference to a Bank_window object,
// so we can call the quit() function.  Objective is to call function
// quit() which does the real work specific to this button.

void Bank_window::cb_quit(Address, Address pw) {
	reference_to<Bank_window>(pw).quit();   // quit is defined next
}

//------------------------------------
// what to do when quit button is pressed

void Bank_window::quit() {
	hide();                   // FLTK idiom for delete window
	quit(bank);		// Uncertain
}

// -------------------------------
// callback for when red button (part of color menu) is pressed - boilerplate

void Bank_window::cb_red(Address, Address pw) {
  reference_to<Bank_window>(pw).red_pressed();  
  // red_pressed defined in Bank_window class as part of declaration
}

// -------------------------------
// callback for when blue button (part of color menu) is pressed - boilerplate

void Bank_window::cb_blue(Address, Address pw) {
  reference_to<Bank_window>(pw).blue_pressed();  
  // blue_pressed defined in Bank_window class as part of declaration
}

// -------------------------------
// callback for when black button (part of color menu) is pressed - boilerplate

void Bank_window::cb_black(Address, Address pw) {
  reference_to<Bank_window>(pw).black_pressed();  
  // black_pressed defined in Bank_window class as part of declaration
}

// -------------------------------
// callback for when menu button is pressed - boilerplate

void Bank_window::cb_menu(Address, Address pw)
{  
    reference_to<Bank_window>(pw).menu_pressed();
    // menu_pressed defined in Bank_window class as part of declaration
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

	// Construct a Bank_window for each Bank
	Bank_window win(US,Point(100,100),960,720,"Bank 1 (US)");
	Bank_window win(GB,Point(100,100),960,720,"Bank 2 (Great Britain)");
	Bank_window win(DE,Point(100,100),960,720,"Bank 3 (Germany)");
	Bank_window win(JP,Point(100,100),960,720,"Bank 4 (Japan)");
	Bank_window win(RU,Point(100,100),960,720,"Bank 5 (Russia)");

	// Bank_window's

	// 

	// No longer necessary, for reference when coding the Bank_window class
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



