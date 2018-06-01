#include "Animal.h"
int Animal::nb_animaux=0;

//Constructeur d'Animal sans valeur
Animal::Animal() :
  vivant(true)
{
  x=0;
  y=0;
  energie=100;
  ++nb_animaux;
}
//Constructeur d'Animal avec des valeurs
Animal::Animal(const int x_init,const int y_init,const int energie_init):
vivant(true)
{
  x=x_init;
  y=y_init;
  energie=energie_init;
  ++nb_animaux;
}

//Destructeur d'Animal
Animal::~Animal(){
  --nb_animaux;
}

/******* Setter des variables d'Animal *******/
void Animal::setX(const int x_init){
  x=x_init;
}

void Animal::setY(const int y_init){
  y=y_init;
}
void Animal::setEnergie(const int energie_init){
  energie=energie_init;
}
void Animal::setLettre(const char lettre_init){
  lettre=lettre_init;
}
/***************************************/

//fonction qui sert a définir l'animal comme mort
void Animal::mort(){
  vivant=false;
}

/******* Getter des variables d'Animal *******/
int Animal::getX() const{
  return x;
}
int Animal::getY() const{
  return y;
}
int Animal::getEnergie() const{
  return energie;
}
bool Animal::getVivant() const{
  return vivant;
}
/***************************************/



//Affichage console de x,y et energie
void Animal::affiche() const{
  cout << "x:" << x << "\n" << "y:"<< y << "\n" <<"energie :"<< energie << "\n\n";
}
