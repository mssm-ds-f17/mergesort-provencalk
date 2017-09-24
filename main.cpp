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
    string name;
    Thing(int id=0,string s="");
};
Thing::Thing(int id, string s){
    this->id=id;
    this->name=s;
}
int random(int maxValue) {
    return rand() % maxValue + 1;
}
std::string randomString(int length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const unsigned int max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
vector<Thing> makeRandomThings(int count, int maxId)
{
    vector<Thing> things;
    for (int i = 0; i < count; i++) {
        things.push_back(Thing(random(maxId),randomString(5)));
    }
    for (int i = 0; i < count; i++) {
        things[i].thingNum = i+1;
    }
    return things;
}

void print(vector<int> v){
    for(unsigned int i=0;i<v.size();i++){
        cout<<v[i]<<", ";
    }
    cout<<endl;
}
void print(vector<Thing> t){
    for(unsigned int i=0; i<t.size(); i++){
        cout<<t[i].id<<": ";
        cout<<t[i].name<<", ";
    }
    cout<<endl;
}

bool isSorted(vector<Thing>& things, function<bool(const Thing& a, const Thing& b)> comp){
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
bool operator<(string& a, string& b){
    const char charset[]="a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,"
                          "A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,"
                          "0,1,2,3,4,5,6,7,8,9";
    int a_index;
    int b_index;
    for(unsigned int i=0;i<a.size();i++){
        for(unsigned int j=0;j<sizeof(charset);j++){
            if(a[i]==charset[j]){
                a_index=j;
            }
            if(b[i]==charset[j]){
                b_index=j;
            }
            if(a_index<b_index){
                return true;
            }
            else{
                break;
            }
        }
    }
     return false;
}
bool operator<(Thing& a, Thing& b) {
    if(a.id<b.id){
        return true;
    }
    else if(a.id==b.id&&a.name<b.name){
        return true;
    }
    else{
        return false;
    }
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
        if(t[i]<t[j]){
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
}
void merge(vector<int>&v, int l, int m, int r){
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
void mergeSort(vector<Thing>& t, int start, int end){
    if(start < end){
        int middle = (start+end)/2;
        mergeSort(t,start,middle);
        mergeSort(t,middle+1,end);
        merge(t,start,middle,end);
    }
}
void mergeSort(vector<int>& values, int start, int end){
    if(start < end){
        int middle = (start+end)/2;
        mergeSort(values,start,middle);
        mergeSort(values,middle+1,end);
        merge(values,start,middle,end);
    }
}

int main()
{   vector<Thing>t=makeRandomThings(10,20);
    vector<int> v{6,78,3,22,45,33,63,88,54,99,1};
    print(v);
    print(t);
    mergeSort(v,0,v.size()-1);
    mergeSort(t,0,t.size()-1);
    print(v);
    print(t);
    return 0;
}
