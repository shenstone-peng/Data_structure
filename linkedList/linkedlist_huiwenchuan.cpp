#include "csapp.h"
using namespace std;



struct Node{
        char data;
        Node* next=NULL;
};


/* values for echo_int*/


class Solution
{
        public:
                Solution(){
                        //self.sp=new Node;
                        sp=new Node;
                        sp->data='h';
                        length=0;
                        rear=sp;
                }
                void print()
                {
                        if(NULL == &(this->sp))
                        {
                                cout<<"the Node is empty"<<endl;
                        }
                        rear=sp;
                        while(this->rear->next)
                        {
                                cout<<this->rear->next->data<<"->";
                                rear=rear->next;

                        }
                        cout<<"NULL"<<endl;
                        cout<<"length:"<<this->length<<endl;
                }
                void insert(char& value)
                {
                        Node* add=(Node*)malloc(sizeof(Node));
                        add->data=value;
                        rear->next=add;
                        rear=add;
                        this->length++;
                }
                bool isHuiWenOrNot()
                {
                        if(NULL == this->sp)
                        {
                                return true;
                        }
                        Node* L1;
                        Node* L2=(Node*)malloc(sizeof(Node));
                        L1=this->sp->next;
                        int l=length/2;
 for(int i=0;i<l;i++)
                        {
                                L2->data=(L1->data);
                                Node* pp=(Node*)malloc(sizeof(Node*));
                                pp->next=L2;
                                L2=pp;
                                L1=L1->next;
                        }
                        if(length%2)
                        {
                                L1=L1->next;
                                l=l+1;
                        }

                        for(int i=l;i<length;i++)
                        {
                                if(L1->data ==L2->next->data)
                                {
                                        L1=L1->next;
                                        L2=L2->next;
                                        continue;
                                }
                                return false;
                        }
                        return true;
                }
        Node* sp;
        int length;
        Node* rear;
};


int main(int argc,char** argv)
{
        Solution* mylink=new Solution();
//      for(int i=0;i<100;i++)
//      {
//              mylink->insert(i);
//      }
//      mylink->print();
//      char* sp=new char('f');
        char sp[10]="abededcba";
        //*sp="f";
        for(int i=0;i<9;i++)
        {
                mylink->insert(sp[i]);
        }
        //mylink->insert(sp);
//      mylink->insert('s');
        mylink->print();
        if(mylink->isHuiWenOrNot())
                cout<<"os"<<endl;
        else
                cout<<"the spring is not hui wen"<<endl;
        return 0;
}
