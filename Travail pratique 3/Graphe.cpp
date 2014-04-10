/**
 * \file Graphe.cpp
 * \brief Implémentation d'un graphe orienté où chaque sommet un nom.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique numéro 3
 *
 */

#include "Graphe.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP3
{
Graphe::Graphe()
{
	nbSommets = 0;
	nbArcs = 0;
	listeSommets = 0;
}

Graphe::Graphe(const Graphe &source)
{
	nbSommets = source.nbSommets;
	nbArcs = source.nbArcs;
	listeSommets = source.listeSommets;

	Sommet* courant = listeSommets;
	Sommet* nouveau = source.listeSommets;

	for (int i=0; i< nbSommets; i++)
	{
		courant = &*nouveau;
		Arc* arcCourant = courant->listeDest;
		Arc* arcNouveau = nouveau->listeDest;
		while (arcNouveau != 0)
		{
			arcCourant = &*arcNouveau;
			arcCourant = arcCourant->suivDest;
			arcNouveau = arcNouveau->suivDest;
		}
		courant = courant->suivant;
		nouveau = nouveau->suivant;
	}

}

Graphe::~Graphe()
{
	detruireGraphe();
}

Graphe& Graphe::operator=(const Graphe& src)
{
	detruireGraphe();

	nbSommets = src.nbSommets;
		nbArcs = src.nbArcs;
		listeSommets = src.listeSommets;

		Sommet* courant = listeSommets;
		Sommet* nouveau = src.listeSommets;

		for (int i=0; i< nbSommets; i++)
		{
			courant = &*nouveau;
			Arc* arcCourant = courant->listeDest;
			Arc* arcNouveau = nouveau->listeDest;
			while (arcNouveau != 0)
			{
				arcCourant = &*arcNouveau;
				arcCourant = arcCourant->suivDest;
				arcNouveau = arcNouveau->suivDest;
			}
			courant = courant->suivant;
			nouveau = nouveau->suivant;
		}
	return (*this);
}

bool Graphe::arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const
{
	if (!(sommetExiste(sommetUn) && sommetExiste(sommetDeux))) throw std::logic_error("arcExiste: Un ou plusieurs somments manquants");
	Sommet * courant = listeSommets;

	//Les arcs n'ont pas de direction, il suffit donc juste de vérifier la liste des arcs à partir
	//d'un des deux sommets.
	for (int i=0; i<nbSommets; i++)
	{
		if (courant->nom == sommetUn)
		{
			Arc* arcCourant = courant->listeDest;
			while (arcCourant != 0)
			{
				if (arcCourant->dest->nom == sommetDeux) return true;
				arcCourant = arcCourant->suivDest;
			}
		}
	}
	return false;
}

void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
{
	if (!(arcExiste(nom1, nom2))) throw std::logic_error("enleverArc: L'arc n'existe pas.");

	Sommet* courant = listeSommets;
	Arc* aSupprimer = new Arc();
	for (int i=0; i<nbSommets; i++)
	{
		if (courant->nom == nom1)
		{
			//L'arc est le premier élément de la liste
			if (courant->listeDest->dest->nom == nom2)
			{
				//La liste contient plus d'un arc
				if (courant->listeDest->suivDest != 0)
				{
					aSupprimer = courant->listeDest;
					courant->listeDest = courant->listeDest->suivDest;
				}
				//La liste contient un seul arc
				else courant->listeDest = 0;
			}
			else
			{
				Arc* arcCourant = courant->listeDest;
				while(arcCourant->suivDest->dest->nom != nom2)
				{
					arcCourant = arcCourant->suivDest;
				}
				//L'arc est le dernier de la liste
				if (arcCourant->suivDest->suivDest == 0)
				{
					aSupprimer = arcCourant->suivDest;
					arcCourant->suivDest = 0;
				}
				else
				{
					aSupprimer = arcCourant->suivDest;
					arcCourant->suivDest = arcCourant->suivDest->suivDest;
				}
			}
		}
		else if (courant->nom == nom2)
		{
			//L'arc est le premier élément de la liste
			if (courant->listeDest->dest->nom == nom1)
			{
				//La liste contient plus d'un arc
				if (courant->listeDest->suivDest != 0)
				{
					aSupprimer = courant->listeDest;
					courant->listeDest = courant->listeDest->suivDest;
				}
				//La liste contient un seul arc
				else courant->listeDest = 0;
			}
			else
			{
				Arc* arcCourant = courant->listeDest;
				while(arcCourant->suivDest->dest->nom != nom1)
				{
					arcCourant = arcCourant->suivDest;
				}
				//L'arc est le dernier de la liste
				if (arcCourant->suivDest->suivDest == 0)
				{
					aSupprimer = arcCourant->suivDest;
					arcCourant->suivDest = 0;
				}
				else
				{
					aSupprimer = arcCourant->suivDest;
					arcCourant->suivDest = arcCourant->suivDest->suivDest;
				}
			}
		}
		courant = courant->suivant;
	}
	delete aSupprimer;
	nbArcs--;
}

void Graphe::ajouterArc(const std::string& nom1, const std::string& nom2, float duree, float cout, int ns)
{
	if (!(sommetExiste(nom1) && sommetExiste(nom2))) throw std::logic_error("ajouterArc: Un ou plusieurs somments manquants");
	if (arcExiste(nom1, nom2)) throw std::logic_error("ajouterArc: L'arc existe deja");

	//On récupère les adresses des sommets nom1 et nom2
	Sommet* courant = listeSommets;
	Sommet* un;
	Sommet* deux;
	for (int i=0; i < nbSommets; i++)
	{
		if (courant->nom == nom1)un = courant;
		else if (courant->nom  == nom2) deux = courant;
		courant = courant->suivant;
	}
	courant = listeSommets;
	Arc* nouveau = new Arc();
	nouveau->ponder.cout = cout;
	nouveau->ponder.duree = duree;
	nouveau->ponder.ns = ns;

	Arc* temp = new Arc();
	temp->ponder.cout = cout;
	temp->ponder.duree = duree;
	temp->ponder.ns = ns;
	for (int i=0; i < nbSommets; i++)
	{
		if (courant->nom == nom1)
		{
			if (courant->listeDest == 0)
			{
				nouveau->dest = deux;
				courant->listeDest = &*nouveau;
			}
			else
			{
				Arc* dest = courant->listeDest;
				while (dest->suivDest != 0) dest = dest->suivDest;
				nouveau->dest = deux;
				dest->suivDest = &*nouveau;
			}
		}
		else if (courant->nom  == nom2)
		{
			if (courant->listeDest == 0)
			{
				temp->dest = un;
				courant->listeDest = &*temp;
			}
			else
			{
				Arc* dest = courant->listeDest;
				while (dest->suivDest != 0) dest = dest->suivDest;
				temp->dest = un;
				dest->suivDest = &*temp;
			}
		}
		courant = courant->suivant;
	}
	nbArcs++;
}

void Graphe::ajouterSommet(const std::string& nom, float lt, float lg)
{
	if(sommetExiste(nom)) throw std::logic_error("AjouterSommet: le sommet existe deja!\n");

	Sommet* nouveau = new Sommet;
	nouveau->nom = nom;
	nouveau->coord.lg = lg;
	nouveau->coord.lt = lt;
	Sommet* courant = listeSommets;

	if (nbSommets == 0)
	{
		listeSommets = &*nouveau;
		listeSommets->precedent = 0;
	}
	else if (nbSommets == 1)
	{
		listeSommets->suivant = nouveau;
		nouveau->precedent = listeSommets;
	}
	else
	{
		for (int i=1; i<nbSommets; i++) courant = courant->suivant;
		courant->suivant = &*nouveau;
		courant->suivant->precedent = courant;
	}

	nbSommets++;
}

bool Graphe::sommetExiste(const std::string& nom) const
{
	if (nbSommets == 0) return false;
	Sommet* courant = listeSommets;
	for (int j = 0; j < nbSommets; j++)
	{
		if(nom == courant->nom) return true;
		courant = courant->suivant;
	}
	return false;
}

void Graphe::enleverSommet(const std::string& nom)
{
	if (!sommetExiste(nom)) throw std::logic_error("Le sommet n'existe pas");
	if (nbSommets == 1)
	{
		listeSommets = 0;
	}
	else
	{
		Sommet* courant = listeSommets;
		for (int i=0; i<nbSommets; i++)
		{
			if (courant->nom == nom)
			{
				//l'élément à delete est le premier de la liste
				if (courant->precedent == 0)
				{
					listeSommets = listeSommets->suivant;
					listeSommets->precedent = 0;
					Arc* arcCourant = courant->listeDest;
					Arc* arcTemp = arcCourant;
					while (arcTemp != 0)
					{
						arcTemp = arcTemp->suivDest;
						enleverArc(courant->nom, arcCourant->dest->nom);
						arcCourant = arcTemp;
					}
					delete courant;
					nbSommets--;
					return;
				}
				//l'élément à delete est le dernier de la liste
				else if (courant->suivant == 0)
				{
					Arc* arcCourant = courant->listeDest;
					Arc* arcTemp = arcCourant;
					while (arcTemp != 0)
					{
						arcTemp = arcTemp->suivDest;
						enleverArc(courant->nom, arcCourant->dest->nom);
						arcCourant = arcTemp;
					}
					courant->precedent->suivant = 0;
					delete courant;
					nbSommets--;
					return;
				}
				//l'élément à delete n'est pas le premier, ni le dernier
				else
				{
					Arc* arcCourant = courant->listeDest;
					Arc* arcTemp = arcCourant;
					while (arcTemp != 0)
					{
						arcTemp = arcTemp->suivDest;
						enleverArc(courant->nom, arcCourant->dest->nom);
						arcCourant = arcTemp;
					}
					courant->precedent->suivant = courant->suivant;
					courant->suivant->precedent = courant->precedent;
					delete courant;
					nbSommets--;
					return;
				}
			}
			courant = courant->suivant;
		}
	}
}

std::vector<std::string> Graphe::listerNomsSommets() const
{
	if (nbSommets == 0) throw std::logic_error("Aucun sommet présent dans le réseau");

	std::vector<std::string> sommets;
	Sommet* courant = listeSommets;
	for (int i=0; i< nbSommets; i++)
	{
		sommets.push_back(courant->nom);
		courant = courant->suivant;
	}
	return sommets;
}

std::vector<std::string> Graphe::listerSommetsAdjacents(const std::string& nom) const
{
	if (!(sommetExiste(nom))) throw std::logic_error("listerSommetsAdjacents: Le sommet n'existe pas");

	//On retourne l'adresse du sommet en argument
	std::vector<std::string> sommets;
	Sommet* courant = listeSommets;
	for (int i=0; i < nbSommets; i++)
	{
		if (courant->nom == nom)
		{
			Arc* arcCourant = courant->listeDest;
			while (arcCourant != 0)
			{
				sommets.push_back(arcCourant->dest->nom);
				arcCourant = arcCourant->suivDest;
			}
		}
		courant = courant->suivant;
	}
	return sommets;
}

int Graphe::nombreSommets() const
{
	return nbSommets;
}



/**
* \brief Retourne le nombre d'arc dans la liste des sommets
* \post Le graphe reste inchangé.
*/
int Graphe::nombreArcs() const
{
   return nbArcs;
}

/**
* \fn  Graphe::Sommet*  Graphe::_sommetAssocierAuNom(const std::string& nom)
* \brief retourne un pointeur vers le sommet correspondant au nom recu en param
* \return un pointeur vers le sommet qui correspond au nom recu en param
* \post Le graphe reste inchangé.
*/
Graphe::Sommet*  Graphe::_sommetAssocierAuNom(const std::string& nom)
{
   Sommet* courant = listeSommets;
   for (int j = 0; j < nbSommets; j++)
   {
      if(nom == courant->nom){
         return courant; // on donne la valeur en refence de courant a source
      }
      courant = courant->suivant;
   }
   return 0;
}

bool Graphe::estVide() const
{
	return nbSommets == 0;
}

Ponderations Graphe::getPonderationsArc(const std::string& sommetUn, const std::string& sommetDeux) const
{
	if (!(arcExiste(sommetUn, sommetDeux))) throw std::logic_error("getPonderationsArc: L'arc n'existe pas");
	//On se positionne sur le bon sommet (sommetUn)
	Sommet* courant = listeSommets;
	while (courant->nom != sommetUn) courant = courant->suivant;
	//On se positionne sur le bon arc
	Arc* arcCourant = courant->listeDest;
	while (arcCourant->dest->nom != sommetDeux) arcCourant = arcCourant->suivDest;
	return arcCourant->ponder;
}

std::string Graphe::getNomSommet(float lt, float lg) const
{
	Sommet* courant = listeSommets;
	for (int i=0; i<nbSommets; i++)
	{
		if (courant->coord.lg == lg && courant->coord.lt == lt)
			return courant->nom;
		courant = courant->suivant;
	}
	throw std::logic_error("getNomSommet: Les coordonnees ne representent aucun sommet");
}

Coordonnees Graphe::getCoordonnesSommet(const std::string& nom) const
{
	if (estVide()) throw std::logic_error("getCoordonneesSommet: Il n'y a aucun sommet dans le graphe");
	if (!(sommetExiste(nom))) throw std::logic_error("getCoordoneesSommet: le sommet n'existe pas");

	Sommet* courant = listeSommets;
	while (courant->nom != nom) courant = courant->suivant;
	return courant->coord;
}

float Graphe::getDistanceEucledienne(const std::string& sommetUn, const std::string& sommetDeux) const
{
	if (!(sommetExiste(sommetUn)) && !(sommetExiste(sommetDeux))) throw std::logic_error("getDistanceEucledienne: un ou plusieurs sommets n'existent pas");

	Coordonnees un;
	Coordonnees deux;
	Sommet* courant = listeSommets;
	for (int i=0; i<nbSommets; i++)
	{
		if (courant->nom == sommetUn) un = courant->coord;
		else if(courant->nom == sommetDeux) deux = courant->coord;
		courant = courant->suivant;
	}
	const float distance = sqrt(pow((un.lg - deux.lg), 2.0) + pow((un.lt - deux.lt), 2.0));
	return distance;
}

void Graphe::detruireGraphe()
{
	Sommet* courant = listeSommets;
	for (int i=0; i<nbSommets; i++)
	{
		Arc* arcCourant = courant->listeDest;
		while (arcCourant != 0)
		{
			enleverArc(courant->nom, arcCourant->dest->nom);
			arcCourant = arcCourant->suivDest;
		}
		enleverSommet(courant->nom);
		courant = courant->suivant;
	}
	//on supprime les tableaux
	delete listeSommets;
}

}//Fin du namespace
