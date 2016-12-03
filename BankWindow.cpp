
#include "Bank_Window.h"


Bank_Window::Bank_Window( Bank_Network & n, International_Bank & b, string bank_name ) :

	bank( b ),

	network( n ),

	Window( Point(100,100), 660, 525, bank_name ),

	main_menu( Point( x_max() - 110, 30 ), 100, 20, Menu::vertical, "Main Menu" )

{

	mode = 0;

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
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Transfer",  cb_transfer )  );
	main_menu.attach(  new Button(  Point(0,0), 0, 0,  "Save To",  cb_save )  );

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
		view_remove_money.add_inbox( currency);
		view_remove_money.add_button( submit );
	}

	View_Controller view_display_money ( "Bank Money" );
	{
		Out_box currency1 ( Point(140,125), 100, 20, "Currency: " );
		Out_box amount1   ( Point(260,150), 100, 20, "Amount: "   );

		Out_box currency2 ( Point(140,200), 100, 20, "Currency: " );
		Out_box amount2   ( Point(260,225), 100, 20, "Amount: "   );

		Out_box currency3 ( Point(140,275), 100, 20, "Currency: " );
		Out_box amount3   ( Point(260,300), 100, 20, "Amount: "   );

		Out_box currency4 ( Point(140,350), 100, 20, "Currency: " );
		Out_box amount4   ( Point(260,375), 100, 20, "Amount: "   );

		Out_box currency5 ( Point(140,425), 100, 20, "Currency: " );
		Out_box amount5   ( Point(260,450), 100, 20, "Amount: "   );

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

		Out_box result  ( Point(250,250), 100, 20, "Result: "  );
		Out_box name    ( Point(250,275), 100, 20, "Name: "  );
		Out_box id      ( Point(250,300), 100, 20, "Account ID: "  );
		Out_box balance ( Point(250,325), 100, 20, "Current Balance: " );

		view_is_patron.add_inbox( query   );
		view_is_patron.add_button( submit  );
		view_is_patron.add_outbox( result  );
		view_is_patron.add_outbox( name    );
		view_is_patron.add_outbox( id      );
		view_is_patron.add_outbox( balance );
	}

	View_Controller view_display_patrons ( "Display Patrons");
	{
		Button previous  ( Point(425,250), 50, 50, "Prev", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box balance1 ( Point(100,200), 90, 20, "Current Balance: " );

		Out_box name3    ( Point(300,150), 90, 20, "Name: "  );
		Out_box id3      ( Point(300,175), 90, 20, "Account ID: "  );
		Out_box balance3 ( Point(300,200), 90, 20, "Current Balance: " );

		Out_box name4    ( Point(100,275), 90, 20, "Name: "  );
		Out_box id4      ( Point(100,300), 90, 20, "Account ID: "  );
		Out_box balance4 ( Point(100,325), 90, 20, "Current Balance: " );

		Out_box name6    ( Point(300,275), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,300), 90, 20, "Account ID: "  );
		Out_box balance6 ( Point(300,325), 90, 20, "Current Balance: " );

		Out_box name7    ( Point(100,400), 90, 20, "Name: "  );
		Out_box id7      ( Point(100,425), 90, 20, "Account ID: "  );
		Out_box balance7 ( Point(100,450), 90, 20, "Current Balance: " );

		Out_box name9    ( Point(300,400), 90, 20, "Name: "  );
		Out_box id9      ( Point(300,425), 90, 20, "Account ID: "  );
		Out_box balance9 ( Point(300,450), 90, 20, "Current Balance: " );

		Button next      ( Point(425,325), 50, 50, "Next", cb_display_next );

		view_display_patrons.add_button( previous );

		view_display_patrons.add_outbox( name1    );
		view_display_patrons.add_outbox( id1      );
		view_display_patrons.add_outbox( balance1 );

		view_display_patrons.add_outbox( name3    );
		view_display_patrons.add_outbox( id3      );
		view_display_patrons.add_outbox( balance3 );

		view_display_patrons.add_outbox( name4    );
		view_display_patrons.add_outbox( id4      );
		view_display_patrons.add_outbox( balance4 );

		view_display_patrons.add_outbox( name6    );
		view_display_patrons.add_outbox( id6      );
		view_display_patrons.add_outbox( balance6 );

		view_display_patrons.add_outbox( name7    );
		view_display_patrons.add_outbox( id7      );
		view_display_patrons.add_outbox( balance7 );

		view_display_patrons.add_outbox( name9    );
		view_display_patrons.add_outbox( id9      );
		view_display_patrons.add_outbox( balance9 );

		view_display_patrons.add_button( next );
	}

	View_Controller view_deposit ( "Make Deposit");
	{
		In_box name     ( Point(200,225), 100, 20, "Name: "     );
		In_box amount   ( Point(200,250), 100, 20, "Amount: "   );
		In_box currency ( Point(200,275), 100, 20, "Currency: " );
		Button submit   ( Point(200,300), 100, 20, "Add", cb_deposit_submit );

		view_deposit.add_inbox(   name   );
		view_deposit.add_inbox(  amount  );
		view_deposit.add_inbox( currency );
		view_deposit.add_button(  submit  );
	}

	View_Controller view_withdraw ( "Make Withdraw" );
	{
		In_box name     ( Point(200,225), 100, 20, "Name: "     );
		In_box amount   ( Point(200,250), 100, 20, "Amount: "   );
		In_box currency ( Point(200,275), 100, 20, "Currency: " );
		Button submit   ( Point(200,300), 100, 20, "Add", cb_deposit_submit );

		view_withdraw.add_inbox(   name   );
		view_withdraw.add_inbox(  amount  );
		view_withdraw.add_inbox( currency );
		view_withdraw.add_button(  submit  );
	}

	View_Controller view_display_overdrawn ( "Overdrawn Patrons" );
	{
		Button previous  ( Point(425,250), 50, 50, "Prev", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box balance1 ( Point(100,200), 90, 20, "Current Balance: " );

		Out_box name3    ( Point(300,150), 90, 20, "Name: "  );
		Out_box id3      ( Point(300,175), 90, 20, "Account ID: "  );
		Out_box balance3 ( Point(300,200), 90, 20, "Current Balance: " );

		Out_box name4    ( Point(100,275), 90, 20, "Name: "  );
		Out_box id4      ( Point(100,300), 90, 20, "Account ID: "  );
		Out_box balance4 ( Point(100,325), 90, 20, "Current Balance: " );

		Out_box name6    ( Point(300,275), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,300), 90, 20, "Account ID: "  );
		Out_box balance6 ( Point(300,325), 90, 20, "Current Balance: " );

		Out_box name7    ( Point(100,400), 90, 20, "Name: "  );
		Out_box id7      ( Point(100,425), 90, 20, "Account ID: "  );
		Out_box balance7 ( Point(100,450), 90, 20, "Current Balance: " );

		Out_box name9    ( Point(300,400), 90, 20, "Name: "  );
		Out_box id9      ( Point(300,425), 90, 20, "Account ID: "  );
		Out_box balance9 ( Point(300,450), 90, 20, "Current Balance: " );

		Button next      ( Point(425,325), 50, 50, "Next", cb_display_next );

		view_display_overdrawn.add_button( previous );

		view_display_overdrawn.add_outbox( name1    );
		view_display_overdrawn.add_outbox( id1      );
		view_display_overdrawn.add_outbox( balance1 );

		view_display_overdrawn.add_outbox( name3    );
		view_display_overdrawn.add_outbox( id3      );
		view_display_overdrawn.add_outbox( balance3 );

		view_display_overdrawn.add_outbox( name4    );
		view_display_overdrawn.add_outbox( id4      );
		view_display_overdrawn.add_outbox( balance4 );

		view_display_overdrawn.add_outbox( name6    );
		view_display_overdrawn.add_outbox( id6      );
		view_display_overdrawn.add_outbox( balance6 );

		view_display_overdrawn.add_outbox( name7    );
		view_display_overdrawn.add_outbox( id7      );
		view_display_overdrawn.add_outbox( balance7 );

		view_display_overdrawn.add_outbox( name9    );
		view_display_overdrawn.add_outbox( id9      );
		view_display_overdrawn.add_outbox( balance9 );

		view_display_overdrawn.add_button( next );
	}

	View_Controller view_display_transactions ( "Add Patron" );
	{
		Button previous  ( Point(425,250), 50, 50, "Prev", cb_display_prev );

		Out_box name1    ( Point(100,150), 90, 20, "Name: "  );
		Out_box id1      ( Point(100,175), 90, 20, "Account ID: "  );
		Out_box type1    ( Point(100,200), 90, 20, "Type: " );
		Out_box date1    ( Point(100,225), 90, 20, "Date: " );
		Out_box time1    ( Point(100,250), 90, 20, "Time: " );
		Out_box balance1 ( Point(100,275), 90, 20, "Current Balance: " );

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

		Out_box name6    ( Point(300,350), 90, 20, "Name: "  );
		Out_box id6      ( Point(300,375), 90, 20, "Account ID: "  );
		Out_box type6    ( Point(300,400), 90, 20, "Type: " );
		Out_box date6    ( Point(300,425), 90, 20, "Date: " );
		Out_box time6    ( Point(300,450), 90, 20, "Time: " );
		Out_box balance6 ( Point(300,475), 90, 20, "Current Balance: " );

		Button next      ( Point(425,325), 50, 50, "Next", cb_display_next );

		view_display_transactions.add_button( previous );

		view_display_transactions.add_outbox( name1 );
		view_display_transactions.add_outbox( id1   );
		view_display_transactions.add_outbox( type1 );
		view_display_transactions.add_outbox( date1 );
		view_display_transactions.add_outbox( time1 );
		view_display_transactions.add_outbox( balance1 );

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

		view_display_transactions.add_outbox( name6 );
		view_display_transactions.add_outbox( id6   );
		view_display_transactions.add_outbox( type6 );
		view_display_transactions.add_outbox( date6 );
		view_display_transactions.add_outbox( time6 );
		view_display_transactions.add_outbox( balance6 );

		view_display_transactions.add_button( next );
	}

	View_Controller view_transfer ( "Transfer Funds" );
	{
		In_box name     ( Point(200,200), 100, 20, "Name: "     );
		In_box bank     ( Point(200,225), 100, 20, "Bank: "     );
		In_box amount   ( Point(200,250), 100, 20, "Amount: "   );
		In_box currency ( Point(200,275), 100, 20, "Currency: " );
		Button submit   ( Point(200,300), 100, 20, "Transfer", cb_transfer_submit );

		view_transfer.add_inbox(   name   );
		view_transfer.add_inbox(   bank   );
		view_transfer.add_inbox(  amount  );
		view_transfer.add_inbox( currency );
		view_transfer.add_button(  submit  );
	}

	View_Controller view_save ( "Save to File" );
	{
		In_box file   ( Point(200,225), 100, 20, "File: " );
		Button submit ( Point(200,255), 100, 20, "Save", cb_save_submit );

		view_save.add_inbox( file   );
		view_save.add_button( submit );
	}

	add_view(  view_default       ); // 0
	add_view(  view_add_money     );
	add_view(  view_remove_money  ); // 2
	add_view(  view_display_money );
	add_view(  view_add_patron    ); // 4
	add_view(  view_is_patron     );
	add_view(  view_display_patrons ); // 6
	add_view(  view_deposit         );
	add_view(  view_withdraw        ); // 8
	add_view(  view_display_overdrawn    );
	add_view(  view_display_transactions ); // 10
	add_view(  view_transfer  );
	add_view(  view_save      ); // 12

	remode(0);
	remode(1);
	remode(2);
	remode(3);
	remode(4);
	remode(5);
	remode(6);
	remode(7);
	remode(8);
	remode(9);
	remode(10);
	remode(11);
	remode(12);

	remode(0);

	redraw();

}

