#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <QtWidgets>
#include "boutonfenetre.h"

class Menubar : public QWidget{
  Q_OBJECT

public:
  Menubar(QWidget *parent = 0);
  ~Menubar();

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent  *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

public slots:
  void initialisation_titre(const QString &title);
  void Minimized();
  void Maximized();
  void Quit();

private:
  QPixmap *m_cache;
  QLabel* m_Title;
  BoutonFenetre* m_Close;
  BoutonFenetre* m_Maximize;
  BoutonFenetre* m_Minimize;
  QPoint m_Diff;
  QHBoxLayout *m_layoutTitleBar;
};

#endif
