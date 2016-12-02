

#include "view_controller.h"

using namespace Banking;
using namespace Graph_lib;

View_Controller::View_Controller( string t )
{
	title = Text ( Point( 175, 40 ), t );
    title.set_font( Graph_lib::Font::times_bold );
    title.set_font_size( 25 );
}


void View_Controller::add_widget( Widget & widget ) 
{

	widgets.push_back( widget );

}


void View_Controller::enable( ) 
{

	if (! enabled )  {
		for ( Widget & w : widgets ) {
			w.show();
		}
	}

	enabled = true;

}


void View_Controller::disable( ) 
{

	if ( enabled )  {
		for ( Widget & w : widgets ) {
			w.hide();
		}
	}

	enabled = false;

}


bool View_Controller::is_enabled( ) 
{

	return enabled;

}

