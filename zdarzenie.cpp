#include "zdarzenie.h"
#include "data.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>

Zdarzenie::Zdarzenie(){
    tresc = "nic";
    dataDo = "nic";
    Data tymcz;
    czasZdarz = tymcz;
}

static const int BRAK = -44;

static int jakiMiesiac ( const string & str ){
    int mie = BRAK;
    if ( str.find("sty") != string::npos || str.find("styczen") != string::npos || str.find("stycznia") != string::npos )
        mie = 1;
    else if ( str.find("lut") != string::npos || str.find("luty") != string::npos || str.find("lutego") != string::npos )
        mie = 2;
    else if ( str.find("mar") != string::npos || str.find("marzec") != string::npos || str.find("marca") != string::npos )
        mie = 3;
    else if ( str.find("kwi") != string::npos || str.find("kwiecien") != string::npos || str.find("kwietnia") != string::npos )
        mie = 4;
    else if ( str.find("maj") != string::npos || str.find("maja") != string::npos )
        mie = 5;
    else if ( str.find("czer") != string::npos || str.find("czerwiec") != string::npos || str.find("czerwca") != string::npos || str.find("cze") != string::npos )
        mie = 6;
    else if ( str.find("lip") != string::npos || str.find("lipiec") != string::npos || str.find("lipca") != string::npos )
        mie = 7;
    else if ( str.find("sie") != string::npos || str.find("sierpien") != string::npos || str.find("sierpnia") != string::npos )
        mie = 8;
    else if ( str.find("wrz") != string::npos || str.find("wrzesien") != string::npos || str.find("wrzesnia") != string::npos )
        mie = 9;
    else if ( str.find("paz") != string::npos || str.find("pazdziernik") != string::npos || str.find("pazdziernika") != string::npos )
        mie = 10;
    else if ( str.find("lis") != string::npos || str.find("listopad") != string::npos || str.find("listopada") != string::npos )
        mie = 11;
    else if ( str.find("gru") != string::npos || str.find("grudzien") != string::npos || str.find("grudnia") != string::npos )
        mie = 12;
    return mie;
}

static bool czyGodzina ( const string & str ){
    if ( str.find("godzina") != string::npos || str.find("godziny") != string::npos || str.find("godz") != string::npos )
        return true;
    return false;
}
//stale dodawane do przypisywania dzisijeszej daty. Wynika z dzia³ania funkcji localtime

