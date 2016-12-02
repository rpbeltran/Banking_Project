
#include "Bank_Window.h"


Bank_Window::Bank_Window( Bank_Network & n, International_Bank & b, string bank_name ) :

	bank( b ),
	
	network( n),

	Window( Point(100,100), 600, 500, bank_name ),

	main_menu( Point( x_max()-70, 30 ), 70, 20, Menu::vertical, "Main Menu" )

{

	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Add Money",             cb_add_money            )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Remove Money",          cb_remove_money         )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Display Money",         cb_display_money        )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Add Patron",            cb_add_patron           )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Is Patron?",            cb_is_patron            )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Display Patrons",       cb_display_patron       )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Make Deposit",          cb_deposit              )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Make withdrawal",       cb_withdraw             )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Display Overdrawn",     cb_display_overdrawn    )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Display Transactions",  cb_display_transactions )  );

	attach(main_menu);



	View_Controller view_default( "Use this menu to do things =>" );

	View_Controller view_add_money ( "Add Money" );
	{
		In_box amount   ( Point(200,225), 100, 20, "Amount: " );
		In_box currency ( Point(200,250), 100, 20, "Currency: " );
		Button submit   ( Point(200,275), 100, 20, "Add", cb_add_money_submit );

		view_add_money.add_inbox( amount );
		view_add_money.add_inbox( currency );
		view_add_money.add_button( submit );
	}

	View_Controller view_remove_money ( "Remove Money" );
	{
		In_box amount   ( Point(200,225), 100, 20, "Amount: " );
		In_box currency ( Point(200,250), 100, 20, "Currency: " );
		Button submit   ( Point(200,275), 100, 20, "Remove", cb_remove_money_submit );

		view_remove_money.add_inbox( amount );
		view_remove_money.add_inbox( currency );
		view_remove_money.add_button( submit );
	}

	View_Controller view_display_money ( "Bank Money");
	{
		Out_box currency1 ( Point(140,150), 100, 20, "Currency: " );
		Out_box amount1   ( Point(260,150), 100, 20, "Amount: "   );

		Out_box currency2 ( Point(140,200), 100, 20, "Currency: " );
		Out_box amount2   ( Point(260,200), 100, 20, "Amount: "   );

		Out_box currency3 ( Point(140,250), 100, 20, "Currency: " );
		Out_box amount3   ( Point(260,250), 100, 20, "Amount: "   );

		Out_box currency4 ( Point(140,300), 100, 20, "Currency: " );
		Out_box amount4   ( Point(260,300), 100, 20, "Amount: "   );

		Out_box currency5 ( Point(140,350), 100, 20, "Currency: " );
		Out_box amount5   ( Point(260,350), 100, 20, "Amount: "   );

		view_display_money.add_outbox( currency1 );
		view_display_money.add_outbox( amount1   ); 
		view_display_money.add_outbox( currency2 );
		view_display_money.add_outbox( amount2   ); 
		view_display_money.add_outbox( currency3 );
		view_display_money.add_outbox( amount3   ); 
		view_display_money.add_outbox( currency4 );
		view_display_money.add_outbox( amount4   ); 
		view_display_money.add_outbox( currency5 );
		view_display_money.add_outbox( amount5   ); 
	}

	View_Controller view_add_patron ( "Add Patron");
	{
		In_box name   ( Point(200,225), 100, 20, "Name: " );
		Button submit ( Point(200,255), 100, 20, "Add", cb_add_patron_submit );

		view_add_patron.add_inbox( name   );
		view_add_patron.add_button( submit );
	}

	View_Controller view_is_patron ( "Check Patron");
	{
		In_box query  ( Point(250,175), 100, 20, "Name: " );
		Button submit ( Point(250,200), 100, 20, "Perform Query", cb_is_patron_submit );

		Out_box result  ( Point(300,300), 100, 20, "Result: "  );
		Out_box name    ( Point(300,325), 100, 20, "Name: "  );
		Out_box id      ( Point(300,350), 100, 20, "Account ID: "  );
		Out_box balance ( Point(300,375), 100, 20, "Current Balance: " );

		view_is_patron.add_inbox( query   );
		view_is_patron.add_button( submit  );
		view_is_patron.add_outbox( result  );
		view_is_patron.add_outbox( name    );
		view_is_patron.add_outbox( id      );
		view_is_patron.add_outbox( balance );
	}

	View_Controller view_display_patrons ( "Display Patrons");
	{
		Button previous  ( Point(25,225), 50, 50, "Prev 9", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box balance1 ( Point(100,200), 90, 20, "Current Balance: " );

		Out_box name2    ( Point(200,150), 90, 20, "Name: "  );
		Out_box id2      ( Point(200,175), 90, 20, "Account ID: "  );
		Out_box balance2 ( Point(200,200), 90, 20, "Current Balance: " );

		Out_box name3    ( Point(300,150), 90, 20, "Name: "  );
		Out_box id3      ( Point(300,175), 90, 20, "Account ID: "  );
		Out_box balance3 ( Point(300,200), 90, 20, "Current Balance: " );

		Out_box name4    ( Point(100,275), 90, 20, "Name: "  );
		Out_box id4      ( Point(100,300), 90, 20, "Account ID: "  );
		Out_box balance4 ( Point(100,325), 90, 20, "Current Balance: " );

		Out_box name5    ( Point(200,275), 90, 20, "Name: "  );
		Out_box id5      ( Point(200,300), 90, 20, "Account ID: "  );
		Out_box balance5 ( Point(200,325), 90, 20, "Current Balance: " );

		Out_box name6    ( Point(300,275), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,300), 90, 20, "Account ID: "  );
		Out_box balance6 ( Point(300,325), 90, 20, "Current Balance: " );

		Out_box name7    ( Point(100,400), 90, 20, "Name: "  );
		Out_box id7      ( Point(100,425), 90, 20, "Account ID: "  );
		Out_box balance7 ( Point(100,450), 90, 20, "Current Balance: " );

		Out_box name8    ( Point(200,400), 90, 20, "Name: "  );
		Out_box id8      ( Point(200,425), 90, 20, "Account ID: "  );
		Out_box balance8 ( Point(200,450), 90, 20, "Current Balance: " );

		Out_box name9    ( Point(300,400), 90, 20, "Name: "  );
		Out_box id9      ( Point(300,425), 90, 20, "Account ID: "  );
		Out_box balance9 ( Point(300,450), 90, 20, "Current Balance: " );

		Button next      ( Point(425,225), 50, 50, "Next 9", cb_display_next );

		view_display_patrons.add_button( previous );

		view_display_patrons.add_outbox( name1    );
		view_display_patrons.add_outbox( id1      );
		view_display_patrons.add_outbox( balance1 );

		view_display_patrons.add_outbox( name2    );
		view_display_patrons.add_outbox( id2      );
		view_display_patrons.add_outbox( balance2 );

		view_display_patrons.add_outbox( name3    );
		view_display_patrons.add_outbox( id3      );
		view_display_patrons.add_outbox( balance3 );

		view_display_patrons.add_outbox( name4    );
		view_display_patrons.add_outbox( id4      );
		view_display_patrons.add_outbox( balance4 );

		view_display_patrons.add_outbox( name5    );
		view_display_patrons.add_outbox( id5      );
		view_display_patrons.add_outbox( balance5 );

		view_display_patrons.add_outbox( name6    );
		view_display_patrons.add_outbox( id6      );
		view_display_patrons.add_outbox( balance6 );

		view_display_patrons.add_outbox( name7    );
		view_display_patrons.add_outbox( id7      );
		view_display_patrons.add_outbox( balance7 );

		view_display_patrons.add_outbox( name8    );
		view_display_patrons.add_outbox( id8      );
		view_display_patrons.add_outbox( balance8 );

		view_display_patrons.add_outbox( name9    );
		view_display_patrons.add_outbox( id9      );
		view_display_patrons.add_outbox( balance9 );

		view_display_patrons.add_button( next );
	}

	View_Controller view_deposit ( "Make Deposit");
	{
		In_box name     ( Point(200,225), 100, 20, "Name: "     );
		In_box amount   ( Point(200,225), 100, 20, "Amount: "   );
		In_box currency ( Point(200,250), 100, 20, "Currency: " );
		Button submit   ( Point(200,275), 100, 20, "Add", cb_deposit_submit );

		view_deposit.add_inbox(   name   );
		view_deposit.add_inbox(  amount  );
		view_deposit.add_inbox( currency );
		view_deposit.add_button(  submit  );
	}

	View_Controller view_withdraw ( "Make Withdraw" );
	{
		In_box name     ( Point(200,225), 100, 20, "Name: "     );
		In_box amount   ( Point(200,225), 100, 20, "Amount: "   );
		In_box currency ( Point(200,250), 100, 20, "Currency: " );
		Button submit   ( Point(200,275), 100, 20, "Add", cb_deposit_submit );

		view_withdraw.add_inbox(   name   );
		view_withdraw.add_inbox(  amount  );
		view_withdraw.add_inbox( currency );		
		view_withdraw.add_button(  submit  );
	}

	View_Controller view_display_overdrawn ( "Overdrawn Patrons" );
	{
		Button previous  ( Point(25,225), 50, 50, "Prev 9", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box balance1 ( Point(100,200), 90, 20, "Current Balance: " );

		Out_box name2    ( Point(200,150), 90, 20, "Name: "  );
		Out_box id2      ( Point(200,175), 90, 20, "Account ID: "  );
		Out_box balance2 ( Point(200,200), 90, 20, "Current Balance: " );

		Out_box name3    ( Point(300,150), 90, 20, "Name: "  );
		Out_box id3      ( Point(300,175), 90, 20, "Account ID: "  );
		Out_box balance3 ( Point(300,200), 90, 20, "Current Balance: " );

		Out_box name4    ( Point(100,275), 90, 20, "Name: "  );
		Out_box id4      ( Point(100,300), 90, 20, "Account ID: "  );
		Out_box balance4 ( Point(100,325), 90, 20, "Current Balance: " );

		Out_box name5    ( Point(200,275), 90, 20, "Name: "  );
		Out_box id5      ( Point(200,300), 90, 20, "Account ID: "  );
		Out_box balance5 ( Point(200,325), 90, 20, "Current Balance: " );

		Out_box name6    ( Point(300,275), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,300), 90, 20, "Account ID: "  );
		Out_box balance6 ( Point(300,325), 90, 20, "Current Balance: " );

		Out_box name7    ( Point(100,400), 90, 20, "Name: "  );
		Out_box id7      ( Point(100,425), 90, 20, "Account ID: "  );
		Out_box balance7 ( Point(100,450), 90, 20, "Current Balance: " );

		Out_box name8    ( Point(200,400), 90, 20, "Name: "  );
		Out_box id8      ( Point(200,425), 90, 20, "Account ID: "  );
		Out_box balance8 ( Point(200,450), 90, 20, "Current Balance: " );

		Out_box name9    ( Point(300,400), 90, 20, "Name: "  );
		Out_box id9      ( Point(300,425), 90, 20, "Account ID: "  );
		Out_box balance9 ( Point(300,450), 90, 20, "Current Balance: " );

		Button next      ( Point(425,225), 50, 50, "Next 9", cb_display_next );

		view_display_overdrawn.add_button( previous );

		view_display_overdrawn.add_outbox( name1    );
		view_display_overdrawn.add_outbox( id1      );
		view_display_overdrawn.add_outbox( balance1 );

		view_display_overdrawn.add_outbox( name2    );
		view_display_overdrawn.add_outbox( id2      );
		view_display_overdrawn.add_outbox( balance2 );

		view_display_overdrawn.add_outbox( name3    );
		view_display_overdrawn.add_outbox( id3      );
		view_display_overdrawn.add_outbox( balance3 );

		view_display_overdrawn.add_outbox( name4    );
		view_display_overdrawn.add_outbox( id4      );
		view_display_overdrawn.add_outbox( balance4 );

		view_display_overdrawn.add_outbox( name5    );
		view_display_overdrawn.add_outbox( id5      );
		view_display_overdrawn.add_outbox( balance5 );

		view_display_overdrawn.add_outbox( name6    );
		view_display_overdrawn.add_outbox( id6      );
		view_display_overdrawn.add_outbox( balance6 );

		view_display_overdrawn.add_outbox( name7    );
		view_display_overdrawn.add_outbox( id7      );
		view_display_overdrawn.add_outbox( balance7 );

		view_display_overdrawn.add_outbox( name8    );
		view_display_overdrawn.add_outbox( id8      );
		view_display_overdrawn.add_outbox( balance8 );

		view_display_overdrawn.add_outbox( name9    );
		view_display_overdrawn.add_outbox( id9      );
		view_display_overdrawn.add_outbox( balance9 );

		view_display_overdrawn.add_button( next );
	}

	View_Controller view_display_transactions ( "Add Patron" );
	{
		Button previous  ( Point(25,225), 50, 50, "Prev 6", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box type1    ( Point(100,200), 90, 20, "Type: " );
		Out_box date1    ( Point(100,225), 90, 20, "Date: " );
		Out_box time1    ( Point(100,250), 90, 20, "Time: " );
		Out_box balance1 ( Point(100,275), 90, 20, "Current Balance: " );

		Out_box name2    ( Point(200,150), 90, 20, "Name: "  );
		Out_box id2      ( Point(200,175), 90, 20, "Account ID: "  );
		Out_box type2    ( Point(200,200), 90, 20, "Type: " );
		Out_box date2    ( Point(200,225), 90, 20, "Date: " );
		Out_box time2    ( Point(200,250), 90, 20, "Time: " );
		Out_box balance2 ( Point(200,275), 90, 20, "Current Balance: " );

		Out_box name3    ( Point(300,150), 90, 20, "Name: "  );
		Out_box id3      ( Point(300,175), 90, 20, "Account ID: "  );
		Out_box type3    ( Point(300,200), 90, 20, "Type: " );
		Out_box date3    ( Point(300,225), 90, 20, "Date: " );
		Out_box time3    ( Point(300,250), 90, 20, "Time: " );
		Out_box balance3 ( Point(300,275), 90, 20, "Current Balance: " );

		Out_box name4    ( Point(100,350), 90, 20, "Name: "  );
		Out_box id4      ( Point(100,375), 90, 20, "Account ID: "  );
		Out_box type4    ( Point(100,400), 90, 20, "Type: " );
		Out_box date4    ( Point(100,425), 90, 20, "Date: " );
		Out_box time4    ( Point(100,450), 90, 20, "Time: " );
		Out_box balance4 ( Point(100,475), 90, 20, "Current Balance: " );

		Out_box name5    ( Point(200,350), 90, 20, "Name: "  );
		Out_box id5      ( Point(200,375), 90, 20, "Account ID: "  );
		Out_box type5    ( Point(200,400), 90, 20, "Type: " );
		Out_box date5    ( Point(200,425), 90, 20, "Date: " );
		Out_box time5    ( Point(200,450), 90, 20, "Time: " );
		Out_box balance5 ( Point(200,475), 90, 20, "Current Balance: " );

		Out_box name6    ( Point(300,350), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,375), 90, 20, "Account ID: "  );
		Out_box type6    ( Point(300,400), 90, 20, "Type: " );
		Out_box date6    ( Point(300,425), 90, 20, "Date: " );
		Out_box time6    ( Point(300,450), 90, 20, "Time: " );
		Out_box balance6 ( Point(300,475), 90, 20, "Current Balance: " );

		Button next ( Point(425,225), 50, 50, "Next 6", cb_display_next );

		view_display_transactions.add_button( previous );

		view_display_transactions.add_outbox( name1 );
		view_display_transactions.add_outbox( id1   );
		view_display_transactions.add_outbox( type1 );
		view_display_transactions.add_outbox( date1 );
		view_display_transactions.add_outbox( time1 );
		view_display_transactions.add_outbox( balance1 );

		view_display_transactions.add_outbox( name2 );
		view_display_transactions.add_outbox( id2   );
		view_display_transactions.add_outbox( type2 );
		view_display_transactions.add_outbox( date2 );
		view_display_transactions.add_outbox( time2 );
		view_display_transactions.add_outbox( balance2 );

		view_display_transactions.add_outbox( name3 );
		view_display_transactions.add_outbox( id3   );
		view_display_transactions.add_outbox( type3 );
		view_display_transactions.add_outbox( date3 );
		view_display_transactions.add_outbox( time3 );
		view_display_transactions.add_outbox( balance3 );

		view_display_transactions.add_outbox( name4 );
		view_display_transactions.add_outbox( id4   );
		view_display_transactions.add_outbox( type4 );
		view_display_transactions.add_outbox( date4 );
		view_display_transactions.add_outbox( time4 );
		view_display_transactions.add_outbox( balance4 );

		view_display_transactions.add_outbox( name5 );
		view_display_transactions.add_outbox( id5   );
		view_display_transactions.add_outbox( type5 );
		view_display_transactions.add_outbox( date5 );
		view_display_transactions.add_outbox( time5 );		
		view_display_transactions.add_outbox( balance5 );

		view_display_transactions.add_outbox( name6 );
		view_display_transactions.add_outbox( id6   );
		view_display_transactions.add_outbox( type6 );
		view_display_transactions.add_outbox( date6 );
		view_display_transactions.add_outbox( time6 );
		view_display_transactions.add_outbox( balance6 );

		view_display_transactions.add_button( next );
	}

	add_view(  view_default       );
	add_view(  view_add_money     );
	add_view(  view_remove_money  );
	add_view(  view_display_money );
	add_view(  view_add_money     );
	add_view(  view_add_money     );
	add_view(  view_add_money     );
	add_view(  view_add_money     );
	add_view(  view_add_money     );
	add_view(  view_add_money     );
	add_view(  view_add_money     );

}

