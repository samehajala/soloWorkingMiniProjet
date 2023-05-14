#include"Simulation.h"
#include<chrono>
using namespace std ;
map<string , long> Simulation::executer(Bourse &bourse ,Trader& trader , Date dateDebut , Date dateFin,double solde )
{
    map<string,long> maSimulation;
    PorteFeuille porteFeuille(solde) ;
    Date datePrecedente ;
    Date dateCourante=dateDebut ;
    int NombreDesTransactionTotale=0 ;
    int NombreDesTransactionAcheter=0 ;
    int NombreDesTransactionVendre=0 ;
    int NombreDesTransactionRien=0 ;
    int NombreDesTransactionEchouees=0 ;
    int nombreJourFermee=0 ;
    int nombreGetActionsDisponibleParDate=0 ;
    double soldeTotal ;
    while(dateCourante<=dateFin)
    {

        cout<<dateCourante<<endl ;
        vector<string> actionsdisponiblesaujourdhui ;
        auto tStart = chrono::high_resolution_clock::now();
        actionsdisponiblesaujourdhui=bourse.getActionsDisponibleParDate(bourse.getDateCourante()) ;
         auto tEnd = chrono::high_resolution_clock::now();
         auto temps_ecoule = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count();
         maSimulation["tempsGetActionsDisponibleParDate"]+=temps_ecoule ;
        nombreGetActionsDisponibleParDate++ ;
        if(actionsdisponiblesaujourdhui.size()==0)
        {       cout<<"bonjour pas action "<<endl;
                nombreJourFermee++;
             dateCourante.passToNextDay() ;
             bourse.PasserALaJourneeSuivante() ;
        }
        else{
        int nombreTransactionParJour=0 ;
        Transaction transaction=trader.choisirTransaction(bourse,porteFeuille) ;
        if(transaction.getTypeTransaction()==Rien)
        {
            cout<<"Rien faire"<<endl  ;
            NombreDesTransactionRien++ ;
        }

        while((nombreTransactionParJour<100) && (transaction.getTypeTransaction()!=Rien))
        {
            if(transaction.getTypeTransaction()==Acheter)
            {

                Titre titreAchete(transaction.getNomAction(),transaction.getQuantite()) ;
                if(porteFeuille.getSolde()>=bourse.getPrixJournalierParDatePourUneAction(dateCourante,transaction.getNomAction())*titreAchete.getQuantite()&& bourse.getPrixJournalierParDatePourUneAction(dateCourante,transaction.getNomAction())!=0)
                {
                    cout<<"Achater\t"<<transaction.getNomAction()<<"\t"<<transaction.getQuantite()<<endl ;
                    porteFeuille.acheterTitre(titreAchete,bourse.getPrixJournalierParDatePourUneAction(dateCourante,transaction.getNomAction())*titreAchete.getQuantite()) ;
                    NombreDesTransactionAcheter++ ;

                }
                else
                {
                    cout<<"La Transaction  "<<"Achater\t"<<transaction.getQuantite()<<"\t"<<transaction.getNomAction()<<"\test impossible"<<endl ;
                    NombreDesTransactionEchouees++ ;
                }
            }
            else
            {
                cout<<"Vendre\t"<<transaction.getNomAction()<<"\t"<<transaction.getQuantite()<<endl ;
                Titre titreVendre(transaction.getNomAction(),transaction.getQuantite()) ;
                porteFeuille.vendreTitre(titreVendre,bourse.getPrixJournalierParDatePourUneAction(dateCourante,transaction.getNomAction())*titreVendre.getQuantite()) ;
                NombreDesTransactionVendre ++ ;



            }
            transaction=trader.choisirTransaction(bourse,porteFeuille) ;
            nombreTransactionParJour++ ;
            NombreDesTransactionTotale++ ;
        }
        }
        /*for(auto t:porteFeuille.getTitres())
        {
            soldeTotal+=t.getQuantite()*bourse.getDernierPrixDuneAction(dateFin,t.getNomAction()) ;
            cout<<"solde totale est "<<soldeTotal<<endl  ;
        }*/

        dateCourante.passToNextDay() ;
        bourse.PasserALaJourneeSuivante() ;


    }
       float soldeTotalAvantVendre = porteFeuille.getSolde();
        cout<<"solde avant vendre "<<soldeTotalAvantVendre<<endl ;
        for (auto t : porteFeuille.getTitres())
        {

            float prixVente = bourse.getDernierPrixDuneAction(dateFin, t.getNomAction()) *t.getQuantite() ;
            porteFeuille.vendreTitre(t, prixVente);
        }
        // Obtenir le solde total

        maSimulation["nombre Des Transactions Totales"]=NombreDesTransactionTotale ;
        maSimulation["NombreDesTransactionAcheter"]=NombreDesTransactionAcheter ;
        maSimulation["NombreDesTransactionEchouees"]=NombreDesTransactionEchouees;
        maSimulation["NombreDesTransactionVendre"]=NombreDesTransactionVendre ;
        maSimulation["solde"]=porteFeuille.getSolde();
        maSimulation["nombreGetActionsDisponibleParDate"]=nombreGetActionsDisponibleParDate ;
        maSimulation["moyenneGetActionParDate"]=maSimulation["tempsGetActionsDisponibleParDate"]/nombreGetActionsDisponibleParDate ;

        cout<<"bonjour je fais les statistiquer"<<endl;
return maSimulation ;
}
