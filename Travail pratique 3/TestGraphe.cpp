/*
 * TestGraphe.cpp
 *
 *  Created on: 18 mars 2014
 *      Author: etudiant
 */
#include "Graphe.h"
#include <iostream>

using namespace TP3;
int main()
{
	Graphe graph;
	graph.ajouterSommet("un", 3.10, 4.10);
	graph.ajouterSommet("deux", 5.20, 6.20);
	graph.ajouterSommet("trois", 3.30, 4.30);
	graph.ajouterArc("un", "deux", 2.00, 200.00, 4);
	if (graph.arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	graph.enleverArc("un", "deux");
	graph.ajouterArc("un", "deux", 2.00, 200.00, 4);
	graph.ajouterArc("un", "trois", 2.00, 200.00, 4);
	Graphe graph2;
	graph2 = graph;
	if (graph2.arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	if (graph.arcExiste("un", "deux")) std::cout << "arc existe" << std::endl;
	std::vector<std::string> sommets = graph.listerSommetsAdjacents("un");
	for (unsigned int i=0; i<sommets.size(); i++) std::cout << sommets[i] << ' ';
	Ponderations ponder = graph.getPonderationsArc("un", "deux");
	std::cout << ponder.cout << ' ' << ponder.duree << ' ' << ponder.ns << std::endl;
	//std::cout << graph.getNomSommet(3.20, 4.20) << std::endl;
	Coordonnees coord = graph.getCoordonnesSommet("un");
	std::cout << coord.lg << ' ' << coord.lt << std::endl;
	return 0;
}
