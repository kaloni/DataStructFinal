#include<iostream>
#include <fstream>
#include<string>
#include<iomanip> //using setw()
#include<sstream>
#include<stdlib.h>
#include "HeapType.cpp"
#include "HashTable.cpp"
#include "Graph.h"

using namespace std;


enum StatusType {Free, Rented};

enum ClassType { Electric, Lady, Road, Hybrid, NoClass};

enum xStationType {
    Danshui, Hongshulin, Beitou,
    Shilin, Zhongshan, Xinpu,
    Ximen, Liuzhangli, Muzha,
    Guting, Gongguan, Jingmei, NoStation = -1 };

//typedef char LicenseType[5];
struct LicenseType {
public:
    LicenseType() {
        for(int i = 0; i < 5; ++i) {
            license[i] = '0';
        }
    }
    LicenseType(string str) {
        if( str.length() < 5 )
            throw "LicenseType Constructor : Invalid license string";
        else {
            for(int i = 0; i < 5; ++i) {
                license[i] = str[i];
            }
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
    friend ostream& operator<<(ostream& os, const LicenseType& lt);
    char license[5];
};

ostream& operator<<(ostream& os, const LicenseType& lt) {
    for(int i = 0; i < 5; ++i)
        os << lt.license[i];
    return os;
}

int hashfunc(LicenseType key);

struct BikeType{
    BikeType() : Mileage(0) {}
    BikeType(LicenseType license, ClassType classtype, int mileage, xStationType station) :
    License(license), Status(Free), Class(classtype), Mileage(mileage), Station(station) {}
    LicenseType License;
    StatusType Status;
    int Mileage; /* most recently rented mileage */
    int Cursor; /* cursor to the entry in heap where there is a pointer to this node */
    xStationType Station;
    ClassType Class;
};

// operator > for comparing bikes
bool operator>(const BikeType& b1, const BikeType& b2) {
    return b1.Mileage > b2.Mileage;
}
bool operator==(const BikeType& b1, const BikeType& b2) {
    return ( !(b1 > b2) && !(b2 > b1) );
}
ostream& operator<< (ostream &out, BikeType &bike)
{
    cout << bike.Mileage;
    return out;
}

typedef struct BikeType* BikePtr;

struct BikePtrComp {
    bool operator()(BikePtr p1, BikePtr p2) {
        /*
        if( p1->License == p2->License ) {
            return false;
        }
         */
        return p1->Mileage >= p2->Mileage;
    }
};

bool licenseComp(BikePtr p1, BikePtr p2) {
    return p1->License == p2->License;
}

typedef HeapType<BikePtr, BikePtrComp> BikeHeap;
typedef HashTable<LicenseType, BikePtr> BikeTable;

struct StationType{
    //xStationType Station;
    int Net; /* total income of station */
    int Nets[4];
    int Num[4];
    BikeHeap HRent;
    BikeHeap heaps[4];
    /*
     int NetElectric;
     int NetLady;
     int NetRoad;
     int NetHybrid;
     */
    /*
     int NumElectric; // number of electric bikes
     int NumLady; // number of lady bikes
     int NumRoad; // number of road bikes
     int NumHybrid; // number of hybrid bikes
     */
    /*
    BikeHeap HElectric;
    BikeHeap HLady;
    BikeHeap HRoad;
    BikeHeap HHybrid;
    */

    void add(BikePtr bike){
        heaps[bike->Class].insert(bike);
    }
}Station[12];

void NewBike(ClassType Class, string License, int Mile, xStationType StationName, HashTable<LicenseType, BikePtr>&ht ){
    
    BikeType *newnode = new BikeType(LicenseType(License), Class, Mile, StationName);
    Station[StationName].Num[Class]++;
    Station[StationName].add(newnode);
    ht.insert(newnode->License, newnode);
    
    /*
    //cout<<Class<<" "<<License<<" "<<Mile<<" "<<StationName<<endl;
    newnode->Class=Class;
    int i;
    for(i=0; i<5; i++){
        newnode->License[i]=License[i];
    }

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
     */

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

//template<class K, class V>
void Inquire(string Licensestr, HashTable<LicenseType, BikePtr>& ht){

    cout << setw(15) << "License" << setw(15) << "Mileage"<<setw(15) << "Class" << setw(15) << "Station"<<endl;
    cout<<"============================================================"<<endl;
    LicenseType License(Licensestr);
    BikePtr* bikeMetaPtr = ht.get(License);
    if( bikeMetaPtr ) {
        BikePtr bike = *bikeMetaPtr;
        xStationType station = bike->Station;
        ClassType Class=bike->Class;
        int mileage = bike->Mileage;
        cout << setw(15) << License<< setw(15) <<mileage<<setw(15) << Class<< setw(15) << station<<endl;
    }
    else {
        cout << "Bike " << Licensestr << " does not belong to our company." << endl;
    }

   /* int LicenseTag=(int)License[0]-48;
    //cout<<LicenseTag<<endl;

    int i=1;
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

    HashTable<K,V>::NodeType* ptr;
    while(ptr){
        if(ptr->key==License)
            cout << setw(15) << ptr->key<< setw(15) << ptr->mile<<setw(15) << ptr->class << setw(15) << ptr->station<<endl;
        else
            ptr=ptr->next;
    }
    if(ptr==NULL)
        cout << "Bike "<<License<<" does not belong to our company."<<endl;*/

    //int LicenseTag=hashfunc(License_Type);

}

/*template<class K, class V>
void find_bike(string License,HashTable<K, V>& ht){
    BikePtr bike = ht.get(License);
    int mileage = bike->Mileage;
}*/

//template<class T, class Comp, class K, class V>
void JunkIt(string Licensestr, BikeHeap& heap, BikeTable& ht){
    LicenseType License;
    //License.license;
    int i;
    for(i=0;i<5; i++){
        License.license[i]=Licensestr[i];
    }
    BikePtr bike = *ht.get(License);
    int index = heap.find(bike, &licenseComp);
    if(index>=0){
        ht.erase(License);
        heap.remove(index);
        delete bike;
    }

}

template<class K, class V>
void printHashTable(HashTable<K, V>& ht) {
    for(int i = 0; i < ht.size(); ++i) {
        if( ht[i].size() > 0 ) {
            cout << "[" << i << "]";
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
void HashReport(){
}

// print a heap in console
void printHeap(BikeHeap& heap) {
    for(int i = 0; i < heap.size(); i = 2*i + 1) {
        for(int j = 0; j <= i; ++j) {
            cout << "(" << heap[i+j]->License << ", " << heap[i+j]->Mileage << ")";
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

// create bit mask for extracting bits (like bitnullptr,0s 11-18 in hash function)
unsigned createMask(unsigned start, unsigned end) {
    int hashfunc(LicenseType key);
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

xStationType strToStationType(const string& stationName) {
    if(stationName == "Danshui")
        return Danshui;
    else if(stationName == "Hongshulin")
        return Hongshulin;
    else if(stationName == "Beitou")
        return Beitou;
    else if(stationName =="Shilin")
        return Shilin;
    else if(stationName =="Zhongshan")
        return Zhongshan;
    else if(stationName =="Xinpu")
        return Xinpu;
    else if(stationName =="Ximen")
        return Ximen;
    else if(stationName =="Liuzhangli")
        return Liuzhangli;
    else if(stationName =="Muzha")
        return Muzha;
    else if(stationName =="Guting")
        return Guting;
    else if(stationName =="Gongguan")
        return Gongguan;
    else if(stationName =="Jingmei")
        return Jingmei;
    return NoStation;
}

string stationTypeToString(int stationName) {
    if(stationName == Danshui)
        return "Danshui";
    else if(stationName == Hongshulin)
        return "Hongshulin";
    else if(stationName == Beitou)
        return "Beitou";
    else if(stationName == Shilin)
        return "Shilin";
    else if(stationName == Zhongshan)
        return "Zhongshan";
    else if(stationName == Xinpu)
        return "Xinpu";
    else if(stationName == Ximen)
        return "Ximen";
    else if(stationName == Liuzhangli)
        return "Liuzhangli";
    else if(stationName == Muzha)
        return "Muzha";
    else if(stationName == Guting)
        return "Guting";
    else if(stationName == Gongguan)
        return "Gongguan";
    else if(stationName == Jingmei)
        return "Jingmei";
    return "NoStation";
}

ClassType strToClass(string str) {
    if(str == "Electric")
        return Electric;
    else if(str == "Lady")
        return Lady;
    else if(str == "Road")
        return Road;
    else if(str == "Hybrid")
        return Hybrid;
    return NoClass;
}

int main(int argc, char* argv[]){

    BikeTable bikeTable(256, &hashfunc);
    BikeHeap bikeHeap;
    
    // This is how we read from file
    ifstream in_stream;
    in_stream.open("Testcases/TC1/testCase01");
    streambuf *cinbuf = cin.rdbuf();
    cin.rdbuf( in_stream.rdbuf() );
    
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
            iss >> Class>>License>>Mile>>Station;
            Type = strToClass(Class);
            StationName = strToStationType(Station);
            NewBike(Type, License, Mile, StationName, bikeTable);
        }
        else if(move=="Inquire"){
            iss >> License;
            Inquire(License, bikeTable);
        }
        else if(move=="JunkIt"){
            iss >> License;
            JunkIt(License, bikeHeap, bikeTable);
        }
        else if(move=="HashReport"){
            HashReport();
        }
    }
    
    // Remember to close the ifstream and restore cin buffer
    cin.rdbuf( cinbuf );
    in_stream.close();
    
    ////////////////// Testing ////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
    // Graph Test (station map)
    // open the station map file
    /*
     ifstream in_stream;
     in_stream.open("Testcases/TC1/testMap");
     streambuf *cinbuf = cin.rdbuf();
     cin.rdbuf( in_stream.rdbuf() );
     
     // declase the station map as a graph
     Graph stationMap(12);
     // parse the station map file into graph
     string str;
     while( cin >> str) {
     xStationType from = getStationType(str);
     cin >> str;
     xStationType to = getStationType(str);
     cin >> str;
     int distance;
     try {
     stringstream ss(str);
     ss >> distance;
     //distance = stoi(str);
     }
     catch(...) {
     cerr << "Parse error : Could not parse distance between " << stationTypeToString(from) << " and " << stationTypeToString(to) << endl;
     exit(-1);
     }
     if( from != NoStation && to != NoStation )
     stationMap.insert(from, to, distance);
     else
     cerr << "Parse error : Could not parse station names : " << stationTypeToString(from) << " | " << stationTypeToString(to) << endl;
     }
     
     // restore iostream, close filestream
     cin.rdbuf( cinbuf );
     in_stream.close();
     
     // print the station map (printed as integers, because that's how it's stored)
     // 0 is Danshui, 1 is Hongshulin etc.
     cout << "   StationMap Graph    " << endl;
     cout << stationMap << endl;
     
     
     cout << "   Shortest paths from Danshui to all other stations   " << endl;
     // get the "previous station vector" from the dijkstra shortest path algorithm
     // this gives all shortests paths from, in this case, Danshui station
     vector<int> prev = stationMap.dijkstra(Danshui);
     // Calculate path to each station, and print the paths :)
     for(int i = 0; i < stationMap.size(); i++) {
     forward_list<int> shortest_path = stationMap.getPath(prev, i);
     if( ! shortest_path.empty() ) {
     
     for(forward_list<int>::iterator it = shortest_path.begin();;) {
     cout << stationTypeToString(*it);
     if( ++it != shortest_path.end() )
     cout << "->";
     else break;
     }
     cout << endl;
     }
     }
     */
    // End of Graph Test
    ////////////////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // HeapType Test
    /*
     struct BikeMin {
     bool operator()(const BikeType& b1, const BikeType& b2) {
     return b1.Mileage < b2.Mileage;
     }
     };
     
     BikePtr a,b,c;
     a = new BikeType;
     b = new BikeType;
     c = new BikeType;
     a->License[0] = 'a';
     b->License[0] = 'b';
     c->License[0] = 'c';
     a->Mileage = 1;
     b->Mileage = 1;
     c->Mileage = 1;
     BikeHeap bikeHeap;
     bikeHeap.insert(a);
     bikeHeap.insert(b);
     bikeHeap.insert(c);
     
     printHeap(bikeHeap);
     
     int index = bikeHeap.find(b, &licenseComp);
     cout << "index = " << index << endl;
     cout << "mileage = " << b->Mileage << endl;
     
     delete a;
     delete b;
     delete c;
     a = b = c = nullptr;
     */
    // End of HeapType Test
    ////////////////////////////////////////////////////////////////////////////////////////
    
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // HashTable Test
    /*
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
     */
    // End of HashTable Test
    ////////////////////////////////////////////////////////////////////////////////////////
    //*/
    
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

    return 0;
}


