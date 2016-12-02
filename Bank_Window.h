

#include "Graph.h"
#include "GUI.h"
#include "Window.h"
#include "network.h"
#include "view_controller.h"

using namespace Banking;
using namespace Graph_lib;

struct Bank_Window : public Graph_lib::Window {

	// data

	int mode;

	int display_pos;

	vector<View_Controller> views;

	Bank_Network & network;
	International_Bank & bank;

	// member functions

	Bank_Window( Bank_Network & n, International_Bank & b, string name ) ;

	Menu main_menu;

	void add_view( View_Controller & );

	void remode( int );

	void quit();

	// callbacks

	static void cb_add_money            (Address, Address);
	static void cb_remove_money         (Address, Address);
	static void cb_display_money        (Address, Address);
	static void cb_add_patron           (Address, Address);
	static void cb_is_patron            (Address, Address);
	static void cb_display_patron       (Address, Address);
	static void cb_deposit              (Address, Address);
	static void cb_withdraw             (Address, Address);
	static void cb_display_overdrawn    (Address, Address);
	static void cb_display_transactions (Address, Address);

	static void cb_add_money_submit    (Address, Address);
	static void cb_remove_money_submit (Address, Address);
	static void cb_add_patron_submit   (Address, Address);
	static void cb_is_patron_submit    (Address, Address);
	static void cb_deposit_submit      (Address, Address);
	static void cb_withdraw_submit     (Address, Address);

	static void cb_display_prev   (Address, Address);
	static void cb_display_next   (Address, Address);

	static void cb_next (Address, Address);
	static void cb_quit (Address, Address);

};