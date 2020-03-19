#include <iostream>
#include <ctime>
#include <algorithm>
#include <list>
#include <fstream>
#include "zdarzenie.h"
#include "powloka.h"
#include "terminarz.h"
#include "data.h"

using namespace std;

int main(){
    time_t czas;
    time( & czas );
    struct tm * aktualnyCzas = localtime( & czas );
    cout<<"siema"<<endl;
    Data teraz( aktualnyCzas );
    cout<<"siema"<<endl;
    Terminarz mojTerminarz;
    cout<<"siema"<<endl;
    wczytajDane( teraz, mojTerminarz );
    cout<<"siema"<<endl;

    powitanie();
    cout<<"siema"<<endl;

    int odp;

    do {
        wypiszMenu();
        cin>>odp;
        aktualizuj( aktualnyCzas );
        aktualizujObecnaDate( teraz, aktualnyCzas );

        switch ( odp ){
            case 1 :{
                dodajDoListy( teraz, mojTerminarz );
                break;
            }
            case 2 :{
                usunZdarzenie( mojTerminarz );
                break;
            }
            case 3 :{
                wypisz( mojTerminarz, teraz, aktualnyCzas );
                break;
            }
            case 4 :{
                cout<<"\nW Twoim Terminarzu jest juz "<<(mojTerminarz.ileZdarzen())<<" zdarzen."<<endl;
                break;
            }
            case 5 :{
                wypiszObecnaDate( teraz, aktualnyCzas );
                break;
            }
            case 6 :{
                instrukcja();
                break;
            }
            case 7 :{
                break;
            }
            default : {
                cout<<"\nPodales niepoprawna odpowiedz\n"<<endl;
                czyscBuff();
                break;
            };
        }
    }
    while ( odp != 7 );

    cout<<"### Do zobaczenia! ###"<<endl;
    zapiszDane( mojTerminarz );
    return 0;
}
