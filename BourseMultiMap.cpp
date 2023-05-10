#include"BourseMultiMap.h"
vector<string> BourseMultiMap::getActionsDisponibleParDate(const Date& dateEntree) const {
    vector<string> actions;
    if(dateEntree>dateDuJour)
    {
        return actions ;
    }
    for(auto const& element :Historique)
    {
        if((element.second).getDate()==dateEntree && ((element.second).getDate()<dateDuJour || (element.second).getDate()==dateDuJour) ){
            actions.push_back((element.second).getNomAction()) ;

        }
    }

    return actions;
}
vector<PrixJournalier> BourseMultiMap::getPrixJournalierParDate(const Date& dateEntree) const  {
    vector<PrixJournalier> prixJournaliers;
    if(dateEntree>dateDuJour)
    {
        return prixJournaliers ;
    }
    for (auto const& element :Historique) {
        if ((element.second).getDate() == dateEntree) {
            prixJournaliers.push_back(element.second);
        }
    }
    return prixJournaliers;
}
float BourseMultiMap::getPrixJournalierParDatePourUneAction(const Date& dateEntree ,const string& nomAction  ) const
{
    float PrixU=0.0;
    vector<PrixJournalier> prixJournaliers;
    for (auto const& element :Historique)
    {
        if ((element.second).getDate() == dateEntree)
        {
            prixJournaliers.push_back(element.second);
        }
    }
    if(dateEntree>dateDuJour)
    {
        return PrixU ;
    }
    for(auto const& element :Historique)
    {
        if((element.second).getDate()==dateEntree && (element.second).getNomAction()==nomAction)
        {
            PrixU=(element.second).getPrix() ;
        }
    }
    return PrixU ;
}
void BourseMultiMap::PasserALaJourneeSuivante()
{
    dateDuJour.passToNextDay() ;
}