void Bank_Window::add_view( View_Controller & view ) 
{
	views.push_back( move( view ) );

	View_Controller & view_ref = views.back( );

	for ( In_box & w : view_ref.inboxes ) {
		attach( w );
	}

	for ( Out_box & w : view_ref.outboxes ) {
		attach( w );
	}

	for ( Button & w : view_ref.buttons ) {
		attach( w );
	}
}

void Bank_Window::remode( int m ) 
{
	views[mode].disable();
	views[m].enable();
	mode = m;
}

void Bank_Window::quit() 
{
	hide();
}



// callbacks

void Bank_Window::cb_add_money ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 1;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_remove_money ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 2;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_money ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 3;

	// todo

	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_add_patron ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 4;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_is_patron ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 5;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_patron ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 6;

	// todo 

	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_deposit ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 7;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_withdraw ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 8;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_overdrawn ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 9;

	// todo

	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_transactions ( Address, Address win )
{
	reference_to<Bank_Window>(win).mode = 10;

	// todo

	reference_to<Bank_Window>(win).redraw();
}



void Bank_Window::cb_add_money_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	double amount = atof( view.inboxes[0].get_string().c_str() );
	string currency = view.inboxes[1].get_string();
	
	bank.add_money( bank.currency( currency ), amount );

}

