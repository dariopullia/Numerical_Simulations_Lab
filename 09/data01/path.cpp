#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "../../rangen/random.h"
#include "path.h"



using namespace std;


//-----------------FUNZIONE UTILE----------
bool IsInVec(int n, int v[], int size ){
    bool res=false;
    for (int i=0; i<size; i++){
        if (n==v[i]){
            res=true;
            break;
        }
    }
    return res;
}





//------------------------ PATH----------------------

Path :: Path(int d){
    start =new Town;
    start->SetNext(start);
    start->SetPrevious(start);
    
    dim=d;
    len=0;
}
Path :: Path(){
    start =new Town;
    start->SetNext(start);
    start->SetPrevious(start);
    
    dim=0;
    len=0;
}
Path :: ~Path(){
    //Town *current=start->GetPrevious();
    //Town *prev=current->GetPrevious();
    int i=0;
    start->GetPrevious()->SetNext(NULL);
    for (Town* current = start, *Next; current;)
    {
        i++;
        Next = current->GetNext();
        
        delete current;
        //cout<<"cc "<<Next<<endl;
        current = Next;
        
    }
    //Dispose();
    //cout<<"wow "<<i<<endl;

}//IMPO






void Path :: Dispose (){
while(!(start->GetID()==0)){
//cout<<"Sto per cancellare qualcosa, dim e indirizzo: "<<dim<<" "<<start->GetNext()<<endl;    

Town *appo=start;
dim--;
start=start->GetNext();

delete appo;
}
//cout<<start->GetNext()<<" "<<start->GetPrevious()<< " "<<start<<endl;
//delete start;
//cout<<start->GetNext()<<" "<<start->GetPrevious()<< " "<<start<<endl;

}



void Path :: Append(double x, double y, int i){
    Town* nt=new Town;
    nt->SetX(x);
    nt->SetY(y);
    nt->SetID(i);
    nt->SetNext(start);
    nt->SetPrevious(this->GetLastTown());
    this->GetLastTown()->SetNext(nt);
    this->GetStart()->SetPrevious(nt);
  
    //nt->print();
}


void Path :: print(){
    Town* pos=start;
    cout<<"-------------------------------Path---------------------------"<<endl;
    cout<<"---------Dim: "<<dim<<" --------- Len: "<<len<<" --------------------"<<endl;
    pos->print();
    pos=pos->GetNext();    
    while(!(pos->GetID()==0)){
        pos->print();
        pos=pos->GetNext();
        }
    cout<<"-------------------------------END Path---------------------------"<<endl;
}
void Path :: shortPrint(){
    Town* pos=start;
    cout<<"------------Path----------"<<endl;
    cout<<"Dim: "<<dim<<" - Len: "<<len<<""<<endl<<"[";
    cout<<""<<pos->GetID()<<", ";
    pos=pos->GetNext();
    while(!(pos->GetID()==0)){
        cout<<""<<pos->GetID()<<", ";
        pos=pos->GetNext();
        }
    cout<<"]"<<endl;
    cout<<"----------END Path--------"<<endl;

}







Town* Path :: GetLastTown(){
    return start->GetPrevious();
}




void Path :: MeasureLen(){
    len=0;
    Town* pos=start;
    //pos->print();
    //cout<<pos->GetID()<<" "<<len<<endl;

    while (!(pos->GetNext()->GetID()==0)){
    //cout<<"PreCoreDump "<<i<<endl;

        len+= pow(pos->GetX() -pos->GetNext()->GetX() ,2) + pow(pos->GetY() -pos->GetNext()->GetY() ,2);
        //cout<<len<<endl;
        //cout<<pos->GetID()<<" "<<len<<endl;
        pos=pos->GetNext();
    }
    //cout<<pos->GetID()<<" "<<len<<endl;

    len+= pow(start->GetX() -pos->GetX() ,2) +pow(start->GetY() -pos->GetY() ,2);
    //cout<<pos->GetID()<<" "<<len<<endl;

}


void Path :: Fix(){
    if (start->GetID()==0) return;    
    while (start->GetID()!=0) start=start->GetNext();

}






//----------------------------GENETIC TRANSFORMATIONS----------------------------------

