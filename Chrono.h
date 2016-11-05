
#include <iostream>
using namespace std;



namespace Chrono {


//-------------------------------------------------------------------------------------


class Date {
public:
    enum Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    class Invalid : public exception { 

        virtual const char* what() const throw() {
            return "Invalid arguments for Chrono::Date";
        }

    };

    Date(int y, Month m, int d);       // check for valid date and initialize
    Date( Month mm, int dd, int yy);
    Date();                            // default constructor
    
    // the default copy operations are fine

    // non-modifying operations:
    int   day()   const { return d; }
    Month month() const { return m; }
    int   year()  const { return y; }

    int   to_julian();
    int   days_since( Date date );
    int   days_since_911();

    // modifying operations:
    void add_day(int n);        
    void add_month(int n);
    void add_year(int n);

private:
    int   y;
    Month m;
    int   d;
};


bool is_date(int y, Date::Month m, int d); // true for valid date

bool leapyear(int y);                  // true if y is a leap year


bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);


//-------------------------------------------------------------------------------------


class Time {

public:

    enum AmPm { Am, Pm };

    class Invalid : public exception { 

        virtual const char* what() const throw() {
            return "Invalid arguments for Chrono::Time";
        }

    };

    Time( int h, int m, int s );       
    Time( int h, int m, int s, AmPm meridian );
    Time( );                            

    // non-modifying operations:
    int hour()    const { return hours; }
    int minute() const { return minutes; }
    int second() const { return seconds; }
    int ampm()    const { return meridian; }

    void display_12( );
    void display_24( );

    // modifying operations:
    bool adjustAmPm();

private:

    int hours;
    int minutes;
    int seconds;
    AmPm meridian;

};

bool operator==(const Time& a, const Time& b);

bool operator!=(const Time& a, const Time& b);

bool is_time( int h, int m, int s ); // true for valid time

//-------------------------------------------------------------------------------------


} // Chrono



