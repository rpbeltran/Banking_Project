
//
// This is example code from Chapter 9.8 "The Date class" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Chrono.h"
#include <iomanip>


namespace Chrono {


Date::Date(int yy, Month mm, int dd)
    : y(yy), m(mm), d(dd)
{
    if (!is_date(yy,mm,dd)) throw Invalid();
}


Date::Date( Month mm, int dd, int yy) : Date( yy, mm, dd ) { } // Previous constructor already checks for errors


const Date& default_date()
{
    static const Date dd(2001,Date::jan,1); // start of 21st century
    return dd;
}


Date::Date()
    :y(default_date().year()),
     m(default_date().month()),
     d(default_date().day())
{

}




void Date::add_day(int n)
{
    // ...
}


void Date::add_month(int n)
{
    // ...
}


void Date::add_year(int n)
{
    if (m==feb && d==29 && !leapyear(y+n)) { // beware of leap years!
        m = mar;        // use March 1 instead of February 29
        d = 1;
    }
    y+=n;
}




int Date::to_julian( )
// Description: Converts a date from the gregorian calendar to the julian calendar
// Precondition: date is a valid Chrono::Date object
// Post-condition: Returns an integer corresponding to the days that have passed since the beginning of the Julian Period
{
        
    int jan_feb_adjust = (14 - m) / 12; // 1 for January and Febuary, otherwise 0
    int julian_year = y + 4800 - jan_feb_adjust; // a year value that starts in march
    int julian_month = m + 12 * jan_feb_adjust - 3;

    int days_since_march_1 = (153 * julian_month + 2) / 5; 

    return d + days_since_march_1 + (365*julian_year) + julian_year/4 - julian_year/100 + julian_year/400 - 32045;
}


int Date::days_since( Date date ) 
// Description: Returns the number of days between day_1 and day_2
// Precondition: day_1 and day_2 are valid Chrono::Date objects
// Post-condition: Returns an int corresponding to the difference in days between both dates
{

    return to_julian() - date.to_julian();

}


int Date::days_since_911( ) {
    return days_since( Date( sep, 11, 2001 ) );
}




// helper functions:

bool is_date(int y, Date::Month  m, int d)
{
    // assume that y is valid

    if (d<=0) return false; // d must be positive

    int days_in_month = 31; // most months have 31 days

    switch (m) {
        case Date::feb: // the length of February varies
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Date::apr: case Date::jun: case Date::sep: case Date::nov:
            days_in_month = 30; // the rest have 30 days
            break;
    }

    if (days_in_month<d) return false;

    return true;
} 


bool leapyear(int y)
{
    return ( ( y % 4 == 0 ) && ( ( y %  100 != 0 ) ||  (y % 400 != 0) ) );
}




bool operator==(const Date& a, const Date& b)
{
    return a.year()==b.year()
        && a.month()==b.month()
        && a.day()==b.day();
}


bool operator!=(const Date& a, const Date& b)
{
    return !(a==b);
}




ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() 
              << ')';
}


istream& operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
        is.clear(ios_base::failbit);                    // set the fail bit
        return is;
    }
    dd = Date(y,Date::Month(m),d);     // update dd
    return is;
}




enum Day {
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};




Day day_of_week(const Date& d)
{
    // ...
    return sunday;
}


Date next_Sunday(const Date& d)
{
    // ...
    return d;
}


Date next_weekday(const Date& d)
{
    // ...
    return d;
}






//--------------------------------------------------------------------------------------------






Time::Time( int h, int m, int s )
// Description: 24h format time constructor
// Precondition: h ( 0 <= h < 24 ), m ( 0 <= m < 60 ), and s ( 0 <= s < 60 ) are integers
// Postcondition: Chrono::Time object constructed for given inputs
{
    if (! is_time( h, m, s ) ) {
        throw Invalid();
    }

    hours = h;
    minutes = m;
    seconds = s;
    adjustAmPm();
}


Time::Time( int h, int m, int s, Time::AmPm am_pm )
// Description: 12h format Time Constructor
// Precondition: h ( 1 <= h <= 12 ), m ( 0 <= m < 60 ), and s ( 0 <= s < 60 ) are ints, am_pm is Time::AmPm enum type
// Postcondition: Chrono::Time object constructed for given inputs
{
    if ( h <= 0 ) {
        throw Invalid();
    }

    if ( am_pm == Time::Am && h == 12 ) {
        h = 0;
    }

    if ( am_pm == Time::Pm && h != 12 ) {
        h += 12;
    }

    if (am_pm == Time::Am && h >= 12 ) {
        throw Invalid();
    }

    if (! is_time( h, m, s ) ) {
        throw Invalid();
    }

    hours = h;
    minutes = m;
    seconds = s;
    meridian = am_pm;
}


Time::Time( ) : Time( 0, 0, 0 ) 
// Description: Default Time Constructor initalizes to (0, 0, 0)
// Precondition: None
// Postcondition: Time object is constructed and set to (0, 0, 0)
{ };




bool Time::adjustAmPm( )
// Description: Sets the the proper meridian based on the hour
// Precondition: hours is already initialized to it's proper value
// Postcondition: meridian is initialized to it's proper value based on hours
{
    if ( hours < 12 ) {
        meridian = Time::Am;
    }
    else {
        meridian = Time::Pm;
    }
}




void Time::display_24 ( ) 
// Description: Takes a Chrono::time object and displays it in 24 hour format
// Precondition: time is an initialized Chrono::Time object 
// Postcondition: time is displayed in 24 hour format, nothing is returned
{

    cout  << '(' 
          << hour()   << ',' 
          << setfill('0') << setw(2) << minute() << ',' 
          << setfill('0') << setw(2) <<  second() 
          << ')' 
          << endl;
}


void Time::display_12( ) 
// Description: Takes a Chrono::time object and displays it in 12 hour format
// Precondition: time is an initialized Chrono::Time object
// Postcondition: time is displayed in 12 hour format, nothing is returned
{

    // Convert AmPm to a useable string 
    string am_pm = ( ampm() == Time::Am ) ? "am" : "pm";

    // Adjust hours from 24 hour format to 12 hour format
    int hour_12 = hour() % 12;
    hour_12 = ( hour_12 == 0 ) ? 12 : hour_12;

    cout  << "(" 
          << hour_12 << ',' 
          << setfill('0') << setw(2) << minute() << ',' 
          << setfill('0') << setw(2) << second() 
          << ") " 
          << am_pm
          << endl;
}




bool is_time( int h, int m, int s )
// Description: Decides whether a given set of time parameters are valid
// Precondition: h, m, and s are ints representing a time's hours, minutes, and seconds respectively
// Postcondition: Returns true if the supplied parameters are valid, otherwise false
{
    return h >= 0 && h < 24 && 
           m >= 0 && m < 60 && 
           s >= 0 && s < 60;  
} 




bool operator==( const Time& a, const Time& b )
// Description: Overload of == for two Time objects, decides if two times are equal
// Precondition: a and b are intitialized Chrono::time objects
// Postcondition: returns true id a == b, otherwise false
{
    return a.hour() == b.hour()
        && a.minute() == b.minute()
        && a.second() == b.second();
}


bool operator!=( const Time& a, const Time& b )
// Description: Overload of != for two Time objects, decides if two times are unequal
// Precondition: a and b are intitialized Chrono::time objects
// Postcondition: returns false if a == b, otherwise true
{
    return !( a == b );
}




} // Chrono


