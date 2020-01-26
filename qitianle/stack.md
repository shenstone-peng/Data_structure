### 栈
#### 作业
- 用数组实现一个顺序栈
```c++{.line-numbers}
class ArrayStack
{
  public:
  string *stack;
  int count;
  int n;
  ArrayStack(int ss){
    string* p=new string[ss];
    stack=p;
    count=0;
    this->n=ss;
  }
  bool push(string item)
  {
    if(count==n)return false;
    stack[count]=item;
    ++count;
    return true;
  }
  string pop()
  {
    if(count==0)return NULL;
    string tmp=stack[count-1];
    count--;
    return tmp;
  }
}
```
- 用链表实现一个链式栈
```c++
struct Node{
        string data;
        Node* next=NULL;
};
class LinkedListStack
{
public:
  Node* head;
  Node* rear;
  int count;
  int n;
  LinkedListStack()
  {
    head=new Node;
    head->data="head";
    rear=head;
    count=0;
  }
  void push(string value)
  {
          Node* pTmp=(Node*)malloc(sizeof(Node));
          pTemp->data=value;
          //rear->next=add;
          //rear=add;
          pTmp->next=head->next;
          head->next=pTmp->next;
          this->count++;
  }
  string pop()
  {
    if(NULL==head->next)return "";
    Node* ptmp=(Node*)malloc(sizeof(Node));
    ptmp=head->next;
    string pp=ptmp->data;
    head->next=ptmp->next;
    free(ptmp);
    return pp;
  }
}

```
- 编程模拟实现一个浏览器的前进、后退功能
20.[Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
32.[https://leetcode.com/problems/valid-parentheses/](https://leetcode.com/problems/longest-valid-parentheses/)
150.[Evaluate Reverse Polish Notatio](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
