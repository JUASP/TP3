/*
 * TestReseauAerien.cpp
 *
 *  Created on: 18 mars 2014
 *      Author: etudiant
 */
#include "ReseauAerien.h"
#include <iostream>

using namespace TP3;
int main()
{
   clock_t clock_AStar;
   ReseauAerien reseau;
   Chemin cheminAvec1,cheminAvec2;


   reseau.GetUnReseau()->ajouterSommet("un", 3.10, 4.10);

   reseau.GetUnReseau()->ajouterSommet("deux", 5.20, 6.20);

   reseau.GetUnReseau()->ajouterSommet("trois", 3.30, 4.30);

   reseau.GetUnReseau()->ajouterArc("un", "deux", 2.00, 200.00, 4);

   if (reseau.GetUnReseau()->arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
   reseau.GetUnReseau()->enleverArc("un", "deux");
   reseau.GetUnReseau()->ajouterArc("un", "deux", 2.00, 200.00, 4);
   reseau.GetUnReseau()->ajouterArc("un", "trois", 2.00, 200.00, 4);
   std:: cout << "Debut operator << " << std::endl;
   std::cout << reseau;
   std:: cout << "fin operator << "<< std::endl;

   std:: cout << "test avec option 1" << std::endl;
   cheminAvec1 = reseau.rechercheCheminDijkstra("un","deux",true);

   std::cout << "duree total: "<<cheminAvec1.dureeTotale << std::endl;
   std::cout << "Voici le chemin le plus cours de la origine vers la destination: ";
   for(unsigned int i=0; i < cheminAvec1.listeVilles.size();i++){
      std::cout << " " << cheminAvec1.listeVilles[i] << "->";
   }



   std:: cout << "test avec option 2" << std::endl;
   cheminAvec2 = reseau.rechercheCheminDijkstra("un","deux",false);

   std::cout << "cout total: "<<cheminAvec2.coutTotal << std::endl;
   std::cout << "Voici le chemin le plus cours de la origine vers la destination: ";
   for(unsigned int i=0; i < cheminAvec2.listeVilles.size();i++){
      std::cout << " " << cheminAvec2.listeVilles[i] << "->";
   }

   clock_AStar = clock();
   std::cout << "\nTemps de calcul: " << (long)(clock_AStar) << " millisecondes\n\n";
   return 0;
}
