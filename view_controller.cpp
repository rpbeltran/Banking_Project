

#include "view_controller.h"

using namespace Graph_lib;

View_Controller::View_Controller( string t )
{
	title = t;
}


void View_Controller::add_inbox( Widget & widget ) 
{
	//inboxes.emplace_back( widget.loc, widget.width, widget.height, widget.label );
}

void View_Controller::add_outbox( Out_box & widget ) 
{

	//outboxes.emplace_back( widget.loc, widget.width, widget.height, widget.label );

}

void View_Controller::add_button( Button & widget ) 
{

	//buttons.emplace_back( widget.loc, widget.width, widget.height, widget.label, widget.do_it );

}


void View_Controller::enable( ) 
{

	if (! enabled )  {

		for ( In_box & w : inboxes ) {
			w.show();
		}

		for ( Out_box & w : outboxes ) {
			w.show();
		}

		for ( Button & w : buttons ) {
			w.show();
		}

	}

	enabled = true;

}


void View_Controller::disable( ) 
{

	if ( enabled )  {

		for ( In_box & w : inboxes ) {
			w.hide();
		}

		for ( Out_box & w : outboxes ) {
			w.hide();
		}

		for ( Button & w : buttons ) {
			w.hide();
		}

	}

	enabled = false;

}


bool View_Controller::is_enabled( ) 
{

	return enabled;

}