void Path :: Swap(int A, int B, int n){
    int appo;

    Town* pos=start;
    Town* Ai;
    Town* Af;

    Town* Bi;
    Town* Bf;

    Town* memoBi;
    Town* memoBf;
        
    if (n<=0 or A==B) return;
    n--; //

    if (A>B){
    appo=A;
    A=B;
    B=appo;
    }
    if (B - A < n+2) {
        //cout<<"Caso1"<<endl;
        this->Shift(A,B-1,n+1);
        return;
    }
    if (B+n+1>dim+A-1) {
        //cout<<"ENTRO"<<endl;
        this->Shift(B,dim+A-1,n+1);
        return;
    }    

    for (int i=0; i<A;i++){
    //pos->print();
    pos=pos->GetNext();   
    } 
    Ai=pos;
    for (int i=0; i<n;i++){
        pos=pos->GetNext();
    }
    Af=pos;

    //Tolgo il segmento
    Ai->GetPrevious()->SetNext(Af->GetNext()); 
    Af->GetNext()->SetPrevious(Ai->GetPrevious()); 
    //-----

    for (int i=0; i<B-(A+n);i++){
    //pos->print();
    pos=pos->GetNext();   
    } 
    Bi=pos;
    for (int i=0; i<n;i++){
        pos=pos->GetNext();
    }
    Bf=pos;

    //Tolgo il segmento
    Bi->GetPrevious()->SetNext(Bf->GetNext()); 
    Bf->GetNext()->SetPrevious(Bi->GetPrevious()); 
    //-----

    memoBi=Ai->GetPrevious();
    memoBf=Af->GetNext();


    Ai->SetPrevious(Bi->GetPrevious());
    Ai->GetPrevious()->SetNext(Ai);
    Af->SetNext(Bf->GetNext());
    Af->GetNext()->SetPrevious(Ai);
    

    Bi->SetPrevious(memoBi);
    Bi->GetPrevious()->SetNext(Bi);

    Bf->SetNext(memoBf);
    Bf->GetNext()->SetPrevious(Bi);

};


void Path :: Invert(int A,int B){
    int appo;
    Town* pos=start;
    Town* ATown;
    Town* BTown;
    Town* memo2;
    if (A>B){
        appo=A;
        A=B;
        B=appo;
    }
    if (B-A>dim-2) B=A+dim-2;

    for (int i=0; i<A;i++){
    //pos->print();
    pos=pos->GetNext();   
    } 

    //pos->print();

    appo=B-A;
    ATown=pos;
    pos=pos->GetNext();

    for (int i=0; i<appo-1;i++){
        memo2=pos->GetNext();
        pos->SetNext(pos->GetPrevious());
        pos->SetPrevious(memo2);
        pos=pos->GetPrevious();
    }
    BTown=pos;

    memo2=ATown->GetPrevious();

    ATown->SetPrevious(ATown->GetNext());
    ATown->SetNext(BTown->GetNext());

    BTown->SetNext(BTown->GetPrevious());
    BTown->SetPrevious(memo2);
 
    BTown->GetPrevious()->SetNext(BTown);
    ATown->GetNext()->SetPrevious(ATown); 
}


void Path :: Shift(int A, int B, int n){

    int appo;
    Town* pos=start;
    Town* ATown;
    Town* BTown;
    Town* memo;
    if (A>B){
    appo=A;
    A=B;
    B=appo;
    }

    if (B-A>=dim-1){
        return;
    }

    for (int i=0; i<A;i++){
    //pos->print();
    pos=pos->GetNext();   
    } 
    appo=B-A;
    ATown=pos;
    for (int i=0; i<appo;i++){
        pos=pos->GetNext();
    }
    BTown=pos;


    //Tolgo il segmento
    ATown->GetPrevious()->SetNext(BTown->GetNext()); 
    BTown->GetNext()->SetPrevious(ATown->GetPrevious()); 
    //--

    for (int i=0; i<n+1;i++){
        pos=pos->GetNext();
    }


    memo=pos->GetPrevious();
    pos->GetPrevious()->SetNext(ATown);
    pos->SetPrevious(BTown);
    BTown->SetNext(pos);    
    ATown->SetPrevious(memo);



}


