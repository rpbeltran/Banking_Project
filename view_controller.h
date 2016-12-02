
#include "GUI.h"
#include "Graph.h"

using namespace Banking;
using namespace Graph_lib;

struct View_Controller {

	vector< Widget > widgets;

	bool enabled;

	Text title;

	View_Controller( string );

	void add_widget( Widget & );

	void enable();
	void disable();

	bool is_enabled();

};
