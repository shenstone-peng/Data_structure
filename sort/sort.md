
---
【基础知识】
有序度：数组中具有有序关系的元素对的个数。
```{.line-numbers}
  有序元素对：a[i]<=a[j] (i<j)
```
>举例：
{2,4,3,1,5,6}
有序对：{(2,4) (2,3) (2,5) (2,6)
(4,5) (4,6) (3,5) (3,6)
(1,5) (1,6) (5,6)}
所以有序度为11

【公式】逆序度=满有序度-有序度
我们排序的过程就是一种增加有序度，减少逆序度的过程，最后达到满有序度，就说明排序完成了。

----

# 冒泡排序
- 【原地排序】：冒泡的过程只涉及相邻数据的交换操作，只需要常量级的临时空间，所以它的空间复杂度为O（1），是原地算法。  
- 【稳定排序】：在冒泡排序中，只有交换才可以改变两个元素的前后顺序。为了保证  冒泡排序算法的稳定性，当有相邻的两个元素大小相等的时候，我们不做交换，相同大小的数据在排序前后不会改变顺序，所以冒泡排序是稳定的排序算法。  
- 【时间复杂度】  
```
   分析方法：
 
 时间复杂度可以通过求解（逆序度->有序度）的平均操作总数来得到。  
 
 举例：冒泡排序每交换一次，有序度加1。对n个数据的数组进行冒泡排序，平均交换次数是多少呢？最坏情况下，初始状态的有序度是0，
      所以要进行n*(n-1)/2次交换。最好情况下，初始状态的有序度是n*(n-1)/2,就不需要进行交换。我们可以取个中间值n*(n-1)/4，
      来表示初始有序度既不是很高也不是很低的平均情况。
```
实现code
```c++{.line-numbers}
void bubbleSort(vector<int> A){
        int size=A.size();
        bool flag=false;//判断是否需要继续排序
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
```
-----
# 插入排序
【原地排序】从实现过程可以很明显地看出，插入排序算法的运行并不需要额外的存储空间，所以空间复杂度是O(1)，也就是说，这是一个原地排序算法。
【稳定排序】在插入排序中，对于值相同的元素，我们可以选择将后面出现的元素，插入到前面出现元素后面，这样就可以保持原有的前后顺序不变，所以插入排序是稳定的排序算法。  
【时间复杂度】因为移动一次减少一点逆序度，所以平均时间复杂度还是O(n^2)
实现code
```c++{.line-numbers}
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
```
---
# 选择排序
选择排序算法的实现思路有点类似插入排序，也分为已排序区间。但是选择排序每次会从排序区间找到最小的元素，将其放到已排序的末尾。

------------

# 快速排序
【中心思想】如果要排序数组中下标从p到r之间的一组数据，我们选择p到r之间任意的一个数据作为pivot。我们遍历p到r之间的数据，将小于pivot的放到左边，将大于pivot的放到右边，将pivot放到中间。然后再重复操作pivot左边的数组，和右边的数组。根据分治和递归的处理思想，直至区间缩小到1，就说明所有的数据都有序了。

递推公式：
```
递推公式：
quick_sort(p..r)=quick_sort(p..q-1)+quick_sort(q..r)

终止条件：
p>=r
```


伪代码
```
//快速排序，A是数组，n表示数组的大小
quick_sort(A,n){
  quick_sort_c(A,0,n-1);
}
//快速排序递归函数，p,r为下标
quick_sort_c(A,p,r){
  if p>=r then return;

  q=partition(A,p,r);//获取分区点
  quick_sort_c(A,p,q-1);
  quick_sort_c(A,q+1,r)

}
```


实现code
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
总结：归并排序的处理过程是由下到上的，先处理子问题，然后再合并。而快排正好相反，它的处理过程是由上到下的。归并排序虽然是稳定的，时间复杂度为O(nlogn)的算法，但由于是非原地排序算法，内存空间消耗很大。而快排则通过设计巧妙的原地分区函数，可以实现原地排序，解决了归并排序占用太多内存的问题。


-----
PS:如何在无序数组找到第k个数,时间复杂度O(n)
利用分治思想，先选择一个数作为pivot，以此数进行分区，得到这个数在数组中的位置，然后与k比较，再选择新的分区，直到找到刚好第k个数。
实现code
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
