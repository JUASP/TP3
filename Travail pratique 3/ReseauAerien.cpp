/**
 * \file ReseauAerien.cpp
 * \brief Impl�mentattion de la classe ReseauAerien.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique num�ro 3
 *
 */

#include "ReseauAerien.h"
//vous pouvez inclure d'autres librairies si c'est n�cessaire

namespace TP3
{
/**
 * \fn ReseauAerien::ReseauAerien()
 * \brief constructeur par d�faut
 * \post Un r�seau a�rien vide est instanci�.
 */
ReseauAerien::ReseauAerien(){ //Le constructeur ne fait rien vu que le type ReseauAerien est compos� d'un graphe.
} //C'est le constructeur de ce dernier qui sera appel�.







/**
 * \fn ReseauAerien::~ReseauAerien()
 * \brief D�truit et lib�re toute la m�moire allou�e auparavant pour le r�seau a�rien.
 * \post Toute la m�moire allou�e auparavant pour le r�seau a�rien est lib�r�e.
 * \post L'Objet ReseauAerien n'est plus valide.
 */
ReseauAerien::~ReseauAerien(){
   //viderReseau();
} //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appel� implicitement






/**
 *\fn ReseauAerien::ReseauAerien(const ReseauAerien &source)
* \brief Constructeur de copie.
* \pre Il y a assez de m�moire.
* \post la copie a été effectuer
* \exception bad_alloc S'il n'y a pas assez de m�moire.
*/
ReseauAerien::ReseauAerien(const ReseauAerien &source){
   unReseau.operator =(source.unReseau); // Ici on utilise la surchage de l'operateur = de Graphe.
   nomReseau = source.nomReseau; // simple affectation de string.
}






/**
* \fn ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src)
* \brief Surcharge de l'op�rateur d'affectation.
* \pre Il doit y avoir assez de m�moire.
* \param une référence sur un autre ReseauAerien
* \post Le r�seau a�rien a un contenu identique � src.
* \return retourne l'objet ReseauAerien courant
* \exception bad_alloc S'il n'y a pas assez de m�moire.
*/
ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src){
   //viderReseau(); // on s'assure que le réseau est vide.

   unReseau.operator =(src.unReseau); // Ici on utilise la surchage de l'operateur = de Graphe.
   nomReseau = src.nomReseau; // simple affectation de string.

   return (*this); // retourne l'objet courant
}






/**
* \fn void ReseauAerien::viderReseau()
* \brief Vider le r�seau
* \post Le reseau est d�truit
*/
void ReseauAerien::viderReseau(){
   unReseau.detruireGraphe(); // on fais appelle au destructeur de unReseau
   nomReseau.clear(); // on vide la string
}





/**
* \fn Graphe * ReseauAerien::GetUnReseau ()
*  \brief Retourne le pointeur sur le reseau.
*
*  \pre le reseau est valide.
*
*  \post Le reseau peut etre chang�e.
*/
Graphe * ReseauAerien::GetUnReseau (){
   return &unReseau;
}





/**
* \fn std::vector<ReseauAerien> ReseauAerien::composantesFortConnexes()
* \brief D�terminer les composantes fortement connexes d�un r�seau.
*  Cette fonction retourne un tableau (vector)
*  Chaque �l�ment du tableau retourn� contiendra un sous-r�seau dont toutes
*  les villes appartiennent � la m�me composante fortement connexe.
* \pre Le reseau est correctement initialis�.
* \post Le tableau des sous-reseaux est retourn�.
* \post Le reseau original reste inchang�.
* \exception bad_alloc si pas assez de m�moire pour cr�er le tableau
*/
std::vector<ReseauAerien> ReseauAerien::composantesFortConnexes(){
   std::vector<ReseauAerien> leVector;
   return leVector;
}




