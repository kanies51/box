#include <iostream>
#include <vector>
using namespace std;

bool dom(vector < int > & BX,  vector < int > &BY){ //zwraca true jesli X<Y w dom
    bool dom=true;
    unsigned int i=0;
    int sumaX=0, sumaY=0;
               while(i<BX.size() && dom){
                sumaX+=*(BX.begin()+i);
                sumaY+=*(BY.begin()+i);
                if(sumaX<sumaY) dom= false; else i++;
               }
                return dom;
}

void zmien(vector < int > & BX, int i, int j)
{
    *(BX.begin()+i)=*(BX.begin()+i)-1;
    *(BX.begin()+j)=*(BX.begin()+j)+1;
}
bool sprawdz(vector < int > & BX,  vector < int > &BY, vector < int > & GX,  vector < int > &GY){ //zwraca false jesli wektory gamma nie sa zawarte w beta lub gdy wymiary sie nie zgadzaja
    int sumaBX=0, sumaBY=0, sumaGX=0, sumaGY=0;
    unsigned int i=0;
    bool sprawdz=true;
    while(i<BX.size() && sprawdz){
        sumaBX+=*(BX.begin()+i);
        sumaGX+=*(GX.begin()+i);
        sumaBY+=*(BY.begin()+i);
        sumaGY+=*(GY.begin()+i);
        if(!((*(BX.begin()+i)==*(GX.begin()+i) || *(BX.begin()+i)==*(GX.begin()+i)+1) &&
           (*(BY.begin()+i)==*(GY.begin()+i) || *(BY.begin()+i)==*(GY.begin()+i)+1)))
            sprawdz=false;
            i++;
    }
    if(sumaBX!=sumaBY || sumaGX!=sumaGY) sprawdz = false;
    return sprawdz;
}
void box(vector < int > & BX,  vector < int > &BY, vector < int > & GX,  vector < int > &GY){
    if(dom(BX,BY)&&dom(GX,GY))
    {   unsigned int i=0,j=0, i0;
        bool dominance=true;
       while(i<BX.size()&& dominance){
        if(*(BY.begin()+i)<=*(BX.begin()+i) && *(GY.begin()+i)<=*(GX.begin()+i)){
          i++;
        }
        else{
            if(*(BY.begin()+i)>*(BX.begin()+i)&&*(GY.begin()+i)>*(GX.begin()+i)){ //krok 3 algorytmu
                    if(*(BX.begin()+i)==*(GX.begin()+i)){           //krok 3 a
                        j=0;
                        while(*(BX.begin()+j)<=*(BY.begin()+j)){
                            j++;
                        }
                        if(*(BX.begin()+j)==*(GX.begin()+j)){       //krok 3 a i
                            cout << "\nbeta-gamma na X ";
                            zmien(BX,j,i);
                            zmien(GX,j,i);
                        }else
                        {
                            cout<<"\nbeta na X ";
                            zmien(BX,j,i);                       //krok 3 a ii
                        }
                        cout<<i<<","<<j;
                    }
                    else{                                            //krok 3 b
                        j=0;
                        while(*(GX.begin()+j)<=*(GY.begin()+j)){
                            j++;
                        }
                        if(*(BX.begin()+j)==*(GX.begin()+j)){       //krok 3 b i
                            cout<<"\ngamma na X ";
                            zmien(GX,j,i);
                        }else
                        {                                           //krok 3 b ii
                            cout<<"\nbeta-gamma1 na X ";
                            zmien(BX,j,i);
                            zmien(GX,j,i);
                        }
                        cout<<i<<","<<j;
                    }
               }
            else{
                 if(*(GY.begin()+i)>*(GX.begin()+i)){               //krok 2 algorytmu
                    i0=i;
                    while(*(BY.begin()+i0)==*(BY.begin()+i0+1)&&*(GY.begin()+i0)==*(GY.begin()+i0+1))
                    {
                        i0++;
                    }
                    j=0;
                    while(*(GX.begin()+j)<=*(GY.begin()+j)){
                        j++;
                    }
                    while(*(BX.begin()+j)==*(BX.begin()+j+1))
                    {
                        j++;
                    }
                    if(*(BY.begin()+j)>*(GY.begin()+j)){          //krok 2 a
                        cout << "\ngamma na Y ";
                        zmien(GY,i,j);
                    }
                    else{                                           //krok 2b
                        while(*(BY.begin()+i0)==*(BY.begin()+i0+1))
                        {
                            i0++;
                        }
                        if(*(GY.begin()+j)==*(BY.begin()+j))
                        {cout<< "\nbeta na Y ";
                        zmien(BY,i0,j);
                        }
                        else{
                        cout<< "\ngamma na Y ";
                        zmien(GY,i0,j);}
                    }
                    cout<<i0 <<"," <<j;
                 }
                 else{                                              //krok 1 algorytmu
                     j=0;
                    while(*(BX.begin()+j)<=*(BY.begin()+j)){
                        j++;
                    }
                    while(*(BX.begin()+j)==*(BX.begin()+j+1))
                    {
                        j++;
                    }
                     if(*(BX.begin()+j)>*(GX.begin()+j)){          //krok 1 a
                        cout << "\nbeta na X ";
                        zmien(BX,j,i);
                    }
                    else{                                           //krok 1b
                        cout<< "\nbeta-gama na X ";
                        zmien(BX,j,i);
                        zmien(GX,j,i);
                    }
                    cout<<i <<"," <<j;
                    }
                 }
            dominance=(dom(BX,BY)&&dom(GX,GY));
            }
        }
        if(!dominance)cout<<"BLAD";
    }
    else cout << "NIE";

}
int main()
{
    vector < int > vect;
    vector < int > BX, BY, GX, GY;
    int a;
    while(cin>>a)
    {
     vect.push_back(a);
    }
    a=vect.size()/4;
    BX.assign(vect.begin(),vect.begin()+a);
    GX.assign(vect.begin()+a,vect.begin()+2*a);
    BY.assign(vect.begin()+2*a,vect.begin()+3*a);
    GY.assign(vect.begin()+3*a,vect.end());
    if(sprawdz(BX,BY,GX,GY))
        box(BX,BY,GX,GY);
    else
        cout<<"Wektory niepoprawne";
    return 0;
}
