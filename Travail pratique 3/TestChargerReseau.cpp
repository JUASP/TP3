/*
 *
 * \file TestChargerReseau.cpp
 * \brief Test des methodes d'entre sortie
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

	ReseauAerien reseauAerien;
   std::ifstream Entree;
   std::ofstream Sortie;

   Entree.open("ReseauAerien.txt", std::ios::in);
   if(Entree.is_open())
   {
      reseauAerien.chargerReseau(Entree);
   }
   else  std::cout << "ERREUR: Fichier introuvable!" << std::endl;

   Entree.clear();

   Sortie.open("SauvegardeReseau", std::ios::out);
   if(Sortie.is_open()){

      reseauAerien.sauvegarderReseau(Sortie);
      std::cout << "Le reseau a bien ete sauvegarde! Le voici :" << std::endl << reseauAerien << std::endl;

   }
   else std::cout << "ERREUR : il y a eu un probleme lors de la sauvegarde" << std::endl;

   Sortie.close();

   return 0;
}