Zdarzenie::Zdarzenie( const string & tr, const string & daDo , const Data & dzisiaj ){
    tresc = tr;

    string nowy = daDo;
    transform ( nowy.begin(), nowy.end(), nowy.begin(), ::tolower );

    if ( nowy.find( "do" ) != string::npos ) {      //sprawdzenie jaki rodzaj daty wprowadzono
        dataDo = nowy;                              //jesli data "do" , po prostu przypisz zeby potem wyswietlic w takiej formie jak wpisano
        nowy.erase( nowy.find("do") , 2 );          //i usun zbedne znaki
    }
    else
        dataDo = "nic";     //nie wypisuj takiej daty

    string tekst;
    string liczby;
    int dl = nowy.size();

    for ( int i = 0; i < dl; ++i ){
        if ( isdigit(nowy[i]) )
            liczby += nowy[i];
        else if ( nowy[i] != ' ' && nowy[i] != '.' && nowy[i] != ',' && nowy[i] != ':' && nowy[i] != ';' && nowy[i] != '/')
            tekst += nowy[i];
    }
    int dlLiczby = liczby.size();

    int godz_;
    int minuta_;
    int dzien_;
    int mies_;
    int rok_;
        //przypadek 1 : podano slownie godzine, a miesiaca w ogole
        if ( czyGodzina( tekst ) && jakiMiesiac( tekst ) == BRAK && dlLiczby == 4 ){
            //cout<<"war 1"<<endl;
            godz_ = atoi( (liczby.substr( 0, 2 )).c_str() );
            minuta_ = atoi( (liczby.substr( 2, 2 )).c_str() );
            //domyslnie ustawienie reszty skladowych na "dzisiaj"
            dzien_ = dzisiaj.podajDzien();
            mies_ = dzisiaj.podajMiesiac();
            rok_ = dzisiaj.podajRok();
        }
        //przypadek 2: podano sama godzine - potrzebne zaznaczenie, ze jest to godzina, a nie dzien miesiaca
        else if ( czyGodzina( tekst ) && jakiMiesiac( tekst ) == BRAK && dlLiczby == 4 ) {
            //cout<<"war 2"<<endl;
            godz_ = atoi ( (liczby.substr(0,2)).c_str() );
            minuta_ = atoi ( (liczby.substr(2,2)).c_str() );
            //reszta ustawona na "dzisiaj"
            dzien_ = dzisiaj.podajDzien();
            mies_ = dzisiaj.podajMiesiac();
            rok_ = dzisiaj.podajRok();
        }
        //przypadek 3: podano sama date bez roku - brak zaznaczenia, ze jest to godzina
        else if ( !(czyGodzina( tekst )) && jakiMiesiac( tekst ) == BRAK && dlLiczby == 4 ) {
            //cout<<"war 3"<<endl;
            dzien_ = atoi ( (liczby.substr(0,2)).c_str() );
            mies_ = atoi ( (liczby.substr(2,2)).c_str() );
            godz_ = dzisiaj.zwrocNIC();
            minuta_ = dzisiaj.zwrocNIC();
            rok_ = dzisiaj.podajRok();
        }
        //przypadek 4 : date podano numerami, a godzine za data
        else if ( jakiMiesiac( tekst ) == BRAK && dlLiczby == 12 ){
            //cout<<"war 4"<<endl;  //podano slowo godzina oraz date cyframi
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = atoi ( (liczby.substr( 2, 2 )).c_str() );
            rok_ = atoi ( (liczby.substr( 4, 4 )).c_str() );
            godz_ = atoi ( (liczby.substr( 8, 2 )).c_str() );
            minuta_ = atoi ( (liczby.substr( 10, 2 )).c_str() );
        }
        //przypadek 5: podano pelna date, ale miesiac podano slownie
        else if ( jakiMiesiac( tekst ) != BRAK && dlLiczby == 10 ){
            //cout<<"war 5"<<endl;
            //cout<<"powstal taki ciag liczb: "<<endl<<liczby<<endl;
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = jakiMiesiac( tekst );
            rok_ = atoi ( (liczby.substr( 2, 4 )).c_str() );
            godz_ = atoi ( (liczby.substr( 6, 2 )).c_str() );
            minuta_ = atoi ( (liczby.substr( 8, 2 )).c_str() );
            //cout<<"wczytano:\ndzien: "<<czasZdarz.dzien<<"\nmies: "<<czasZdarz.mies<<"\nrok: "<<czasZdarz.rok<<"\ngodzina: "<<czasZdarz.godzina<<"\nminuta: "<<czasZdarz.minuta<<endl;
        }
        //przypadek 6: podano dzien, miesiac slownie, np 15 kwietnia; rok domyslnie na obecny, godzina - nieznana
        else if ( dlLiczby == 2 && jakiMiesiac( tekst ) != BRAK ){
            //cout<<"war 6"<<endl;   //podano sam miesiac bez godziny
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = jakiMiesiac( tekst );
            rok_ = dzisiaj.podajRok();
            godz_ = dzisiaj.zwrocNIC();
            minuta_ = dzisiaj.zwrocNIC();
        }
        //przypadek 7: taki jak poprzedni tylko podano tez rok
        else if ( dlLiczby == 6 && jakiMiesiac( tekst ) != BRAK && !(czyGodzina( tekst )) ){
            //cout<<"war 7"<<endl;
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = jakiMiesiac( tekst );
            rok_ = atoi ( (liczby.substr( 2, 4 )).c_str() );
            godz_ = dzisiaj.zwrocNIC();
            minuta_ = dzisiaj.zwrocNIC();
        }
        //przypadek 8: podano slownie miesiac oraz godzine, bez roku
        else if ( dlLiczby == 6 && jakiMiesiac( tekst ) != BRAK && czyGodzina( tekst ) ){
            //cout<<"war 8"<<endl;
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = jakiMiesiac( tekst );
            rok_ = dzisiaj.podajRok();
            godz_ = atoi ( (liczby.substr( 2, 2 )).c_str() );
            minuta_ = atoi ( (liczby.substr( 4, 2 )).c_str() );
        }
        //przypadek 9: podano tylko date, tylko cyframi
        else if ( dlLiczby == 8 && jakiMiesiac( tekst ) == BRAK ){
            //cout<<"war 9"<<endl;
            dzien_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
            mies_ = atoi ( (liczby.substr( 2, 2 )).c_str() );
            rok_ = atoi ( (liczby.substr( 4, 4 )).c_str() );
            godz_ = dzisiaj.zwrocNIC();
            minuta_ = dzisiaj.zwrocNIC();
        }
        //przypadek 10: podano slowo "dzisiaj"
        else if ( tekst.find("dzisiaj") != string::npos || tekst.find("dzis") != string::npos){
            //cout<<"war 10"<<endl;
            if ( liczby.empty() ){
                godz_ = dzisiaj.zwrocNIC();
                minuta_ = dzisiaj.zwrocNIC();
            }
            else {
                godz_ = atoi ( (liczby.substr( 0, 2 )).c_str() );
                minuta_ = atoi ( (liczby.substr( 2, 2 )).c_str() );
            }
            dzien_ = dzisiaj.podajDzien();
            mies_ = dzisiaj.podajMiesiac();
            rok_ = dzisiaj.podajRok();
        }
        else {
            cerr<<"NIE UDALO SIE UTWORZYC ZDARZENIA. SPRAWDZ KONSTRUKTOR.\n";
            exit(EXIT_FAILURE);
        }
    Data tymcz( dzien_, mies_, rok_, godz_, minuta_ );
    czasZdarz = tymcz;
}