void Path :: Crossover(Path p, int A, int B){
    int appo;
    Town* pos=start;
    Town* ATown;
    Town* posnew=p.GetStart();

    if (A>B){
    appo=A;
    A=B;
    B=appo;
    }
    appo=B-A+1;

    if (B-A>=dim-1){


        return;
    }
    int toreplace[appo];

    for (int i=0; i<A;i++){
    //pos->print();
    pos=pos->GetNext();   
    } 
    ATown=pos;
    toreplace[0]=ATown->GetID();
    for (int i=0; i<appo;i++){
        pos=pos->GetNext();
        toreplace[i+1]=pos->GetID();
    }
   

    pos=ATown;
    for(int i=0; i<appo;i++){
        while (!IsInVec(posnew->GetID(), toreplace, appo))
        {
            posnew=posnew->GetNext();
        }
        pos->SetID(posnew->GetID());
        pos->SetX(posnew->GetX());
        pos->SetY(posnew->GetY());
        posnew=posnew->GetNext();
        pos=pos->GetNext();

    }
    this->Fix();
}

void Manager :: Try(){

    /*
    int J,K,N;
    double ExpCoef=1;
    for (int z=0; z<1000000;z++){    
        for (int i=0; i<npaths; i++){

            J=(int)rnd.Exp(ExpCoef);
            K=ExpCoef+(int)rnd.Exp(ExpCoef);
            N=(int)rnd.Exp(ExpCoef);


            //paths[i]->shortPrint();

            //cout<<i<<endl;
            //paths[i]->Invert(0,10);
            paths[i]->Shift(J,K,N);
            paths[i]->MeasureLen();
            //paths[i]->Swap(1,1,1);
            //paths[i][0].print();
            //paths[i]->shortPrint();
            if (paths[i]->GetLen()==0){
                //this->shortPrint(i+1);
                paths[i-1]->print();
                cout<<J<<" "<<K<<" "<<N<<endl;
                paths[i]->print();

                return;
            }
            
            
        }
        
    }
*/

    //this->shortPrint(10);


    for (int i=1; i<npaths; i++){

        //paths[i]->shortPrint();

        //cout<<i<<endl;
        //paths[i]->Invert(0,10)
        paths[0]->shortPrint();
        paths[i]->shortPrint();
        paths[i]->Crossover(paths[0][0],0,0);
        paths[i]->MeasureLen();
        paths[i]->shortPrint();

    }



}





//------------------------------------------MANAGER----------------------------------------




Path* Manager :: CreateRandomPath(){
    Path* p= new Path;
    p->setDim(dim);
    int order[dim-1];
    for (int i=0;i<dim-1;i++) order[i]=0;
    
    for (int i=1;i<dim;i++){
        int o=rnd.Rannyu(0,dim-1);
        while(order[o]!=0){
            o=rnd.Rannyu(0,dim-1);
        }
        order[o]=i; //A me pare funzioni a dovere, potenziali pericoli!!
        //cout<<i<<endl;
    }
    //for (int k=0; k<dim-1;k++) cout<<order[k]<<endl; 

    p->GetLastTown()->SetX(Xregion[0]);
    p->GetLastTown()->SetY(Yregion[0]);
    p->GetLastTown()->SetID(0);

    for (int i=0;i<dim-1;i++){
        p->Append(Xregion[order[i]],Yregion[order[i]],order[i]);

    }

    //p.print();
    return p;
}



Manager :: Manager(int d){
    dim=d;
    npaths=2;
    Xregion = new double [d];
    Yregion = new double [d];
    rnd.SetPrimesComb(3);
    shape=0;
    dir="Circ/";

}

Manager :: ~Manager(){
    delete Xregion;
    delete Yregion;
}



void Manager :: CreateRegion(){
   
    if (shape==0) CreateRegionCirc();
    else if (shape==1) CreateRegionSquare();

}



void Manager :: CreateRegionCirc(){
    for (int i=0; i<dim; i++){
        double theta= rnd.Rannyu(0,2*M_PI);
        Xregion[i]=(cos(theta));
        Yregion[i]=(sin(theta));
        //cout<<Xregion[i]<<" "<<Yregion[i]<<endl;
    }
}



void Manager :: CreateRegionSquare(){
    for (int i=0; i<dim; i++){
        Xregion[i]=rnd.Rannyu(-1,1);
        Yregion[i]=rnd.Rannyu(-1,1);
        //cout<<Xregion[i]<<" "<<Yregion[i]<<endl;
    }
}

void Manager :: SetShape(int s){ //0 Circ, 1 Square
    if (s!=0 and s!=1){
        cerr<<"Shape errate"<<endl;
        return;
    }
    if (s==1){
        shape=1;
        dir="Square/";
    }
}





void Manager :: CreatePopulation(){
    paths = new Path*[npaths];
    for (int i=0; i<npaths; i++){
        //cout<<i<<endl;
        paths[i]=CreateRandomPath();
        //paths[i][0].print();
    }
}


