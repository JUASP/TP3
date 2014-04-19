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
* \param src une référence sur un autre ReseauAerien
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
*  \fn std::string * ReseauAerien::GetNomReseau ()
*  \brief Retourne le pointeur sur le reseau.
*
*  \pre le reseau est valide.
*
*  \post Le reseau peut etre chang�e.
*/
std::string * ReseauAerien::GetNomReseau (){
   return &nomReseau;
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
   //ReseauAerien reseauFermeture = fermetureReseau();
   std::map<std::string,int> mapLow; // pour faire le lien entre le nom du sommet et s'il a ete visite
   std::vector<std::string> vecteurNomsSommets = unReseau.listerNomsSommets();
   std::map<std::string,bool> mapVisite; // pour faire le lien entre le nom du sommet et s'il a ete visite
   std::stack<std::string> stackSommet;
   int compteur = 0;

   //Boucle d'initialisation
   for(std::vector<std::string>::iterator it = vecteurNomsSommets.begin(); it < vecteurNomsSommets.end(); it++){
                     mapVisite[(*it)] = false; // on initalize tout a false. car les visites n'ont pas commencer encore
                     mapLow[(*it)] = -1; // on donne la valeur -1 a tout par default.
   }
   //Boucle d'apelle
   for(std::vector<std::string>::iterator it = vecteurNomsSommets.begin(); it < vecteurNomsSommets.end(); it++){
          if(mapVisite[(*it)] == false){
             dfs((*it), leVector, mapVisite, mapLow, stackSommet, compteur);
          }

    }
   return leVector;
}

/**
    *  \fn void ReseauAerien::dfs(std::string sommetCourant, std::vector<ReseauAerien> &leVector,std::map<std::string,bool> &mapVisite,std::map<std::string,int> &mapLow)
    *  \brief fonction utilitaire pour l'algo de tarjan.
    *
    *  \pre les param sont tous valide.
    *  \param sommetCourant correspond au sommet courant
    *  \param leVector notre vecteur de reponse
    *  \param mapVisite outils pour la fonction
    *  \param mapLow outil pour la fonction
    *  \param stackSommet une pile de sommet
    *  \param compteur un compteur pour la fonction
    *
    *  \post les params recu en reference seront modifier.
    */
void ReseauAerien::dfs(std::string sommetCourant, std::vector<ReseauAerien> &leVector,std::map<std::string,bool> &mapVisite,std::map<std::string,int> &mapLow, std::stack<std::string> &stackSommet, int &compteur){

   mapLow[sommetCourant] = compteur++;
   mapVisite[sommetCourant] = true;
   stackSommet.push(sommetCourant);
   int min = mapLow[sommetCourant];
   std::string  villeAdjacenteCourante;
   std::vector<std::string>::iterator itVilleAdj; // iterateur pour se deplacer dans le vecteur des villes adjacentes
   std::vector<std::string> vectorSommetsAdjacents = unReseau.listerSommetsAdjacents(sommetCourant);
   for (itVilleAdj = vectorSommetsAdjacents.begin(); itVilleAdj < vectorSommetsAdjacents.end() ; itVilleAdj++ ) {
         villeAdjacenteCourante = (*itVilleAdj);

         if(mapVisite[villeAdjacenteCourante] == false){
               dfs(villeAdjacenteCourante,leVector, mapVisite, mapLow, stackSommet, compteur);
         }
         if(mapLow[villeAdjacenteCourante] < min){
            min = mapLow[villeAdjacenteCourante];
         }

   }
   if(min < mapLow[sommetCourant]){
      mapLow[sommetCourant] = min;
      return;
   }
   ReseauAerien nouveauReseau;
   std::string tempStack;
   Coordonnees coordTemp;
   do{
      tempStack = stackSommet.top(); // on prend l'element du dessus on le met dans tempStack
      stackSommet.pop();// on retire l'element du dessus.
      coordTemp = unReseau.getCoordonnesSommet(tempStack);
      nouveauReseau.unReseau.ajouterSommet(tempStack,coordTemp.lt,coordTemp.lg);
      mapLow[tempStack] = unReseau.getNbSommets();
   }while(tempStack != sommetCourant);
   leVector.push_back(nouveauReseau);
}