Zdarzenie::Zdarzenie( const Zdarzenie & zdarz ){
    tresc = zdarz.tresc;
    dataDo = zdarz.dataDo;
    czasZdarz = zdarz.czasZdarz;
}

Zdarzenie::~Zdarzenie(){
}

Zdarzenie & Zdarzenie::operator=( const Zdarzenie & zdarz ){
    tresc = zdarz.tresc;
    dataDo = zdarz.dataDo;
    czasZdarz = zdarz.czasZdarz;
    return *this;
}
//czy ta sama data
bool Zdarzenie::operator==( const Zdarzenie & zdarz ) const{
    if ( czasZdarz == zdarz.czasZdarz )
        return true;
   else
    return false;
}

bool Zdarzenie::operator==( const string & str ) const{
    if ( tresc == str )
        return true;
    else
        return false;
}
//porownywanie - rzecz jasna - wzgledem daty. Operator niezbedny do sortowania listy
bool Zdarzenie::operator<( const Zdarzenie & zdarz ) const{
   if ( czasZdarz < zdarz.czasZdarz )
        return true;
   return false;
}

bool Zdarzenie::operator>( const Zdarzenie & zdarz ) const{
    return ( !( *this < zdarz) && !( *this == zdarz ));
}

bool Zdarzenie::czyDzis ( const Data & dzisiaj ){
    if ( czasZdarz.podajRok() == dzisiaj.podajRok() && czasZdarz.podajMiesiac() == dzisiaj.podajMiesiac() && czasZdarz.podajDzien() == dzisiaj.podajDzien() )
        return true;
   else
        return false;
}
//rzecz jasna chodzi tylko o skladowa gdzina, czyli dla godziny 17 wyswietla zarowno 17:00 jak i 17:42
bool Zdarzenie::czyTaGodzina ( const Data & dzisiaj ){
    if ( czyDzis( dzisiaj ) && czasZdarz.podajGodzine() == dzisiaj.podajGodzine() )
        return true;
   else
        return false;
}

static const int iloscDni[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool Zdarzenie::czyBiezacyTydzien ( const Data & dzisiaj , const struct tm * dzis ){
    if ( czasZdarz.podajRok() != dzisiaj.podajRok() )
        return false;

    int roznicaMies = czasZdarz.podajMiesiac() - dzisiaj.podajMiesiac();
    if ( roznicaMies > 1 )
        return false;
    //int czyLutyPrzestepny = 0;
    /*if ( czasZdarz.mies == 2 && czasZdarz.rokPrzestepny == true )
        czyLutyPrzestepny = 1;*/
    int pozostaleDniTyg = 7 - dzis->tm_wday;
    int roznicaDni = czasZdarz.podajDzien() - dzisiaj.podajDzien();
    int roznicaDniMax = iloscDni[ dzisiaj.podajMiesiac() ] - pozostaleDniTyg;

    if ( (roznicaDni <= pozostaleDniTyg && roznicaDni >= 0 && roznicaMies == 0 ) || ( roznicaDni < 0 && roznicaDni >= roznicaDniMax && roznicaMies == 1 ))
        return true;
    else
        return false;
}

bool Zdarzenie::czyTenMiesiac ( const Data & dzisiaj ){
    if ( czasZdarz.podajRok() == dzisiaj.podajRok() && czasZdarz.podajMiesiac() == dzisiaj.podajMiesiac() )
        return true;
    else
        return false;
}

bool Zdarzenie::czyTenRok ( const Data & dzisiaj ){
    if ( czasZdarz.podajRok() == dzisiaj.podajRok() )
        return true;
    else
        return false;
}

ostream & operator<<( ostream & os, const Zdarzenie & zdarz ){
    os<<zdarz.tresc<<endl;
    if ( zdarz.dataDo != "nic" ){
        os<<zdarz.dataDo;
    }
    else{
        os<<zdarz.czasZdarz;
    }
    return os;
}
