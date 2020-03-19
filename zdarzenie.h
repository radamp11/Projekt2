#ifndef ZDARZENIE_H
#define ZDARZENIE_H

#include <iostream>
#include <string>
#include <ctime>
#include "data.h"

using namespace std;

class Zdarzenie{
    private:
        string tresc;
        string dataDo;
        Data czasZdarz;
    public:
        //konstruktory
        Zdarzenie();
        Zdarzenie ( const string & tr, const string & datDo, const Data & dzisiaj );
        Zdarzenie ( const Zdarzenie & zdarz );

        //operatory sa przeciazone zarowno dla obiektow wlasnej klasy, jak i struktury tm z maina wskazujacej dzisiejsza date.
        //wyglada troche niewygodnie, bo te typy sa zupelnie rozne, ale pomoze to w pisaniu maina i shella
        //a takze w sprawdzaniu dat przy wypisywaniu zdarzen z konkretnego okresu

        Zdarzenie & operator=( const Zdarzenie & zdarz );
        bool operator==( const Zdarzenie & zdarz ) const;
        bool operator==( const string & str ) const;
        bool operator<( const Zdarzenie & zdarz ) const;
        bool operator>( const Zdarzenie & zdarz ) const;

        bool czyDzis ( const Data & dzisiaj);
        bool czyTaGodzina ( const Data & dzisiaj );
        bool czyBiezacyTydzien ( const Data & dzisiaj , const struct tm * dzis );
        bool czyTenMiesiac ( const Data & dzisiaj );
        bool czyTenRok ( const Data & dzisiaj );

        friend ostream & operator<<( ostream & os, const Zdarzenie & zdarz );

        ~Zdarzenie();
};

#endif // ZDARZENIE_H
