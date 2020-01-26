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
```c++{.line-numbers}
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
```c++
class Solution {
public:
    bool isValid(string s) {
        stack<int> m;
        unordered_map<char,int> mhash;
        mhash[')']=-1;
        mhash['}']=-2;
        mhash[']']=-3;
        for(int i=0;i<s.size();++i)
        {
            char& tmp=s[i];
            if(tmp == ')' || tmp == '}' || tmp == ']')
            {
                if(m.empty())return false;
                if(m.top()+mhash[tmp]!=0)return false;
                else
                {
                    m.pop();
                }
            }
            else
            {
                switch(s[i])
                {
                    case '(':
                        m.push(1);
                        break;
                    case '{':
                        m.push(2);
                        break;
                    case '[':
                        m.push(3);
                        break;
                    default:
                        return false;
                }
            }
            //cout<<s[i]<<endl;
            //printf("%s\n",s);
        }
        return m.empty();
    }
};

```
32.[longest-valid-parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> sp;
        int start=0;
        int ans=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='(')
            {
                sp.push(i);
            }
            else
            {
                if(sp.empty())
                {
                    start=i+1;
                }
                else
                {
                    int index=sp.top();sp.pop();
                    ans=max(ans,sp.empty()?i-start+1:i-sp.top());
                }
            }
        }
        return ans;
    }
};
```
150.[Evaluate Reverse Polish Notatio](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
```c++{.line-numbers}
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> myStack;
        for(auto str : tokens) {
            if(str != "+" && str != "-" && str != "*" && str != "/") {
                myStack.push(stoi(str));
            }
            else {
                int second = myStack.top(); myStack.pop();
                int first = myStack.top(); myStack.pop();
                int result;
                switch (str[0]) {
                    case '+':{
                        result = first + second;
                        break;
                    }
                    case '-':{
                        result = first - second;
                        break;
                    }
                    case '*':{
                        result = first * second;
                        break;
                    }
                    case '/':{
                        result = first / second;
                        break;
                    }
                    default:{
                        result = 0;
                        break;
                    }
                }
                myStack.push(result);
            }
        }
        return myStack.size() == 1 ? myStack.top() : 0;
    }
};
```
