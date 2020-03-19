#ifndef DATA_H
#define DATA_H

#include <iostream>

using namespace std;

class Data{
    private:
        static const int NIC = -123;
        static const int DODAJ_ROK = 1900;
        static const int DODAJ_MIES = 1;
        int godzina;
        int minuta;
        int dzien;
        int mies;
        int rok;
    public:
        Data();
        Data( const struct tm * dzis );     //data dzisiejsza, terazniejsza
        Data( int dz, int mi, int r, int godz, int minutka );
        Data( const Data & dat );
        ~Data();

        int podajGodzine () const;
        int podajMinute () const;
        int podajDzien () const;
        int podajMiesiac () const;
        int podajRok () const;
        int zwrocNIC () const;

        Data & operator=( const Data & dat );
        bool operator==( const Data & dat ) const;
        bool operator<( const Data & dat ) const;
        bool operator>( const Data & dat ) const;

        friend ostream & operator<<( ostream & os , const Data & dat );
};

#endif // DATA_H
