#include<iostream>
#include<cmath>
#include<list>
#include<algorithm>

using namespace std;

struct Tacka{
    int x;
    int y;
    Tacka(){
        this->x=0;
        this->y=0;
    }
    Tacka(int x,int y){
        this->x=x;
        this->y=y;
    }
    bool operator ==(const Tacka &b){
        if(this->x==b.x and this->y==b.y){
            return true;
        }
        else{
            return false;
        }
    }
    friend ostream &operator <<(ostream& os,const Tacka &t){
        os<<"("<<t.x<<","<<t.y<<")";
        return os;
    }
};

int VektorskiProizvod(Tacka a,Tacka b,Tacka c){
    int y1=a.y-b.y;
    int y2=a.y-c.y;
    int x1=a.x-b.x;
    int x2=a.x-c.x;
    return y2*x1-y1*x2;
}

int Udaljenost(Tacka a,Tacka b,Tacka c){
    double udaljenost_AB=sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
    double udaljenost_AC=sqrt(pow(c.x-a.x,2)+pow(c.y-a.y,2));
    if(udaljenost_AB>udaljenost_AC){
        return 1;
    }
    else if(udaljenost_AB==udaljenost_AC){
        return 0;
    }
    else{
        return -1;
    }
}

list<Tacka> Jedinstvenost(list<Tacka> &tacke){
    list<Tacka> zaVracanje;
    zaVracanje.push_back(tacke.front());
    for(list<Tacka>::iterator it=tacke.begin();it!=tacke.end();it++){
        Tacka provjera= *it;
        bool nema_ga=true;
        for(list<Tacka>::iterator iter=zaVracanje.begin();iter!=zaVracanje.end();iter++){
            if(provjera== *iter){
                nema_ga=false;
            }
        }
        if(nema_ga){
            zaVracanje.push_back(provjera);
        }
    }
    return zaVracanje;
}

list<Tacka> GiftWrapping(list<Tacka> UlazneTacke){
    Tacka pocetak=UlazneTacke.front();
    for(list<Tacka>::iterator it=UlazneTacke.begin();it!=UlazneTacke.end();it++){
        if((*it).x<pocetak.x){
            pocetak=(*it);
        }
    }
    Tacka trenutna=pocetak;
    list<Tacka> ConvexHull;
    ConvexHull.push_back(pocetak);
    list<Tacka> KolinearneTacke;
    while(1){
        Tacka sljedeca=UlazneTacke.front();
        for(list<Tacka>::iterator it=UlazneTacke.begin();it!=UlazneTacke.end();it++){
            if((*it).x==trenutna.x and (*it).y==trenutna.y){
                continue;
            }
            int vektorski_proizvod=VektorskiProizvod(trenutna,sljedeca,(*it));
            if(vektorski_proizvod>0){
                sljedeca=(*it);
                Tacka nula;
                fill(KolinearneTacke.begin(),KolinearneTacke.end(),nula);
            }
            else if(vektorski_proizvod==0){
                if(Udaljenost(trenutna,sljedeca,(*it))<0){
                    KolinearneTacke.push_back(sljedeca);
                    sljedeca=(*it);
                }
                else{
                    KolinearneTacke.push_back((*it));
                }
            }
        }
        for(list<Tacka>::iterator iter=KolinearneTacke.begin();iter!=KolinearneTacke.end();iter++){
            ConvexHull.push_back((*iter));
        }
        if(sljedeca.x==pocetak.x and sljedeca.y==pocetak.y){
            break;
        }
        ConvexHull.push_back(sljedeca);
        trenutna=sljedeca;
    }
    list<Tacka> kraj=Jedinstvenost(ConvexHull);
    return kraj;
}

int main(){
    list<Tacka> ravan;
    list<Tacka> KonveksniOmotac;
    Tacka A(0,0);
    ravan.push_back(A);
    Tacka B(1,2);
    ravan.push_back(B);
    Tacka C(3,3);
    ravan.push_back(C);
    Tacka D(5,1);
    ravan.push_back(D);
    Tacka E(2,1);
    ravan.push_back(E);
    Tacka F(4,-2);
    ravan.push_back(F);
    Tacka G(2,-2);
    ravan.push_back(G);
    KonveksniOmotac=GiftWrapping(ravan);
    for(list<Tacka>::iterator it=KonveksniOmotac.begin();it!=KonveksniOmotac.end();it++){
        cout<<*it<<endl;
    }
 return 0;
}