void Bank_Window::add_view( View_Controller & view )
{
	views.push_back( move( view ) );

	View_Controller & view_ref = views.back( );

	for ( In_box * w : view_ref.inboxes ) {
		attach( *w );
	}

	for ( Out_box * w : view_ref.outboxes ) {
		attach( *w );
	}

	for ( Button * w : view_ref.buttons ) {
		attach( *w );
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
	reference_to<Bank_Window>(win).remode( 1 );
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_remove_money ( Address, Address win )
{
	reference_to<Bank_Window>(win).remode( 2);
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_money ( Address, Address win )
{

	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 3 );

	View_Controller & view = window.views[window.mode];

	for (int i = 0; i < 5; i++){
		view.outboxes[2*i]->put( bank.monies[i].get_currency().type );
		view.outboxes[2*i+1]->put( to_string(bank.monies[i].get_amount()) );
	}

	window.redraw();
}

void Bank_Window::cb_add_patron ( Address, Address win )
{
	reference_to<Bank_Window>(win).remode( 4);
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_is_patron ( Address, Address win )
{
	reference_to<Bank_Window>(win).remode( 5);
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_patron ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 6 );

	View_Controller & view = window.views[window.mode];

	for (int i = 0; i < 6; i++) {

		if (i >= bank.patron_count()) {
			break;
		}

		view.outboxes[3*i]->put( bank.patrons[i].get_name() );
		view.outboxes[3*i+1]->put( to_string(bank.patrons[i].get_account_number()) );
		view.outboxes[3*i+2]->put( to_string(bank.patrons[i].get_balance()) );
	}

	window.redraw();
}

void Bank_Window::cb_deposit ( Address, Address win )
{
	reference_to<Bank_Window>(win).remode( 7);
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_withdraw ( Address, Address win )
{
	reference_to<Bank_Window>(win).remode( 8);
	reference_to<Bank_Window>(win).redraw();
}

void Bank_Window::cb_display_overdrawn ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 9 );

	View_Controller & view = window.views[window.mode];

	int c = 0;
	int i = 0;
	while (c<6) {

		if (i >= bank.patron_count()) {
			break;
		}

		if ( bank.patrons[i].get_balance() < 0) {
			view.outboxes[3*c]->put( bank.patrons[i].get_name() );
			view.outboxes[3*c+1]->put( to_string(bank.patrons[i].get_account_number()) );
			view.outboxes[3*c+2]->put( to_string(bank.patrons[i].get_balance()) );
			c += 1;
		}
		i+=1;
	}


	window.redraw();
}

void Bank_Window::cb_display_transactions ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 10 );

	View_Controller & view = window.views[window.mode];

	for (int i = 0; i < 6; i++) {

		if (i >= bank.patron_count()) {
			break;
		}

		view.outboxes[3*i]->put( bank.patrons[i].get_name() );
		view.outboxes[3*i+1]->put( to_string(bank.patrons[i].get_account_number()) );
		view.outboxes[3*i+2]->put( to_string(bank.patrons[i].get_balance()) );
	}
	window.redraw();
}

