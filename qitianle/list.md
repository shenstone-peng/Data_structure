### 队列
#### 作业
- 用数组实现一个顺序队列
- 用链表实现一个链式队列
- 实现一个循环队列
641.[Design Circular Dequeue](https://leetcode.com/problems/design-circular-deque/submissions/)
```c++
class MyCircularDeque {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        size=k+1;
        _queue.resize(size,0);
        head=0;
        tail=0;
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(isFull())return false;
        head=(head-1+size)%size;
        _queue[head]=value;
        return true;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(isFull())return false;
        _queue[tail]=value;
        tail=(tail+1)%size;
        return true;
    }

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(isEmpty())return false;
        head=(head+1)%size;
        return true;
    }

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(isEmpty())return false;
        tail=(tail-1+size)%size;
        return true;
    }

    /** Get the front item from the deque. */
    int getFront() {
        if(isEmpty())return -1;
        return _queue[head];
    }

    /** Get the last item from the deque. */
    int getRear() {
        if(isEmpty())return -1;
        return _queue[(tail-1+size)%size];
    }

    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return head==tail;
    }

    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return ((tail+1)%size)==head;
    }
    vector<int> _queue;
    int head;
    int tail;
    int size;
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
 ```


239.[sliding window maxium](https://leetcode.com/problems/sliding-window-maximum/)
 ```c++
 class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty())return {};
        vector<int> stack;

        for(int i=k-1;i>=0;i--)if(stack.empty()||nums[stack.back()]<nums[i])stack.push_back(i);
        reverse(stack.begin(),stack.end());

        int start=0;
        vector<int> res={nums[stack[start]]};
        for(int i=k;i<nums.size();++i)
        {
            if(stack[start]<i-k+1)start++;
            while(stack.size()>start&&nums[stack.back()]<=nums[i])stack.pop_back();
            stack.push_back(i);
            res.push_back(nums[stack[start]]);
        }
        return res;
    }
};
 
 ```
 #### 重点
 - 用数组实现的队列叫做顺序队列，用链表实现的队列叫做链式队列
 - 循环队列可以不用考虑数据搬移问题
 - **阻塞队列**其实就是在队列基础上增加了阻塞操作。简单来说就是在队列为空的时候，从队头去数据会被阻塞。因为此时还没有数据可取，直到队列中有了数据才能返回；如果队列已经满了，那么插入数据的操作就会被阻塞，直到队列中有空闲位置后再插入数据，然后再返回。——生产者-消费者模型
 - 在多线程情况下，会有多个线程同时操作队列，这个时候就会存在线程安全问题，那如何实现一个线程安全的队列呢？
 线程安全的队列我们叫做**并发队列**。最简单直接的实现方式是直接在enqueue()、dequeue()方法上加锁，但是锁粒度大并发度会比较低，同一时刻仅允许一个存或者取操作。实际上，给予数组的循环队列，利用CAS原子操作，可以实现非常高效的并发队列。这也是循环队列比链式队列应用更加广发的原因。

 q:线程池没有空闲线程时，新的任务请求线程资源时，线程池该如何处理？各种处理策略又是如何实现的呢？
 a：我们一般有两种策略。第一种是非阻塞的处理方式，直接拒绝任务请求；另一种是阻塞的处理方式，将请求排队，等到有空闲线程是，取出排队的请求继续处理。那如何存储排队的请求呢？
 给予链表的实现方式，可以实现一个支持无限排队的无界队列(unbounded queue)，但是可能会导致过多的请求排队等待，请求处理的响应时间过长。所以，针对响应时间比较命案的系统，基于链表实现的无限排队的线程池是不合适的。
 而基于数组实现的有界队列(bounded queue)，队列的大小有限，所以线程池中排队的请求超过队列大小是，接下来的请求就会被拒绝，这种方式对响应时间命案的系统来说，就相对更加合理。不过，设置一个合理的队列大小，也是非常有讲究的。队列太大导致等待的请求太多，队列太小会导致无法充分利用系统资源、发挥最大性能。
