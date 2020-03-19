#ifndef TERMINARZ_H
#define TERMINARZ_H

#include "zdarzenie.h"
#include <list>
#include <iostream>
#include <fstream>

class Terminarz {
    private:
        list<Zdarzenie> term;
    public:
        Terminarz();
        ~Terminarz();
        void dodajZdarzenie ( const Zdarzenie & zdarz );
        bool puste ();
        int ileZdarzen ();
        void sortuj();
        bool usunZdarzenie ( const string & tr );
        list<Zdarzenie>::iterator poczatek ();
        list<Zdarzenie>::iterator koniec ();

        void drukujListe ();
        void drukujTeraz ( const Data & dat );
        void drukujDzisiaj ( const Data & dat );
        void drukujTydzien ( const Data & dat, const struct tm * dzisiaj );
        void drukujMiesiac ( const Data & dat );
        void drukujRok ( const Data & dat );
};

#endif // TERMINARZ_H
