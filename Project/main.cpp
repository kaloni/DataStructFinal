#include<iostream>
#include<string>
#include<iomanip> //using setw()
#include<sstream>
#include "HeapType.cpp"
#include "HashTable.cpp"

using namespace std;

enum StatusType {Free, Rented};

enum ClassType { Electric, Lady, Road, Hybrid};

enum xStationType {
    Danshui, Hongshulin, Beitou,
    Shilin, Zhongshan, Xinpu,
    Ximen, Liuzhangli, Muzha,
    Guting, Gongguan, Jingmei };

//typedef char LicenseType[5];
struct LicenseType {
public:
    LicenseType() {
        for(int i = 0; i < 5; ++i) {
            license[i] = '0';
        }
    }
    char &operator[](int index) {
        return license[index];
    }
    bool operator==(LicenseType& lt) {
        for(int i = 0; i < 5; ++i) {
            if( license[i] != lt[i] )
                return false;
        }
        return true;
    }
    friend ostream& operator<<(ostream& os, LicenseType& lt);
private:
    char license[5];
};

struct BikeType{
    LicenseType License;
    StatusType Status;
    int Mileage; /* most recently rented mileage */
    int Cursor; /* cursor to the entry in heap where there is a pointer to this node */
    xStationType Station;
    ClassType Class;
};

typedef struct BikeType* BikePtr;

// operator < for comparing bikes
bool operator<(const BikeType& bp1, const BikeType& bp2) {
    return bp1.Mileage < bp2.Mileage;
}
ostream& operator<< (ostream &out, BikeType &bike)
{
    out << bike.Mileage;
    return out;
}
// Use HeapType class instead~~
/*
struct HeapType{
    BikePtr Elem[256]; // use array to implement heap, and each node in the heap is a pointer
    int Number;
};
*/

typedef HeapType<BikePtr> BikeHeap;

struct StationType{
    //xStationType Station;
    int Net; /* total income of station */
    int NetElectric;
    int NetLady;
    int NetRoad;
    int NetHybrid;
    int NumElectric; /* number of electric bikes */
    int NumLady; /* number of lady bikes */
    int NumRoad; /* number of road bikes */
    int NumHybrid; /* number of hybrid bikes */
    int Num[4]; // version 3
    BikeHeap HRent;
    BikeHeap HElectric;
    BikeHeap HLady;
    BikeHeap HRoad;
    BikeHeap HHybrid;
}Station[12];

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
    
    for(i=0; i<5; i++){
        cout<<License[i];
    }
    cout<<endl;
    
    int LicenseTag=(int)License[0]-48;
    //cout<<LicenseTag<<endl;
    
    i=1;
    while(i<5){
        if(isdigit(License[i]))
            LicenseTag=LicenseTag*31+(License[i]-48);
        else
            LicenseTag=LicenseTag*31+(License[i]-55);
        i++;
    }
    LicenseTag>>=10;
    char temp = (char) LicenseTag;
    LicenseTag = temp;
    
    cout<<LicenseTag<<endl;
    
    newnode->Mileage=Mile;
    newnode->Station=StationName;
    newnode->Status=Free;

    // version 3
    Station[StationName].Num[Class]++;
    
    // Station[StationName];
    // version 2
    /*
    switch(Class) {
        case Electric:
            Station[StationName].NumElectric++;
            break;
        case Lady:
            Station[StationName].NumLady++;
            break;
        case Road:
            Station[StationName].NumRoad++;
            break;
        case Hybrid:
            Station[StationName].NumHybrid++;
            break;
    }
     */
    
    // version 1
    /*
    if(Class==0){
        Station[StationName].NumElectric++;
    }
    else if(Class==1){
        Station[StationName].NumLady++;
    }
    else if(Class==2){
        Station[StationName].NumRoad++;
    }
    else if(Class==3){
        Station[StationName].NumHybrid++;
    }
    */
    //Station[StationName].Net++;
    
    
}

void Inquire(string License){
    
}

void JunkIt(string License){
    
}

template<class K, class V>
void printHashTable(HashTable<K, V>& ht) {
    for(unsigned i = 0; i < ht.size(); ++i) {
        if( ht[i].size() > 0 ) {
            typename HashTable<K,V>::ListType::NodeType* node_ptr = ht[i].front;
            while( node_ptr ) {
                cout << node_ptr->key;
                if( node_ptr->next ) {
                    cout << "->";
                }
                node_ptr = node_ptr->next;
            }
            cout << endl;
        }
    }
}
void HashReport(HashTable<LicenseType, BikePtr>& ht){
    printHashTable(ht);
}

// print a heap in console
template<class T>
void printHeap(HeapType<T>& heap) {
    for(int i = 0; i < heap.size(); i = 2*i + 1) {
        for(int j = 0; j <= i; ++j) {
            cout << heap[i+j];
            if( j != i)
                cout << ", ";
        }
        cout << endl;
    }
}

ostream& operator<<(ostream& os, LicenseType& lt) {
    for(int i = 0; i < 5; ++i)
        os << lt[i];
    return os;
}

// create bit mask for extracting bits (like bits 11-18 in hash function)
unsigned createMask(unsigned start, unsigned end) {
    unsigned mask = 0;
    for(unsigned i = start; i < end; ++i) {
        mask |= (1 << i);
    }
    return mask;
}

// The hashfunction used by our program
int hashfunc(LicenseType key) {
    unsigned hash = (unsigned)key[0]-48;
    int i=1;
    while(i<5){
        if(isdigit(key[i]))
            hash = hash*31+(key[i]-48);
        else
            hash = hash*31+(key[i]-55);
        i++;
    }
    hash &= createMask(11,18);
    hash >>= 10;
    return hash;
}

int main(){
    
    // Example using the HeapType class
    /*
    HeapType<BikeType> bikeHeap;
    for(int i = 0; i < 10; ++i) {
        BikeType b;
        b.Mileage = random() % 100;
        bikeHeap.insert(b);
    }
    printHeap(bikeHeap);
     */
    
    // HashTable Example
    typedef HashTable<LicenseType, BikePtr> BikeTable;
    
    BikeTable bikeTable(256, &hashfunc);
    BikeType b1, b2, b3;
    for(int i = 0; i < 5; i++) {
        b1.License[i] = 'a';
        b2.License[i] = 'a';
        b3.License[i] = 'b';
    }
    bikeTable.insert(b1.License, &b1);
    bikeTable.insert(b2.License, &b2);
    bikeTable.insert(b3.License, &b3);
    printHashTable(bikeTable);
    /*
    BikeTable::NodeType* x = bikeTable.get(b1.License);
    if( x ) {
        for(int i = 0; i < 5; i++) {
            cout << x->key[i];
            if( i < 4 ) cout << ", ";
        }
        cout << endl;
    }
    
    int hash = hashfunc(b1.License);
    BikeTable::ListType list = bikeTable[hash];
    bool b = (it_1 != it_2);
    for(BikeTable::ListType::iterator it = list.begin(); it.nonend(); ++it) {
        for(int i = 0; i < 5; ++i) {
            //cout << (*it).key[i] << ", ";
            cout << it->key[i];
            if( i < 4 ) cout << ", ";
        }
        cout << " :: ";
    }
    cout << endl;
    */
    
    
    string state;
    string move;
    string Class,License,Station;
    ClassType Type = Electric;
    xStationType StationName = Danshui;
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
