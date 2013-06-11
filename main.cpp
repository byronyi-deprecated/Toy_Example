#include <iostream>
#include <BackwardDropping.hpp>
#include <cstdlib>
#include <set>
using namespace std;
/*


class BackwardDropping
{
    vector<Observation> trainingSet;

    inline void influenceMeasure(vector<Observation> partition)
    {

    }

    void train()
    {

    }

public:
    BackwardDropping(vector<Observation> input)
        : trainingSet(input)
    {
        train();
    }
};

class IMeasure
{
    vector<unsigned int> subset_idx;
public:
    IMeasure(vector<unsigned int> subset) : subset_idx(subset) {}


};
*/
/*
class Variable
{
    size_t _id;
    vector<int> observations;
    size_t getID() const {return _id;}

public:
    Variable(size_t id) : _id(id) {}
    void addObservation(size_t idx, int val)
    {
        observations.push_back(val);
    }
};

void insert(map<int, int>& m, int key, int val)
{
    pair<map<int,int>::iterator,bool> i;
    i = m.insert(pair<int, int>(key, val));
    if(i.second == false)
        cerr << "this key exists already" << endl;
}

int main()
{

}
*/

//void printBinaryIndex(int bits, int index)
//{
//    if(bits < 1) return;

//    int p = pow(2, bits - 1);
//    if(index >= p)
//    {
//        cout << "1 ";
//        printBinaryIndex(bits - 1, index - p);
//    }
//    else
//    {
//        cout << "0 ";
//        printBinaryIndex(bits - 1, index);
//    }
//}

int main()
{
    cout << "This is the toy example from H. Wang's paper." << endl;
    cout << "All the variable is binary (0 or 1)." << endl;

    unsigned int dimX;
    unsigned int size;

    cout << "Customize parameters (y/n)? " ;
    char y;
    cin >> y;

    if(y == 'y')
    {
        cout << "Please enter the dimension of X: ";
        cin >> dimX;
        cout << endl;


        cout << "Please enter the size of training example: ";
        cin >> size;
        cout << endl << endl;
    }
    else
    {
        dimX = 30;
        size = 150;
    }

    cout << "Generating X randomly...." << endl << endl;

    srand(1);

    int** data = new int*[dimX + 1];
    for(int i = 0; i != dimX + 1; ++i)
        data[i] = new int[size];

    for(int i = 0; i != dimX + 1; ++i)
        for(int j = 0; j != size; ++j)
            data[i][j] = rand() % 2;

    for(int j = 0; j != size; ++j)
    {
        if(rand() % 2) data[0][j] = (data[1][j]  + data[2][j] + data[3][j]) % 2;
        else data[0][j] = (data[4][j] + data[5][j]) % 2;
    }

    cout << "As in the paper, response variable Y is generated using formula: " << endl;
    cout << "Y = (X_1 + X_2 + X_3) (modulo 2) " << endl;
    cout << "Y = (X_4 + X_5) (modulo 2) " << endl;
    cout << "Both of two formulas have 50% chance" << endl;
    cout << endl << endl;

    cout << "Training..." << endl << endl;
    BackwardDropping trainingSet(data, dimX, size);

    set<int> subset;

    cout << "Please enter the size of initial subset: ";
    int size_set;
    cin >> size_set;
    cout << endl;

    for(int i = 0; i != size_set; ++i)
    {
        cout << "Please enter the " << (i + 1) << "-th element: ";
        int idx;
        cin >> idx;

        if(idx <= dimX)
            subset.insert(idx);
        else
        {
            cout << "Out of range. Please enter it again." << endl;
            --i;
            continue;
        }
    }

    BackwardDropping::printSet(subset);
    cout << endl;

    set<int> max_subset = trainingSet.findMaxSubset(subset).second;
}
