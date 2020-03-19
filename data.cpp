#include "data.h"

Data::Data(){
    godzina = NIC;
    minuta = NIC;
    dzien = NIC;
    mies = NIC;
    rok = NIC;
}

Data::Data ( const struct tm * dzis ){ //konstruktor domyslny ustawia date na dzisiaj
    godzina = dzis->tm_hour;
    minuta = dzis->tm_min;
    dzien = dzis->tm_mday;
    mies = dzis->tm_mon + DODAJ_MIES;
    rok = dzis->tm_year + DODAJ_ROK;
}

Data::Data( int dz, int mi, int r, int godz, int minutka ){
    dzien = dz;
    mies = mi;
    rok = r;
    godzina = godz;
    minuta = minutka;
}

Data::Data( const Data & dat ){
    godzina = dat.godzina;
    minuta = dat.minuta;
    dzien = dat.dzien;
    mies = dat.mies;
    rok = dat.rok;
}

Data::~Data(){};

Data & Data::operator=( const Data & dat ){
    godzina = dat.godzina;
    minuta = dat.minuta;
    dzien = dat.dzien;
    mies = dat.mies;
    rok = dat.rok;
    return *this;
}
bool Data::operator==( const Data & dat ) const{
    bool wynik = false;
    if ( godzina == dat.godzina && minuta == dat.minuta && dzien == dat.dzien && mies == dat.mies && rok == dat.rok )
        wynik = true;
    return wynik;
}

bool Data::operator<( const Data & dat ) const{
    if ( rok < dat.rok )
        return true;
    else if ( rok > dat.rok )
        return false;
    else if ( mies < dat.mies )
        return true;
    else if ( mies > dat.mies )
        return false;
    else if ( dzien < dat.dzien )
        return true;
    else if ( dzien > dat.dzien )
        return false;
    else if ( godzina < dat.godzina )
        return true;
    else if ( godzina > dat.godzina )
        return false;
    else if ( minuta < dat.minuta )
        return true;
    else if ( minuta > dat.minuta )
        return false;
    else
        return false;
}

bool Data::operator>( const Data & dat ) const {
    return ( !( *this < dat ) && !( *this == dat ) );
}

int Data::podajGodzine () const{
    int g = godzina;
    return g;
}
int Data::podajMinute () const{
    int m = minuta;
    return m;
}
int Data::podajDzien () const{
    int d = dzien;
    return d;
}
int Data::podajMiesiac () const{
    int mi = mies;
    return mi;
}
int Data::podajRok () const{
    int r = rok;
    return r;
}
int Data::zwrocNIC () const{
    int nicc = NIC;
    return nicc;
}

ostream & operator<<( ostream & os , const Data & dat ){
    os<<"Czas: ";
    if ( dat.dzien < 10 )
        os<<'0';
    os<<dat.dzien<<"/";
    if ( dat.mies < 10 )
        os<<'0';
    os<<dat.mies<<"/"<<dat.rok;
    if ( dat.godzina != dat.NIC ){
        os<<", godzina ";
        if ( dat.godzina < 10 )
            os<<'0';
        os<<dat.godzina<<":";
        if ( dat.minuta < 10 )
            os<<'0';
        os<<dat.minuta;
    }
    return os;
}
