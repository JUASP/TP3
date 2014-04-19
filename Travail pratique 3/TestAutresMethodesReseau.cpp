/*
 *
 * \file TestAutresMethodesReseau.cpp
 * \brief Test des methodes de ReseauAerien
 * \author Julien, Felix et Mathieu
 * \version 0.1
 * \date 18 mars 2014
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
   std:: cout << "fin operator << ";
   ReseauAerien reseau2;
   ReseauAerien reseau3(reseau2); // test constructeur de copie
   reseau2 = reseau; // test de la surchage de l'operateur =
   std::cout << reseau2;
   std:: cout << "debut fermeture" << std::endl;
   ReseauAerien reseauFermer = reseau.fermetureReseau(); // cree la fermeture du reseau
   //std::cout << reseauFermer;
   std:: cout << "fin fermeture" << std::endl;
   std:: cout << "debut compo connexes" << std::endl;
   std::vector<ReseauAerien> connexeFort = reseauFermer.composantesFortConnexes(); // verif composantes Fort connexes
   for(std::vector<ReseauAerien>::iterator it = connexeFort.begin(); it < connexeFort.end(); it++){
      std::cout << "Compo fortemenet connexe" << std::endl;
      std::cout << (*it) << std::endl; // on affiche tous les reseauAerien

   }
   std:: cout << "fin compo connexes" << std::endl;
	if (reseau2.GetUnReseau()->arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	if (reseau.GetUnReseau()->arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	std::vector<std::string> sommets = reseau.GetUnReseau()->listerSommetsAdjacents("un");
	for (unsigned int i=0; i<sommets.size(); i++) std::cout << sommets[i] << ' ';
	Ponderations ponder = reseau.GetUnReseau()->getPonderationsArc("un", "deux");
	std::cout << ponder.cout << ' ' << ponder.duree << ' ' << ponder.ns << std::endl;
	//std::cout << graph.getNomSommet(3.20, 4.20) << std::endl;
	Coordonnees coord = reseau.GetUnReseau()->getCoordonnesSommet("un");
	std::cout << coord.lg << ' ' << coord.lt << std::endl;
	return 0;
}
