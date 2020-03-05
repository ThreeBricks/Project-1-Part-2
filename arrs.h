#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <set>

using namespace std;

int * getSortedArray(int n){
    int *arr=new int[n];
    for(int i=0; i<n;i++){
        arr[i]=n-i;
    }

    return arr;
}

int * getRandomArray(int n){
    int * arr=new int[n];
    set<int> randSet;
    mt19937 randy(time(0));
    while(randSet.size()<static_cast<unsigned int> (n)){
        int v=randy()%n+1;
        randSet.insert(v);
    }
    int i=0;
    for(const auto val: randSet){
        arr[i]=val;
        i+=1;
    }
    shuffle(arr,arr+n,randy);
    return arr;
}
