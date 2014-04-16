#include "ReseauAerien.h"
#include <iostream>

using namespace TP3;
int main()
{
	std::cout << "Exemple avec le graphe présenté en classe:" << std::endl;
	ReseauAerien reseau;
	reseau.GetUnReseau()->ajouterSommet("A", 3.10, 4.10);
	reseau.GetUnReseau()->ajouterSommet("B", 5.20, 6.20);
	reseau.GetUnReseau()->ajouterSommet("C", 3.30, 4.30);
	reseau.GetUnReseau()->ajouterSommet("D", 3.10, 4.10);
	reseau.GetUnReseau()->ajouterSommet("E", 3.10, 4.10);
	reseau.GetUnReseau()->ajouterSommet("F", 3.10, 4.10);
	reseau.GetUnReseau()->ajouterSommet("G", 3.10, 4.10);
	reseau.GetUnReseau()->ajouterArc("A", "B", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("A", "F", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("A", "G", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("F", "B", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("B", "D", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("B", "C", 2.00, 200.00, 4);
	reseau.GetUnReseau()->ajouterArc("C", "D", 2.00, 200.00, 4);


	std::cout << "Le plus court chemin entre A et D: " << std::endl;
	std::vector<std::string> parcours = reseau.rechercheCheminLargeur("A", "D");
	for (std::vector<std::string>::iterator it = parcours.begin(); it != parcours.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
