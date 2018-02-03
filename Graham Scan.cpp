#include<iostream>
#include<stack>
#include<cmath>
#include<vector>
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

int Udaljenost(const Tacka &a,const Tacka &b,const Tacka &c){
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

Tacka SecondTop(stack<Tacka> &A){
    Tacka privremeni=A.top();
    A.pop();
    Tacka zaVracanje=A.top();
    A.push(privremeni);
    return zaVracanje;
}

int VektorskiProizvod(const Tacka &a,const Tacka &b,const Tacka &c){
    int y1=a.y-b.y;
    int y2=a.y-c.y;
    int x1=a.x-b.x;
    int x2=a.x-c.x;
    return y2*x1-y1*x2;
}
Tacka prva;
bool UslovSortiranja(const Tacka &a,const Tacka &b){
    double smjer=VektorskiProizvod(prva,a,b);
    if(smjer>0){
        return true;
    }
    else if(smjer<0){
        return false;
    }
    else{
        if(Udaljenost(prva,a,b)>=0){
            return false;
        }
        else{
            return true;
        }
    }
}

stack<Tacka> GrahamScan(vector<Tacka> &UlazneTacke){
    if(UlazneTacke.size()<3){
        return stack<Tacka> ();
    }
    int minimum_po_y=UlazneTacke[0].y;
    int mini=0;
    for(int i=1;i<UlazneTacke.size();i++){
        int trenutno_po_y=UlazneTacke[i].y;
        if((trenutno_po_y<minimum_po_y) or (trenutno_po_y==minimum_po_y and UlazneTacke[i].x<UlazneTacke[mini].x)){
            minimum_po_y=UlazneTacke[i].y;
            mini=i;
        }
    }
    swap(UlazneTacke[0],UlazneTacke[mini]);
    prva=UlazneTacke[0];
    sort(UlazneTacke.begin()+1,UlazneTacke.end(),UslovSortiranja);
    stack<Tacka> ConvexHull;
    ConvexHull.push(UlazneTacke[0]);
    ConvexHull.push(UlazneTacke[1]);
    ConvexHull.push(UlazneTacke[2]);
    for(int i=3;i<UlazneTacke.size();i++){
        while((VektorskiProizvod(SecondTop(ConvexHull),ConvexHull.top(),UlazneTacke[i])<=0) and ConvexHull.size()>2){
            ConvexHull.pop();
        }
        ConvexHull.push(UlazneTacke[i]);
    }
    if(VektorskiProizvod(SecondTop(ConvexHull),ConvexHull.top(),prva)<=0){
        ConvexHull.pop();
    }
    return ConvexHull;
}


int main(){
    vector<Tacka> ravan;
    Tacka A(0,0);
    ravan.push_back(A);
    Tacka B(1,2);
    ravan.push_back(B);
    Tacka C(3,3);
    ravan.push_back(C);
    Tacka D(2,1);
    ravan.push_back(D);
    Tacka E(5,1);
    ravan.push_back(E);
    Tacka F(4,-2);
    ravan.push_back(F);
    Tacka G(2,-2);
    ravan.push_back(G);
    stack<Tacka> kraj=GrahamScan(ravan);
    while(!kraj.empty()){
        cout<<kraj.top()<<endl;
        kraj.pop();
    }
 return 0;
}
