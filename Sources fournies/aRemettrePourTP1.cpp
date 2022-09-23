//
// Created by Mario Marchand
//

#include "DonneesGTFS.h"
#include <iostream>


using namespace std;


//! \brief ajoute les lignes dans l'objet GTFS
//! \param[in] p_nomFichier: le nom du fichier contenant les lignes
//! \throws logic_error si un problème survient avec la lecture du fichier
void DonneesGTFS::ajouterLignes(const std::string &p_nomFichier)
{
    //unordermap contenant les lignes ayant comme clé l'identifiant
    unordered_map<string, Ligne> t_lignes;
    //multimap des lignes ayant comme clé le # de la ligne
    multimap<string, Ligne> t_lignes_par_numero;

    //Objet de la classe ifstream Input file stream class
    ifstream ifsFichierTexte ("C:/Users/Jean-/Documents/TP1/TP1/RTC-1aout-25nov/routes.txt",ios_base::in);

    //Vérification que le fichier c'est ouvert
    if(ifsFichierTexte.is_open()) {
        //On ignore la première ligne
        string t_ligne_poubelle;
        getline(ifsFichierTexte, t_ligne_poubelle);
        //Objet string contenant les lignes
        string t_ligne_lecture;
        //Vector contenant les lignes stocké
        vector<string> t_vec_ligne;


        while (getline(ifsFichierTexte,t_ligne_lecture)) {
            t_vec_ligne = string_to_vector(t_ligne_lecture, ',');
            Ligne t_ligneC(t_vec_ligne [0], t_vec_ligne[2],t_vec_ligne[4], Ligne::couleurToCategorie(t_vec_ligne[7]));
            t_lignes.insert(pair<string,Ligne>(t_vec_ligne[0],t_ligneC));
            t_lignes_par_numero.insert(pair<string,Ligne>(t_vec_ligne[2],t_ligneC));
        }
        m_lignes_par_numero = t_lignes_par_numero;
        m_lignes = t_lignes;
                //On ferme le fichier
        ifsFichierTexte.close();
    }
    else{
        throw logic_error("Erreur le fichier n'a pas été trouvé !");
    }



}

//! \brief ajoute les stations dans l'objet GTFS
//! \param[in] p_nomFichier: le nom du fichier contenant les stations
//! \throws logic_error si un problème survient avec la lecture du fichier
void DonneesGTFS::ajouterStations(const std::string &p_nomFichier)
{
    //Vector contenant les lignes stocké
    vector<string> t_vec_ligne;
    //Map contenant les stations
    map<string, Station> t_stations;

    //Objet string contenant les lignes
    string t_ligne_lecture;

    //Objet de la classe ifstream Input file stream class
    ifstream ifsFichierTexte ("C:/Users/Jean-/Documents/TP1/TP1/RTC-1aout-25nov/stops.txt",ios_base::in);

    //Vérification que le fichier c'est ouvert
    if(ifsFichierTexte.is_open()) {
        //On ignore la première ligne
        string t_ligne_poubelle;
        getline(ifsFichierTexte,t_ligne_poubelle);

        //Boucle lisant le fichier
        while (getline(ifsFichierTexte,t_ligne_lecture)) {
            t_vec_ligne = string_to_vector(t_ligne_lecture, ',');
            Station t_stationC(t_vec_ligne[0],t_vec_ligne[2],t_vec_ligne[3], Coordonnees(stod(t_vec_ligne[4]),stod(t_vec_ligne[5])));
            t_stations.insert(pair<string,Station>(t_vec_ligne[0],t_stationC));
        }
        m_stations = t_stations;
    }
    else{
        throw logic_error("Erreur le fichier n'a pas été trouvé !");
    }


}

