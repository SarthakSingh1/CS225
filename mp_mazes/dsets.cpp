/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num){
    for(int i = 0; i<num;i++){
        mySet.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(mySet[elem] <0){return elem;}
    else{return find(mySet.at(elem));}
}

void DisjointSets::setunion(int a, int b)
{
int rootA = find(a);
int rootB = find(b);

int new_size = mySet[rootA] + mySet[rootB];
if (mySet[rootA] < mySet[rootB])
{
    mySet[rootB] = rootA;
    mySet[rootA] = new_size;
    }
    else{
        mySet[rootA] = rootB;
        mySet[rootB] = new_size;
    }
}

int DisjointSets::size(int elem){
    int root = find(elem);
    return -mySet[root];
}