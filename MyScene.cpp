#include "MyScene.h"

MyScene::MyScene(int nb_animaux,int taille_monde_x_init,int taille_monde_y_init,int nb_lion,int nb_gazelle,int energie,int vitesse_init,QObject *parent) : QGraphicsScene(parent)
{
  //Récupération de la taille du monde
  taille_monde_x=taille_monde_x_init;
  taille_monde_y=taille_monde_y_init;
  /********** Valeur par défaut **********/
  if(nb_animaux==0 && (taille_monde_x==0 || taille_monde_y==0)){
    nb_animaux=10;
    taille_monde_x=10;
    taille_monde_y=10;
    nb_lion=5;
    nb_gazelle=5;
    energie=200;
  }
  /*****************************************/
  sol.resize(taille_monde_y, vector<QGraphicsPixmapItem*> (taille_monde_x));
  animaux_graphique.resize(nb_animaux);
  le_monde=new Monde(nb_animaux,taille_monde_x,taille_monde_y,nb_lion,nb_gazelle,energie); //création du monde
  le_monde->peuplement();
  tabMonde=le_monde->getTabMonde();

  //AffichageduMonde
  affichageMonde();
  Init_Animal();

  //Affichage nombre de lions
  texte="Nombre de lions : "+QString::number(le_monde->getLions());
  affichage_nb_lions = new QGraphicsTextItem(texte);
  affichage_nb_lions->setDefaultTextColor(Qt::white);
  affichage_nb_lions->setPos(this->width()-150, this->height());
  this->addItem(affichage_nb_lions);

  //Affichage nombre de gazelles
  texte="Nombre de gazelles : "+QString::number(le_monde->getGazelles());
  affichage_nb_gazelles = new QGraphicsTextItem(texte);
  affichage_nb_gazelles->setDefaultTextColor(Qt::white);
  affichage_nb_gazelles->setPos(this->width()-150, this->height());
  this->addItem(affichage_nb_gazelles);

  //Affichage nombre d'animaux mangé
  texte="Nombre de mort manger : "+QString::number(le_monde->getAnimaux_manger());
  affichage_nb_animaux_mange = new QGraphicsTextItem(texte);
  affichage_nb_animaux_mange->setDefaultTextColor(Qt::white);
  affichage_nb_animaux_mange->setPos(this->width()-150, this->height());
  this->addItem(affichage_nb_animaux_mange);

  //Timer
  timer= new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(update()));
  timer->start(320-vitesse_init*3);
}

void MyScene::update(){
  le_monde->passeuntour();
  tabMonde=le_monde->getTabMonde();
  affichageAnimal();
  statut(); //Affichage du nb de lion et gazelle vivante et du nombre d'animaux mangé
}

/********** Sol du monde **********/
void MyScene::affichageMonde(){
  for (int i = 0; i < taille_monde_y; i++) {
    for (int j = 0; j < taille_monde_x; j++) {
      sol[i][j] = new QGraphicsPixmapItem(QPixmap("img/sol.png"));
      sol[i][j]->setPos(j*32,i*32);
      this->addItem(sol[i][j]);
    }
  }
}
/*****************************************/

/******* Création des animaux_graphique par rapport a la tabanimal **********/
void MyScene::Init_Animal(){
  int x,y;
  char type_animal;
  tabanimal=le_monde->getTabanimal();
  taille_tabanimal=le_monde->getAnimaux();
  for (int i = 0; i < taille_tabanimal; i++) {
      y=tabanimal[i]->getY();
      x=tabanimal[i]->getX();
      type_animal=tabanimal[i]->getLettre();
      if(type_animal=='L'){
        animaux_graphique[i] = new QGraphicsPixmapItem(QPixmap("img/lion.png"));
      }else if(type_animal=='G'){
        animaux_graphique[i] = new QGraphicsPixmapItem(QPixmap("img/gazelle.png"));
      }else if(type_animal=='X'){
        animaux_graphique[i] = new QGraphicsPixmapItem(QPixmap("img/tombe.png"));
      }
      animaux_graphique[i]->setPos(x*32,y*32);
      this->addItem(animaux_graphique[i]);
  }
}
/*****************************************/

/******* Déplacement des animaux dans la vue graphique et changement d'image si l'animal est mort **********/
void MyScene::affichageAnimal(){
  tabanimal=le_monde->getTabanimal();
  int x,y;
  char type_animal;
  for (int i = 0; i < taille_tabanimal; i++) {
    type_animal=tabanimal[i]->getLettre();

    if(type_animal=='X' && tabanimal[i]->getVivant()==true){
      delete animaux_graphique[i];
      animaux_graphique[i] = new QGraphicsPixmapItem(QPixmap("img/tombe.png"));
      this->addItem(animaux_graphique[i]);
      tabanimal[i]->mort(); //On utilise la varriable vivant de class Animal pour éviter de refaire un changement d'image
    }
      y=tabanimal[i]->getY();
      x=tabanimal[i]->getX();
      animaux_graphique[i]->setPos(x*32,y*32);
  }
}
/*****************************************/

/******* Affichage du nb de lion et gazelle vivante et du nombre d'animaux mangé **********/
void MyScene::statut(){
texte="Nombre de lions : "+QString::number(le_monde->getLions());
affichage_nb_lions->setPlainText(texte);
texte="Nombre de gazelles : "+QString::number(le_monde->getGazelles());
affichage_nb_gazelles->setPlainText(texte);
texte="Nombre de mort manger : "+QString::number(le_monde->getAnimaux_manger());
affichage_nb_animaux_mange->setPlainText(texte);
}

void MyScene::changementvitesse(int vitesse_init) {
  vitesse=vitesse_init;
  timer->setInterval(320-vitesse*3);
}
/*****************************************/