/**
* \brief D�terminer la fermeture transitive du reseau.
* \pre Le reseau est correctement initialis�.
* \post La fermeture transitive du reseau est retourn�e.
* \post Le reseau original reste inchang�.
* \exception bad_alloc si pas assez de m�moire
*/
ReseauAerien ReseauAerien::fermetureReseau(){
   ReseauAerien reseauFermeture((*this)); // reseauFermeture correspond a un nouveau reseau qui utilie le constructeur de copie pour mettre ses valeurs par defaut.
   std::vector<std::string> vectorNomsSommets = unReseau.listerNomsSommets();
   Ponderations ponde1;
   Ponderations ponde2;
   for (unsigned int i = 0; i < vectorNomsSommets.size(); i++) {
         for (unsigned int j = 0; j < vectorNomsSommets.size(); j++) {
            for (unsigned int k = 0; k < vectorNomsSommets.size(); k++) {
               if (!reseauFermeture.unReseau.arcExiste(vectorNomsSommets[j], vectorNomsSommets[k])
                     && reseauFermeture.unReseau.arcExiste(vectorNomsSommets[j], vectorNomsSommets[i])
                     && reseauFermeture.unReseau.arcExiste(vectorNomsSommets[i], vectorNomsSommets[k]))
               {
                  // on obtient la ponderation de l'Arc entre le vecteur J et I
                  ponde1 = reseauFermeture.unReseau.getPonderationsArc(vectorNomsSommets[j], vectorNomsSommets[i]);
                  // on obtient la ponderation de l'Arc entre le vecteur i et K
                  ponde2 = reseauFermeture.unReseau.getPonderationsArc(vectorNomsSommets[i], vectorNomsSommets[k]);
                  // on ajoute un arc entre J  K ayant la ponderation de ponde 1 + ponde 2.
                  reseauFermeture.unReseau.ajouterArc(vectorNomsSommets[j], vectorNomsSommets[k],(ponde1.duree + ponde2.duree),(ponde1.cout + ponde2.cout),(ponde1.ns + ponde2.ns)) ;
               }// fin if
            }
         }
      }

   return reseauFermeture;
}



