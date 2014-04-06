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
 * \brief constructeur par d�faut
 * \post Un r�seau a�rien vide est instanci�.
 */
ReseauAerien::ReseauAerien(){ //Le constructeur ne fait rien vu que le type ReseauAerien est compos� d'un graphe.
} //C'est le constructeur de ce dernier qui sera appel�.







/**
 * \brief D�truit et lib�re toute la m�moire allou�e auparavant pour le r�seau a�rien.
 * \post Toute la m�moire allou�e auparavant pour le r�seau a�rien est lib�r�e.
 * \post L'Objet ReseauAerien n'est plus valide.
 */
ReseauAerien::~ReseauAerien(){
   //viderReseau();
} //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appel� implicitement






/**
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
* \brief Vider le r�seau
* \post Le reseau est d�truit
*/
void ReseauAerien::viderReseau(){
   unReseau.detruireGraphe(); // on fais appelle au destructeur de unReseau
   nomReseau.clear(); // on vide la string
}





/**
*  \brief Retourne le pointeur sur le reseau.
*
*  \pre le reseau est valide.
*
*  \post Le reseau peut etre chang�e.
*/
Graphe * ReseauAerien::GetUnReseau (){
   return &unReseau;
}
}//Fin du namespace
