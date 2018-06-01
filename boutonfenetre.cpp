#include "boutonfenetre.h"
#include <QPainter>

//Constructeur BoutonFenetre sans valeur
BoutonFenetre::BoutonFenetre(TypeBouton type, QWidget *parent) : QAbstractButton(parent),
  m_type(type),m_statut(statut_normal),m_normal (NULL),m_surligne(NULL),m_clique(NULL){
}

//Destructeur BoutonFenetre
BoutonFenetre::~BoutonFenetre(){
  delete m_normal ;
  delete m_surligne;
  delete m_clique;
}

//Fonction de redimensionnement de la fenetre
void BoutonFenetre::resizeEvent(QResizeEvent *event){
  Q_UNUSED(event);
  InitPixmaps();
}

//Fonction qui dessine les pixmap par rapport a leur type
void BoutonFenetre::paintEvent(QPaintEvent  *event){
  Q_UNUSED(event);
  QPainter painter(this);

  if(isEnabled()){
    switch(m_statut){
    case statut_normal:
      if(m_normal  != NULL) painter.drawPixmap(0, 0, *m_normal );
      break;
    case statut_surligne:
      if(m_surligne != NULL) painter.drawPixmap(0, 0, *m_surligne);
      break;
    case statut_clique:
      if(m_clique != NULL) painter.drawPixmap(0, 0, *m_clique);
      break;
    }
  }else{
    if(m_normal != NULL) painter.drawPixmap(0, 0, *m_normal);
  }
}

/********** Initialisation des Pixmap **********/
void BoutonFenetre::InitPixmaps(){
  InitPixmap(&m_normal );
  InitPixmap(&m_surligne);
  InitPixmap(&m_clique);

  switch(m_type){
  case bouton_minimize:
    InitMinimize();
    break;
  case bouton_maximize:
    InitMaximize();
    break;
  case bouton_close:
    InitClose();
    break;
  }
}

void BoutonFenetre::InitPixmap(QPixmap **pixmap){
  delete *pixmap;
  *pixmap = new QPixmap(size());
  (*pixmap)->fill(Qt::transparent);
}
/*************************************/

void BoutonFenetre::InitMinimize()
{
  /********** Bordure du bouton **********/
  QPolygon bordure;
  bordure << QPoint(0, 4) << QPoint(4, 0) << QPoint(width() - 1, 0) << QPoint(width() - 1, height() - 1)
         << QPoint(0, height() - 1);
  /*************************************/

  /********** Symbole du bouton **********/
  QPolygon symbole;
  symbole << QPoint(4, height() - 8) << QPoint(width() - 4, height() - 8) << QPoint(width() - 4, height() - 4)
         << QPoint(4, height() - 4);
  /*************************************/

  QColor gradientStart(0, 0, 0, 0);
  QColor gradientEnd(0, 0, 0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd  );

  QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
  invertlinearGrad.setColorAt(0, gradientEnd);
  invertlinearGrad.setColorAt(1, gradientStart);

  QPainter painter;

  /********** Vision normal **********/
  painter.begin(m_normal);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::black));
  painter.drawPolygon(symbole);
  painter.end();
  /****************************/

  /********** Vision surligné **********/
  painter.begin(m_surligne);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::white));
  painter.drawPolygon(symbole);
  painter.end();
  /*****************************/

  /********** Vision cliqué **********/
  painter.begin(m_clique);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(invertlinearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(Qt::white));
  painter.drawPolygon(symbole);
  painter.end();
  /*****************************/
}

