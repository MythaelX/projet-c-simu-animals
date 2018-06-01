#include "Monde.h"
#include"fenetrePrincipale.h"

int main(int argc, char **argv){
  srand(time(NULL));
  int choix;
  cout << "Choisez un mode affichage ? (0:Quitter; 1:Console; 2+:QT)\n";
  cin >> choix;
  //Quitter :
  if (choix==0){
    return 0;
  //mode console :
  }else if(choix==1){
    int taille_monde_x,taille_monde_y,nb_lion,nb_gazelle,energie;
    cout << "Propriétés du monde :\nTaille du monde en X :";
    cin >> taille_monde_x;
    cout << "Taille du monde en Y :";
    cin >>  taille_monde_y;
    cout << "Nombre de lions :";
    cin >>  nb_lion;
    cout << "Nombre de gazelles :";
    cin >>  nb_gazelle;
    cout << "Energie des animaux :";
    cin >>  energie;
    Monde le_monde(nb_lion+nb_gazelle,taille_monde_x,taille_monde_y,nb_lion,nb_gazelle,energie);
    le_monde.peuplement();
    while (le_monde.getAnimaux()!=0){
      le_monde.affiche();
      le_monde.passeuntour();
    }
    cout << "\n\nnombre d'animaux mangé:" << le_monde.getAnimaux_manger()<<"\n";
  //mode graphique:
  }else{
    QApplication app (argc, argv);
    FenetrePrincipale w;
    w.show();
    return app.exec();
  }
}
