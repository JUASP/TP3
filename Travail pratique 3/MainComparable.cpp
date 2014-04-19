/* *
 * \file MainComparable.cpp
 * \brief Test la complexite des methodes
 * \author Julien, Felix et Mathieu
 * \version 0.1 * \date 18 mars 2014 *
 * Travail pratique num�ro 3
 * Created on: 18 mars 2014
 * Author: etudiant
 * */

#include "ReseauAerien.h"
#include <iostream>
#include <ctime>

using namespace TP3;
int main()
{
   clock_t parcour_largeur, endBFS,
           dijkstra, endDijk,
           bellmanford, endBell,
           astar, endAstar;
   Chemin cheminDijkstra, cheminBellmanFord, cheminAStar;
   std::vector<std::string> cheminBFS;
   ReseauAerien reseau;


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

   parcour_largeur = clock();
   cheminBFS = reseau.rechercheCheminLargeur("un","trois");
   endBFS = clock();
   clock_t clockTicksTakenBFS = endBFS - parcour_largeur;
   double timeInSecondsBFS = clockTicksTakenBFS / (double) CLOCKS_PER_SEC;

   dijkstra = clock();
   cheminDijkstra = reseau.rechercheCheminDijkstra("un", "trois", true);
   endDijk = clock();
   clock_t clockTicksTakenDijk = endDijk - dijkstra;
   double timeInSecondsDijk = clockTicksTakenDijk / (double) CLOCKS_PER_SEC;

   astar = clock();
   cheminAStar = reseau.algorithmeAstar("un", "trois", true);
   endAstar = clock();
   clock_t clockTicksTakenA = endAstar - astar;
   double timeInSecondsA = clockTicksTakenA / (double) CLOCKS_PER_SEC;

   bellmanford = clock();
   cheminBellmanFord = reseau.bellManFord("un", "trois", 1);
   endBell = clock();
   clock_t clockTicksTakenBell = endBell - bellmanford;
   double timeInSecondsBell = clockTicksTakenBell / (double) CLOCKS_PER_SEC;


   std::cout << "Voici la duree des algorithmes en milliseconde : " << std::endl
             << "BFS : " << timeInSecondsBFS << std::endl
             << "Dijkstra : " << timeInSecondsDijk << std::endl
             << "Bellam-Ford : " << timeInSecondsBell << std::endl
             << "A* : " << timeInSecondsA << std::endl << std::endl;

   return 0;
};