void Manager :: DestroyPopulation(){
    

    for (int i=0; i<npaths; i++){
    delete paths[i];
    }
    //delete [] paths;
}



Path* Manager :: copyPath(Path p){
    Path* np=new Path;

    np->setDim(p.GetDim());
    np->setLen(p.GetLen());

    Town* pos=p.GetStart();
    np->GetLastTown()->SetX(Xregion[0]);
    np->GetLastTown()->SetY(Yregion[0]);
    np->GetLastTown()->SetID(0);
    pos=pos->GetNext();
    while (pos->GetNext()->GetID()!=0){

        np->Append(pos->GetX(), pos->GetY(),pos->GetID());
        pos=pos->GetNext();
        //np->shortPrint();

    }
    np->Append(pos->GetX(), pos->GetY(),pos->GetID());

    return np;
    //p.print();
}


void Manager :: TestPopulation(){
    for (int i=0; i<npaths; i++){
        paths[i][0].MeasureLen();
    }
}

void Manager :: RankPopulation(){
    mergesort(paths, 0, npaths-1);

}

void Manager :: print(){
    for (int i=0; i<npaths; i++){
        paths[i][0].print();
    }
}

void Manager :: shortPrint(){
    for (int i=0; i<npaths; i++){
        paths[i][0].shortPrint();
    }


}
void Manager :: shortPrint(int n){
    if (n>npaths) n=npaths;
    for (int i=0; i<n; i++){
        paths[i][0].shortPrint();
    }


}


void Manager :: Mutate(){

    Path** newpaths= new Path*[npaths];
    int o;
    //double ExpCoef=0.015;
    double Espo=3.;
    //double ShiftMean=0;
    //double ShiftSig=dim/4;
    double rand; 
    int J,K,N;

    for (int i=0; i<npaths; i++){
        o=npaths*(pow(rnd.Rannyu(),Espo));
        newpaths[i]=copyPath(paths[o][0]);

        rand=rnd.Rannyu();
        if (rand<0.15){

            J=(int)rnd.Rannyu(0,dim);
            K=(int)rnd.Rannyu(0,dim);
            N=(int)rnd.Rannyu(0,dim);
            newpaths[i][0].Shift(J,K,N);
            //cout <<J<<" "<<K<<" "<<N<<endl;
            //newpaths[i]->shortPrint();
            
        }
        else if (rand<0.3) {
            J=(int)rnd.Rannyu(0,dim);
            K=(int)rnd.Rannyu(0,dim);
            N=(int)rnd.Rannyu(0,dim);
            newpaths[i][0].Swap(J,K,N);
        }
        else if (rand<0.45){
            J=(int)rnd.Rannyu(0,dim);
            K=(int)rnd.Rannyu(0,dim);
            newpaths[i][0].Invert(J,K);
        }
        
        else if(rand<0.8){
            J=(int)rnd.Rannyu(0,dim);
            K=(int)rnd.Rannyu(0,dim);;
            N=npaths*(pow(rnd.Rannyu(),Espo));
            N=N%npaths;
            newpaths[i][0].Crossover(paths[N][0],J,K);            
        }
        else if (rand<0.85){

            newpaths[i]=CreateRandomPath();
        }
    }
    paths=newpaths;

}



void Manager :: SaveBest(int n){
    double appo=0;

    ofstream Bests;
    Bests.open(dir+"Bests.dat",ios::app);
    
    for (int i=0; i<n; i++){
    Town* pos=paths[i][0].GetStart();
    Bests<<pos->GetID()<<" ";
    pos=pos->GetNext();
    while(!(pos->GetID()==0)){
        Bests<<pos->GetID()<<" ";
        pos=pos->GetNext();
        }
    
    Bests<<paths[i][0].GetLen()<<" ";//endl;
    }

    for(int j=0; j<npaths/2;j++){
        appo+=paths[j][0].GetLen();
    }
    appo=appo/(npaths/2);
    Bests<<appo<<endl;

    Bests.close();
}

void Manager :: SaveBestCoord(){
    ofstream Region;
    Region.open(dir+"BestCoord.dat");
    
    Town* pos=paths[0][0].GetStart();
    Region<<pos->GetX()<<" "<<pos->GetY()<<endl;
    pos=pos->GetNext();
    while(!(pos->GetID()==0)){
        Region<<pos->GetX()<<" "<<pos->GetY()<<endl;
        pos=pos->GetNext();
        }
    Region.close();
}

