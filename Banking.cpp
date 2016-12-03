

#include "Banking.h"

namespace Banking {


	// -------------------------------------------------------------------------------------------------------------

	// Currency struct

	Currency::Currency( string t, double er ) : type( t ), exchange_rate( er ) { }


	// -------------------------------------------------------------------------------------------------------------

	// Money class

	Money::Money ( ) : currency( Currency("USD", 1.0) ), amount ( 0.0 ) { }
	Money::Money ( Currency c, double a) : currency( c ), amount( a ) { }
	Money::Money ( Currency c ) : currency( c ), amount ( 0.0 ) { }

	Currency Money::get_currency( ) const {
		return currency;
	}

	double   Money::get_amount( ) const {
		return amount;
	}

	void Money::set_amount( double new_amount ) {
		amount = new_amount;
	}

	ostream& operator<<(ostream& os, const Money & money)
	// Money Output stream overload
	// Output format:
	//(name,account_number,balance)
	{
		return os << '(' << money.get_currency( ).type << ',' << money.get_currency( ).exchange_rate  << ',' << money.get_amount( ) << ')';
	}

	istream& operator>>(istream& is, Money & money)
	// Money input stream overload
	// Input format:
	//(name,account_number,balance)
	{

	    string type;
	    char t1, t2, t3;
	    double er;
	    double amount;
	    char ch1, ch2, ch3, ch4;
	    is >> ch1 >> t1 >> t2 >> t3 >> ch2 >> er >> ch3 >> amount >> ch4;

	    stringstream t_build;
	    t_build << t1 <<t2 <<t3;
	    t_build >> type;

	    if (!is) return is;
	    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
	        is.clear(ios_base::failbit);                    // set the fail bit
	        return is;
	    }
	    money = Money( Currency( type, er), amount );// update money
	    return is;
	}


	// -------------------------------------------------------------------------------------------------------------

	// Patron class


	Patron::Patron ( string nam, int acct_num, double bal) : name(nam), account_number( acct_num ), balance( bal ) { }

	string Patron::get_name( ) const {

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
	    char ch1, ch3, ch4;

	    is >> ch1;

	    stringstream name_ss;
	    char name_ch;

	    while ( is >> name_ch ) {

	    	if ( name_ch == ',' )
	    		break;

	    	name_ss << name_ch;

	    }
	    name_ss >> name;

	    is >> account_number;
	    is >> ch3;

	    is >> balance;
	    is >> ch4;

	    patron = Patron(name,account_number,balance);     // update patron
	    return is;

	}




	// -------------------------------------------------------------------------------------------------------------

	// Transaction class


	Transaction::Transaction( string patron, int account, double balance, Transaction::Type trans_type, double amnt, Chrono::Date trans_date, Chrono::Time trans_time ) {

		patron_name = patron;
		patron_account = account;
		new_balance = balance;
		type = trans_type;
		amount = amnt;
		date = trans_date;
		time = trans_time;

	}

	ostream & operator<<(ostream& os, const Transaction & transaction)
	// Transaction Output stream overload
	// Output format:
	//( patron_name, patron_account, type, amount, date, time )
	{
		string type = "deposit";
		if ( transaction.type == Transaction::Type(1) ){
			type = "withdraw";
		}

		return os << '(' << transaction.patron_name <<
			',' << transaction.patron_account <<
			',' << transaction.amount <<
			',' << type <<
			',' << transaction.date <<
			',' << transaction.time << ')';
	}

	istream & operator>>(istream& is, Transaction & transaction)
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

		//(
		is >> ch1;

		// account_name
		stringstream name_ss;
	    char name_ch;
	    while ( is >> name_ch ) {
	    	if ( name_ch == ',' )
	    		break;
	    	name_ss << name_ch;
	    }
	    name_ss >> patron_name;

	    //,

	    //patron_account
	    is >> patron_account;

	    //,
	    is >> ch3;

	    //amount
	    is >> amount;

	    //,
	    is >> ch5;

	    //type
	    stringstream type_ss;
	    char type_ch;
	    while ( is >> type_ch ) {
	    	if ( type_ch == ',' )
	    		break;
	    	type_ss << type_ch;
	    }
	    type_ss >> type_string;
	    if (type_string == "deposit") {
	    	type = Transaction::Type(2);
	    }

	    //,



	    //date
	    is >> date;

	    //,
	    is >> ch6;

	    //time
	    is >> time;

	    //)
	    is >> ch7;

	    transaction = Transaction( patron_name,patron_account,new_balance,type,amount,date,time );     // update transaction
	    return is;






	}




	// -------------------------------------------------------------------------------------------------------------

	// Bank Class

	Bank::Bank( ) {

		money = Money( Currency("USD",1.0) );

	}

	Bank::Bank( string filename )
	// Description: Bank Constructor loads patron and transaction data from a text file
	// Pre-condition: String filename is the filename for the data file to load in
	// Input File Format:
	//		patron1
	//		patron2
	//		...
	//		transaction1
	//		transaction2
	//		<end-of-file>
	// Post-condition: Bank is initialized with entries read into patrons, and transations vectors
	// Error-handling: throws exceptions for:
	//	file not found
	//	file not formatted properly
	{

		ifstream file( filename );

		string m_str;
		stringstream m_ss;
		getline(file, m_str);
		m_ss << m_str;
		m_ss >> money;

		string temp;
		getline(file, temp);

	    string str;
	    stringstream ss;

	    while (getline(file, str))
	    {
	        if ( str == "--")
	        	break;

	        Patron p ("",0,0);
	        ss << str;
	        ss >> p;

	        patrons.push_back( p );

	        ss.str("");

	    }

	    while (getline(file, str))
	    {
	        Transaction t ( "",0,0, Transaction::Type(1),0,Chrono::Date(),Chrono::Time() );
	        ss << str;
	        ss >> t;

	        transactions.push_back( t );
	        ss.str("");
	    }

	    file.close();

	}

	void Bank::Save_to( string filename )
	// Description: saves bank data to a text file
	// Precondition: String filename points is the name of the file to be created
	// Post-condition: patrons and transactions are
	{
		ofstream file ( filename );

		file << money << endl;
		file << "--" << endl;
		for ( Patron & p : patrons)
			file << p << endl;
		file << "--" << endl;
		for ( Transaction & t : transactions )
			file << t << endl;

		file.close();

	}

	bool Bank::is_patron ( string name ) const
	// Description: Check if a name belongs to a patron
	// Pre-condition: String name is the name of the patron we are looking for
	// Post-condition: Returns true if a patron of the specified name is in patrons, otherwise false
	{
		for (int i = 0; i < patrons.size(); ++i) {
			if (name == patrons[i].get_name()) { return 1; }
		}
		return 0;
	}

	Patron & Bank::get_patron ( string name )
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

	void Bank::set_patron_balance ( Patron & patron, double balance )
	{
		for (int i = 0; i < patrons.size(); ++i) {
			if (patron.get_account_number() == patrons[i].get_account_number()) {
				patrons[i].set_balance( balance );
				break;
			}
		}
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

		if ( patrons.size() == 0 ) {
			cout << "Bank currently has no patrons." << endl << endl;
		}

		for (int i = 0; i < patrons.size(); ++i) {
			cout << "Patron name: "<< patrons[i].get_name() << endl << "Patron Number: " << patrons[i].get_account_number() << endl << "patron balance: " << patrons[i].get_balance() << endl << endl;
		}

	}

	void Bank::display_overdrawn ( )
	// Description: Displays overdrawn patrons
	{
		bool hasOverdrawn = false;

		for (int i = 0; i < patrons.size(); ++i) {
			if (patrons[i].get_balance() < 0){
				cout << "Patron name: "<< patrons[i].get_name() << endl << "Patron Number: " << patrons[i].get_account_number() << endl << "patron balance: " << patrons[i].get_balance() << endl << endl;
				hasOverdrawn = true;
			}
		}

		if (hasOverdrawn == false) {
			cout << "Bank currently has no overdrawn patrons." << endl << endl;
		}

	}

	void Bank::display_transactions ( )
	// Description: Displays transactions
	// Note: Use overloaded output stream operators
	{

		if ( transactions.size() == 0 ) {
			cout << "Bank currently has no transactions on file." << endl << endl;
		}

		for (int i = 0; i < transactions.size(); ++i) {
			cout << transactions[i] << endl;
		}

	}

	void Bank::withdraw ( Patron & patron, double amount )
	// Description: Withdraw an amount of money from a patrons account, record the transaction, remove the money from the bank
	// Precondition: patron is a reference to a patron in patrons, amount is a positive double
	// Post-condition: patron.amount is modified, a new entry is added to transactions, remove_money is called
	// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
	{

		if (amount <= 0){
			error("invalid operation: negative amount");
		}

		if (amount > total_money() ) {
			cout << "Sorry, The bank has insufficient funds for this" << endl << endl;
		}

		else {

			// Changes patron balance
			set_patron_balance(patron, patron.get_balance()-amount);
			// Adds transaction
			Transaction::Type type = Transaction::Type(1);
			transactions.push_back(
				Transaction( patron.get_name(), patron.get_account_number(),  patron.get_balance(), type, amount, Chrono::Date(), Chrono::Time() )
			);
			remove_money(amount);

		}

	}

	void Bank::deposit ( Patron & patron, double amount)
	// Description: Deposit an amount of money from a patrons account, record the transaction, add the money to the bank
	// Precondition: patron is a reference to a patron in patrons, amount is a positive double
	// Post-condition: patron.amount is modified, a new entry is added to transactions, add_money is called
	// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
	{

		if (amount <= 0) error("invalid operation: negative amount");

		// Changes patron balance
		set_patron_balance(patron, patron.get_balance()+amount);
		// Adds transaction
		Transaction::Type type = Transaction::Type(2);
		transactions.push_back(
			Transaction( patron.get_name(), patron.get_account_number(), patron.get_balance() + amount, type, amount, Chrono::Date(), Chrono::Time() )
		);
		add_money(amount);

	}

	double Bank::total_money( ) const
	// Description: Get total money in USD
	// Note: US bank only has one Money object to consider
	{
		return money.get_amount();
	}

	void Bank::add_money( double amount )
	// Description: Add money to bank
	// Precondition: amount is a positive double
	// Post-condition: money.amount is updated
	{

		if (amount <= 0)
			error("invalid operation: negative amount");

		money.set_amount(money.get_amount() + amount);

	}

	void Bank::remove_money( double amount )
	// Description: Subtract money from bank
	// Precondition: amount is a positive double
	// Post-condition: money.amount is updated
	{

		if (amount <= 0)
			error("invalid operation: negative amount");

		if (amount > total_money() ) {
			cout << "Sorry, The bank has insufficient funds for this" <<endl <<endl;
		}
		else {
			money.set_amount(money.get_amount() - amount);
		}

	}




	// -------------------------------------------------------------------------------------------------------------

	// International Bank Class


	Currency Bank::currency ( string currency_name )
	// Description: Get Currency data object from currency name
	{

		if ( currency_name == "USD" ){
			return Currency( "USD", 1.0 );
		}
		else if ( currency_name == "GBP" ){
			return Currency( "GBP", .76 );
		}
		else if ( currency_name == "EUR" ){
			return Currency( "EUR", .89 );
		}
		else if ( currency_name == "JPY" ){
			return Currency( "JPY", 102.09 );
		}
		else if ( currency_name == "RUB" ){
			return Currency( "RUB", 65.97 );
		}

		error( "Error: Unknown currency!" );

	}


	International_Bank::International_Bank ( Currency dc ) : default_currency( dc )
	{
		monies.push_back(  Money( currency("USD"), 20000 * currency("USD").exchange_rate / default_currency.exchange_rate )  );
		monies.push_back(  Money( currency("GBP"), 20000 * currency("GBP").exchange_rate / default_currency.exchange_rate )  );
		monies.push_back(  Money( currency("EUR"), 20000 * currency("EUR").exchange_rate / default_currency.exchange_rate )  );
		monies.push_back(  Money( currency("JPY"), 20000 * currency("JPY").exchange_rate / default_currency.exchange_rate )  );
		monies.push_back(  Money( currency("RUB"), 20000 * currency("RUB").exchange_rate / default_currency.exchange_rate )  );
	}


	International_Bank::International_Bank ( string filename ) : default_currency( currency("USD") )
	// Description: International_Bank Constructor loads default currency, patron, and transaction data from a text file
	// Pre-condition: String filename is the filename for the data file to load in
	// Input File Format:
	//		currency_name
	//		money
	//		money
	//		money
	//		money
	//		money
	//		...
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

		ifstream file( filename );

		string dc_type;
		getline(file, dc_type);
		default_currency = currency( dc_type );

		for (int i = 0; i<5; i++) {
			Money m;
			string m_str;
			stringstream m_ss;
			getline(file, m_str);
			m_ss << m_str;
			m_ss >> m;
			monies.push_back( m );
		}


		string temp;
		getline(file, temp);

	    string str;
	    stringstream ss;

	    while (getline(file, str))
	    {
	        if ( str == "--")
	        	break;

	        Patron p ("",0,0);
	        ss << str;
	        ss >> p;

	        patrons.push_back( p );

	        ss.str("");

	    }

	    while (getline(file, str))
	    {
	        Transaction t ( "",0,0, Transaction::Type(1),0,Chrono::Date(),Chrono::Time() );
	        ss << str;
	        ss >> t;

	        transactions.push_back( t );
	        ss.str("");
	    }

	    file.close();

	}

	void International_Bank::Save_to( string filename )
	// Description: saves bank data to a text file
	// Precondition: String filename points is the name of the file to be created
	// Post-condition: patrons and transactions are
	{
		ofstream file ( filename );

		file << default_currency.type << endl;

		for (Money m : monies)
			file << m << endl;

		file << "--" << endl;

		for ( Patron & p : patrons)
			file << p << endl;

		file << "--" << endl;

		for ( Transaction & t : transactions )
			file << t << endl;

		file.close();
	}


	void International_Bank::withdraw ( Patron patron, Currency currency, double amount )
	// Description: Withdraw an amount of money of a specific currency from a patrons account, record the transaction, remove the money from the bank
	// Precondition: patron is a reference to a patron in patrons, currency is the type of currency withrawn, amount is a positive double
	// Post-condition: patron.amount is modified, a new entry is added to transactions, remove_money is called
	// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
	{

		if (amount <= 0) {
			error("invalid operation: negative amount");
		}

		double current = 0;
		for (int i = 0; i < monies.size(); ++i) {
			if (monies[i].get_currency().type == currency.type) {
				current = monies[i].get_amount();
				break;
			}
		}

		if (amount >  current ) {

			cout << "Sorry, The bank has insufficient funds for this" << endl << endl;

		} else {

			remove_money(currency,amount);
			// convert amount to amount in default currency
			amount = default_currency.exchange_rate * amount / currency.exchange_rate;
			// Changes patron balance in default currency
			set_patron_balance(patron, patron.get_balance()-amount);
			// Adds transaction in default currency
			Transaction::Type type = Transaction::Type(1);
			transactions.push_back(
				Transaction( patron.get_name(), patron.get_account_number(),  patron.get_balance()-amount, type, amount, Chrono::Date(), Chrono::Time() )
			);

		}

	}


	void International_Bank::deposit ( Patron patron, Currency currency, double amount )
	// Description: Deposit an amount of money from a patrons account, record the transaction, add the money to the bank
	// Precondition: patron is a reference to a patron in patrons, amount is a positive double
	// Post-condition: patron.amount is modified, a new entry is added to transactions, add_money is called
	// Error handling: raise an exception if amount is negative, or transaction is impossible (insufficient funds)
	{

		if (amount <= 0)
			error("invalid operation: negative amount");

		add_money(currency,amount);

		// convert amount to amount in default currency
		amount = default_currency.exchange_rate * amount / currency.exchange_rate;

		// Changes patron balance in default currency
		set_patron_balance(patron, patron.get_balance()+amount);

		// Adds transaction in default currency
		Transaction::Type type = Transaction::Type(2);
		transactions.push_back(
			Transaction( patron.get_name(), patron.get_account_number(),  patron.get_balance()-amount, type, amount, Chrono::Date(), Chrono::Time() )
		);

	}


	double International_Bank::total_money( ) const
	// Description: Get total money in default_currency
	// Note: iterate through moneys, and convert to default currency rates
	{

		double total = 0;
		for (int i = 0; i < monies.size(); ++i) {
			total = total + default_currency.exchange_rate * monies[i].get_amount() / monies[i].get_currency().exchange_rate;
		}
		return total;

	}

	void International_Bank::display_total_money( )
	// Description: Get total money in default_currency
	// Note: iterate through moneys, and convert to default currency rates
	{
		for (int i = 0; i < monies.size(); ++i) {
			cout << monies[i].get_currency().type << ": " << monies[i].get_amount() << endl;
		}
		cout << endl;
	}


	void International_Bank::add_money( Currency currency, double amount)
	// Description: Add money to bank
	// Pre-Condition: currency is one of the acceptable currencies, amount is a positive double
	// Post-condition: amount is added to proper entry in moneys, or entry is created if necessary
	{

		for (int i = 0; i < monies.size(); ++i) {
			if (monies[i].get_currency().type == currency.type)
				monies[i].set_amount(monies[i].get_amount()+amount);
		}

	}


	void International_Bank::remove_money( Currency currency, double amount)
	// Desscription: Subtract money of a specific currency from bank
	// Pre-Condition: currency is one of the acceptable currencies, amount is a positive double
	// Post-condtion: amount is subtracted from proper entry in moneys
	{

		for (int i = 0; i < monies.size(); ++i) {
			if (monies[i].get_currency().type == currency.type) {

				if (amount >  monies[i].get_amount() ) {
					cout << "Sorry, The bank has insufficient funds for this" << endl << endl;
					break;
				}
				monies[i].set_amount(monies[i].get_amount()-amount);

			}
		}

	}



}