//! \brief ajoute les transferts dans l'objet GTFS
//! \breif Cette méthode doit âtre utilisée uniquement après que tous les arrêts ont été ajoutés
//! \brief les transferts (entre stations) ajoutés sont uniquement ceux pour lesquelles les stations sont prensentes dans l'objet GTFS
//! \brief les transferts sont ajoutés dans m_transferts
//! \brief les from_station_id des stations de m_transferts sont ajoutés dans m_stationsDeTransfert
//! \param[in] p_nomFichier: le nom du fichier contenant les station
//! \throws logic_error si un problème survient avec la lecture du fichier
//! \throws logic_error si tous les arrets de la date et de l'intervalle n'ont pas été ajoutés
void DonneesGTFS::ajouterTransferts(const std::string &p_nomFichier)
{

//écrire votre code ici

}


//! \brief ajoute les services de la date du GTFS (m_date)
//! \param[in] p_nomFichier: le nom du fichier contenant les services
//! \throws logic_error si un problème survient avec la lecture du fichier
void DonneesGTFS::ajouterServices(const std::string &p_nomFichier)
{

    //Objet de la classe ifstream Input file stream class
    ifstream ifsFichierTexte ("C:/Users/Jean-/Documents/TP1/TP1/RTC-1aout-25nov/calendar_dates.txt",ios_base::in);
    //Vérification que le fichier c'est ouvert
    if(ifsFichierTexte.is_open()) {
        //Conteneur de service
        unordered_set<string> t_services;
        //Vector contenant les lignes stocké
        vector<string> t_vec_ligne;
        //Objet string contenant les lignes
        string t_ligne_poubelle;
        string t_ligne_lecture;

        getline(ifsFichierTexte,t_ligne_poubelle);

        //Boucle lisant le fichier
        while (getline(ifsFichierTexte,t_ligne_lecture)) {
            t_vec_ligne = string_to_vector(t_ligne_lecture,',');

            Date t_date(stoul(t_vec_ligne[1].substr(0,4)),stoul(t_vec_ligne[1].substr(4, 2)),stoul(t_vec_ligne[1].substr(6,2)));
            if(t_vec_ligne[2]=="1" and t_date==m_date){
                t_services.insert(t_vec_ligne[0]);
            }

        }

        m_services = t_services;
    }else
    {
        cout<<"Erreur le fichier n'a pas été trouvé ! "<<endl;
    }


}

//! \brief ajoute les voyages de la date
//! \brief seuls les voyages dont le service est présent dans l'objet GTFS sont ajoutés
//! \param[in] p_nomFichier: le nom du fichier contenant les voyages
//! \throws logic_error si un problème survient avec la lecture du fichier
void DonneesGTFS::ajouterVoyagesDeLaDate(const std::string &p_nomFichier)
{
    //Objet de la classe ifstream Input file stream class
    ifstream ifsFichierTexte ("C:/Users/Jean-/Documents/TP1/TP1/RTC-1aout-25nov/trips.txt",ios_base::in);

    //Vérification que le fichier c'est ouvert
    if(ifsFichierTexte.is_open()) {
        //Conteneur de voyage
        map<string, Voyage> t_voyages;
        //Vector contenant les lignes stocké
        vector<string> t_vec_ligne;
        //Objet string contenant les lignes
        string t_ligne_poubelle;
        string t_ligne_lecture;

        getline(ifsFichierTexte,t_ligne_poubelle);

        //Boucle lisant le fichier
        while (getline(ifsFichierTexte,t_ligne_lecture)) {
            t_vec_ligne = string_to_vector(t_ligne_lecture,',');
            Voyage t_voyageC (t_vec_ligne [3],t_vec_ligne[0], t_vec_ligne[1],t_vec_ligne[4]);

            for(unordered_set<string>::iterator iter = m_services.begin(); iter != m_services.end(); iter++){
                if(t_vec_ligne[1]==*iter){
                    t_voyages.insert(pair<string,Voyage>(t_vec_ligne[3],t_voyageC));
                }
            }
            //t_voyages.insert(pair<string,Voyage>(t_vec_ligne[3],t_voyageC));
        }
        m_voyages = t_voyages;
    }
    else{ cout<<"Erreur le fichier n'a pas été trouvé ! "<<endl;}
}

