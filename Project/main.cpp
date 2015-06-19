#include<iostream>
#include <fstream>
#include<string>
#include<iomanip> //using setw()
#include<sstream>
#include<stdlib.h>
#include "HeapType.cpp"
#include "HashTable.cpp"
#include<vector>
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
        for(int i = 0; i < 5; ++i) {
            license[i] = str[i];

        if( str.length() < 5 )
            throw "LicenseType Constructor : Invalid license string";
        else for(int i = 0; i < 5; ++i) {
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
        if(bike->Status==0)
            heaps[bike->Class].insert(bike);
        else
            HRent.insert(bike);
    }
}Station[12];

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

string classToStr(ClassType classtype) {
    if(classtype == Electric)
        return "Electric";
    else if(classtype == Lady)
        return "Lady";
    else if(classtype == Road)
        return "Road";
    else if(classtype == Hybrid)
        return "Hybrid";
    return "NoClass";
}


void NewBike(ClassType Class, string License, int Mile, xStationType StationName, HashTable<LicenseType, BikePtr>&ht ){

    BikeType *newnode = new BikeType(LicenseType(License), Class, Mile, StationName);
    Station[StationName].Num[Class]++;
    Station[StationName].add(newnode);
    ht.insert(newnode->License, newnode);

    cout << "New bike is received by Station " << stationTypeToString(StationName) << "." << endl;
}

void Inquire(string Licensestr, HashTable<LicenseType, BikePtr>& ht){

    LicenseType License(Licensestr);
    BikePtr* bikeMetaPtr = ht.get(License);
    if( bikeMetaPtr ) {
        BikePtr bike = *bikeMetaPtr;
        xStationType station = bike->Station;
        ClassType Class = bike->Class;
        int mileage = bike->Mileage;
        cout << setw(15) << "License" << setw(15) << "Mileage"<<setw(15) << "Class" << setw(15) << "Station"<<endl;
        cout<<"============================================================"<< endl;
        cout << setw(11) << License << setw(15) << mileage<<setw(15) << classToStr(Class) << setw(15) << stationTypeToString(station) << endl << endl;
    }
    else {
        cout << "Bike " << Licensestr << " does not belong to our company." << endl;
    }
}

void StationReport(xStationType statName) {

}

void UBikeReport() {

}

void JunkBikePtr(BikePtr bikeHeap){

}


void Rent(xStationType StationName, ClassType Class) {
    if(Station[StationName].heaps[Class].top()){
        Station[StationName].heaps[Class].top()->Status=Rented;
        Station[StationName].add(Station[StationName].heaps[Class].top());
        Station[StationName].heaps[Class].remove(0);
        cout<<"A bike is rented from "<<stationTypeToString(StationName)<<"."<<endl;
    }
    else
        cout<<"No free bike is available."<<endl;
}

int Returns(xStationType statName,  LicenseType license, int mile, HashTable<LicenseType, BikePtr>&ht, Graph &stationMap) {
    BikePtr* bikeMetaPtr = ht.get(license);
    if( bikeMetaPtr ) {
        BikePtr bike = *bikeMetaPtr;
        bike->Status=Free;

        //ºâ¿ú
        //int Mile=0;
        vector<int> prev = stationMap.dijkstra(bike->Station);
             // Calculate path to each station, and print the paths :)
             //for(int i = 0; i < stationMap.size(); i++) {
             forward_list<int> shortest_path = stationMap.getPath(prev, statName);
             int dist=0;
             if( ! shortest_path.empty() ) {

                 for(forward_list<int>::iterator it = shortest_path.begin(); it != shortest_path.end();) {
                     int from_tmp = *it;

                     //if( it + 1 != shortest_path.end() ) {
                     forward_list<int>::iterator it_next = it;
                     it_next++;
                     if( it_next != shortest_path.end() ) {
                        int to_tmp = *(it_next);
                        dist += stationMap.distance(from_tmp, to_tmp);
                     }
                     it = it_next;
                    //}
                    //if( ++it != shortest_path.end() ){}
                 //cout << "->";
                    //else break;
                }
             //cout << endl;
             }
            // }

        int charge=0;
        int tmp=mile-bike->Mileage;

        if(tmp>dist){
            switch(bike->Class){
                case 0:
                    charge=tmp*40;
                    break;
                case 1:
                    charge=tmp*30;
                    break;
                case 2:
                    charge=tmp*20;
                    break;
                case 3:
                    charge=tmp*25;
                    break;
            }
        }
        else{
            switch(bike->Class){
                case 0:
                    charge=tmp*30;
                    break;
                case 1:
                    charge=tmp*25;
                    break;
                case 2:
                    charge=tmp*15;
                    break;
                case 3:
                    charge=tmp*20;
                    break;
            }
        }


        bike->Mileage=mile;
        Station[statName].add(bike);
        Station[statName].Nets[bike->Class]+=charge;
        Station[statName].Net+=charge;
        cout<<"Rental charge for this bike is "<<charge<<"."<<endl;
    }
    return 0;
}

