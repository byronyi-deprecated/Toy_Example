#ifndef BACKWARDDROPPING_HPP
#define BACKWARDDROPPING_HPP

#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <map>
using namespace std;

class BackwardDropping
{
public:
    BackwardDropping(int** observation, unsigned int num_x, unsigned int sample_size);
    ~BackwardDropping();

    pair<double,set<int> > findMaxSubset(const set<int>& subset);

private:
    int dropOneVariable(const set<int>& subset);
    double I_stat(const set<int>& s);
    double pow(double num, int exp);

    unsigned int x;
    unsigned int size;
    double ratio;
    int** data;
};

#endif // BACKWARDDROPPING_HPP
