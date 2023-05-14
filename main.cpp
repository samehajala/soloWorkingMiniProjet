#include <iostream>
#include"Date.h"
#include"PersistancePrixJournaliers.h"
#include"PrixJournalier.h"
#include"BourseVector.h"
#include<map>
#include"Transaction.h"
#include"TraderAleatoire.h"
#include<string>
#include"Titre.h"
#include <ctime>
#include"BourseSet.h"
#include"Simulation.h"
#include"BourseMultiMap.h"
#include<chrono>
#include<set>
using namespace std;

int main()
{
    auto tStart = chrono::high_resolution_clock::now();
    srand(time(nullptr));//time(nullptr)
     PersistancePrixJournaliers pers ;
    vector<PrixJournalier> prixJour ;
    prixJour=pers.lirePrixJournaliersDUnFichier("prices.csv") ;
    cout<<"La taille de votre fichier csv est:\t"<<prixJour.size()<<endl ;
    set<PrixJournalier> prixJourSet;
    for(auto pj=prixJour.begin();pj!=prixJour.end();++pj)
    {
        prixJourSet.insert(*pj) ;
    }
    multimap<Date,PrixJournalier>  prixJourMultiMap ;
    for(auto pj=prixJour.begin();pj!=prixJour.end();++pj )
    {
        prixJourMultiMap.insert(make_pair(pj->getDate(),*pj)) ;
    }

    Date d1(4,1,2010);
     BourseVector bourse(d1,prixJour) ;
     BourseSet bourseset(d1,prixJourSet) ;
     BourseMultiMap bourseMultiMap(d1,prixJourMultiMap) ;
    cout<<"date debut simulation"<<bourse.getDateCourante()<<endl ;

    vector<Titre> titres ;

    PorteFeuille p ;
    TraderAleatoire TA ;
    Transaction tx ;
    Simulation maSimulation ;
    Date d3(6,9,2010) ;
    map<string,long> statistiquesSimulation ;
    int choix ;
    cout<<"entrer votre choix de Bourse  "<< endl ;
    cin>>choix ;
    if(choix==1)
     {
        statistiquesSimulation=Simulation::executer(bourseset,TA,d1,d3,1000) ;
        cout<<"on a fini la Simulation avec succes et voici les statistiques "<<endl ;
        cout<<"Le nombre total des transactions est:\t"<<statistiquesSimulation["nombre Des Transactions Totales"]<<endl ;
        cout<<"Le nombre des actions acheter est:\t"<<statistiquesSimulation["NombreDesTransactionAcheter"]<<endl ;
        cout<<"Le nombre des actions qui ont echouees est:\t"<<statistiquesSimulation["NombreDesTransactionEchouees"]<<endl ;
        cout<<"Le nombre des actions Vendre est:\t"<<statistiquesSimulation["NombreDesTransactionVendre"]<<endl ;
        cout<<"Le solde final est:\t"<<statistiquesSimulation["solde"]<<endl ;
        cout<<"nbr de getaction est \t"<<statistiquesSimulation["nombreGetActionsDisponibleParDate"]<<endl ;
        cout<<"temps de getAction est \t"<<statistiquesSimulation["tempsGetActionsDisponibleParDate"]<<endl ;
        cout<<"moyenne de getAction est \t"<<statistiquesSimulation["moyenneGetActionParDate"]<<endl ;
     }
    else if (choix==2)
    {
        statistiquesSimulation=Simulation::executer(bourse,TA,d1,d3,1000) ;
        cout<<"on a fini la Simulation avec succes et voici les statistiques "<<endl ;
        cout<<"Le nombre total des transactions est:\t"<<statistiquesSimulation["nombre Des Transactions Totales"]<<endl ;
        cout<<"Le nombre des actions acheter est:\t"<<statistiquesSimulation["NombreDesTransactionAcheter"]<<endl ;
        cout<<"Le nombre des actions qui ont echouees est:\t"<<statistiquesSimulation["NombreDesTransactionEchouees"]<<endl ;
        cout<<"Le nombre des actions Vendre est:\t"<<statistiquesSimulation["NombreDesTransactionVendre"]<<endl ;
        cout<<"Le solde final est:\t"<<statistiquesSimulation["solde"]<<endl ;
        cout<<"nbr de getaction est \t"<<statistiquesSimulation["nombreGetActionsDisponibleParDate"]<<endl ;
        cout<<"temps de getAction est \t"<<statistiquesSimulation["tempsGetActionsDisponibleParDate"]<<endl ;
        cout<<"moyenne de getAction est \t"<<statistiquesSimulation["moyenneGetActionParDate"]<<endl ;
    }
    else
    {
        statistiquesSimulation=Simulation::executer(bourseMultiMap,TA,d1,d3,1000) ;
        cout<<"on a fini la Simulation avec succes et voici les statistiques "<<endl ;
        cout<<"Le nombre total des transactions est:\t"<<statistiquesSimulation["nombre Des Transactions Totales"]<<endl ;
        cout<<"Le nombre des actions acheter est:\t"<<statistiquesSimulation["NombreDesTransactionAcheter"]<<endl ;
        cout<<"Le nombre des actions qui ont echouees est:\t"<<statistiquesSimulation["NombreDesTransactionEchouees"]<<endl ;
        cout<<"Le nombre des actions Vendre est:\t"<<statistiquesSimulation["NombreDesTransactionVendre"]<<endl ;
        cout<<"Le solde final est:\t"<<statistiquesSimulation["solde"]<<endl ;
        cout<<"nbr de getaction est \t"<<statistiquesSimulation["nombreGetActionsDisponibleParDate"]<<endl ;
        cout<<"temps de getAction est \t"<<statistiquesSimulation["tempsGetActionsDisponibleParDate"]<<endl ;
        cout<<"moyenne de getAction est \t"<<statistiquesSimulation["moyenneGetActionParDate"]<<endl ;
    }
    auto tEnd = chrono::high_resolution_clock::now();
    double temps_ecoule = chrono::duration<double, milli>(tEnd - tStart).count();
    cout << "La mesure du temps d'execution est de " << temps_ecoule << "milli secondes . " << endl;
    return 0;
}
