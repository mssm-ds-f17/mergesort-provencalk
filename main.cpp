#include <iostream>
#include <vector>
#include <functional>
#include "gtest/gtest.h"
#include <math.h>

using namespace std;

class Thing{
public:
    int id;
    int thingNum;
    Thing(){}
    Thing(int id){this->id=id;}
};
bool compareThingsById(const Thing&a, const Thing&b){
    return a.id<b.id;
}
bool isSorted(const vector<int>& values){
    if(values.size()<=1){
        return true;
    }
    for(unsigned int i=1; i<values.size();i++){
        if(values[i]<=values[i-1]){
            return false;
        }
    }
    return true;
}
void print(vector<int> v){
    for(unsigned int i=0;i<v.size();i++){
        cout<<v[i]<<", ";
    }
    cout<<endl;
}

/*bool isSorted(vector<Thing>& things, function<bool(const Thing& a, const Thing& b)> comp){
    if(things.size()<=1){
        return true;
    }
    for(unsigned int i=1;i<things.size();i++){
        if(comp(things[i],things[i-1])){
            return false;
        }
    }
    return true;
}

void merge(vector<Thing>&t, int l, int m, int r){
    int i,j,k;
    //temporary vectors
    vector<Thing>T(r-l+1);
    //merge int T
    i=l;
    j=m+1;
    k=0;
    while(i<=m&&j<=r){
        if(t[i].thingNum<t[j].thingNum){
            T[k]=t[i];
            i++;
        }
        else{
            T[k]=t[j];
            j++;
        }
        k++;
    }
    //copy any remaining elements
    while(i<=m){
        T[k]=t[i];
        i++;
        k++;
    }
    while(j<=r){
        T[k]=t[j];
        j++;
        k++;
    }
    //move data from T to t
    for(i=l;i<=r;i++){
        t[i]=T[i-l];
    }
}*/
void merge(vector<int>v, int l, int m, int r){
    int i,j,k;
    //temporary vectors
    vector<int>V(r-l+1);
    //merge into V
    i=l;
    j=m+1;
    k=0;
    while(i<=m&&j<=r){
        if(v[i]<v[j]){
            V[k]=v[i];
            i++;
        }
        else{
            V[k]=v[j];
            j++;
        }
        k++;
    }
    //copy any remaining element
    while(i<=m){
        V[k]=v[i];
        i++;
        k++;
    }
    while(j<=r){
        V[k]=v[j];
        j++;
        k++;
    }
    //merge back into v
    for(i=l; i<=r;i++){
        v[i]=V[i-l];
    }
}
/*void mergeSort(vector<Thing>& t, int start, int end){
    if(start < end){
        int middle = (start+end)/2;
        mergeSort(t,start,middle);
        mergeSort(t,middle+1,end);
        merge(t,start,middle,end);
    }
}
*/
void mergeSort(vector<int> values, int start, int end){
    if(start < end){
        int middle = start+end/2;
        mergeSort(values,start,middle);
        mergeSort(values,middle+1,end);
        merge(values,start,middle,end);
    }
}

int main()
{
    vector<int> v{6,78,3,22,45,33,63,88,54,99,1};
    cout<<v.size()<<endl;
    mergeSort(v,0,v.size()-1);
    print(v);
    return 0;
}
