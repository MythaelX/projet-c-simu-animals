#include "fenetrePrincipale.h"
#include "MyScene.h"
#include "menu_bar.h"

//Constructeur de FenetrePrincipale
FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QMainWindow(parent) {
  m_cache=NULL;
  this->setWindowFlags(Qt::FramelessWindowHint); //suppresion des bordures de la fenetrePrincipale

  /********** Parametre de la fenetre principale **********/
  menu_bar =new Menubar;
  menu_bar->initialisation_titre("Mini projet C++");
  resize(500, 600); //Taille fenetre
  setAttribute(Qt::WA_TranslucentBackground); //Transparence de la fenetre
  centrer_ecran();
  /*************************************/

  /********** le layout main **********/
  widget_general = new QWidget;
  layout_principal=new QGridLayout;
  layout_principal->setMargin(0);
  layout_principal->setSpacing(0);
  layout_principal->addWidget(menu_bar,0,0);
  layout_principal->setRowStretch(5, 1);
  widget_general->setLayout(layout_principal);
  this->setCentralWidget(widget_general);
  /*************************************/

  /********** Le Label du titre de l'onglet + case pleine écran **********/
  titre_onglet=new QLabel(this);
  titre_onglet->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 30px");
  titre_onglet->setText("Propriétés de la simulation");
  titre_onglet->setAlignment(Qt::AlignHCenter);
  titre_onglet->setContentsMargins(0,20,0,0);
  layout_principal->addWidget(titre_onglet,1,0);
  /*************************************/

  /********** Le layout du formulaire de la configuration de la simulation et de ses widgets **********/
  taille_monde_x = new QSpinBox;
  taille_monde_x->setRange(0, 9999);

  taille_monde_y= new QSpinBox;
  taille_monde_y->setRange(0, 9999);

  lion = new QSpinBox;
  lion->setRange(0, 999);

  gazelle = new QSpinBox;
  gazelle->setRange(0, 999);

  energie = new QSpinBox;
  energie->setRange(0, 999);

  QFormLayout *layout_form = new QFormLayout;
  layout_form->setSpacing(0);
  layout_form->setContentsMargins(0,20,0,0);
  layout_form->setVerticalSpacing(5);

  texte_monde_x=new QLabel(this);
  texte_monde_x->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px");
  texte_monde_x->setText("Taille du monde en X :");
  layout_form->addRow(texte_monde_x,taille_monde_x);

  texte_monde_y=new QLabel(this);
  texte_monde_y->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px");
  texte_monde_y->setText("Taille du monde en Y :");
  layout_form->addRow(texte_monde_y, taille_monde_y);

  texte_lion=new QLabel(this);
  texte_lion->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px");
  texte_lion->setText("Nombre de lion :");
  layout_form->addRow(texte_lion, lion);

  texte_gazelle=new QLabel(this);
  texte_gazelle->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px");
  texte_gazelle->setText("Nombre de gazelle :");
  layout_form->addRow(texte_gazelle, gazelle);

  texte_energie=new QLabel(this);
  texte_energie->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px");
  texte_energie->setText("Nombre d'énergie initial :");
  layout_form->addRow(texte_energie, energie);

  layout_form->setFormAlignment(Qt::AlignHCenter);
  layout_principal->addLayout(layout_form,2,0);
  /*************************************/

  /********** Le layout du slider vitesse **********/
  layout_vitesse = new QVBoxLayout;
  texte_vitesse=new QLabel(this);
  texte_vitesse->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 16px");
  texte_vitesse->setText("Vitesse:");
  layout_vitesse->addWidget(texte_vitesse);
  layout_vitesse->setContentsMargins(50,30,30,200);
  valeur_vitesse = new QLCDNumber(3);
  valeur_vitesse->setSegmentStyle(QLCDNumber::Filled);
  valeur_vitesse->setFixedHeight(50);
  vitesse = new QSlider(Qt::Horizontal);
  vitesse->setRange(0,100);
  connect(vitesse, SIGNAL(valueChanged(int)),valeur_vitesse, SLOT(display(int)));

  layout_vitesse->addWidget(valeur_vitesse);
  layout_vitesse->addWidget(vitesse);
  layout_vitesse->setAlignment(Qt::AlignHCenter);
  layout_principal->addLayout(layout_vitesse,3,0);
  /*************************************/

  /********** Le layout du bouton pour demarrer la simulation **********/
  layout_bouton_demarrer = new QVBoxLayout;
  layout_bouton_demarrer->setContentsMargins(50,20,30,0);

  bouton_demarrer = new QPushButton("Démarrer la simulation");
  connect(bouton_demarrer, SIGNAL(clicked()), this, SLOT(slot_demarrer()));
  bouton_demarrer->setFont(QFont("Arial bold", 30));
  bouton_demarrer->setCursor(Qt::PointingHandCursor);

  layout_bouton_demarrer->addWidget(bouton_demarrer);
  layout_principal->addLayout(layout_bouton_demarrer,3,0);
  /*************************************/

  /********** Le layout du bouton pour fermer la fenetre **********/
  layout_bouton_stop = new QVBoxLayout;
  layout_bouton_stop->setContentsMargins(50,170,30,0);
  bouton_quitter = new QPushButton("Quitter");
  bouton_quitter->setFont(QFont("Arial bold", 30));
  bouton_quitter->setCursor(Qt::PointingHandCursor);
  connect(bouton_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

  layout_bouton_stop->addWidget(bouton_quitter);
  layout_principal->addLayout(layout_bouton_stop,3,0);
  /*************************************/
}

//Destructeur fenetrePrincipale
FenetrePrincipale::~FenetrePrincipale(){}

/********** Fonction pour centrer la fenetre **********/
void FenetrePrincipale::centrer_ecran()
{
  widget = QApplication::desktop();
  int bureau_width = widget->width();
  int bureau_height = widget->height();
  int x = bureau_width / 2 - this->width() / 2;
  int y = bureau_height / 2 - this->height() / 2;
  this->move(QPoint(x, y));
}
/*************************************/

/**********  Fonction qui dessine la fenetre **********/
void FenetrePrincipale::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);
  if(m_cache != NULL)
  {
    QPainter painter(this);
    painter.drawPixmap(0, 0, *m_cache);
  }
}
/*************************************/
void FenetrePrincipale::resizeEvent(QResizeEvent *event)
{
  QColor darkBlue (23, 23, 34);
  QColor lightBlue(177, 177, 203);
  Q_UNUSED(event);

  delete m_cache;
  m_cache = new QPixmap(size());
  m_cache->fill(Qt::transparent);
  QPainter painter(m_cache);

  /********** Fond de la fenetre **********/
  QPolygon background;
  if(simulation==false){
  background << QPoint(0, 16) << QPoint(16, 0)<< QPoint(width() - 1, 0) <<QPoint(width() - 1, height()-17)  <<QPoint(width() - 17, height()-1)   << QPoint(36, height() -  1)
             << QPoint(16, height() - 21) << QPoint(16, 272) << QPoint(0, 256);
  }else{
    background << QPoint(0, 16) << QPoint(16, 0)<< QPoint(width() - 1, 0) <<QPoint(width() - 1, height()-17)  <<QPoint(width() - 17, height()-1)   << QPoint(17, height() -  1)
               << QPoint(0,height() - 18);
  }
  painter.setPen(QPen(darkBlue));
  painter.setBrush(QBrush(darkBlue));
  painter.drawPolygon(background);
  /*****************************************/

  /********** Bordure de la fenetre **********/
  QPolygon bordure;
  if(simulation==false){
  bordure << QPoint(4, 20)<< QPoint(20, 4)<< QPoint(width() - 4, 4) << QPoint(width() - 4, height() - 20) << QPoint(width() - 20, height() - 5)  << QPoint(40, height() - 5)
          << QPoint(20, height() - 25) << QPoint(20, 268) << QPoint(4, 252);
  }else{
  bordure << QPoint(4, 20)<< QPoint(20, 4)<< QPoint(width() - 4, 4) << QPoint(width() - 4, height() - 20) << QPoint(width() - 20, height() - 5)  << QPoint(40, height() - 5)
          << QPoint(19, height() - 5) << QPoint(4, height() - 20);
  }
  painter.setPen(QPen(lightBlue));
  painter.setBrush(Qt::NoBrush);
  painter.drawPolygon(bordure);
  /*****************************************/
}

