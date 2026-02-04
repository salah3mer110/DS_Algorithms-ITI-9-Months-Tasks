#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class KeyType, class ValueType>
class MapEntry {
    KeyType key;
    ValueType value;
public:
    MapEntry(KeyType _key, ValueType _value) : key(_key), value(_value) {}
    KeyType getKey() const {
        return key;
    }
    ValueType getValue() const {
        return value;
    }
};

template<class KeyType, class ValueType>
class HashTable {
    vector<list<MapEntry<KeyType, ValueType>>> theLists;
    int currentSize;
public:
    explicit HashTable(int size = 101) : theLists(size), currentSize(0) {}

    bool Contains(const KeyType& x) const
    {
        int WhichList = MyHashFunction(x);
        const list<MapEntry<KeyType, ValueType>>& Bucket = theLists[WhichList]; 

        typename list<MapEntry<KeyType, ValueType>>::const_iterator itr = Bucket.begin();  

        while (itr != Bucket.end())
        {
            if ((*itr).getKey() == x)  
                return true;
            itr++;
        }
        return false;
    }

    bool Insert(const KeyType& X, const ValueType& Y)
    {
        if (Contains(X)) return false;

        int WhichList = MyHashFunction(X);

        theLists[WhichList].push_back(MapEntry<KeyType, ValueType>(X, Y));

        currentSize++;

        ///Check Load Factor : currentSize / theLists.size , > 0.7 rehashing (increase Vector Size By 2 , rehash All existing object )
        if ((float)currentSize / theLists.size() > 0.7)
            Rehash();

        return true;
    }

    bool Remove(const KeyType& X)
    {
        int WhichList = MyHashFunction(X);

        auto itr = std::find(theLists[WhichList].begin(), theLists[WhichList].end(), X);

        if (itr == theLists[WhichList].end())  return false;

        theLists[WhichList].erase(itr); /// RemoteAt(Node*)
        currentSize--;
        return true;
    }

    void MakeEmpty()
    {
        for (auto& lst : theLists)  
            lst.clear();
        currentSize = 0;
    }

    void Rehash()  
    {
        vector<list<MapEntry<KeyType, ValueType>>> oldLists = theLists;

        theLists.clear();
        theLists.resize(oldLists.size() * 2);
        currentSize = 0;

        for (const auto& bucket : oldLists) {
            for (const auto& el : bucket) {
                Insert(el.getKey(), el.getValue()); 
            }
        }
    }

    ValueType LookUP(const KeyType& Key) const
    {
        int index = MyHashFunction(Key);
        const list<MapEntry<KeyType, ValueType>>& bucket = theLists[index];

        for (const auto& el : bucket) { 
            if (el.getKey() == Key)
                return el.getValue();
        }

        return ValueType();
    }

protected:
    int MyHashFunction(const KeyType& x) const
    {
        hash<KeyType> hashFunction;
        int InitialHashValue = hashFunction(x);
        return InitialHashValue % theLists.size();
    }
};

int main()
{
    HashTable<int, string> table(3);
    cout << "Insert tests\n";
    cout << table.Insert(1, "Ali") << endl;
    cout << table.Insert(2, "Mohamed") << endl;
    cout << table.Insert(1, "X") << endl;
    cout << "\nContains tests\n";
    cout << table.Contains(1) << endl;
    cout << table.Contains(3) << endl;
    cout << "\nLookUP tests\n";
    cout << table.LookUP(1) << endl;
    cout << table.LookUP(2) << endl;
    cout << table.LookUP(99) << endl;
    cout << "\nRemove tests\n";
    cout << table.Remove(2) << endl;
    cout << table.Contains(2) << endl;
    cout << table.Remove(2) << endl;
    cout << "\nRehash test\n";
    table.Insert(3, "Omar");
    table.Insert(4, "Youssef");
    table.Insert(5, "Ahmed");
    cout << table.LookUP(3) << endl;
    cout << table.LookUP(4) << endl;
    cout << table.LookUP(5) << endl;

    return 0;
}