/**
* \fn Chemin ReseauAerien::bellManFord(const std::string& origine,const std::string& destination, int dureeCoutNiveau)
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

                   for(std::vector<std::string>::iterator it = vecteurNomsSommets.begin(); it < vecteurNomsSommets.end(); it++){

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

                        //std::cout << "ville courante: " <<villeCourante << std::endl;

                        for (itVilleAdj = vectorSommetsAdjacents.begin(); itVilleAdj < vectorSommetsAdjacents.end() ; itVilleAdj++ )
                        {
                           villeAdjacenteCourante = (*itVilleAdj);
                           //std::cout << "ville courante ( for): " <<villeCourante << std::endl;
                           //std::cout << "ville courante adjacente: " << villeAdjacenteCourante << std::endl;
                           if(unReseau.arcExiste(villeCourante,villeAdjacenteCourante)){
                           ponde = unReseau.getPonderationsArc(villeCourante, villeAdjacenteCourante); // on remplis l'objet ponde avec la ponderation entre les deux sommets
                           }
                           else continue;
                           //std::cout << "ponderation de l'arc: " << ponde.ns << std::endl;
                           if(mapNomsPoids[villeCourante] + ponde.ns < mapNomsPoids[villeAdjacenteCourante]){
                              //std::cout << "a l'interieur valeur map Poids: " << mapNomsPoids[villeCourante]<< " pour: " << villeCourante << std::endl;
                              //std::cout << "poids avant changement pour adjacente: " << mapNomsPoids[villeAdjacenteCourante]<< " pour: " << villeAdjacenteCourante << std::endl;
                              mapNomsPoids[villeAdjacenteCourante] = mapNomsPoids[villeCourante] + ponde.ns;
                              //std::cout << "poids apres changement pour adjacente: " << mapNomsPoids[villeAdjacenteCourante]<< " pour: " << villeAdjacenteCourante << std::endl;

                              //std::cout << "precendent avant changement pour adjacente: " << mapPrecedent[villeAdjacenteCourante]<< " pour: " << villeAdjacenteCourante << std::endl;
                              mapPrecedent[villeAdjacenteCourante] = villeCourante; // on associe villeCourante comme precedent des Vecteurs adjacents
                              //std::cout << "precendent apres changement pour adjacente: " << mapPrecedent[villeAdjacenteCourante]<< " pour: " << villeAdjacenteCourante << std::endl;
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
                         if(unReseau.arcExiste(villeCourante,villeAdjacenteCourante)){
                         ponde = unReseau.getPonderationsArc(villeCourante, villeAdjacenteCourante); // on remplis l'objet ponde avec la ponderation entre les deux sommets
                         }else continue;
                         if (mapNomsPoids[villeAdjacenteCourante] > mapNomsPoids[villeCourante] + ponde.ns){
                                 cheminLePlusCourt.reussi = false;
                                 return cheminLePlusCourt;
                         }
                        }// fin for des villes adjacentes
                   }// fin for qui parcours tous les sommets
                   cheminLePlusCourt.reussi = true;
                   cheminLePlusCourt.nsTotal = mapNomsPoids[destination];
                   cheminLePlusCourt.listeVilles.push_back(destination); // on ajoute notre destination a la liste
                   //std::cout <<"valeur destination out: " << destination <<std::endl;
                   std::string courant = mapPrecedent[destination];
                   cheminLePlusCourt.listeVilles.push_back(courant);// on ajoute son precedent
                   //std::cout <<"valeur courant out: " << courant <<std::endl;
                   while(courant != origine){ // parcours de la destionation jusqu'a l'origine avec les precedents
                      //std::cout <<"valeur courant in : " << courant <<std::endl;
                      courant = mapPrecedent[courant];
                      cheminLePlusCourt.listeVilles.push_back(courant); // on append le vecteur avec le sommet courant
                   }

                   break; // break pour le selectcase
         }// fin switch
   return cheminLePlusCourt;
}

//NEW
/*
* \fn std::vector<std::string> rechercheCheminLargeur (const std::string& origine, const std::string& destination)
*
* \param[in] origine: le sommet d'origine
* \param[in] destination: le sommet de destination
*
* \return un tableau (vector) de string contenant les noms des villes du chemin
*/
std::vector<std::string> ReseauAerien::rechercheCheminLargeur (const std::string& origine, const std::string& destination)
{

   std::vector<Predecesseur> predecesseurs;

   if (!(unReseau.sommetExiste(origine)) && !(unReseau.sommetExiste(destination))) throw std::logic_error("rechercheCheminlargeur: Le sommet d'origine et/ou de destination n'existe pas");

   unReseau.setAllStatesFalse();
   std::queue<std::string> fileEnLargeur;

   unReseau.setState(origine, true);
   fileEnLargeur.push(origine);

   std::vector<std::string> parcours;
   while (!fileEnLargeur.empty())
   {
      std::string courant = fileEnLargeur.front();
      fileEnLargeur.pop();
      std::vector<std::string> vecSuccesseurs = unReseau.getSuccesseurs(courant);

      for (std::vector<std::string>::iterator it = vecSuccesseurs.begin(); it != vecSuccesseurs.end(); ++it)
      {
         if (unReseau.getState(*it) != true)
         {
            unReseau.setState(*it, true);
            fileEnLargeur.push(*it);
            Predecesseur predCourant;
            predCourant.sommet = *it;
            predCourant.pred = courant;
            predecesseurs.push_back(predCourant);
            if (*it == destination)
            {
               parcours.insert(parcours.begin(), destination);
               std::string recherche = destination;
               for (std::vector<Predecesseur>::reverse_iterator itPred = predecesseurs.rbegin(); itPred != predecesseurs.rend(); ++itPred)
               {
                  if (itPred->sommet.compare(recherche) == 0)
                  {
                     parcours.insert(parcours.begin(), itPred->pred);
                     recherche = itPred->pred;
                  }
               }
               return parcours;
            }
         }
      }
   }
   return parcours;
}

/**
 * \fn std::vector<std::string> ReseauAerien::split(std::string& str, std::string& delim)
*  \brief Separe un chaine de caractere selon un delimiteur donnee.
*
*  \pre la chaine a coupe
*  \pre le delimiteur selon lequel la chaine sera coupe
*
*  \post Retourne un vecteur de chaque nouvelle piece
*/
std::vector<std::string> ReseauAerien::split(std::string& str, std::string& delim)
   {
         unsigned start = 0;
         unsigned end;
         std::vector<std::string> v;

         while( (end = str.find(delim, start)) != std::string::npos )
         {
               v.push_back(str.substr(start, end-start));
               start = end + delim.length();
         }
         v.push_back(str.substr(start));
         return v;
   }