/**
* \fn Chemin bellManFord(const std::string& origine,const std::string& destination, int dureeCoutNiveau)
*  \brief Retourne le pointeur sur le reseau.
*
*  \pre le reseau est valide.
*  \pre les param d'entree sont dans l'ensemble des noeuds du reseau
*  \pre dureeCoutNiveau = 1 ou 2 ou 3
*  \param origine est une variable string qui correspond a la ville d'origine
*  \param destination est une variable string qui correspond a la ville de la destination
*  \param dureeCoutNiveau est le type de pondération que nous allons utiliser
*
*  \return un element de type Chemin
*  \post retourne le chemin le plus court.
*  \exception logic_error si les villes ne font pas parti du reseau aerien
*  \exception logic_error si la valeur de dureeCoutNiveau != 1..3
*/
Chemin ReseauAerien::bellManFord(const std::string& origine,const std::string& destination, int dureeCoutNiveau){
   Chemin cheminLePlusCourt;
   if(!(1 <= dureeCoutNiveau <= 3)){ // verif du param dureeCoutNiveau
       throw std::logic_error("bellManFord:logic_error l'indice pour dureeCoutNiveau n'est pas reconnu!");
    }
   if(!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination)){ // verif si nos param sont inclu dans les sommets
      throw std::logic_error("bellManFord:logic_error les villes saisies ne font pas partie du reseau aerien");
   }
   switch(dureeCoutNiveau)
         {
           case 1: // cas pour durée de vol comme pondération
                   cheminLePlusCourt = rechercheCheminDijkstra(origine,destination, true);
                   break;
           case 2: // cas pour cout du vol comme pondération
                   cheminLePlusCourt = rechercheCheminDijkstra(origine,destination, false);
                   break;
           case 3: // cas pour niveau de sécurite comme pondération

                   std::vector<std::string> vecteurNomsSommets = unReseau.listerNomsSommets();
                   std::map<std::string,int> mapNomsPoids; // pour faire le lien entre le nom du sommet et son poids.


                   /* --------------Vieux code
                    * std::vector<std::string> listerSommetsAdjacents = unReseau.listerSommetsAdjacents(listeNomsSommets[i]);
                    std::vector<int> pondeCumule[unReseau.nombreSommets()]; // on cree un vecteur de int de taille nombreSoummets
                   //on initialise tous les sommets a INT_MAX
                   for (int i = 0; i < vecteurNomsSommets.size(); i++){
                      pondeCumule[i]   = INT_MAX;
                   }
                   pondeCumule[indexOrigine] = 0; //le sommet d'origine qui aura la valeur de 0
                   ----------------*/

                   for(std::vector<std::string>::iterator it = vecteurNomsSommets.begin(); it <= vecteurNomsSommets.end(); it++){
                       if(it == origine){
                          mapNomsPoids[it] = 0; // on donne 0 a la source
                          break;
                       }
                       mapNomsPoids[it] = INT_MAX; // on doit INT_MAX a tous les sommets
                   }


                   // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
                    // to any other vertex can have at-most |V| - 1 edges
                   int k,j;
                   Ponderations ponde;
                   Sommet * som1,som2;
                   std::vector<std::string> listerSommetsAdjacents;
                  // Sommet *  _sommetAssocierAuNom(const std::string& nom);
                   for (k = 0; k <= unReseau.nombreSommets() ; k++) // relache tous les arcs
                    {
                      listerSommetsAdjacents = unReseau.listerSommetsAdjacents(vecteurNomsSommets[k]);
                        for (j=0; j < listerSommetsAdjacents.size(); j++)
                        {

                           ponde = unReseau.getPonderationsArc(som1, som2);
                           int u = graph->edge[j].src;
                           int v = graph->edge[j].dest;
                           int weight = graph->edge[j].weight;
                           if (dist[u] + weight < dist[v])
                            dist[v] = dist[u] + weight;

                        }

                    }


                   break;
         }// fin switch
   return cheminLePlusCourt;
}
}//Fin du namespace