/********** Affichage de la simulation **********/
void FenetrePrincipale::slot_demarrer() {
  myscene = new MyScene((lion->value()+gazelle->value()),taille_monde_x->value(),taille_monde_y->value(),lion->value(),gazelle->value(),energie->value(),valeur_vitesse->value(),this);
  /********** Suppresion des layouts et des widgets inutile **********/
  delete bouton_demarrer;
  delete layout_bouton_demarrer;
  delete texte_energie;
  delete texte_gazelle;
  delete texte_lion;
  delete texte_monde_y;
  delete texte_monde_x;
  delete energie;
  delete gazelle;
  delete lion;
  delete taille_monde_x;
  delete taille_monde_y;
  /*****************************************/

  simulation=true; //variable pour le dimensionnement de la fenetre (changement de figure pour l'affichage)
  connect(vitesse, SIGNAL(valueChanged(int)),this, SLOT(scene_vitesse())); //Récuperation de la valeur vitesse quand la valeur change
  resize(1000,900);
  centrer_ecran();
  titre_onglet->setText("===== Simulation du monde =====");
  /********** Le layout de la vue de la scène  **********/
  QVBoxLayout *layout_graphique=new QVBoxLayout;
  myview = new QGraphicsView(myscene, this);
  myview->setBackgroundBrush(QBrush(Qt::black));
  layout_graphique->setContentsMargins(20,5,20,0);
  layout_graphique->addWidget(myview);
  layout_principal->addLayout(layout_graphique,2,0);
  /*************************************/

  /********** Replacement des layouts qui n'ont pas été suprimé  **********/
  layout_principal->removeItem(layout_vitesse);
  layout_vitesse->setContentsMargins(50,5,50,0);
  layout_principal->addLayout(layout_vitesse,4,0);
  layout_principal->removeItem(layout_bouton_stop);
  layout_bouton_stop->setContentsMargins(50,10,50,20);
  layout_principal->addLayout(layout_bouton_stop,5,0);
  /*************************************/
  /********** Son de la simulation  **********/
  son = new QSound("sound/music.wav");
  son->play();
  /*************************************/
}
/*************************************/

//Fonction qui recupere la vitesse pendant la simulation
void FenetrePrincipale::scene_vitesse(){
  myscene->changementvitesse(valeur_vitesse->value());
}
