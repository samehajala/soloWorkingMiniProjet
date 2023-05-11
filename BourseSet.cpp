#include"BourseSet.h"
#include <bits/stdc++.h>
vector<string> BourseSet::getActionsDisponibleParDate(const Date& dateEntree) const {
    vector<string> actions;

    if(dateEntree > dateDuJour) {
        return actions;
    }

    PrixJournalier recherchePrix(dateEntree) ;

    auto it = Historique.lower_bound(recherchePrix);
    while (it != Historique.end() && it->getDate() == dateEntree && it->getDate() <= dateDuJour) {
        actions.push_back(it->getNomAction());
        ++it;
    }

    return actions;
}
/*
vector<string> BourseSet::getActionsDisponibleParDate(const Date& dateEntree) const {
    vector<string> actions;

    if(dateEntree>dateDuJour)
    {
        return actions ;
    }
    for(auto pj=Historique.begin();pj!= Historique.end();++pj)
    {
        if(pj->getDate()==dateEntree && (pj->getDate()<dateDuJour || pj->getDate()==dateDuJour) ){
            actions.push_back(pj->getNomAction()) ;

        }
    }

    return actions;
}*/
vector<PrixJournalier> BourseSet::getPrixJournalierParDate(const Date& dateEntree) const  {
    vector<PrixJournalier> prixJournaliers;
   if(dateEntree > dateDuJour) {
        return prixJournaliers ;
    }

    PrixJournalier recherchePrix(dateEntree) ;

    auto it = Historique.lower_bound(recherchePrix);
    while (it != Historique.end() && it->getDate() == dateEntree && it->getDate() <= dateDuJour) {
        prixJournaliers.push_back(*it);
        ++it;
    }
    return prixJournaliers;
}
/*
vector<PrixJournalier> BourseSet::getPrixJournalierParDate(const Date& dateEntree) const  {
    vector<PrixJournalier> prixJournaliers;
    if(dateEntree>dateDuJour)
    {
        return prixJournaliers ;
    }
    for (auto pj=Historique.begin();pj!=Historique.end();++pj) {
        if (pj->getDate() == dateEntree) {
            prixJournaliers.push_back(*pj);
        }
    }
    return prixJournaliers;
}*/
float BourseSet::getPrixJournalierParDatePourUneAction(const Date& dateEntree ,const string& nomAction  ) const
{
    float PrixU=0.0;
    vector<PrixJournalier> prixJournaliers;
    for (auto pj=Historique.begin();pj!=Historique.end();++pj)
    {
        if (pj->getDate() == dateEntree)
        {
            prixJournaliers.push_back(*pj);
        }
    }
    if(dateEntree>dateDuJour)
    {
        return PrixU ;
    }
    for(auto pj=Historique.begin();pj!=Historique.end();++pj)
    {
        if(pj->getDate()==dateEntree && pj->getNomAction()==nomAction)
        {
            PrixU=pj->getPrix() ;
        }
    }
    return PrixU ;
}
void BourseSet::PasserALaJourneeSuivante()
{
    dateDuJour.passToNextDay() ;
}

