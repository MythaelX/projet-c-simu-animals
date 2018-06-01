#ifndef GAZELLE_H
#define GAZELLE_H
class Gazelles : public Animal{
  private:

  public:
    Gazelles(const int xinit,const int yinit, const int energieinit){
      x=xinit;
      y=yinit;
      energie=energieinit;
      lettre='G';}
    ~Gazelles(){}
    void affiche(){cout << "energie=" << energie << "\nx=" << x  << "\ny=" << y <<"\n";}
    char getLettre()const{return lettre;}
};
#endif
