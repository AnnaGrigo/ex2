#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_



class UnionFind
{
  public:
    int numberOfElements;
    int *size;
    int *parents;
    Company **data;
    double *value_increase;
    int *owners;

    UnionFind(int numberOfElements);
    ~UnionFind();
    Company *Find(int index);
    void increasesize(int group_id, int increase = 1);
    void Union(int p, int q, double factor);
    double getCompanyValue(int comp_id);
};

#endif