//! \brief ajoute les arrets aux voyages présents dans le GTFS si l'heure du voyage appartient à l'intervalle de temps du GTFS
//! \brief Un arrêt est ajouté SSI son heure de départ est >= now1 et que son heure d'arrivée est < now2
//! \brief De plus, on enlève les voyages qui n'ont pas d'arrêts dans l'intervalle de temps du GTFS
//! \brief De plus, on enlève les stations qui n'ont pas d'arrets dans l'intervalle de temps du GTFS
//! \param[in] p_nomFichier: le nom du fichier contenant les arrets
//! \post assigne m_tousLesArretsPresents à true
//! \throws logic_error si un problème survient avec la lecture du fichier
void DonneesGTFS::ajouterArretsDesVoyagesDeLaDate(const std::string &p_nomFichier)
{
    //Objet de la classe ifstream Input file stream class
    ifstream ifsFichierTexte ("C:/Users/Jean-/Documents/TP1/TP1/RTC-1aout-25nov/stop_times.txt",ios_base::in);

    //Vérification que le fichier c'est ouvert
    if(ifsFichierTexte.is_open()) {
        //Conteneur de voyage
        map<string, Voyage> t_voyages;
        //Vector contenant les lignes stocké
        vector<string> t_vec_ligne;
        //Objet string contenant les lignes
        string t_ligne_poubelle;
        string t_ligne_lecture;

        getline(ifsFichierTexte,t_ligne_poubelle);

        //Boucle lisant le fichier
        while (getline(ifsFichierTexte,t_ligne_lecture)) {
            t_vec_ligne = string_to_vector(t_ligne_lecture,',');
            Heure t_heure_arrivee(stoul(t_vec_ligne[1].substr(0,2)),stoul(t_vec_ligne[1].substr(3,2)),stoul(t_vec_ligne[1].substr(6,2)));
            Heure t_heure_depart(stoul(t_vec_ligne[2].substr(0,2)),stoul(t_vec_ligne[2].substr(3,2)),stoul(t_vec_ligne[2].substr(6,2)));
            if(t_heure_depart>= m_now1 and t_heure_arrivee < m_now2) {
                Arret t_arret(t_vec_ligne[3], t_heure_arrivee, t_heure_depart, stoul(t_vec_ligne[4]), t_vec_ligne[0]);
                Arret::Ptr a_ptr = make_shared<Arret>(t_vec_ligne[3], t_heure_arrivee, t_heure_depart, stoul(t_vec_ligne[4]), t_vec_ligne[0]);
                m_voyages[t_vec_ligne[0]].ajouterArret(a_ptr);
            }
        }
    }
    else{
        cout<<"Erreur le fichier n'a pas été trouvé ! "<<endl;
    }
}



/* //Méthode parcourant chacune des parties d'une ligne
            int i = 0;
            size_t position = 0;
            size_t nextPosition = 0;
            while (i != 8) {

                nextPosition = t_ligneEn[0].find(',', position);
                if (i == 0) {
                    t_route_id = t_ligneEn[0].substr(position, nextPosition - position);
                    cout << "identifiant unique de la ligne d autobus : " << t_route_id << endl;
                };
                if (i == 2) {
                    t_route_short_name = t_ligneEn[0].substr(position, nextPosition - position);
                    cout << "numero de la ligne : " << t_route_short_name << endl;
                };
                if (i == 4) {
                    t_route_desc = t_ligneEn[0].substr(position, nextPosition - position);
                    cout << "texte decrivant la ligne : " << t_route_desc << endl;
                };
                if (i == 7) {
                    string t_str = t_ligneEn[0].substr(position, nextPosition - position);
                    t_str.erase(remove(t_str.begin(), t_str.end(), ' '), t_str.end());
                    t_route_color = Ligne::couleurToCategorie(t_str);
                    cout << "CategorieBus : " << Ligne::categorieToString(t_route_color) << endl;
                };

                position = nextPosition + 1;
                i++;
            }*/


