/*
 *
 * \file TestBellmanFord.cpp
 * \brief Test de l'algo BellmanFord
 * \author Julien, Felix et Mathieu
 * \version 0.1
 * \date 1 avril 2014
 *
 *  Travail pratique num�ro 3
 *  Created on: 18 mars 2014
 *      Author: etudiant
 */
#include "ReseauAerien.h"
#include <iostream>

using namespace TP3;
int main()
{
   ReseauAerien reseau;
	Chemin cheminAvec1,cheminAvec2,cheminAvec3;
	clock_t clock_bellManFord;

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
   cheminAvec1 = reseau.bellManFord("un","deux",1);
   if(cheminAvec2.reussi){
   std::cout << "duree total: "<<cheminAvec1.dureeTotale << std::endl;
   }else std::cout << "le chemin 1 n'a pas réussi"<< std::endl;


   std:: cout << "test avec option 2" << std::endl;
   cheminAvec2 = reseau.bellManFord("un","deux",2);
   if(cheminAvec2.reussi){
      std::cout << "cout total: "<<cheminAvec2.coutTotal << std::endl;
   }else std::cout << "le chemin 2 n'a pas réussi"<< std::endl;


   std:: cout << "test avec option 3" << std::endl;
   cheminAvec3 = reseau.bellManFord("un","deux",3);
   if(cheminAvec3.reussi){
      std::cout << "ns total: "<<cheminAvec3.nsTotal << std::endl;
      std::cout << "Voici le chemin le plus cours de la origine vers la destination: ";
      for(unsigned int i=0; i < cheminAvec3.listeVilles.size();i++){
         std::cout << " " << cheminAvec3.listeVilles[i] << "->";
      }
   }else std::cout << "le chemin 3 n'a pas réussi"<< std::endl ;

   clock_bellManFord = clock();
     std::cout << "\nTemps de calcul: " << (long)(clock_bellManFord) << " millisecondes\n\n";
   /*
   ReseauAerien reseau2;
   ReseauAerien reseau3(reseau2); // test constructeur de copie
   reseau2 = reseau; // test de la surchage de l'operateur =
   std::cout << reseau2;
   ReseauAerien reseauFermer = reseau.fermetureReseau(); // cree la fermeture du reseau
   std::cout << reseauFermer;
	if (reseau2.GetUnReseau()->arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	if (reseau.GetUnReseau()->arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	std::vector<std::string> sommets = reseau.GetUnReseau()->listerSommetsAdjacents("un");
	for (unsigned int i=0; i<sommets.size(); i++) std::cout << sommets[i] << ' ';
	Ponderations ponder = reseau.GetUnReseau()->getPonderationsArc("un", "deux");
	std::cout << ponder.cout << ' ' << ponder.duree << ' ' << ponder.ns << std::endl;
	//std::cout << graph.getNomSommet(3.20, 4.20) << std::endl;
	Coordonnees coord = reseau.GetUnReseau()->getCoordonnesSommet("un");
	std::cout << coord.lg << ' ' << coord.lt << std::endl;
	return 0;*/
   return 0 ;
}
