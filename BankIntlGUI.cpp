

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
	Button next_button;                // button indicating next DLL point is ready
	Button quit_button;                // end program
	In_box next_x;                     // box for entering x coord of point to add
	In_box next_y;                     // box for entering y coord of point to add
	Out_box xy_out;                    // box for displaying last points added
	In_box next_xx;                    // box for entering x coord of point to remove
	In_box next_yx;                    // box for entering y coord of point to remove
	Out_box xyx_out;                   // box for displaying last points removed
	Menu color_menu;                   // menu of color choices for the DLL
	Button menu_button;                // button to display the color menu

	// function members

void change(Color c) {             // change the color of the DLL
	dll.set_color(c);
}

void hide_menu() {     
    // hides the color menu and shows the button to display the color menu
    color_menu.hide(); 
    menu_button.show(); 
}

// actions invoked by callbacks:

void red_pressed() {
    change(Color::red);
    hide_menu();        // once a color is chosen from the menu, hide the menu
  }

void blue_pressed() {
    change(Color::blue);
    hide_menu();
}

void black_pressed() {
    change(Color::black);
    hide_menu();
}

void menu_pressed() {
    // when menu button is pressed, hide the menu button and show the 
    // actual menu of colors
    menu_button.hide();    
    color_menu.show();
}

void next();   // defined below

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

	// initialize "Next curve" button
	next_button(
			Point(x_max()-150,0),   // location of button
			70, 20,                 // dimensions of button
			"Next curve",           // label of button
			cb_next),               // callback function for button
	// initialize quit button
	quit_button(
			Point(x_max()-70,0),    // location of button
			70, 20,                 // dimensions of button 
			"Quit",                 // label of button
			cb_quit),               // callback function for button
	// initialize the next_x inbox
	next_x(
		Point(x_max()-330,0),       // location of box
		50, 20,                     // dimensions of box
		"coord x:"),                // label of box 
	// initialize the next_y inbox
	next_y(
		Point(x_max()-210,0),       // location of box
		50, 20,                     // dimensions of box
		"coord y:"),                // label of box
	// initialize the outbox
	xy_out(
		Point(100,0),               // location of box
		100, 20,                    // dimensions of box
		"coord (x,y):"),            // label of box
	// initialize the scalar_x inbox
	next_xx(
		Point(x_max()-330,30),      // location of box
		50, 20,                     // dimensions of box
		"remove x:"),               // label of box 
	// initialize the scalar_y inbox
	next_yx(
		Point(x_max()-210,30),      // location of box
		50, 20,                     // dimensions of box
		"remove y:"),               // label of box
	// initialize the outbox
	xyx_out(
		Point(100,30),              // location of box
		100, 20,                    // dimensions of box
		"remove (x,y):"),           // label of box
	// initialize the color menu
	color_menu(                        
			Point(x_max()-70,30),   // location of menu
			70, 20,                 // dimensions of menu
			Menu::vertical,         // list menu items vertically
			"color"),               // label of menu 
	// initialize the menu button
	menu_button(
			Point(x_max()-80,30),  // location of menu button
			80, 20,                // dimensions of button 
			"color menu",          // label of button
			cb_menu)               // callback for button

  // body of constructor follows
{

	// attach buttons and boxes to window
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no coord");        // output to out box
	attach(next_xx);
	attach(next_yx);
	attach(xyx_out);
	xyx_out.put("no coord");       // output to out box

	dll.last_removed_point = Point(next_xx.get_int(),next_yx.get_int());

	// First make 3 buttons for color menu, one for each color, and 
	// attach them to the menu: the attach function of the Menu struct
	// adjusts the size and location of the buttons; note callback functions).
	// Then attach menu to window but hide it (initially, the menu button
	// is displayed, not the actual menu of color choices).

	color_menu.attach(new Button(Point(0,0),0,0,"red",cb_red)); 
	color_menu.attach(new Button(Point(0,0),0,0,"blue",cb_blue));
	color_menu.attach(new Button(Point(0,0),0,0,"black",cb_black));
	attach(color_menu);
	color_menu.hide(); 

	// attach menu button
	attach(menu_button);

	// attach shape that holds the DLL to be displayed
	attach(dll);
}

// Define window class' functions here.



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



