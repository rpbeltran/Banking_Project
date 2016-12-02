
#include "GUI.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

struct View_Controller {

	vector< In_box > inboxes;
	vector< Out_box > outboxes;
	vector< Button > buttons;

	bool enabled;

	string title;

	View_Controller( string );

	void add_inbox( Widget &);
	void add_outbox( Out_box & );
	void add_button( Button &);

	void enable();
	void disable();

	bool is_enabled();

};
