// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;
//Done
HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = new HashNode;
    nw->key = key;
    nw->next = next;
    return nw;
}
//Done
HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new HashNode*[tableSize];
    for (int i = 0; i < bsize; i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        count += s[i];
    }
    return (count % tableSize);
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
    //TODO
    int index = hashFunction(key);
    HashNode * temp = table[index];
    while(temp != NULL) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    //TODO: Search the list at that specific index and return the node if found
    return NULL;
    
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    
    //TODO
    HashNode * temp = searchItem(key);
    if (temp == NULL) {
        int index = hashFunction(key);
        HashNode * nw = createNode(key, table[index]);
        nw->commitNums.push_back(cNum);
        table[index] = nw;
        return true;
    } else {
        temp->commitNums.push_back(cNum);
        return true;
    }
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        HashNode * temp = table[i];
        while(temp) {
            cout << temp->key << "(";
            for (int k = 0; k < temp->commitNums.size(); k++) {
                cout << temp->commitNums.at(k) << ",";
            }
            cout << ")";
            if (temp->next != NULL) {
                cout << "-->";
            }
            temp = temp->next;
        }
        cout << endl;
    }
}
