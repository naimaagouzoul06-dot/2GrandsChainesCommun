#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;

// Fonction pour trouver la plus grande sous-chaîne commune entre deux chaînes
string plusGrandeSousChaineCommune(const string& s1, const string& s2) {
    string plusLongue = "";

    for (size_t i = 0; i < s1.length(); ++i) {
        for (size_t j = i + 1; j <= s1.length(); ++j) {
            string sousChaine = s1.substr(i, j - i);

            if (s2.find(sousChaine) != string::npos) {
                if (sousChaine.length() > plusLongue.length()) {
                    plusLongue = sousChaine;
                }
            }
        }
    }
    return plusLongue;
}

int main() {
    string chemin = "computer.txt";

    // Vérification de l'existence du fichier
    if (!filesystem::exists(chemin)) {
        cout << "ERREUR : Le fichier 'mots10.txt' n'existe pas." << endl;
        return 1;
    }

    ifstream fichier(chemin);
    if (!fichier) {
        cout << "ERREUR : Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    vector<string> vecteurMots;
    string motLu;

    while (fichier >> motLu) {
        vecteurMots.push_back(motLu);
    }
    fichier.close();

    if (vecteurMots.size() < 2) {
        cout << "ERREUR : Le fichier doit contenir au moins 2 mots." << endl;
        return 1;
    }

    vector<string> sousChainesMaximales;
    size_t maxLongueurGlobale = 0;

    // Comparaison de CHAQUE mot avec TOUS LES AUTRES mots du fichier
    for (size_t i = 0; i < vecteurMots.size(); ++i) {
        for (size_t j = i + 1; j < vecteurMots.size(); ++j) {
            string sc = plusGrandeSousChaineCommune(vecteurMots[i], vecteurMots[j]);
            size_t lg = sc.length();

            if (lg > maxLongueurGlobale) {
                maxLongueurGlobale = lg;
                sousChainesMaximales.clear();
                if (!sc.empty()) {
                    sousChainesMaximales.push_back(sc);
                }
            } else if (lg == maxLongueurGlobale && lg > 0) {
                // Éviter les doublons dans la liste
                if (find(sousChainesMaximales.begin(), sousChainesMaximales.end(), sc) == sousChainesMaximales.end()) {
                    sousChainesMaximales.push_back(sc);
                }
            }
        }
    }

    // Affichage final propre et direct dans le shell
    cout << "========================================" << endl;
    cout << "   PLUS GRANDE SOUS-CHAINE COMMUNE" << endl;
    cout << "========================================" << endl;

    if (maxLongueurGlobale > 0) {
        cout << "Longueur : " << maxLongueurGlobale << " caractère(s)" << endl;
        cout << "Sous-chaîne(s) correspondante(s) :" << endl;
        for (const string& s : sousChainesMaximales) {
            cout << " - '" << s << "'" << endl;
        }
    } else {
        cout << "Aucune sous-chaîne commune n'a été trouvée entre les mots." << endl;
    }

    return 0;
}
