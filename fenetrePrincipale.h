#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include "menu_bar.h"
#include "MyScene.h"
#include <QSound>
class FenetrePrincipale : public QMainWindow {
  Q_OBJECT

  public:
    FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();
    void centrer_ecran();

  public slots:
    void slot_demarrer();
    void scene_vitesse();

  protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void fenetre_pleine_ecran();

  private:
    QWidget * widget_general;
    Menubar* menu_bar;
    QPixmap *m_cache;
    QLCDNumber *valeur_vitesse;
    QDesktopWidget *widget;
    QGridLayout* layout_principal;
    QVBoxLayout *layout_vitesse;
    QVBoxLayout * layout_bouton_demarrer;
    QVBoxLayout * layout_bouton_stop;
    QHBoxLayout *layout_graphique;
    QLabel* titre_onglet;
    QLabel* texte_monde_x;
    QLabel* texte_monde_y;
    QLabel* texte_lion;
    QLabel* texte_gazelle;
    QLabel* texte_energie;
    QLabel* texte_vitesse;
    QSpinBox *taille_monde_x;
    QSpinBox  *taille_monde_y;
    QSpinBox  *lion;
    QSpinBox  *gazelle;
    QSpinBox  *energie;
    QSlider * vitesse;
    QPushButton* bouton_demarrer;
    QPushButton *bouton_quitter;
    QPushButton *bouton_retour;
    QGraphicsView * myview;
    QSound* son;
    MyScene *myscene;
    bool simulation=false;
  };
#endif
