#include "BackwardDropping.hpp"

BackwardDropping::BackwardDropping(int** observation, unsigned int num_x, unsigned int sample_size)
    : x(num_x), size(sample_size)
{
    data = new int*[x + 1];

    for(unsigned int i = 0; i != x + 1; ++i)
    {
        data[i] = new int[size];

        for(unsigned int j = 0; j != size; ++j)
            data[i][j] = observation[i][j];
    }

    int Y1_cnt = 0;
    for(unsigned int j = 0; j != sample_size; ++j)
        Y1_cnt += data[0][j];

    ratio = Y1_cnt / (double) sample_size;
}

BackwardDropping::~BackwardDropping()
{
    for(unsigned int i = 0; i != x + 1; ++i)
        delete [] data[i];

    delete [] data;
}



pair<double,set<int> > BackwardDropping::findMaxSubset(const set<int>& subset)
{
    cout << "The I stat of initial subset is " << I_stat(subset) << endl << endl;
    map<double, set<int> > candidates;

    double i_stat = I_stat(subset);
    candidates.insert(pair<double, set<int> > (i_stat, subset));

    set<int> candidate = subset;

    while(candidate.size() > 1)
    {
        pair<double, set<int> > temp = dropOneVariable(candidate);

        candidates.insert(temp);

        candidate = temp.second;
    }

    double max_I_stat = 0.0;

    for(map<double, set<int> >::iterator iter = candidates.begin(); iter != candidates.end(); ++iter)
        max_I_stat = (iter->first > max_I_stat)? iter->first : max_I_stat;

    map<double, set<int> >::iterator max_iter = candidates.find(max_I_stat);

    cout << "Found the set yielding the highest i_stat. The i_stat is " << max_iter->first << endl;
    printSet(max_iter->second);
    cout << endl;

    return *max_iter;
}



pair<double, set<int> > BackwardDropping::dropOneVariable(const set<int>& subset)
{
    map<double, set<int> > candidates;

    for(set<int>::iterator iter = subset.begin(); iter != subset.end(); ++iter)
    {
        set<int> tentative = subset;
        tentative.erase(*iter);

        double i_stat = I_stat(tentative);
        candidates.insert(pair<double, set<int> >(i_stat, tentative));
    }

    double max_I_stat = 0.0;

    for(map<double, set<int> >::iterator iter = candidates.begin(); iter != candidates.end(); ++iter)
        max_I_stat = (iter->first > max_I_stat)? iter->first : max_I_stat;

    map<double, set<int> >::iterator max_iter = candidates.find(max_I_stat);

    if(max_iter == candidates.end())
    {
        cout << "Cannot drop a variable by max I stat. Drop a variable by chance." << endl;

        set<int> tentative = subset;
        tentative.erase(tentative.begin());

        return pair<double, set<int> >(I_stat(tentative), tentative);
    }

    cout << "Dropped one variable. The I stat is " << max_iter->first << endl;
    printSet(max_iter->second);
    cout << endl;

    return *max_iter;
}


void BackwardDropping::printSet(const set<int>& s)
{
    cout << "Printing the current set: ";
    for(set<int>::iterator iter = s.begin(); iter != s.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}


double BackwardDropping::I_stat(const set<int>& s)
{
    vector<list<int> > subsets( pow(2, s.size()), list<int>() );

    for(size_t i = 0; i != size; ++i)
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
        int Y1_cnt = 0;
        size_t partition_size = (*iter1).size();

        for(list<int>::iterator iter2 = (*iter1).begin(); iter2 != (*iter1).end(); ++iter2)
        {
            if(data[0][*iter2])
                ++Y1_cnt;
        }

        i_stat += pow(ratio * partition_size - Y1_cnt, 2);
    }

    return i_stat;
}

double BackwardDropping::pow(double num, int exp)
{
    if(exp < 1) return 1;
    return pow(num, exp - 1) * num;
}
