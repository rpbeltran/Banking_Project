
// Banking Header File

//
// Contains Definitions For:
//
//    Banking::Currency
//    Banking::Money
//    Banking::Patron
//    Banking::Transaction
//    Banking::Bank
//

#include "std_lib_facilities_4.h"
#include "Chrono.h"

namespace Banking {

	//
	// Currency struct
	// Holds information about a particular currency type 
	//
	// Data Stored:
	//		Type of currency
	//		Exchange rate to USD ( amount per 1 USD )
	//	

	struct Currency {

		string type;

		double exchange_rate;

		Currency ( String, Double );

	};

	// -------------------------------------------------------------------------------------------------------------

	//
	// Money class 
	// Holds information about the money objects in the Bank ( amount and type )
	//
	// Data Stored:
	//		Type of currency
	//		Amount of currency
	//
	
	class Money {

		Currency currency;

		Double amount;

	public:

		Money ( Currency, Double );
		Money ( Currency );

		Currency get_currency( ) const;
		double   get_amount() const;

		void set_amount( Double );

	};

	// -------------------------------------------------------------------------------------------------------------


	//
	// Patron Class
	// Holds information about the customers in the Bank 
	//
	// Data Stored:
	//		name
	//		account number
	//		account balance (in USD’s)
	// 
	// Note: To avoid difficulties with reading into a string variable, use the underscores ( _ ) in place of spaces for Patron names.
	//

	class Patron {

		String name;

		int account_number;

		double balance;

	public:

		Patron ( String, int, double );

		String get_name( ) const;
		int    get_account_number( ) const;
		double get_balance( ) const;

		void set_balance( double );

	};

	ostream& operator<<(ostream& os, const Patron & patron)
	istream& operator>>(istream& is, Patron & patron)



	// -------------------------------------------------------------------------------------------------------------

	//
	// Transaction Struct
	// Holds information about customer deposits and withdrawals in the Bank 
	//
	// Data Stored:
	//		patron name, account number, and resulting account balance
	//		transaction type (withdraw or deposit) and amount
	//		Chrono::Date transaction Date, Chrono::Time transaction time 
	//

	struct Transaction {

		enum Type {
			withdraw = 1, deposit
    	};

		// Patron Data
		String patron_name;
		int patron_account;
		double new_balance;

		// Transaction Data
		Type type;
		double amount;
		Chrono::Date date;
		Chrono::Time time;

		// Constructor
		Transaction( String, int, double, Type, double, Chrono::Date, Chrono::Time );
	
	};

	ostream& operator<<(ostream& os, const Transaction & transaction)
	istream& operator>>(istream& is, Transaction & transaction)
	



	// -------------------------------------------------------------------------------------------------------------


	//
	// Bank Class
	//

	class Bank {

		vector<Patron> patrons;

		vector<Transaction> transactions;

		Money money;

	public:

		Bank( );
		Bank( String ); // Load state from a text file

		void Save_to( String ) const; // Dump State into a textfile

		bool    is_patron ( String ) const; // Check if a name belongs to a patron
		Patron get_patron ( String ) const; // Get patron by name
		void   add_patron ( Patron ); // Add a new patron

		void display_patrons ( ); // Display all patrons data
		void display_overdrawn(); // Displays overdrawn patrons
		void display_transactions();

		void withdraw ( Patron & p, double );
		void deposit  ( Patron & p, double );

		double total_money( ) const; // Get total money in USD
		void add_money( double ); // Add money in USD
		void remove_money( double );

		int patron_count() { return patrons.size(); }

	};

	// -------------------------------------------------------------------------------------------------------------


	//
	// International Bank Class
	//

	class International_Bank : Bank {
		
		Currency default_currency;

		vector<Money> monies;

	public:

		International_Bank ( Currency );
		International_Bank ( Currency, String );

		Currency currency( string ); // return currency object from it's name

		void withdraw ( Patron, Currency, double );
		void deposit ( Patron, Currency, double );

		void display_total_money(); ///

		double total_money( ) const; // Get total money in default_currency
		void add_money( Currency, double );
		void remove_money( Currency, double );

	};



}
