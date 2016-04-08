#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <set>
#include <map>
#include "point2d.h"
#include "town.h"
#include "algorithm"
using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";

/*
 * Study French isotoponyms
 */


int main()
{
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
    cout << "Error while reading file" << endl;
    return 2;
    }
    if (nb_towns == 0) {
    cout << "No town found" << endl;
    return 1;
    }
    // Say how many towns have been read
    cout << "File read in: "
     << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
     << towns.size() /* same as nb_towns */ << endl;
    cout << "First town in file: " << towns[0] << endl;

    /***************************************************************************************************/

    map<string, int> occurences_noms;
    map<Point2D, int> occurences_coord;

    set<Town> noms;
    set<Town> coordonnees;

    // Pour chaque nom, combien de fois il apparait
    for(vector<Town>::iterator it = towns.begin() ; it != towns.end() ; it++){
        occurences_noms[(*it).name()]+=1;
        occurences_coord[it->point()]+=1;

        if(occurences_noms[(*it).name()] > 1)
            noms.insert(*it);

        if(occurences_coord[it->point()] > 1)
            coordonnees.insert(*it);
    }

    /***************************************************************************************************/

    // Calcul de N et C

    int N = 0;
    int C = 0;

    for(map<string, int>::iterator it = occurences_noms.begin() ; it!= occurences_noms.end() ; it++){
        if((*it).second > 1)
            N++;
    }

    for(map<Point2D, int>::iterator it = occurences_coord.begin() ; it!= occurences_coord.end() ; it++){
        if(it->second > 1)
            C++;
    }

    cout<<"N = "<<N<<endl;
    cout<<"C = "<<C<<endl;

    /***************************************************************************************************/

    // Intersection (calculé en O(towns.size())) : je n'ai pas réussi à utiliser correctement set_intersection


    int n_c = 0;

    for(vector<Town>::iterator it = towns.begin() ; it != towns.end() ; it++){
        if(occurences_noms[(*it).name()] > 1 && occurences_coord[it->point()] > 1)
            n_c++;
    }

    cout<<"Nombre de villes ayant les deux propriétés = "<<n_c<<endl;

//    int size = min(noms.size(), coordonnees.size());
//    vector<Town> vect(size); <----------- Ne reconnaît pas ce constructeur!
//    vector<Town>::iterator end = set_intersection(noms.begin(), noms.end(), coordonnees.begin(), coordonnees.end(), vect.begin());
//    vect.resize(end-vect.begin());

    /***************************************************************************************************/


    // Histogramme des noms
    set<int> valeurs_possibles_noms;
    for(map<string, int>::iterator it = occurences_noms.begin() ; it!= occurences_noms.end() ; it++)
        valeurs_possibles_noms.insert((*it).second);


    vector< pair<int, int> > histogramme_noms;
    for(set<int>::iterator it = valeurs_possibles_noms.begin() ; it!= valeurs_possibles_noms.end() ; it++)
        histogramme_noms.push_back(pair<int, int>(*it, 0));

    for(vector< pair<int, int> >::iterator it_hist = histogramme_noms.begin() ; it_hist != histogramme_noms.end() ; it_hist++){
        for(map<string, int>::iterator it_nom = occurences_noms.begin() ; it_nom!= occurences_noms.end() ; it_nom++){
            if((*it_nom).second == (*it_hist).first)
                (*it_hist).second += 1;

        }
        cout<<"Nombre de noms apparaissant "<<(*it_hist).first<<" fois: "<<(*it_hist).second<<endl;
    }

    /***************************************************************************************************/


    // Histogramme des coordonnées
    set<int> valeurs_possibles_coord;
    for(map<Point2D, int>::iterator it = occurences_coord.begin() ; it!= occurences_coord.end() ; it++)
        valeurs_possibles_coord.insert((*it).second);

    vector< pair<int, int> > histogramme_coord;
    for(set<int>::iterator it = valeurs_possibles_coord.begin() ; it!= valeurs_possibles_coord.end() ; it++)
        histogramme_coord.push_back(pair<int, int>(*it, 0));

    for(vector< pair<int, int> >::iterator it_hist = histogramme_coord.begin() ; it_hist != histogramme_coord.end() ; it_hist++){
        for(map<Point2D, int>::iterator it_coord = occurences_coord.begin() ; it_coord!= occurences_coord.end() ; it_coord++){
            if((*it_coord).second == (*it_hist).first)
                (*it_hist).second += 1;

        }
        cout<<"Nombre de coordonnées apparaissant "<<(*it_hist).first<<" fois: "<<(*it_hist).second<<endl;
    }

    /***************************************************************************************************/



    // That's all folks
    return 0;
}