void Bank_Window::cb_transfer( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 11 );

	View_Controller & view = window.views[window.mode];

	window.redraw();
}


void Bank_Window::cb_save( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	window.remode( 12 );

	View_Controller & view = window.views[window.mode];

	window.redraw();
}

void Bank_Window::cb_transfer_submit( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0]->get_string(); // name
	string bank_name = view.inboxes[1]->get_string(); // bank
	double amount = atof(view.inboxes[2]->get_string().c_str()); //amount
	string currency = view.inboxes[3]->get_string(); //currency

	cout << "N: " << name << endl;
	cout << "B: " << bank_name << endl;
	cout << "A: " << amount << endl;
	cout << "C: " << currency << endl;

	try {
		for ( International_Bank & transfer_bank : window.network.banks ) {
			if ( transfer_bank.default_currency.type == bank_name ) {

				if ( true ) {
					cout << 1 << endl;
					if( bank.is_patron(name)) {
						cout << 2 << endl;
						if (bank.get_patron(name).get_balance() >= amount ) {
							cout << 3 << endl;
							bank.withdraw( bank.get_patron(name), bank.currency(currency), amount );
							transfer_bank.deposit( transfer_bank.get_patron(name), bank.currency(currency), amount );
							break;
						}
					}
				}
				cout << "Can not complete transfer" << endl;
			}
		}
	}
	catch(...) {
		cout << currency;
	}
}


