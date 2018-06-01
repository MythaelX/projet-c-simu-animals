#ifndef LION_H
#define LION_H
class Lions: public Animal{
  private:

  public:
    Lions(const int xinit,const int yinit, const int energieinit){
      x=xinit;
      y=yinit;
      energie=energieinit;
      lettre='L';}
    ~Lions(){}
    void affiche(){cout << "energie=" << energie << "\nx=" << x  << "\ny=" << y << "\n";}
    char getLettre()const{return lettre;}
};
#endif
