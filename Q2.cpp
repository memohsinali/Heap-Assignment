#include<iostream>
#include<cassert>
#include<fstream>
#include<string>
using namespace std;

template <class v>
struct HashItem
{
public:
    int key;
    v value;
    short status;

    HashItem() {

        key = 0;
        status = 0;
    }
};

template <class v>
class HashMap
{
private:
    HashItem<v>* hashArray;
    int capacity;
    int currentElements;

    virtual int getNextCandidateIndex(int key, int i) const
    {
        return ((key + i) % capacity);
    }


    // this function duplicates when load factor increases 0.75

    void duplicateCapacity()
    {
        int oldCapacity = capacity; // storing previous track of capacity

        HashItem<v>* temp = new HashItem<v>[capacity];
        for (int i = 0; i < capacity; i++)
        {
            temp[i] = hashArray[i];
        }

        delete[] hashArray;

        hashArray = new HashItem<v>[capacity * 2];
        capacity = capacity * 2;
        currentElements = 0;
        for (int i = 0; i < oldCapacity; i++)
        {
            if (temp[i].status == 2)
            {
                insert(temp[i].key, temp[i].value);
            }
        }
    }

public:

    //default constructor
    HashMap()
    {
        capacity = 10;
        hashArray = new HashItem<v>[capacity];
        currentElements = 0;
    }

    //parametarized constructor
    HashMap(int const capacity)
    {
        assert(capacity > 1);            // calling assert when capacity 
        this->capacity = capacity;
        hashArray = new HashItem<v>[capacity];
        currentElements = 0;
    }
    void insert(int const key, v const value)
    {

        float LF = ((float)currentElements / (float)capacity);     // typecasting to avoid warning converting from int type to float type
        if (LF >= 0.75)
        {
            duplicateCapacity();
        }

        int index = key % capacity;
        if (hashArray[index].status != 2)
        {
            hashArray[index].key = key;
            hashArray[index].value = value;
            hashArray[index].status = 2;
        }

        else if (hashArray[index].status == 2)
        {
            int i = 1;
            while (hashArray[index].status == 2)
            {
                index = getNextCandidateIndex(key, i++);
            }
        }
        currentElements++;
    }
    bool deleteKey(int const key)
    {
        int index = key % capacity;
        int i = 1;
        if (hashArray[index].key != key)
        {
            while (hashArray[index].key != key)
            {
                int i = 0;

                if (hashArray[index].status == 0)
                {
                    cout << "There is no key to be deleted\n";
                    return 0;
                }
                if (hashArray[index].status == 1)
                {
                    cout << "The key is already deleted\n";
                    return 0;
                }
                index = getNextCandidateIndex(key, i++);
            }
            return 1;
        }
        hashArray[index].status = 1;
        currentElements--;     // decrement currentElements 
        return 1;
    }
    v* get(int const key)
    {
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].key != key && hashArray[index].status != 0)
        {
            index = getNextCandidateIndex(key, i++);
        }


        if (hashArray[index].status == 0 || hashArray[index].status == 1)
        {
            return nullptr;
        }

        if (hashArray[index].key == key && hashArray[index].status == 2)
        {
            return (&hashArray[index].value);
        }


    }

    int get_Capacity()
    {
        return capacity;
    }

    ~HashMap()
    {
        if (hashArray != nullptr)
        {
            hashArray = nullptr;
        }

        delete hashArray;
    }

};

template<class v>

class QHashMap : public HashMap<v>
{
public:

    int getNextCandidateIndex(int key, int i)
    {
        i++;
        int capacity = HashMap<v> ::get_Capacity();
        i = i * i;
        return (key + i) % capacity;
    }

};

template<class v>
class DHashMap : public HashMap<v>
{
public:
    int getNextCandidateIndex(int key, int i)
    {
        int capacity = HashMap<v>::get_Capacity();
        int first_value = key % capacity;
        int second_value = (5 - (key % 5));
        int index = (first_value + i * second_value) % capacity;
        return index;
    }
};


void populateHash(string filename, HashMap<string>* hash)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "File not successfully opened\n" << endl;
        return;
    }

    int id;
    string name;

    while (inputFile >> id >> name)
    {
        hash->insert(id, name);
    }

    inputFile.close();
}


int main()
{

    HashMap<string>* map;
    map = new HashMap<string>;
    populateHash("Students.txt", map);
    cout << *map->get(9);
    map->deleteKey(9);
    assert(map->get(9) == nullptr);

    delete map;

    map = new QHashMap<string>;
    populateHash("students.txt", map);
    cout << *map->get(98);
    map->deleteKey(98);
    assert(map->get(98) == nullptr);
    delete map;

    map = new DHashMap<string>;
    populateHash("students.txt", map);
    cout << *map->get(101);
    map->deleteKey(101);
    assert(map->get(101) == nullptr);
    delete map;

    map = new HashMap<string>;
    populateHash("Students.txt", map);
    if (map->get(30) != nullptr)
    {
        cout << *map->get(30);
        map->deleteKey(30);
        assert(map->get(30) == nullptr);
    }
    delete map;
    return 0;

}