/**
 * \fn Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string& destination, bool dureeCout)
*  \brief Retourne le chemin le plus court selon l'algorithme A*.
*
*  \pre le reseau est valide.
*  \pre le point d'origine existe.
*  \pre le point d'arrivee existe.
*
*  \post Retourne le chemin le plus cours.
*  \post Retourne un booleen selon un succes ou un echec
*/
Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string& destination, bool dureeCout)
{
   Chemin cheminFinal;
      std::vector<std::string> nomsSommet = unReseau.listerNomsSommets();
      std::map<std::string, float> costs;
      std::map<std::string, std::string> precedent;
      std::priority_queue<std::string> priorityQueue;
      float cost;

      //Verifie que le point de depart et la destination sont valide
      if(!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
      {
         throw std::logic_error("Le point d'origine ou d'aller n'existe pas");
      }

      for(std::vector<std::string>::iterator it = nomsSommet.begin(); it < nomsSommet.end(); it++)
      {
         if((*it) == origine)
         {
            costs[(*it)] = 0;
            precedent[(*it)] = "";
            continue;
         }
         costs[(*it)] = infinie;
      }

      priorityQueue.push(origine);

      while(!priorityQueue.empty())
      {
         std::string currentCity = priorityQueue.top();
         priorityQueue.pop();

         for(unsigned int i = 0; i < unReseau.listerSommetsAdjacents(currentCity).size(); i++)
         {
            std::string target = unReseau.listerSommetsAdjacents(currentCity)[i];

            if(unReseau.arcExiste(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]))
            {
               if(dureeCout == true)
               {
                  cost = unReseau.getPonderationsArc(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]).cout + unReseau.getDistanceEucledienne(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]);
                  std::cout << "Cout : " << cost << std::endl;
               }
               else cost = unReseau.getPonderationsArc(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]).duree + unReseau.getDistanceEucledienne(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]);
            }
            else continue;

            float distanceThroughCurrentCity = costs.at(currentCity) + cost;

            std::cout << "Cout vers ville courante : " << distanceThroughCurrentCity << std::endl;

            if(distanceThroughCurrentCity < costs.at(target))
            {
               costs.at(target) = distanceThroughCurrentCity;
               precedent.insert(std::pair<std::string, std::string>(target, currentCity));
               std::cout << "Destination : " << target << std::endl;
               std::cout << "Ville courante : " << currentCity << std::endl;
               priorityQueue.push(target);
            }
         }
      }

      cheminFinal.reussi = true;
      cheminFinal.coutTotal = costs[destination];
      cheminFinal.dureeTotale = costs[destination];
      cheminFinal.listeVilles.push_back(destination);
      std::string courant = precedent[destination];
      cheminFinal.listeVilles.push_back(courant);

      while(courant != origine)
      {
         courant = precedent[courant];
         cheminFinal.listeVilles.push_back(courant);
      }

      return cheminFinal;
}

