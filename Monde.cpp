#include "Monde.h"

//Constructeur de Monde avec des valeurs
Monde::Monde(const int nb_animaux_init,const int taille_monde_x_init,const int taille_monde_y_init,const int nb_lion_init,const int nb_gazelle_init,const int energie_init){
  nb_animaux=nb_animaux_init;
  taille_monde_x=taille_monde_x_init;
  taille_monde_y=taille_monde_y_init;
  nb_lion=nb_lion_init;
  nb_gazelle=nb_gazelle_init;
  energie=energie_init;

  animaux_manger=0;
  tabMonde.resize(taille_monde_y, vector <char> (taille_monde_x));
  for(int i=0;i<taille_monde_y;i++){
    for(int j=0;j<taille_monde_x;j++){
      tabMonde[i][j]='.';
    }
  }
}

//Peuplement du monde
void Monde::peuplement(){
  tabanimal.resize(nb_animaux);
  for (int i = 0; i < nb_animaux; i++) {
      int xrand = rand()%taille_monde_x;
      int yrand = rand()%taille_monde_y;
      if(i<=nb_gazelle-1 && nb_gazelle!=0){
        tabanimal[i]=new Gazelles(xrand,yrand,energie);
      }else{
        tabanimal[i]=new Lions(xrand,yrand,energie);
      }
  }
}

/******* Getter des variables d'Animal *******/
int Monde::getAnimaux_manger(){
  return animaux_manger;
}

int Monde::getLions(){
  return nb_lion;
}

int Monde::getGazelles(){
  return nb_gazelle;
}

int Monde::getAnimaux(){
return nb_animaux;
}

vector<vector <char> > Monde::getTabMonde(){
  return tabMonde;
}

vector <Animal*> Monde::getTabanimal(){
  return tabanimal;
}
/***************************************/

//Affichage du monde en console
void Monde::affiche(){
  system("clear");
  for(int i=0;i<taille_monde_y;i++){
    for(int j=0;j<taille_monde_x;j++){
      cout<<tabMonde[i][j];
    }
    cout<< '\n';
  }
  usleep(100000);
}

//Déplacement des animaux dans le Monde
void Monde::bouge(int i){
  switch (rand()%4) { //Valeur aleatoire entre 0 et 4

    case 0: //nord
      if (tabanimal[i]->getY()-1 >= 0) {
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]='.';
        tabanimal[i]->setY(tabanimal[i]->getY()-1);
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]=tabanimal[i]->getLettre(); //affiche la lettre de animal
      }
      break;

    case 1: //sud
      if (tabanimal[i]->getY()+1 < taille_monde_y) {
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]='.';
        tabanimal[i]->setY(tabanimal[i]->getY()+1);
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]=tabanimal[i]->getLettre();
      }
      break;

    case 2: //ouest
      if (tabanimal[i]->getX()-1 >= 0) {
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]='.';
        tabanimal[i]->setX(tabanimal[i]->getX()-1);
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]=tabanimal[i]->getLettre();

      }
      break;

    case 3: //est
      if (tabanimal[i]->getX()+1 < taille_monde_x) {
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]='.';
        tabanimal[i]->setX(tabanimal[i]->getX()+1);
        tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]=tabanimal[i]->getLettre();
      }
      break;
  }
  tabanimal[i]->setEnergie(tabanimal[i]->getEnergie()-1);
}

//Action a réaliser a chaque tour
void Monde::passeuntour(){
  for (int i = 0; i < nb_animaux; i++) {
    if(tabanimal[i]->getEnergie()<=0 && tabanimal[i]->getLettre()!='X' ){
      mort(i);
    }else if(tabanimal[i]->getLettre()!='X'){
      bouge(i);
      checkpredator(i);
    }
  }
}

//Regarde s'il y'a un lion et une gazelle sur la meme case
void Monde::checkpredator(int i){
  bool fini=false;
  for(int j=0;j<nb_animaux-1 && fini==false ;j++){
    if(tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]==tabMonde[tabanimal[j]->getY()][tabanimal[j]->getX()] && i!=j){
      if(tabanimal[i]->getLettre()=='G' && tabanimal[j]->getLettre()=='L'){
      energiepredator(j,i);
      mort(i);
      fini=true;
      std::cout << "ok3" << '\n';
    }else if(tabanimal[i]->getLettre()=='L' && tabanimal[j]->getLettre()=='G'){
      energiepredator(i,j);
      mort(j);
      fini=true;
      std::cout << "ok2" << '\n';
    }
    }
  }
}

//Tuer un animal
void Monde::mort(int i){
  tabMonde[tabanimal[i]->getY()][tabanimal[i]->getX()]='X';
  if(tabanimal[i]->getLettre()=='G'){
    nb_gazelle-=1;
  }else{
    nb_lion-=1;
  }
  tabanimal[i]->setLettre('X');
}

//Récuperation de l'energie du predator
void Monde::energiepredator(int i_lion,int j_gazelle){
  tabanimal[i_lion]->setEnergie(tabanimal[j_gazelle]->getEnergie()+tabanimal[i_lion]->getEnergie());
  tabanimal[j_gazelle]->setEnergie(0);
  animaux_manger+=1;
}
