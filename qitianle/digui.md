### 递归
#### 作业
- 编程实现斐波那契数列求职
$$
f(n)=f(n-1)+f(n-2)
$$
- 编程实现求阶乘
$$
n!
$$
- 编程实现一组数据结合的全排列
leetcode
70.[Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
```c++
class Solution {
public:
    int climbStairs(int n) {
        if(n==0)return 0;
        if(n==1)return 1;
        if(n==2)return 2;
        int k=n+1;
        int dp[k];
        dp[0]=0;dp[1]=1;dp[2]=2;
        for(int i=3;i<k;i++)
        {
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};

```

#### 重点
递归需要满足三个条件
1. 一个问题的解可以分解为几个子问题的解
2. 这个问题与分解之后的子问题，除了数据规模不同，求解思路完全一样
3. 存在递归终止条件
要警惕的问题：
1. 堆栈溢出
2. 重复计算