/**
* \fn Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string& destination, bool dureeCout)
*  \brief Retourne le chemin le plus court selon l'algorithme de Dijkstra.
*
*  \pre le reseau est valide.
*  \pre le point d'origine existe.
*  \pre le point d'arrivee existe.
*
*  \post Retourne le chemin le plus cours.
*  \post Retourne un booleen selon un succes ou un echec
*/
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string& destination, bool dureeCout)
{
   Chemin cheminFinal;
   std::vector<std::string> nomsSommet = unReseau.listerNomsSommets();
   std::map<std::string, float> costs;
   std::map<std::string, std::string> precedent;
   std::priority_queue<std::string> priorityQueue;
   float cost;

   //Verifie que le point de depart et la destination sont valide
   if(!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
   {
      throw std::logic_error("Le point d'origine ou d'aller n'existe pas");
   }

   for(std::vector<std::string>::iterator it = nomsSommet.begin(); it < nomsSommet.end(); it++)
   {
      if((*it) == origine)
      {
         costs[(*it)] = 0;
         precedent[(*it)] = "";
         continue;
      }
      costs[(*it)] = infinie;
   }

   priorityQueue.push(origine);

   while(!priorityQueue.empty())
   {
      std::string currentCity = priorityQueue.top();
      priorityQueue.pop();

      for(unsigned int i = 0; i < unReseau.listerSommetsAdjacents(currentCity).size(); i++)
      {
         std::string target = unReseau.listerSommetsAdjacents(currentCity)[i];

         if(unReseau.arcExiste(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]))
         {
            if(dureeCout == true)
            {
               cost = unReseau.getPonderationsArc(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]).cout;
               std::cout << "Cout : " << cost << std::endl;
            }
            else cost = unReseau.getPonderationsArc(currentCity, unReseau.listerSommetsAdjacents(currentCity)[i]).duree;
         }
         else continue;

         float distanceThroughCurrentCity = costs.at(currentCity) + cost;

         std::cout << "Cout vers ville courante : " << distanceThroughCurrentCity << std::endl;

         if(distanceThroughCurrentCity < costs.at(target))
         {
            costs.at(target) = distanceThroughCurrentCity;
            precedent.insert(std::pair<std::string, std::string>(target, currentCity));
            std::cout << "Destination : " << target << std::endl;
            std::cout << "Ville courante : " << currentCity << std::endl;
            priorityQueue.push(target);
         }
      }
   }

   cheminFinal.reussi = true;
   cheminFinal.coutTotal = costs[destination];
   cheminFinal.dureeTotale = costs[destination];
   cheminFinal.listeVilles.push_back(destination);
   std::string courant = precedent[destination];
   cheminFinal.listeVilles.push_back(courant);

   while(courant != origine)
   {
      courant = precedent[courant];
      cheminFinal.listeVilles.push_back(courant);
   }

   return cheminFinal;
}


/**
 * \fn void ReseauAerien::sauvegarderReseau(std::ofstream& SortieFichier) const
 * \brief Sauvegarder un r�seau dans un fichier texte (voir format du fichier dans l'�nonc� du Tp).
 * \pre SortieFichier est ouvert correctement.
 * \post SortieFichier n'est pas ferm� par la fonction.
 * \post Si les pr�conditions sont respect�es, les donn�es du r�seau sont sauvegard�es dans le fichier.
 * \exception logic_error si SortieFichier n'est pas ouvert correctement.
 */
void ReseauAerien::sauvegarderReseau(std::ofstream& SortieFichier) const
{

   if(SortieFichier)
   {
      SortieFichier << "Reseau Aerien: " << nomReseau << std::endl;
      SortieFichier << unReseau.nombreSommets() << "villes" << std::endl;
      SortieFichier << unReseau.nombreArcs() << "trajets" << std::endl;

      SortieFichier << "Liste des villes: " << std::endl;

      std::vector<std::string>::iterator villeCourante;
      std::vector<std::string>::iterator trajetCourant;
      std::string nomVilleCourante,villeAdjCourante;
      std::string nomProchaineDestination;

      for(villeCourante = unReseau.listerNomsSommets().begin(); villeCourante < unReseau.listerNomsSommets().end(); villeCourante++)
      {
         nomVilleCourante = (*villeCourante);
         SortieFichier << nomVilleCourante << std::endl;
         SortieFichier << unReseau.getCoordonnesSommet(nomVilleCourante).lg << " " << unReseau.getCoordonnesSommet(nomVilleCourante).lt << std::endl;
      }

      SortieFichier << "Liste des trajets: " << std::endl;

      for(trajetCourant = unReseau.listerNomsSommets().begin(); trajetCourant < unReseau.listerNomsSommets().end(); trajetCourant++)
      {

         nomVilleCourante = (*trajetCourant);
         std::cout << nomVilleCourante  << std::endl;
         for(unsigned int i = 0; i < unReseau.listerSommetsAdjacents(nomVilleCourante).size(); i++)
         {
            std::cout <<" Ville adjacentes in for : " <<unReseau.listerSommetsAdjacents(nomVilleCourante)[i] << std::endl;
            villeAdjCourante = unReseau.listerSommetsAdjacents(nomVilleCourante)[i];
            if(unReseau.arcExiste(nomVilleCourante,villeAdjCourante))
            {
               std::cout <<" YA UN ARC"  << std::endl;
               //std::cout << nomVilleCourante << unReseau.listerSommetsAdjacents(nomVilleCourante)[i] << std::endl;

               SortieFichier << nomVilleCourante << std::endl;
               SortieFichier << unReseau.listerSommetsAdjacents(nomVilleCourante)[i] << std::endl;
               SortieFichier << unReseau.getPonderationsArc(nomVilleCourante, unReseau.listerSommetsAdjacents(nomVilleCourante)[i]).duree << " "
                     << unReseau.getPonderationsArc(nomVilleCourante, unReseau.listerSommetsAdjacents(nomVilleCourante)[i]).cout << " "
                     << unReseau.getPonderationsArc(nomVilleCourante, unReseau.listerSommetsAdjacents(nomVilleCourante)[i]).ns << std::endl;
            }
         }
      }
   }
   else throw std::invalid_argument("saugardeReseau : le fichier texte n'est pas correctement ouvert");
}


