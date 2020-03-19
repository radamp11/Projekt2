#include "terminarz.h"
#include "zdarzenie.h"
#include "powloka.h"

void Terminarz::dodajZdarzenie ( const Zdarzenie & zdarz ){
    if ( term.empty() )
        term.push_back( zdarz );
    else {
        list<Zdarzenie>::iterator iter = term.begin();
        if ( zdarz < *iter )
            term.push_front( zdarz );
            else {
                while ( iter != term.end() ){
                    if ( zdarz < *iter ){
                        term.insert ( iter, zdarz );
                        break;
                    }
                    ++iter;
                    if ( iter == term.end() )
                        term.push_back( zdarz );
                }
            }
        }
}

void Terminarz::drukujListe (){
    list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    while( iter != term.end() ){
        cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
        ++iter;
        ++i;
    }
}
void Terminarz::drukujTeraz ( const Data & dat ){
    list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    int licznikFalsz = 0;
    while( iter != term.end() ){
        if ( (*iter).czyTaGodzina( dat ) ){
            cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
            ++i;
        }
        else if ( i > 1 )
            ++licznikFalsz;
        if ( licznikFalsz >= 2 )
            break;
        ++iter;
    }
}

void Terminarz::drukujDzisiaj ( const Data & dat ){
        list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    int licznikFalsz = 0;
    while( iter != term.end() ){
        if ( (*iter).czyDzis( dat ) ){
            cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
            ++i;
        }
        else if ( i > 1 )
            ++licznikFalsz;
        if ( licznikFalsz >= 2 )
            break;
        ++iter;
    }
}

void Terminarz::drukujTydzien ( const Data & dat, const struct tm * dzisiaj ){
        list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    int licznikFalsz = 0;
    while( iter != term.end() ){
        if ( (*iter).czyBiezacyTydzien( dat, dzisiaj ) ){
            cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
            ++i;
        }
        else if ( i > 1 )
            ++licznikFalsz;
        if ( licznikFalsz >= 2 )
            break;
        ++iter;
    }
}

void Terminarz::drukujMiesiac ( const Data & dat ){
        list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    int licznikFalsz = 0;
    while( iter != term.end() ){
        if ( (*iter).czyTenMiesiac( dat ) ){
            cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
            ++i;
        }
        else if ( i > 1 )
            ++licznikFalsz;
        if ( licznikFalsz >= 2 )
            break;
        ++iter;
    }
}

void Terminarz::drukujRok ( const Data & dat ){
    list<Zdarzenie>::iterator iter = term.begin();
    int i = 1;
    int licznikFalsz = 0;
    while( iter != term.end() ){
        if ( (*iter).czyTenRok( dat ) ){
            cout<<"Zdarzenie "<<i<<": "<<(*iter)<<endl<<endl;
            ++i;
        }
        else if ( i > 1 )
            ++licznikFalsz;
        if ( licznikFalsz >= 2 )
            break;
        ++iter;
    }
}

bool Terminarz::puste ( ){
    return ( term.empty() );
}

int Terminarz::ileZdarzen() {
    return ( term.size() );
}

void Terminarz::sortuj (){
    term.sort();
}

bool Terminarz::usunZdarzenie( const string & tr ){
    list<Zdarzenie>::iterator iter = term.begin();
    while ( iter != term.end() ){
        if ( *iter == tr ){
            term.erase( iter );
            return true;
        }
        else
            ++iter;
    }
    return false;
}

list<Zdarzenie>::iterator Terminarz::poczatek ( ){
   return ( term.begin() );
}

list<Zdarzenie>::iterator Terminarz::koniec ( ){
    return ( term.end() );
}

Terminarz::Terminarz(){}

Terminarz::~Terminarz(){}
