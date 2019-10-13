//
//  main.cpp
//  arrays
//
//  Created by kyoto shen on 2019/10/7.
//  Copyright © 2019 kyoto shen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution{
public:
    void bubbleSort(vector<int> A){
        int size=(int)A.size();
        bool flag=false;
        for (int i=0; i<size; i++) {
            flag=false;
            for (int j=0;j<size-i-1;j++){
                if(A[j]>A[j+1]){
                    int tmp=A[j+1];
                    A[j+1]=A[j];
                    A[j]=tmp;
                    flag=true;
                }

            }
            if(!flag)break;
        }
    }
    void insertionSort(vector<int> A){
        int size=(int)A.size();
        if(size<=1) return ;
        for(int i=1;i<size;i++){
            int tmp=A[i];
            int j=i-1;
            for(;j>=0;j--){
                if(A[j]>tmp){

                    A[j+1]=A[j];

                }
                else break;
            }
            A[j+1]=tmp;
        }
    }
};
int main(int argc, char const *argv[]) {
    printf("hello");
    int a[]={1,3,5,2,43,21,45,32,12,3};
    vector<int> test(a,a+sizeof(a)/sizeof(int));
    Solution* sort=new Solution;
    sort->insertionSort(test);
    return 0;
}