void Trans(xStationType StationName, string license, BikeTable& ht) {
    LicenseType License(license);
    BikePtr* bikeMetaPtr = ht.get(License);
     if( bikeMetaPtr ) {
        BikePtr bike = *bikeMetaPtr;
        if(bike->Status==0){
            int index = Station[bike->Station].heaps[bike->Class].find(bike, &licenseComp);
            Station[bike->Station].heaps[bike->Class].remove(index);
            bike->Station = StationName;
            Station[StationName].add(bike);
            cout<<"Bike "<<license<<" is transferred to "<<stationTypeToString(StationName)<<"."<<endl;
        }
        else
            cout<<"Bike "<<license<<" is now being rented."<<endl;


    }
    else {
        cout << "Bike " << license << " does not belong to our company." << endl;
    }


}

void NetSearch(xStationType statName) {

/*template<class K, class V>
void find_bike(string License,HashTable<K, V>& ht){
    BikePtr bike = ht.get(License);
    int mileage = bike->Mileage;
}*/
}

void JunkIt(string Licensestr, BikeTable& ht) {

    LicenseType License;
    int i;
    for(i=0;i<5; i++){
        License.license[i]=Licensestr[i];
    }
    BikePtr* bikeMetaPtr = ht.get(License);
    if( bikeMetaPtr ) {

        BikePtr bike = *bikeMetaPtr;
        cout << "Bike " << bike->License << " is deleted from " << stationTypeToString(bike->Station) << "." << endl;

        int index = Station[bike->Station].heaps[bike->Class].find(bike, &licenseComp);

        ht.erase(License);
        if(index>=0){
            Station[bike->Station].heaps[bike->Class].remove(index);
            delete bike;
        }
    }
    else {
        cout << "Bike " << Licensestr << " does not belong to our company." << endl;
    }
}



template<class K, class V>
void printHashTable(HashTable<K, V>& ht) {
    cout << "Hash Table" << endl;
    for(int i = 0; i < ht.size(); ++i) {
        if( ht[i].size() > 0 ) {
            cout << i << " ";
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
int hashfunc(LicenseType License) {

    char input[5];
    int binary[50]={0};
    int i,j,k;
    int key=0;
    for ( i=0 ; i<5 ; i++ )
        input[i] = License[i];

    for(i=0;i<5;i++){
        if(isdigit(input[i]))
            key = key*31+(input[i]-48);
        else
            key = key*31+(input[i]-55);
    }
    i=0;
    while(key/2!=0){
        binary[i]=key%2;
        key=key/2;
        i++;
    }
    binary[i]=key%2;
    key=0;
    for(i=10;i<18;i++){
        k=1;
        j=i-10;
        while(j>0){
            k=k*2;
            j--;
        }
        key=key+k*binary[i];
    }
    return key;
}

int main(int argc, char* argv[]){

    BikeTable bikeTable(256, &hashfunc);
    //BikeHeap HEAP;

     ifstream in_stream;
     in_stream.open("Testcases/TC3_basic/testMap");
     ofstream out_stream;
     out_stream.open("Testcases/TC3_basic/test3_output.txt" );
     streambuf *cinbuf = cin.rdbuf();
     cin.rdbuf( in_stream.rdbuf() );
     streambuf *coutbuf = cout.rdbuf();
     cout.rdbuf( out_stream.rdbuf() );

     // declase the station map as a graph
     Graph stationMap(12);
     // parse the station map file into graph
     string str;
     while( cin >> str) {
     xStationType from = strToStationType(str);
     cin >> str;
     xStationType to = strToStationType(str);
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
     //cin.rdbuf( cinbuf );
     in_stream.close();

//    ifstream in_stream;
    in_stream.open("Testcases/TC3_basic/testCase03");
//    streambuf *cinbuf = cin.rdbuf();
    cin.rdbuf( in_stream.rdbuf() );


    string state;
    string move;
    string Class,License,StationString;
    ClassType Type = Electric;
    xStationType StationName = Danshui;
    int Mile;
    while(getline(cin, state)){

        istringstream iss(state);
        iss>>move;

        if(move=="NewBike"){
            iss >> Class>>License>>Mile>>StationString;
            Type = strToClass(Class);
            StationName = strToStationType(StationString);
            NewBike(Type, License, Mile, StationName, bikeTable);
        }
        else if(move=="Inquire"){
            iss >> License;
            Inquire(License, bikeTable);
        }
        else if(move=="JunkIt"){
            iss >> License;
            JunkIt(License, bikeTable);
        }
        else if(move=="HashReport"){
            //HashReport();

            printHashTable(bikeTable);

        }
        else if(move=="Rent"){
            iss>>StationString>>Class;
            Type = strToClass(Class);
            StationName = strToStationType(StationString);
            Rent(StationName, Type);
        }
        else if(move=="Returns"){
            iss>>StationString>>License>>Mile;
            StationName = strToStationType(StationString);
            LicenseType license(License);
            Returns(StationName,  license, Mile, bikeTable,stationMap);

        }
        else if(move=="Trans"){
            iss>>StationString>>License;
            StationName = strToStationType(StationString);
            Trans(StationName, License, bikeTable);
        }
    }

    // Remember to close the ifstream and restore cin buffer
    cin.rdbuf( cinbuf );
    cout.rdbuf( coutbuf );
    in_stream.close();
    out_stream.close();



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

