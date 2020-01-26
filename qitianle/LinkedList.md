### 链表
#### 作业
- 实现单链表、循环链表、双向链表、支持增删操作
- 实现单链表反转
- 实现两个有序的链表合并为一个有序链表
- 实现求链表的中间结点
Leetcode：
141.[Linkede List Cycle](https://leetcode.com/problems/linked-list-cycle/)
```c++{.line-numbers}
class Solution{
  public:
     bool hasCycle(ListNode *head)
     {
       if(NULL == head)return false;
       ListNode* once=head;
       ListNode* twice=head;
       if(NULL==once->next||NULL==twice->next->next)return false;
       while(twice != NULL)
       {
         if(twice->next==NULL||twice->next->next==NULL)return false;
         twice=twice->next->next;
         once=once->next;
         if(once==twice)return true;

       }
       return false;
     }  
}
```
23.[mergeKLists](https://leetcode.com/problems/merge-k-sorted-lists/)
```c++{.line-numbers}
class Solution{
  ListNode* mergeTwoLists（ListNode* L1, ListNode* L2）
  {
    ListNode *res=new ListNode(20);
    ListNode *Cur1=new ListNode(1);
    ListNode *Cur2=new ListNode(1);
    pCur1->next=l1;
    pCur2->next=l2;
        ListNode* head=pRes;
        while(pCur1->next&&pCur2->next)
        {
                if(pCur1->next->val <= pCur2->next->val)
                {
                        ListNode* pTmp=pCur1->next;
                        pCur1->next=pCur1->next->next;
                        pTmp->next=NULL;
                        pRes->next=pTmp;
                        pRes=pRes->next;

                }
                else
                {
                        ListNode* pTp=pCur2->next;
                        pCur2->next=pCur2->next->next;
                        pTp->next=NULL;
                        pRes->next=pTp;
                        pRes=pRes->next;
                }
        }
        if(pCur1->next){ pRes->next=pCur1->next; }
        else{ pRes->next=pCur2->next;}
        return head->next;

    }
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if(lists.empty())return NULL;
        while(!lists.empty())
        {
            if(lists.size()==1)return lists[0];
            ListNode* m_new=mergeTwoLists(lists[0],lists[1]);
            lists.push_back(m_new);
            lists.erase(lists.begin());
            lists.erase(lists.begin());

        }
        return NULL;
     }
};
```
