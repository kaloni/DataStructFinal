Everything is templated as template<class Key, class Value>

3 classes in HashTable.h

1) struct HTNode<Key,Value> is the node type in the linked list

2) class HTList<Key,Value> is the linked list used in hash table

3) class HashTable<K,V> is the hash table. It’s basically a vector<HTList<Key,Value>>

///////////////////////////
CONSTRUCTOR : HashTable(int size, int (*hashfunc)(Key key))

HashTable uses a hash function, which you give the HashTable in constructor as
a function pointer :

///////////////////
INSERT : insert(Key key, Value val)

When doing insert(Key key, Value val), the index is calculated as

int table_index = hashfunc(key)

Then a HTNode is inserted in the HTList (linked list) at position table_index in HashTable as

HashTable[table_index].push_back(new HTNode(key,value))
/////////////////////
GET: HTNode<Key,Value> get(Key key)

get the index in vector as

int table_index = hashfunc(key)

Then, search for the HTNode with HTNode.key == key in the HTList at table_index
///////////////////