#include <iostream>
#include <set>
#include <vector>
#include <list>
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

void printBinaryIndex(int bits, int index)
{
    if(bits < 1) return;

    int p = pow(2, bits - 1);
    if(index >= p)
    {
        cout << "1 ";
        printBinaryIndex(bits - 1, index - p);
    }
    else
    {
        cout << "0 ";
        printBinaryIndex(bits - 1, index);
    }
}

int main()
{
    bool data[5][2000];

    for(int i = 0; i != 5; ++i)
        for(int j = 0; j != 2000; ++j)
        {
            if(data[i][j]) data[i][j] = 1;
            else data[i][j] = 0;
        }

    // random pick several features and construct a subset

    int Y1_cnt = 0;
    for(int j = 0; j != 2000; ++j)
        Y1_cnt += data[0][j];

    double ratio = Y1_cnt / 2000.0;

    set<int> s;
//    s.insert(1);
//    s.insert(2);
//    s.insert(3);
//    s.insert(4);

    vector<list<int> > subsets( pow(2, s.size()), list<int>() );

    for(size_t i = 0; i != 2000; ++i)
    {
        size_t subset_idx = 0;

        for(set<int>::iterator iter = s.begin(); iter != s.end(); ++iter)
        {
            subset_idx *= 2;
            subset_idx += data[*iter][i];
        }

        subsets[subset_idx].push_back(i);
    }

    double i_stat = 0;

    int cnt = 0;

    for(vector<list<int> >::iterator iter1 = subsets.begin(); iter1 != subsets.end(); ++iter1)
    {
        int num_of_Y1 = 0;
        size_t partition_size = (*iter1).size();

        for(list<int>::iterator iter2 = (*iter1).begin(); iter2 != (*iter1).end(); ++iter2)
        {
            if(data[0][*iter2])
                ++num_of_Y1;
        }

        double temp = (ratio * partition_size - num_of_Y1);
        i_stat += pow(temp, 2);

        cout << "Variables in subset: x_{1 2 3 4}.\nThe partition comes from ";
        printBinaryIndex(4, cnt++);
        cout << endl;
        cout << "partition size is " << partition_size << endl;
        cout << "Num of Y1 is " << num_of_Y1 << endl;
        cout << "Y1 ratio in the partition is " << ((double) num_of_Y1 / partition_size) << endl;
        cout << endl;
    }

    cout << "The Y1 ratio in whole sample is " << ratio << endl;
    cout << "I_stat is " << i_stat << endl;

}