/**
 * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
* \brief Charger un r�seau � partir d'un fichier texte en entr�e (voir format du fichier dans l'�nonc� du Tp).
* \pre Il y a assez de m�moire pour charger toutes les villes et les trajets du r�seau.
* \pre fichierEntree est ouvert corectement.
* \post fichierEntree n'est pas ferm� par la fonction.
* \post Si les pr�conditions sont respect�es, les donn�es du r�seau contenu dans le fichier en entr�e sont organis�es dans un graphe en m�moire.
* \exception bad_alloc si pas assez de m�moire pour contenir toute la liste du fichier.
* \exception logic_error si fichierEntree n'est pas ouvert correctement.
*/
void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
{
   if(fichierEntree.peek() == std::ifstream::traits_type::eof())
   {
      throw std::logic_error("chargerSE:logic_error le fichier texte est vide!");
   }
   if(fichierEntree)
   {
      std::string ligne;
      int indice = 0;

      //Var utilitaire pour contenir les infos temporairement
      std::string ville1;
      std::string ville2;
      std::vector<std::string> splitString;
      int passage = 1;

      while (getline(fichierEntree, ligne))
      {

         if(ligne == "Reseau Aerien: Air Canada")
         {
            indice = 0;
            continue;
         }// fin if
         if(ligne == "Liste des villes:"){
            indice = 1;
            continue;
         }//fin if
         if (ligne == "Liste des trajets:"){
            indice = 2;
            continue;
         }// fin if

         std::string delim ;

         switch(indice)
         {
            case 0:
               //Ajout du nom du reseau
               if(!isalpha(ligne[0]))
               {
                  continue;
               }
               else
               {
                  delim = ":";
                  splitString = ReseauAerien::split(ligne, delim);
                  std::string tempString = splitString[1];
                  nomReseau = tempString;
               }
               break;

            case 1:
               //test le premier charactere de la chaine pour voir si cest un nombre ou une lettre
               if(isalpha(ligne[0]))
               {
                  ville1 = ligne;
               }
               else
               {
                  delim = " ";
                  splitString = ReseauAerien::split(ligne, delim);
                  std::vector<float> longEtLat;

                  for(unsigned i = 0; i < splitString.size(); i++){
                        float temp = atof(splitString[i].c_str());
                        longEtLat.push_back(temp);
                     }

                  unReseau.ajouterSommet(ville1, longEtLat[0], longEtLat[1]);
               }
               break;
            case 2:
               //test le premier charactere de la chaine pour voir si cest un nombre ou une lettre
               if(isalpha(ligne[0]))
               {
                  if(passage == 1)
                  {
                    // std::cout << "Ville 1" << std::endl;
                     //std::cout << ville1 << std::endl;
                     ville1 = ligne;
                     passage = 0;
                  }
                  else
                  {
                    // std::cout << "Ville 2" << std::endl;
                     //std::cout << ville2 << std::endl;
                     ville2 = ligne;
                     passage = 1;
                  }
               }
               else
               {
                  delim = " ";
                  splitString = ReseauAerien::split(ligne, delim);
                  std::vector<float> longEtLat;

                  for(unsigned i = 0; i < splitString.size(); i++){
                     float temp = atof(splitString[i].c_str());
                     longEtLat.push_back(temp);
                  }
                  std::cout << "Ville 1 " << ville1 << "Ville 2: "<< ville2 <<  std::endl;
                  if(!(unReseau.arcExiste(ville1,ville2))){
                  unReseau.ajouterArc(ville1, ville2, longEtLat[0], longEtLat[1], longEtLat[2]);
               }
               }
               break;
         }// fin switch

      }// fin while
   }//fin if
   else
   {
      throw std::invalid_argument("chargerSE:le fichier texte n'est pas correctement ouvert");
   }

}
}//Fin du namespace
