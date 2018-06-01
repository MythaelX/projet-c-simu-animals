#include "menu_bar.h"

Menubar::Menubar(QWidget *parent) : QWidget(parent)
{
  setFixedHeight(35); //taille de la barre de menu
  m_cache=NULL;
  m_Title=new QLabel(this);
  m_Title->setStyleSheet("color: white; font-family: Arial; font-weight: bold; font-size: 14px"); //Design du titre de la fenetre

  m_Minimize= new BoutonFenetre(BoutonFenetre::bouton_minimize, this);
  m_Maximize= new BoutonFenetre(BoutonFenetre::bouton_maximize, this);
  m_Close= new BoutonFenetre(BoutonFenetre::bouton_close, this);

  /********** Taille des boutons de la barre de menu **********/
  int size=20;
  m_Minimize->setFixedSize(size,size);
  m_Maximize->setFixedSize(size,size);
  m_Close->setFixedSize(size,size);
  /*************************************/

  /********** Layout contenant les boutons **********/
  m_layoutTitleBar = new QHBoxLayout(this);
  m_layoutTitleBar->setContentsMargins(0,2,5,0);
  m_layoutTitleBar->addWidget(m_Title);
  m_layoutTitleBar->addWidget(m_Minimize);
  m_layoutTitleBar->addWidget(m_Maximize);
  m_layoutTitleBar->addWidget(m_Close);
  /*************************************/
  connect(m_Minimize, SIGNAL(clicked()),this, SLOT(Minimized()));
  connect(m_Maximize, SIGNAL(clicked()),this, SLOT(Maximized()));
  connect(m_Close, SIGNAL(clicked()),this, SLOT(Quit()));
}

Menubar::~Menubar(){}


void Menubar::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
  delete m_cache; // Suppresion de l'ancien cache
  m_cache = new QPixmap(size());  // Creation du cache avec la meme taille que le widget
  m_cache->fill(Qt::transparent);  // Creation d'un fond transparent

  QPainter painter(m_cache);
  QColor lightBlue(177, 177, 203, 255);
  QColor gradientStart(0, 0, 0, 0);
  QColor gradientEnd(0, 0, 0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd);

  /********** Zone du titre de la barre de menu **********/
  QPolygon frame;
  frame << QPoint(20, 4) << QPoint(width() - 4, 4) << QPoint(width() - 4, 32) << QPoint(4, 32)
        << QPoint(4, 20);
  painter.setPen(QPen(lightBlue));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(frame);
  /***************************************/

  /********** Zone des Boutons de la barre de menu **********/
  QPolygon buttons;
  buttons << QPoint(width() - 80, 4) << QPoint(width() -  4, 4) << QPoint(width() -  4, 32)
          << QPoint(width() - 88, 32) << QPoint(width() - 88, 12);
  painter.setPen(QPen(lightBlue));
  painter.setBrush(QBrush(lightBlue));
  painter.drawPolygon(buttons);
  /**********************************************/
  m_Title->move(28,4);
  m_Title->resize(width() - 116, 29);
}

/**********  Fonction qui dessine la bar de menu **********/
void Menubar::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);
  if(m_cache != NULL){
    QPainter painter(this);
    painter.drawPixmap(0, 0, *m_cache);
  }
}
/**********************************************/

//Recupération du titre de la fenetrePrincipale
void Menubar::initialisation_titre(const QString &title)
{
  m_Title->setText(title);
}

/********** Gestion des fonctionalité des 3 boutons(Minimized,Maximized,close) **********/
void Menubar::Minimized(){
    window()->showMinimized();
}

void Menubar::Maximized()
{

  if(window()->windowState() != Qt::WindowMaximized){
    window()->showMaximized();
  }else{
    window()->showNormal();
  }
}

void Menubar::Quit(){
  qApp->quit();
}
/**********************************************/

/******* Déplacement de la fenetre *********/
void Menubar::mousePressEvent(QMouseEvent *event){
  m_Diff = event->pos();
  setCursor(QCursor(Qt::SizeAllCursor));
}

void Menubar::mouseReleaseEvent(QMouseEvent *event){
  Q_UNUSED(event);
  setCursor(QCursor(Qt::ArrowCursor));
}

void Menubar::mouseMoveEvent(QMouseEvent *event){
  QPoint p = event->globalPos();
  window()->move(p - m_Diff);
}
/**********************************************/
