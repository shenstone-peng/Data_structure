### 数组--2020 01 23
#### 作业
- 实现一个支持动态扩容的数组
- 实现一个大小固定的有序数组
- 实现两个有序数组合并为一个有序数组
```c++{.line-numbers}
const int initialLen=10;
template <class T>
class myArray
{
  public:
    myArray(int len=initialLen)
    {
      T* p=new T[len];
      m_data=p;
      m_capacity=len;
      m_size=0;
    }
    //function
    void add(int index,T num);
    void remove(int index);
    void removeElement(T num);
    void resize(int len);
    int size();
    //data
    T* m_data;
    int m_capacity;
    int m_size;

};
/*添加第index个值*/
template <class T>
void Array<T>::add(int index, T num)
{
  if(index<0||index>m_size)
  {
    printf("[Error]Here is a illegal index!\n");
    return;
  }
  if(m_size>=m_capacity)
  {
    resize(2*m_capacity);//扩容2倍空间
  }
  for(int i=m_size-1;i>=index;i--)
  {
    m_data[i+1]=m_data[i];
  }
  m_data[index]=num;
  m_size++;
}
/*删除第index数*/
template <class T>
void Array<T>::remove(int index)
{
  if(index<0||index>m_size)
  {
    printf("[Error]Here is a illegal index!\n");
    return;
  }
  for(int i=index;i<m_size;i++)
  {
    m_data[i]=m_data[i+1];
  }
  m_size--;
}
/*删除值为num的数*/
template <class T>
void Array<T>::removeElement(T num)
{
  int i=0;
  int flag=0;
  for(;i<m_size;i++)
  {
    if(m_data[i]==num)
    {
      flag=1;
      break;
    }
  }
  if(flag==1)
  {
    remove(i);
  }
  else
  {
    printf("[Error]There is no %d in the array",num);
    return;
  }
}
/*扩容*/
template <class T>
void Array<T>::resize(int len)
{
  if(len<=m_capacity)
    printf("[Error]New len is smaller than before\n");
  T* p=new T[len];
  for(int i=0;i<m_size;i++)
  {
    p[i]=m_data[i];
  }
  delete[] m_data;
  m_data=p;
  m_capacity=len;
}
```
Leetcode：
15.[Three Sum](https://leetcode.com/problems/3sum/)
```c++{.line-numbers}
class solution{
  public:
      vector<vector<int> >threeSum(vector<int> nums)
      {
        vector<vector<int> >res;
        if(nums.size()<3)return res;
        for(int i=0;i<nums.size()-2;i++)
        {
          if(nums[i]>0)break;
          if(i>0&&nums[i]==nums[i-1])continue;
          int begin=i+1;
          int end=nums.size()-1;
          while(begin<end)
          {
            int target=nums[i]+nums[begin]+nums[end];
            if(target==0)
            {
              vector<int> ss;
              ss.push_back(nums[i]);
              ss.push_back(nums[begin]);
              ss.push_back(nums[end]);
              res.push_back(ss);
              while(begin<end&&nums[begin]==nums[begin+1])begin++;
              while(begin<end&&nums[end]==nums[end-1])end--;
              begin++;end--;
            }
            else if(target<0)begin++;
            else end--;
          }

        }
        return res;
      }
}
/*先确定一个数，然后从头到尾开始判断缩小范围*/
```
169.[Majority Element](https://leetcode.com/problems/majority-element/)
```c++{.line-numbers}
/*这种方案需要思考，空间复杂度低*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if(nums.size()<=2)return nums[0];
        int candidate=nums[0];
        int count=1;
        for(int i=1;i<nums.size();i++)
        {
            if(nums[i]==candidate)
            count++;
            else
            count--;
            if(count==0)candidate=nums[i+1];
        }
        return candidate;
    }
};
```
41.[Missing Positive](https://leetcode.com/problems/first-missing-positive/)
solution1
```c++{.line-numbers}
class Solution {
public:
    void swap(vector<int>& nums, int i, int j)
    {
        int tmp=nums[i];
        nums[i]=nums[j];
        nums[j]=tmp;
    }
    int firstMissingPositive(vector<int>& nums) {
        //int flag=1;
        int i=0;
        int length=nums.size();

        while(i<length)
        {
            if(nums[i]<=0 || nums[i]> length || nums[i]==i+1)
            {
                i++;
            }
           else
            {
               if(nums[i]==nums[nums[i]-1])
               {
                   i++;
                   continue;
               }
                swap(nums,i,nums[i]-1);
            }
        }
        for(int k=0;k<length;k++)
        {
            if(nums[k]!=k+1)return k+1;
        }
        return length+1;

    }
};
```
solution2
```c++{.line-numbers}
class Solution {
public:
    struct comparator {
 bool operator()(int i, int j) {
 return i > j;
 }
};
    int firstMissingPositive(vector<int>& nums) {
        priority_queue<int, std::vector<int>, comparator> minHeap;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]>0)minHeap.push(nums[i]);
        }
            //minHeap.push(nums[i]);
        if(minHeap.empty())return 1;
        int min=minHeap.top();
        minHeap.pop();
        if(min!=1)return 1;
        while(!minHeap.empty())
        {
            int tmp=minHeap.top();
            minHeap.pop();

            if(tmp-min>1)return min+1;
            min=tmp;
        }
        return min+1;
    }
};
```

#### 重点：
1. 数组适合查找操作，但是查找的时间复杂度并不为O(1)。即便是排序好的数组，你用二分查找，时间复杂度也是O(logn)。所以正确表述应该是，数组支持随机访问，根据下标随机访问的时间复杂度为O(1)
2. 数组的插入和删除十分低效，因为需要先遍历找到位置，再进行插入和删除操作
  改进措施：
【插入】：
    - 在数组第k个位置插入元素i。可以直接将原来的第k个元素移至数组末尾，然后在第k个位置插入元素i。（**重要**：前提是数组无顺序要求）
【删除】：
    - 将多次删除操作集中在一起执行，然后再一次性移动数组。这样可以节省移动数组的次数。（**重要**：JVM标记清除垃圾回收算法的核心思想）
3. 警惕数组越界问题
```c++{.line-numbers}
int main(int argc, char** argv)
{
  int i=0;
  int arr[3]={0};
  for(;i<=3;i++)
  {
    arr[i]=0;
    printf("hello,world");
  }
  return 0;
}

```
这段代码会无限打印”hello.world"，因为arr[3]访问越界，正好访问到了i的位置，导致i被赋值为0
4. 容器和数组的选择
- 数组性能好
- 如果事先数据大小已知，并且对数据的操作非常简单，也可以直接使用数组。
- 多维数组时，数组更加直观

#### 笔记：
JVM标记清除算法：
大多数主流虚拟机采用可达性分析算法来判断对象是否存活，在标记阶段，会便利所有GC ROOTS，将所有GC ROOTS可达的对象标记为存活。只有当标记工作完成后，清理工作才会开始。
不足：1.效率问题。标记和清理效率都不高，但是当知道只有少量垃圾产生时会很高效。
     2.空间问题。会产生不连续的内存空间碎片

二维数组内存寻址：
```
对于m*n的数组，a[i][j](i<m,j<n)的地址为
address(a)+(i*n+j)*type_size
```