void Manager :: SaveRegion(){
    ofstream Region;
    Region.open(dir+"Region.dat");
    for (int i=0; i<dim;i++) Region<<Xregion[i]<<" "<<Yregion[i]<<endl; 
    Region.close();
}

   

   



 
//----------------------------MERGESORT IMPLEMENTATION----------------------------------------------



void Manager ::mergesort(Path **v, int low, int high){

int appo=(high-low)/2;
if (low!=high){
mergesort(v, low, low+appo);
mergesort(v, low+appo+1, high);
}
if (low!=high){
merge(v, low,low+appo, high);
}

}


void Manager ::merge(Path **v, int low, int mid, int high) {

    int i, h, j;

    Path **appo = new Path*[high-low+1];    //Vettore di appoggio
                                    //in questo vettore ricopieremo
                                    //in ordine gli elementi

    i=0; //I indichera` la prima posizione libera del vettore appo
    h=low; //Dove inizia il primo sottovettore
    j=mid+1; //Dove inizia il secondo sottovettore.
    //Osservazione: in ogni suddivisione mergesort produce due
    //sottovettori senza soluzione di continuita`.
    while ((h <= mid) and (j<=high)) {
        if(v[h][0].GetLen() <= v[j][0].GetLen()) {
            appo[i]= v[h];  //Ricopia l'elemento piu` piccolo
                            //dal sottovettore di sx
            h++;            //Incrementa indice vettore sx
        }
        else {
            appo[i] = v[j]; //Ricopia da dx
            j++;            //Incrementa indice dx
        }

        i++; //Incrementa indice vettore appo
    }

    //Qui finsce il while. A questo punto se uno dei due sottovettori
    //non e` vuoto, per costruzione conterra` elementi >= di tutti
    //quelli gia` ricopiati in appo.
    //Riverso quindi in appo gli elementi residui senza fare controlli
    // sui valori

    if(h > mid) { //Vuol dire che il sottovettore di sx e` vuoto

        for (int k = j; k <= high; k++) {
            appo[i] = v[k];
            i++;
        }
    }
    else { //E` il sottovettore di dx ad essere vuoto

        for (int k = h; k <= mid; k++) {
            appo[i] = v[k];
            i++;
        }
    }

    //Qui il vettore appo contiene i due sottovettori "fusi"
    //in modo ordinato.
    //Ricopio la sequenza ordinata nel vettore originale.

    for(int k=low; k<=high; k++)
        v[k]=appo[k-low];   //Ricordate che il vettore di
                            //appoggio ha indici a partire da 0

    //Finto: rimuovo il vettore di appoggio.
    //cout<<"ciao"<<endl;
    //appo->Dispose();
    //delete [] appo;


}


//-----------------TOWN--------------

Town :: Town(){

    Next=this;
    Previous=this;
    ID=0;

}

Town :: ~Town(){
    
    /*
    delete Next;
    delete Previous;
    
    Next=NULL;
    Previous=NULL;
    X=0;
    Y=0;

    cout<<"distruggo città"<<endl; //Commentare o scommentare questo cout cambia il risultato, follia
    */
}


void Town :: SetX(double xn){
    X=xn;
}


void Town :: SetY(double yn){
    Y=yn;
}



void Town :: print(){
    cout<<"------------Town "<<this->GetID()<<" ---- "<<this<< " --------"<<endl;
    cout<<"Town Coord: "<<this->GetX()<<" "<<this->GetY()<<endl;
    if(this->GetPrevious()!=NULL) cout<<"Prev: "<<this->GetPrevious()<<"    ID : "<<this->GetPrevious()->GetID() <<endl;
    else cout<<"Citta' iniziale ";

    if(this->GetNext()!=NULL)    cout<<"Next: "<<this->GetNext()<< "    ID : "<<this->GetNext()->GetID()<<endl;
    else cout<<"     Ultima citta'"<<endl<<endl;

}


void Town :: shortPrint(){
    cout<<"------------Town "<<this->GetID()<<" ----------"<<endl;
    if(this->GetPrevious()!=NULL)   cout<<"Prev: "<<this->GetPrevious()->GetID();
    else cout<<"Citta' iniziale ";
    if(this->GetNext()!=NULL)   cout<<"     Next: "<<this->GetNext()->GetID()<<endl<<endl; 
    else cout<<"     Ultima citta'"<<endl<<endl;
}