void Bank_Window::cb_save_submit( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string file = view.inboxes[0]->get_string();

	bank.Save_to( file );

}

void Bank_Window::cb_add_money_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	double amount = atof( view.inboxes[0]->get_string().c_str() );
	string currency = view.inboxes[1]->get_string();

	bank.add_money( bank.currency( currency ), amount );

}

void Bank_Window::cb_remove_money_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	double amount = atof( view.inboxes[0]->get_string().c_str() );
	string currency = view.inboxes[1]->get_string();

	bank.remove_money( bank.currency( currency ), amount );
}

void Bank_Window::cb_add_patron_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0]->get_string();

	int num = bank.patron_count();

	Patron patron( name, num, 0);

	bank.add_patron( patron );
}

void Bank_Window::cb_is_patron_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0]->get_string();

	Out_box * result   = view.outboxes[0];
	Out_box * username = view.outboxes[1];
	Out_box * id       = view.outboxes[2];
	Out_box * balance  = view.outboxes[3];

	if( bank.is_patron(name) ) {

		Patron patron = bank.get_patron( name );

		result->put( "User found" );
		username->put( patron.get_name() );
		id->put( to_string( patron.get_account_number() ) );
		balance->put( to_string(patron.get_balance()) );

	} else {
		result->put( " Not Found ");
		username->put( "---" );
		id->put( "---");
		balance->put( "---" );
	}

}

void Bank_Window::cb_deposit_submit ( Address, Address win )
{
	Bank_Window & window = reference_to<Bank_Window>(win);

	International_Bank & bank = window.bank;

	View_Controller & view = window.views[window.mode];

	string name = view.inboxes[0]->get_string();
	double amount = atof( view.inboxes[1]->get_string().c_str() );
	string currency = view.inboxes[2]->get_string();

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

	string name = view.inboxes[0]->get_string();
	double amount = atof( view.inboxes[1]->get_string().c_str() );
	string currency = view.inboxes[2]->get_string();

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
	if (reference_to<Bank_Window>(win).display_pos == -1){
		reference_to<Bank_Window>(win).display_pos = 1;
	}
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
