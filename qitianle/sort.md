### 排序
- 实现归并排序
```c++{.line-numbers}
void merge_sort(vector<int> nums,int n)
{
  merge_sort_c(nums,0,n-1);
}
void merge_sort_c(vector<int> nums,int start,int end)
{
  if(start>=end)return;
  int middle=(end+start)/2;
  merge_sort_c(nums,start,middle);
  merge_sort_c(nums,middle+1,end);
  merge(nums,start,middle,end);
}
void merge(vector<int> nums,int p,int q,int r)
{
  int i=p;
  int j=q+1;
  int k=0;
  vector<int> tmp(r-p+1);
  while(i<=q&&j<=r)
  {
    if(nums[i]<=A[j])
    {
      tmp[k++]=A[i++];
    }
    else
    {
      tmp[k++]=A[j++];
    }
  }
  int start =i;
  int end=q;
  if(j<=r)
  {
    start=j;end=r;
  }
  tmp[k:]=nums[start:end];
  nums[p:r]=tmp[0:];
}

```
- 实现快速排序
```c++{.line-numbers}
//获得分区点函数思路：1.从头开始遍历，i指向第一个大于pivot的数，j指向当前数，当A[j]<pivot时，将A[j]和A[i]互换，同时i++，最后将A[i]与pivot交换。
2.这样的好处是原地排序，不需要多余的内存空间
3.这样的坏处是不稳定
int partition(vector<int> &A, int p, int r){
                int pivot=A[r];
                int i=p;
                for(int j=p;j<r;j++){
                        if(A[j]<pivot){
                                int tmp=A[i];
                                A[i]=A[j];
                                A[j]=tmp;
                                i++;
                        }
                }
                for(int k=r;k>i;k--){
                        A[k]=A[k-1];
                }
                A[i]=pivot;
                return i;
        }



void quick_sort_c(vector<int> &A, int p, int r){
                if(p >= r) return ;
                int q = partition(A,p,r);
                quick_sort_c(A,p,q-1);
                quick_sort_c(A,q+1,r);
        }



void quick_sort(vector<int> &A){
                int size=(int)A.size();
                quick_sort_c(A,0,size-1);
        }
```
- 实现插入排序
```c++{.line-numbers}
void insertionSort(std::vector<int> nums)
{
  int size=nums.size();
  for(int i=0;i<nums.size();i++)
  {
    int tmp=nums[i];
    int j=i-1;
    for(;j>=0;j--)
    {
      if(tmp<nums[j])
      {
        nums[j+1]=nums[j];
      }
      else{
        break;
      }
    }
    nums[j+1]=tmp;
  }
}

```
- 实现冒泡排序
```c++{.line-numbers}
void bubbleSort(vector<int> nums)
{
  for（int i=0;i<nums.size();i++)
  {
    bool flag=true;
    for(int j=0;j<nums.size()-i-1;j++)
    {
      if(nums[j]>nums[j+1])
      {
        int tmp=nums[j];
        nums[j]=nums[j+1];
        nums[j+1]=tmp;
        flag=false;
      }
    }
    if(flag)break;
  }
}

```
- 实现选择排序
- 编程实现O(n)时间复杂度内找到一组数据的第K大元素
```c++{.line-numbers}
int partition(vector<int> &A, int p, int r){
                int pivot=A[r];
                int i=p;
                for(int j=p;j<r;j++){
                        if(A[j]<pivot){
                                int tmp=A[i];
                                A[i]=A[j];
                                A[j]=tmp;
                                i++;
                        }
                }
                for(int k=r;k>i;k--){
                        A[k]=A[k-1];
                }
                A[i]=pivot;
                return i;
        }
int findKthValue(vector<int> &A, int k){
               int size=(int)A.size();
               int p,r;
               p=0;
               r=size-1;
               while(p<r){
                       int q=partition(A,p,r);
                       if(q==k-1)return A[q];
                       if(q>k-1) r=q-1;
                       if(q<k-1) p=q+1;
               }
               return A[p];
       }
```


---
### 重点
- 为什么时间复杂度都是O(n)的情况下，插入排序比冒泡排序要好？
答：因为插入排序可以优化为1个赋值操作，而冒泡排序必须要三个



| 排序 | 是否原地排序？   |  是否稳定？  |最好  | 最坏  |平均|
| :------ | :-----  | :----|:----:  |:----:  |:----:  |
|冒泡排序|√|√|O(n)| O(n^2)|O(n^2)|
|插入排序|√|√|O(n)| O(n^2)|O(n^2)|
|选择排序|√|X|O(n^2| O(n^2)|O(n^2)|
