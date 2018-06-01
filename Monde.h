#ifndef MONDE_H
#define MONDE_H

#include "Animal.h"
#include "Gazelle.h"
#include "Lion.h"
#include <unistd.h>

class Monde{
private:
  int taille_monde_x;
  int taille_monde_y;
  int nb_animaux;
  int nb_lion;
  int nb_gazelle;
  int energie;
  int animaux_manger;
  vector <vector <char> > tabMonde;
  vector <Animal*> tabanimal;

public:
  Monde(const int nb_animaux_init,const int taille_monde_x_init,const int taille_monde_y_init,const int nb_lion_init,const int nb_gazelle_init,const int energie_init);
  int getAnimaux_manger();
  int getAnimaux();
  int getLions();
  int getGazelles();
  vector<vector <char> > getTabMonde();
  vector <Animal*> getTabanimal();
  void peuplement();
  void affiche();
  void bouge(int i);
  void passeuntour();
  void mort(int i);
  void checkpredator(int i);
  void energiepredator(int i,int j);
};

#endif
