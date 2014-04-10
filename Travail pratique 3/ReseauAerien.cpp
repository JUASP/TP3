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
   if(dureeCoutNiveau < 1 || dureeCoutNiveau > 3){ // verif du param dureeCoutNiveau
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

                   // étape 1 init tous les conteneurs quon va avoir besoin.
                   std::vector<std::string> vecteurNomsSommets = unReseau.listerNomsSommets();
                   std::map<std::string,int> mapNomsPoids; // pour faire le lien entre le nom du sommet et son poids.
                   std::map<std::string,std::string> mapPrecedent; // map qui va contenir le sommet précedent


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

                      if((*it) == origine){
                          mapNomsPoids[(*it)] = 0; // on donne 0 a la source
                          mapPrecedent[(*it)] = ""; // la source n'as pas de sommet precedent
                          continue;
                       }

                       mapNomsPoids[(*it)] = INT_MAX; // on doit INT_MAX a tous les sommets
                   }


                   // Étape 2 on relache tous les arcs (nombredesommet - 1 fois)
                   int k; // utile pour la boucle qui s'assure de boucler une nombreSommets() fois
                   std::vector<std::string>::iterator itVille; // iterateur pour se deplacer dans le vecteur des villes
                   std::vector<std::string>::iterator itVilleAdj; // iterateur pour se deplacer dans le vecteur des villes adjacentes
                   Ponderations ponde; // objet ponde qui va nous etre utile pour les comparaisons
                   std::string villeCourante; // string villeCourante pour y deposer notre iterateur courant
                   std::string villeAdjacenteCourante; // string villeAdjCourante pour y deposer notre iterateur courant
                   std::vector<std::string> vectorSommetsAdjacents; // on declare le vecteur de somnmets a l'exterieur des boucles.
                  // Sommet *  _sommetAssocierAuNom(const std::string& nom);
                   for (k = 0; k <= unReseau.nombreSommets() ; k++) // on fais la boucle (nombreSommet() - 1) fois
                    {
                      for(itVille = vecteurNomsSommets.begin(); itVille < vecteurNomsSommets.end() ; itVille++ ){ // on parcours tout les sommets
                        villeCourante = (*itVille);
                        vectorSommetsAdjacents = unReseau.listerSommetsAdjacents(villeCourante);

                        for (itVilleAdj = vectorSommetsAdjacents.begin(); itVilleAdj < vectorSommetsAdjacents.end() ; itVilleAdj++ )
                        {
                           villeAdjacenteCourante = (*itVilleAdj);
                           ponde = unReseau.getPonderationsArc(villeCourante, villeAdjacenteCourante); // on remplis l'objet ponde avec la ponderation entre les deux sommets

                           if(mapNomsPoids[villeCourante] + ponde.ns < mapNomsPoids[villeAdjacenteCourante]){
                              mapNomsPoids[villeAdjacenteCourante] = mapNomsPoids[villeCourante] + ponde.ns;
                              mapPrecedent[villeAdjacenteCourante] = villeCourante; // on associe villeCourante comme precedent des Vecteurs adjacents
                           }// fin if

                        }// fin for des villes adjacentes
                      }// fin for qui parcours tous les sommets
                    }// fin for qui est executer nombreSommet() fois

                   //Etape 3: On regarde pour des circuits negatif.
                   for(itVille = vecteurNomsSommets.begin(); itVille < vecteurNomsSommets.end() ; itVille++ ){ // on parcours tout les sommets
                      villeCourante = (*itVille);
                      vectorSommetsAdjacents = unReseau.listerSommetsAdjacents(villeCourante);
                      for (itVilleAdj = vectorSommetsAdjacents.begin(); itVilleAdj < vectorSommetsAdjacents.end() ; itVilleAdj++ ){
                         villeAdjacenteCourante = (*itVilleAdj);
                         ponde = unReseau.getPonderationsArc(villeCourante, villeAdjacenteCourante); // on remplis l'objet ponde avec la ponderation entre les deux sommets
                         if (mapNomsPoids[villeAdjacenteCourante] > mapNomsPoids[villeCourante] + ponde.ns){
                                 cheminLePlusCourt.reussi = false;
                                 return cheminLePlusCourt;
                         }
                        }// fin for des villes adjacentes
                   }// fin for qui parcours tous les sommets
                   cheminLePlusCourt.reussi = true;
                   cheminLePlusCourt.nsTotal = mapNomsPoids[destination];
                   std::string courant = mapPrecedent[destination];
                   cheminLePlusCourt.listeVilles.push_back(courant);
                   while(courant != origine){ // parcours de la destionation jusqu'a l'origine avec les precedents
                      courant = mapPrecedent[courant];
                      cheminLePlusCourt.listeVilles.push_back(courant); // on append le vecteur avec le sommet courant
                   }

                   break; // break pour le selectcase
         }// fin switch
   return cheminLePlusCourt;
}
}//Fin du namespace
