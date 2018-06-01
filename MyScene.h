#ifndef MYSCENE_H
#define MYSCENE_H
#include <QtWidgets>
#include "Monde.h"

class MyScene : public QGraphicsScene {
  Q_OBJECT

  public :
    MyScene(int nb_animaux,int taille_monde_x,int taille_monde_y,int nb_lion,int nb_gazelle,int energie,int vitesse_init,QObject *parent=0);
    void affichageMonde();
    void affichageAnimal();
    void Init_Animal();
    void changementvitesse(int vitesse_init);
    void statut();

  public slots:
    void update();

  private :
    Monde* le_monde;
    vector<vector <char> > tabMonde;
    vector <Animal*> tabanimal;
    QTimer *timer;
    QGraphicsRectItem * qgri;
    vector <vector <QGraphicsPixmapItem*>  > sol;
    vector <QGraphicsPixmapItem*> animaux_graphique;
    int taille_monde_x;
    int taille_monde_y;
    int vitesse;
    int taille_tabanimal;
    QString texte;
    QGraphicsTextItem* affichage_nb_lions;
    QGraphicsTextItem* affichage_nb_gazelles;
    QGraphicsTextItem* affichage_nb_animaux_mange;
};
#endif
