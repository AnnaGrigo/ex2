#include "UnionFind.h"
UnionFind::UnionFind(int numberOfElements)
    : numberOfElements(numberOfElements)
    , size(new int[numberOfElements + 1]())
    , parents(new int[numberOfElements + 1]())
    , data(new Company *[numberOfElements + 1])
    , value_increase(new double[numberOfElements + 1]())
    , owners(new int[numberOfElements + 1]())
{
    for (int i = 1; i < (numberOfElements + 1); i++)
    {
        parents[i] = -1;
        size[i] = 1;
        data[i] = new Company(i, i);
        value_increase[i] = 0;
        owners[i] = -1;
    }
}

UnionFind::~UnionFind()
{
    delete[] size;
    delete[] parents;
    delete[] value_increase;
    delete[] owners;
    for (int i = 1; i < (numberOfElements + 1); i++)
    {
        if (data[i] != nullptr)
            delete data[i];
    }
    delete[] data;
}


Company *UnionFind::Find(int i)
{
    int old_parent = i;
    int parent = this->owners[i];
    double tsum = 0;
    while (parent > -1)
    {
        old_parent = parent;
        tsum += value_increase[i];
        parent = this->owners[parent];
    }
    return data[old_parent];
}

void UnionFind::Union(int acquire, int target, double Factor)
{
    acquire = Find(acquire)->getCompanyId();
    target = Find(target)->getCompanyId();
    double value = Factor * getCompanyValue(target);
    if (size[target] <= size[acquire])
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp];
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2];
        }
        value_increase[temp] += value;
        value_increase[temp2] -= value_increase[temp];
        parents[temp2] = temp;
    }
    else
    {
        int temp, last = acquire;
        while (last != -1)
        {
            temp = last;
            last = parents[temp];
        }
        int temp2, last2 = target;
        while (last2 != -1)
        {
            temp2 = last2;
            last2 = parents[temp2];
        }
        value_increase[temp] += value - value_increase[temp2];
        parents[temp] = temp2;
    }
    size[acquire] += size[target];
    owners[target] = acquire;
}
double UnionFind::getCompanyValue(int comp_id)
{
    double total_val = this->data[comp_id]->getValue();
    while (comp_id != -1)
    {
        total_val += value_increase[comp_id];
        comp_id = parents[comp_id];
    }
    return total_val;
}