void Bank_Window::cb_remove_money_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	double amount = atof( view.inboxes[0].get_string().c_str() );
	string currency = view.inboxes[1].get_string();
	
	bank.add_money( bank.currency( currency ), amount );
}

void Bank_Window::cb_add_patron_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0].get_string();

	int num = bank.patron_count();

	Patron patron( name, num, 0);

	bank.add_patron( patron );
}

void Bank_Window::cb_is_patron_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0].get_string();

	Out_box & result   = view.outboxes[0];
	Out_box & username = view.outboxes[1];  
	Out_box & id       = view.outboxes[2];
	Out_box & balance  = view.outboxes[3];

	if( bank.is_patron(name) ) {

		Patron patron = bank.get_patron( name );

		result.put( "User found" );
		username.put( patron.get_name() );
		id.put( to_string( patron.get_account_number() ) );
		balance.put( to_string(patron.get_balance()) );

	} else {
		result.put( "User not found");
	}

}

void Bank_Window::cb_deposit_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0].get_string(); 
	double amount = atof( view.inboxes[1].get_string().c_str() );  
	string currency = view.inboxes[2].get_string();

	if( bank.is_patron(name) ) {
		bank.deposit( bank.get_patron( name ), bank.currency(currency), amount );
	}
	else {
		cout << name << " is not a patron here";
	}

}

void Bank_Window::cb_withdraw_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0].get_string();
	double amount = atof( view.inboxes[1].get_string().c_str() );  
	string currency = view.inboxes[2].get_string();

	if( bank.is_patron(name) ) {
		bank.withdraw( bank.get_patron( name ), bank.currency(currency), amount );
	}
	else {
		cout << name << " is not a patron here";
	}
}

void Bank_Window::cb_display_prev   ( Address, Address win )
{
	reference_to<Bank_Window>(win).display_pos -= 1;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_next   ( Address, Address win ) 
{
	reference_to<Bank_Window>(win).display_pos += 1;
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_next ( Address, Address win ) 
{
	reference_to<Bank_Window>(win).quit();
}

void Bank_Window::cb_quit ( Address, Address win ) 
{
	reference_to<Bank_Window>(win).quit();
}


