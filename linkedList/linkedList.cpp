#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;

struct node
{
   int data;
   node *next;
};
//fuction for travese the list
void traverse_List(node* pHead)
{
	if(pHead==NULL||pHead->next==NULL)
	{
		printf("Node is NULL\n");
      		return;
  	 }
    	node* pCur=pHead;

 	while(pCur->next)
	{
    		printf("node data is %d\n",pCur->next->data);
   		pCur=pCur->next;
	}
    	printf("finished traverser\n");
   	return;
}
//function for find the position of value in the linked list
node* find_List(node* pHead,int value)
{
	if(pHead==NULL||pHead->next==NULL)

	{
		printf("Node is NULL\n");
                return NULL;
	}
	node* pCur=pHead;
	int index = 0;
	while(pCur->next)
	{
		if(pCur->next->data==value)
		{
			printf("we have found the value in the %d node!",index);
			return pCur;
		}
		index++;
		pCur=pCur->next;
	}
	printf("we have not found the value %d in the nodes",value);
  return NULL;
}
//function for insert the new node which data is value after node *p
void insert_Node(node* p,int value)
{
	node* pNew=new node;
        pNew->data=value;
        pNew->next=p->next;
        p->next=pNew;

}
//function for delete the node which data is value if node exist in the linked list
void delete_Node(node* pHead, int value)
{
	if(pHead==NULL||pHead->next==NULL)
	{
		printf("node is NULL\n");
		return;
	}
	node* pPre=pHead;
	node* pCur=pHead->next;
	while(pCur)
	{
		if(pCur->data==value)
		{
			printf("find the value which need to delete\n");
			pPre->next=pCur->next;
			free(pCur);
			printf("have DELETE the node!\n");
			printf("now the node is\n");
			traverse_List(pHead);
			return;
		}
		pCur=pCur->next;
		pPre=pPre->next;
	}
	printf("we don't find the value:(\n");
        return;
}
//function for reverse the linked list
void reverse_Linkedlist(node* pHead)
{
	if(pHead==NULL|pHead->next==NULL)
	{
		printf("node is NULL\n");
		return;
	}
	node* pPre=pHead->next;
	node* pCur=pHead->next->next;
	while(pCur)
	{
		node* pTmp=pCur->next;
		pCur->next=pPre;
		pPre=pCur;
		pCur=pTmp;
	}
	//build the head structure of node
	pHead->next->next=NULL;
	pHead->next=pPre;
	printf("--------------------\n");
	printf("finished the reverse\n");
	traverse_List(pHead);
	return;
}
//get the length of node
int getLength(node* pHead)
{
	int len=0;
	if(pHead==NULL||pHead->next==NULL)
	{
		printf("node is NULL\n");
		return len;
	}
	node* pCur=pHead;
	while(pCur->next)
	{
		len++;
		pCur=pCur->next;
	}
	return len;
}
//input :node * head
//output:arrayList list which contain the datas of node in the reverse sorted
//print list from the tail of node
vector<int> printListFromTail(node* pHead)
{
	vector<int> res;
	if(pHead==NULL||pHead->next==NULL)
	{
		printf("node is NULL\n");
		return res;
	}

	reverse_Linkedlist(pHead);
	node* pCur=pHead;
	while(pCur->next)
	{
		res.push_back(pCur->next->data);
		pCur=pCur->next;
	}
	return res;

}
//input: node* head  int K
//output:node* p
//get the N-K node

//solution1
node* searchNodeK(node* pHead, int K)
{
	int len=0;
	len=getLength(pHead);
	if(K > len)
	{
		printf("K is larger than node\n");
		return NULL;
	}
	node* pCur=pHead;
	int k=len-K;
	while(k)
	{
		pCur=pCur->next;
		k--;
	}
	printf("the value is %d\n",pCur->next->data);
	return pCur->next;
}
//solution 2
//head->1->2->3->4->NULL
node* searchNodeK2(node* pHead, int k)
{
  if(pHead==NULL||pHead->next==NULL)
  {
    printf("node is NULL\n");
    return NULL;
  }
  node* pFir=pHead;
  node* pSec=pHead;
  for(int i=0;i<k;i++)
  {
    pFir=pFir->next;
  }
  while(pFir)
  {
    pFir=pFir->next;
    pSec=pSec->next;
  }
  printf("f2:the value is %d",pSec->data);
  return pSec;
}

//problem:判断链表是否有环：单链表中的环是指链表末尾的节点的next指针不为NULL，而是指向了链表中的某个节点，导致链表中出现了环形结构
//我的思路，遍历链表，将每个节点的地址存在数组中/哈希表中，然后对比是否存在相同的节点
bool isExistLoop(node* pHead)
{
  int flag=0;
  if(pHead==NULL||pHead->next==NULL)
  {
    printf("node is NULL\n");
    return flag;
  }
  unordered_map<node*,int> m;
  node* pCur=pHead;
  while(pCur->next)
  {
    if(m[pCur->next])
    {
      printf("error node is %d\n", pCur->next->data);
      printf("flag is %d\n", flag);
      return flag;
    }
    else
    {
      m[pCur->next]=1;
      pCur=pCur->next;
    }
  }
  flag=1;
  printf("flag is %d\n", flag);
  return flag;
}
//solution2:设置快指针和慢指针，如果没有环路的话，快指针和慢指针会在末尾相遇，如果有环路，那多次循环后必然会在一个节点相遇
int isExistLoop2(node* pHead)
{
  int flag=0;
  if(pHead==NULL||pHead->next==NULL)
  {
    printf("node is NULL\n");
    return flag;
  }
  node* pSlow=pHead;
  node* pFast=pHead;
  do {
    if(pFast->next==NULL||pFast->next->next==NULL) //遇到null说明没有环路，直接返回正确
    {
      flag=1;
      printf("flag is %d\n", flag);
      return flag;
    }
    pSlow=pSlow->next;                          //没遇到null，就继续赛跑
    pFast=pFast->next->next;
  } while(pFast!=pSlow);
  printf("flag is %d\n", flag);
  return flag;
}

int main()
{
 	node *head;
	head=(node *)malloc(sizeof(node));
  	(*head).data=-1;
  // node *head2;
   	node *p1,*p2,*p3,*p4;
   	p1=(node *)malloc(sizeof(node));
   	(*p1).data=1;


   	p2=(node *)malloc(sizeof(node));
   	(*p2).data=2;

   	p3=(node *)malloc(sizeof(node));
  	(*p3).data=3;

   	p4=(node *)malloc(sizeof(node));
  	(*p4).data=4;

//      head->p1->p2->p3->NULL
    	p1->next=p2;
    	p2->next=p3;
    	p3->next=p2;
      head->next=p1;
//      head->next=p4;
   	printf("hi\n");
//   	insert_Node(p3,4);
//  	traverse_List(head);
//      find_List(head,5);
//	delete_Node(head,4);
//	reverse_Linkedlist(head);
//	vector<int> ans;
//	ans=printListFromTail(head);
//	searchNodeK(head,2);
//  searchNodeK2(head,2);
//	traverse_List(head);
   int i=isExistLoop2(head);
return 0;
}

