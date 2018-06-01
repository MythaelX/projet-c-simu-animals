#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <vector>
using namespace std;

class Animal{
protected:
  int x,y,energie;
  char lettre;
  bool vivant;
public:
  static int nb_animaux;
  Animal();
  Animal(const int x_init,const int y_init, const int energie_init);
  virtual ~Animal();
  int getX() const;
  int getY() const;
  int getEnergie() const;
  bool getVivant() const;
  void setX(const int x_init);
  void setY(const int y_init);
  void setEnergie(const int energie_init);
  void setLettre(const char lettre_init);
  void affiche() const;
  void mort();
  virtual char getLettre()const=0;
};

#endif
