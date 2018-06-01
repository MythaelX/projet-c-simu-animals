#ifndef BOUTONFENETRE_H
#define BOUTONFENETRE_H

#include <QAbstractButton>

class BoutonFenetre : public QAbstractButton{
Q_OBJECT
public:
  enum TypeBouton{
    bouton_minimize, bouton_maximize, bouton_close
  };
  BoutonFenetre(TypeBouton type, QWidget *parent = 0);
  ~BoutonFenetre();
  void InitPixmaps();
  void InitPixmap(QPixmap **pixmap);
  void InitMinimize();
  void InitMaximize();
  void InitClose();

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  enum ButtonState{
    statut_normal, statut_surligne, statut_clique
  };

  TypeBouton  m_type;
  ButtonState m_statut;
  QPixmap *m_normal;
  QPixmap *m_surligne;
  QPixmap *m_clique;
};

#endif
