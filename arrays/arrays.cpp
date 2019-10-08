#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;


const int initialLen=10;

template <class T>
class Array{
public:
  Array(int len = initialLen){
    T* p = new T[len];
    m_data = p;
    m_capacity = len;
    m_size = 0;
  }
  void resize(int len) {
    if(len<=m_capacity){
      printf("new len is smaller than before\n");
      //return false;
    }
    T* p = new T[len];
    for (int i = 0; i < m_size; ++i){
      p[i]=m_data[i];
    }
    delete[] m_data;
    m_data=p;
    m_capacity=len;
  }
  int size(){
    return m_size;
  }
  //...
//private:
  T* m_data;       //数组首个数据的指针
  int m_capacity;  //数组容量
  int m_size;     //数组实际大小
};

int main(int argc, char const *argv[]) {
  Array<int>* sp=new Array<int>(10);
  sp->m_data[0]=1;
  sp->m_data[1]=2;
  if(sp->m_data[0]==NULL){
    printf("ummm\n");
  }
  if(sp->m_data[2]==NULL){
    printf("right\n");
  }
  int a=2;
  //int b=lcm(2,3);
  printf("%d",b);
  return 0;
}
