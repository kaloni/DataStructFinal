#include<iostream>
#include<string>
#include<iomanip> //using setw()
#include<sstream>

using namespace std;

enum StatusType {Free, Rented};

enum ClassType { Electric, Lady, Road, Hybrid};

enum xStationType {
    Danshui, Hongshulin, Beitou,
    Shilin, Zhongshan, Xinpu,
    Ximen, Liuzhangli, Muzha,
    Guting, Gongguan, Jingmei };

typedef char LicenseType[5];

struct BikeType{
    LicenseType License;
    StatusType Status;
    int Mileage; /* most recently rented mileage */
    int Cursor; /* cursor to the entry in heap where there is a pointer to this node */
    xStationType Station;
    ClassType Class;
};

typedef struct BikeType *BikePtr;

struct HeapType{
    BikePtr Elem[256]; /* use array to implement heap, and each node in the heap is a pointer*/
    int Number;
};

struct StationType{
    xStationType Station;
    int Net; /* total income of station */
    int NetElectric;
    int NetLady;
    int NetRoad;
    int NetHybrid;
    int NumElectric; /* number of electric bikes */
    int NumLady; /* number of lady bikes */
    int NumRoad; /* number of road bikes */
    int NumHybrid; /* number of hybrid bikes */
    HeapType HRent;
    HeapType HElectric;
    HeapType HLady;
    HeapType HRoad;
    HeapType HHybrid;
};

struct HNodeType {
    LicenseType License ;
    BikePtr Ptr; /* point to the node representing the bike */
    struct HNodeType *next_ptr; /*point to the next node in the chaining list*/
};

struct HTableType {
    HNodeType table[256];
    /*since each entry in the hash table is a pointer, it will be initialized as NULL;*/
    int BikeNum; /* the number of bikes in the hash table */
};

void NewBike(ClassType Class, string License, int Mile, xStationType StationName){
    //cout<<Class<<" "<<License<<" "<<Mile<<" "<<StationName<<endl;
    BikeType *newnode=new BikeType;
    newnode->Class=Class;
    int i;
    for(i=0; i<5; i++){
        newnode->License[i]=License[i];
    }
    
    
    int LicenseTag=License[0];
    i=1;
    while(i<5){
        if(isdigit(License[i]))
            LicenseTag=LicenseTag*31+((int)License[i]-48);
        else
            LicenseTag=LicenseTag*31+((int)License[i]-55);
        i++;
    }
    cout<<endl;
    newnode->Mileage=Mile;
    newnode->Station=StationName;
    newnode->Status=Free;
}

void Inquire(string License){
    
}

void JunkIt(string License){
    
}

void HashReport(){
}

int main(){
    
    string state;
    string move;
    string Class,License,Station;
    ClassType Type;
    xStationType StationName;
    int Mile;
    while(getline(cin, state)){
        istringstream iss(state);
        iss>>move;
        if(move=="NewBike"){
            iss>>Class>>License>>Mile>>Station;
            if(Class=="Electric")
                Type=Electric;
            else if(Class=="Lady")
                Type=Lady;
            else if(Class=="Road")
                Type=Road;
            else if(Class=="Hybrid")
                Type=Hybrid;
            if(Station=="Danshui")
                StationName=Danshui;
            else if(Station=="Hongshulin")
                StationName=Hongshulin;
            else if(Station=="Beitou")
                StationName=Beitou;
            else if(Station=="Shilin")
                StationName=Shilin;
            else if(Station=="Zhongshan")
                StationName=Zhongshan;
            else if(Station=="Xinpu")
                StationName=Xinpu;
            else if(Station=="Ximen")
                StationName=Ximen;
            else if(Station=="Liuzhangli")
                StationName=Liuzhangli;
            else if(Station=="Muzha")
                StationName=Muzha;
            else if(Station=="Guting")
                StationName=Guting;
            else if(Station=="Gongguan")
                StationName=Gongguan;
            else if(Station=="Jingmei")
                StationName=Jingmei;
            NewBike(Type,License,Mile,StationName);
        }
        else if(move=="Inquire"){
            iss>>License;
            Inquire(License);
        }
        else if(move=="JunkIt"){
            iss>>License;
            JunkIt(License);
        }
        else if(move=="HashReport"){
            HashReport();
        }
    }
}
