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
//添加操作
  void add(int index, T num);
  void addFirst(T num);
  void addLast(T num);
//删除操作
  void remove(int index);
  T removeFirst();
  T removeLast();
  void removeElement(T num);
  //...
//private:
  T* m_data;       //数组首个数据的指针
  int m_capacity;  //数组容量
  int m_size;     //数组实际大小
};
//--------------------------------------
//              添加操作
//--------------------------------------
template <class T>
void Array<T>::add(int index, T num){
  if(index<0 || index > m_size){
    cout<<"illegal index"<<endl;
    throw 0;
  }
  if(m_size>=m_capacity){
    resize(2*m_capacity);
  }
  for(int i=m_size-1;i>=index;i--){
    m_data[i+1]=m_data[i];

  }
  m_data[index]=num;
  m_size++;
}
template <class T>
void Array<T>::addLast(T num){
  if(m_size >= m_capacity){
    resize(2*m_capacity);
  }
  m_data[m_size] = num;
  m_size++;
}
template <class T>
void Array<T>::addFirst(T num){
  add(0,num);
}

//--------------------------------------
//           删除操作
//--------------------------------------
template <class T>
void Array<T>::remove(int index){
    if(index<0||index>=m_size){
        cout<<"illegal index"<<endl;
        throw 0;
    }
    for(int i=index;i<m_size;i++){
        m_data[i]=m_data[i+1];
    }
    m_size--;
   // return
}
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