void BoutonFenetre::InitMaximize()
{
  /********** Bordure du bouton **********/
  QPolygon bordure;
  bordure << QPoint(0, 0) << QPoint(width() - 5, 0) << QPoint(width() - 1, 4)
         << QPoint(width() - 1, height() - 1) << QPoint(0, height() - 1);
  /*************************************/

  /********** Symbole du bouton **********/
  QPolygon symbole1, symbole2;
  symbole1 << QPoint(4, 4) << QPoint(width() - 4, 4) << QPoint(width() - 4, 8) << QPoint(4, 8);

  symbole2 << QPoint(4, 8) << QPoint(width() - 4, 8) << QPoint(width() - 4, height() - 4)
          << QPoint(4, height() - 4);
  /*************************************/

  QColor gradientStart(0, 0, 0, 0);
  QColor gradientEnd(0, 0, 0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd);

  QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
  invertlinearGrad.setColorAt(0, gradientEnd);
  invertlinearGrad.setColorAt(1, gradientStart);

  QPainter painter;

  /********** Vision normal **********/
  painter.begin(m_normal);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(Qt::black));
  painter.drawPolygon(symbole1);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(Qt::NoBrush);
  painter.drawPolygon(symbole2);
  painter.end();
  /****************************/

  /********** Vision surligné **********/
  painter.begin(m_surligne);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(Qt::white));
  painter.setBrush(QBrush(Qt::white));
  painter.drawPolygon(symbole1);
  painter.setPen(QPen(Qt::white));
  painter.setBrush(Qt::NoBrush);
  painter.drawPolygon(symbole2);
  painter.end();
  /*****************************/

  /********** Vision cliqué **********/
  painter.begin(m_clique);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(invertlinearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(Qt::white));
  painter.setBrush(QBrush(Qt::white));
  painter.drawPolygon(symbole1);
  painter.setPen(QPen(Qt::white));
  painter.setBrush(Qt::NoBrush);
  painter.drawPolygon(symbole2);
  painter.end();
  /*****************************/
}

void BoutonFenetre::InitClose()
{
  /********** Bordure du bouton **********/
  QPolygon bordure;
  bordure << QPoint(0, 4)<< QPoint(4, 0) << QPoint(width() - 5, 0) << QPoint(width() - 1, 4)
         << QPoint(width() - 1, height() - 5) << QPoint(width() - 5, height() - 1)
         << QPoint(4, height() - 1) << QPoint(0, height() - 5);
  /*************************************/

  /********** Symbole du bouton **********/
  QLine symbole1(QPoint(4, 4), QPoint(width() - 5, height() - 5));
  QLine symbole2(QPoint(width() - 5, 4), QPoint(4, height() - 5));
  /*************************************/

  QColor gradientStart(  0,   0,   0,   0);
  QColor gradientEnd  (  0,   0,   0, 220);

  QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  linearGrad.setColorAt(0, gradientStart);
  linearGrad.setColorAt(1, gradientEnd);

  QLinearGradient invertlinearGrad(QPointF(0, 0), QPointF(0, height()));
  invertlinearGrad.setColorAt(0, gradientEnd);
  invertlinearGrad.setColorAt(1, gradientStart);

  QPainter painter;

  /********** Vision normal **********/
  painter.begin(m_normal);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(QBrush(Qt::black), 2.0));
  painter.drawLine(symbole1);
  painter.drawLine(symbole2);
  painter.end();
  /****************************/

  /********** Vision surligné **********/
  painter.begin(m_surligne);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(linearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(QBrush(Qt::white), 2.0));
  painter.drawLine(symbole1);
  painter.drawLine(symbole2);
  painter.end();
  /*****************************/

  /********** Vision cliqué **********/
  painter.begin(m_clique);
  painter.setPen(QPen(Qt::black));
  painter.setBrush(QBrush(invertlinearGrad));
  painter.drawPolygon(bordure);
  painter.setPen(QPen(QBrush(Qt::white), 2.0));
  painter.drawLine(symbole1);
  painter.drawLine(symbole2);
  painter.end();
  /*****************************/
}

/**********  Evénement pour les différent type d'affichage(surligné,cliqué,normal) **********/
void BoutonFenetre::enterEvent(QEvent *event)
{
  Q_UNUSED(event);
  m_statut = statut_surligne;
  update();
}

void BoutonFenetre::leaveEvent(QEvent *event)
{
  Q_UNUSED(event);
  m_statut = statut_normal;
  update();
}

void BoutonFenetre::mousePressEvent(QMouseEvent *event)
{
  QAbstractButton::mousePressEvent(event);
  m_statut = statut_clique;
  update();
}

void BoutonFenetre::mouseReleaseEvent(QMouseEvent *event)
{
  QAbstractButton::mouseReleaseEvent(event);
  if(underMouse()) m_statut = statut_surligne;
  else             m_statut = statut_normal;
  update();
}
/*****************************/
