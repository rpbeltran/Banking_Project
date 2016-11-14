
#include "std_lib_facilities_4.h"
#include "Banking.h";
#include "Chrono.h"

using namespace Banking;


// -------------------------------------------------------------------------------------------------------------

// Currency struct


Currency::Currency( String t, Double er ) : type( name ), exchange_rate( er ) { }




// -------------------------------------------------------------------------------------------------------------

// Money class


Money::Money ( Currency c, Double a) : currency( c ), amount( a ) { }
Money::Money ( Currency c ) : Money ( c, 0.0 ) { }

Currency Money::get_currency( ) const {
	return currency;
}

double   Money::get_amount( ) const {
	return amount;
}

void Money::set_amount( Double new_amount ) {
	amount = new_amount;
}




// -------------------------------------------------------------------------------------------------------------

// Patron class


Patron ( String nam, int acct_num, double bal) : name(nam), account_number( acct_num ), balance( bal ) { }

String Patron::get_name( ) const {

	return name;

}

int Patron::get_account_number( ) const {
	
	return account_number;

}

double Patron::get_balance( ) const {

	return balance;

}

void Patron::set_balance( double new_balance ) {

	balance = new_balance;

}

ostream& operator<<(ostream& os, const Patron & patron)
// Patron Output stream overload
// Output format:
//(name,account_number,balance) 
{
	return os << '(' << patron.get_name( ) << ',' << patron.get_account_number( ) << ',' << patron.get_balance( ) << ')';
}

istream& operator>>(istream& is, Patron & patron)
// Patron input stream overload
// Input format:
//(name,account_number,balance)
{
    string name;
    int account_number;
    double balance;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
        is.clear(ios_base::failbit);                    // set the fail bit
        return is;
    }
    patron = Patron(name,account_number,balance);     // update patron
    return is;
}




// -------------------------------------------------------------------------------------------------------------

// Transaction class


Transaction::Transaction( String patron, int account, double balance, Type trans_type, double amnt, Chrono::Date trans_date, Chrono::Time trans_time ) {

	patron_name = patron;
	patron_account = account;
	new_balance = balance;
	type = trans_type;
	amount = amnt;
	date = trans_date;
	time = trans_time;

}

ostream& operator<<(ostream& os, const Transaction & transaction)
// Transaction Output stream overload
// Output format:
//( patron_name, patron_account, type, amount, date, time ) 
{
	type = "deposit";
	if ( transaction.type == 1 ){
		type = "withdraw";
	}

	return os << '(' << transaction.patron_name <<
		',' << transaction.patron_account <<
		',' << transaction.amount <<
		',' << type <<
		',' << transaction.date <<
		',' << transaction.time << ')';
}

istream& operator>>(istream& is, Transaction & transaction)
// Transaction input stream overload
// Input format:
//( patron_name, patron_account, type, amount, date, time ) 
{
	string patron_name;
    int patron_account;
    double new_balance;
	Transaction::Type type = Transaction::Type(1);
	string type_string;
	double amount;
	Chrono::Date date;
	Chrono::Time time;
    char ch1, ch2, ch3, ch4, ch5, ch6, ch7;
    is >> ch1 >> patron_name >> ch2 >> patron_account >> ch3 >> type_string >> ch4 >> amount >> ch5 >> date >> ch6 >> time >> ch7;
	if (type_string == "deposit") { type = Transaction::Type(2); }
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=',' || ch5!=',' || ch6!=',' || ch7!=')') { // oops: format error
        is.clear(ios_base::failbit);                    // set the fail bit
        return is;
    }
    transaction = Patron(patron_name,patron_account,new_balance,type,amount,date,time);     // update patron
    return is;
}




// -------------------------------------------------------------------------------------------------------------

// Bank Class

Bank::Bank( ) { }

Bank::Bank( String filename ) 
// Description: Bank Constructor loads patron and transaction data from a text file
// Pre-condition: String filename is the filename for the data file to load in
// Input File Format:
//		patron1
//		patron2
//		...
//		
//		transaction1
//		transaction2
//		..
//		<end-of-file>
// Post-condition: Bank is initialized with entries read into patrons, and transations vectors
// Error-handling: throws exceptions for:
//	file not found
//	file not formatted properly
{

	// Phase 2

}

void Bank::Save_to( String filename ) const 
// Description: saves bank data to a text file
// Precondition: String filename points is the name of the file to be created
// Post-condition: patrons and transactions are 
{

	// Phase 2

}

bool Bank::is_patron ( String name ) const 
// Description: Check if a name belongs to a patron
// Pre-condition: String name is the name of the patron we are looking for
// Post-condition: Returns true if a patron of the specified name is in patrons, otherwise false
{
	for (int i = 0; i < patrons.size(); ++i) {
		if (name == patrons[i].get_name()) { return 1; }
	}
	return 0;
}

Patron Bank::get_patron ( String name ) const
// Description: Get patron by name
// Pre-condition: String name is the name of a patron
// Post-condition: returns the Patron object from patrons whose 
// Post-Condition: If no patron with that name is found, return null
{
	for (int i = 0; i < patrons.size(); ++i) {
		if (name == patrons[i].get_name()) { 
			return patrons[i]; 
		}
	}
	if (!is_patron(name)) { error("lol no patron named that XD"); }
}

void Bank::add_patron ( Patron patron )
// Description: Add a new patron to patrons
// Pre-condition: Patron patron is a patron object not already in patrons
// Post-condition: patron is added to the end of patrons. Nothing is returned
{

	if (!is_patron(patron.get_name())) { patrons.push_back(patron); }

}

void Bank::display_patrons ( ) 
// Description: Display all patrons data
// Note: Use overloaded output stream operators
// Note: Because this is so similar to save_to, we can overload output for Bank if we want
{

	cout << "all patrons data";

}

void Bank::withdraw ( Patron & patron, double amount )
// Description: Withdraw an amount of money from a patrons account, record the transaction, remove the money from the bank
// Precondition: patron is a reference to a patron in patrons, amount is a positive double
// Post-condition: patron.amount is modified, a new entry is added to transactions, remove_money is called
// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
{

	// todo

}

void Bank::deposit ( Patron patron, double amount)
// Description: Deposit an amount of money from a patrons account, record the transaction, add the money to the bank
// Precondition: patron is a reference to a patron in patrons, amount is a positive double
// Post-condition: patron.amount is modified, a new entry is added to transactions, add_money is called
// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
{

	// todo

}

double Bank::total_money( ) const 
// Description: Get total money in USD
// Note: US bank only has one Money object to consider
{
	// todo
}

void Bank::add_money( double amount )
// Description: Add money to bank
// Precondition: amount is a positive double
// Post-condition: money.amount is updated
{

	// todo

}

void Bank::remove_money( double amount )
// Desscription: Subtract money from bank
// Precondition: amount is a positive double
// Post-condition: money.amount is updated
{

	// todo

}




// -------------------------------------------------------------------------------------------------------------

// International Bank Class


Currency International_Bank::currency ( String currency_name ) 
// Description: Get Currency data object from currency name
{

	switch ( currency_name ) {

		case "USD" : return Currency( "USD", 1.0 );
		case "GBP" : return Currency( "GBP", .76 );
		case "EUR" : return Currency( "EUR", .89 );
		case "JPY" : return Currency( "JPY", 102.09 ); 
		case "RUB" : return Currency( "RUB", 65.97 );

	}	
	
	error( "Error: Unknown currency!" );

}


International_Bank::International_Bank ( Currency currency) : default_currency(currency) { }


International_Bank::International_Bank ( String filename ) 
// Description: International_Bank Constructor loads default currency, patron, and transaction data from a text file
// Pre-condition: String filename is the filename for the data file to load in
// Input File Format:
//		currency_name
//
//		patron1
//		patron2
//		...
//		
//		transaction1
//		transaction2
//		..
//		<end-of-file>
// Post-condition: Bank is initialized with entries read into default_currency, patrons, and transactions vectors
// Error-handling: throws exceptions for:
//	file not found
//	file not formatted properly
{

	// Phase 2

}


void International_Bank::withdraw ( Patron patron, Currency currency, double amount )
// Description: Withdraw an amount of money of a specific currency from a patrons account, record the transaction, remove the money from the bank
// Precondition: patron is a reference to a patron in patrons, currency is the type of currency withrawn, amount is a positive double
// Post-condition: patron.amount is modified, a new entry is added to transactions, remove_money is called
// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
{

	// todo

}


void International_Bank::deposit ( Patron patron, Currency currency, double amount )
// Description: Deposit an amount of money from a patrons account, record the transaction, add the money to the bank
// Precondition: patron is a reference to a patron in patrons, amount is a positive double
// Post-condition: patron.amount is modified, a new entry is added to transactions, add_money is called
// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
{

	// todo

}


double International_Bank::total_money( ) const 
// Description: Get total money in default_currency
// Note: iterate through moneys, and convert to default currency rates
{

	// todo

}


void International_Bank::add_money( Currency currency, double amount)
// Description: Add money to bank
// Pre-Condition: currency is one of the acceptable currencies, amount is a positive double
// Post-condition: amount is added to proper entry in moneys, or entry is created if necessary
{

	// todo

}


void International_Bank::remove_money( Currency currency, double amount) 
// Desscription: Subtract money of a specific currency from bank
// Pre-Condition: currency is one of the acceptable currencies, amount is a positive double
// Post-condtion: amount is subtracted from proper entry in moneys
{

	// todo

}












