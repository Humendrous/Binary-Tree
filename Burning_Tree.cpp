#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

class Node
{
    public:
    int data;
    Node* left,*right;
    Node(int value)
    {
        data=value;
        left=right=NULL;
    }
};
Node * BinaryTree()
{
    int x;
    cin>>x;
    if(x==-1)
    {
        return NULL;
    }
    Node *temp=new Node(x);
    cout<<"Enter unique Number for left children "<<x<<endl;
    temp->left=BinaryTree();
    cout<<"Enter unique Number for Right children "<<x<<endl;
    temp->right=BinaryTree();

    return temp;
}
int burn(Node *root,int &timer,int target)
{
    if(!root)
    return 0;

    if(root->data==target)
    return -1;

    int Left=burn(root->left,timer,target);
    int Right=burn(root->right,timer,target);

    if(Left<0){
        timer= max(timer,abs(Left)+Right);
        return Left-1;
    }
    if(Right<0)
    {
        timer= max(timer,Left+abs(Right));
        return Right-1;
    }

    return 1+max(Left,Right);
}
void find(Node *root, int target, Node * &BurnNode)
{
    if(!root)
    return;

    if(root->data==target){
        BurnNode=root;
    }
    find(root->left,target,BurnNode);
    find(root->right,target,BurnNode);
}
int Height(Node *root)
{ 
     if(!root)
     return 0;

     return 1+max(Height(root->left),Height(root->right));
}
int minTime(Node *root)
{
      int timer=0;
      int target;
      cout<<"Enter Target to Burn Binary tree from the number present:\n";
      cin>>target;
    burn(root,timer,target);

    Node *BurnNode=NULL;
    find(root,target,BurnNode);

    int high=Height(BurnNode)-1;
    return max(timer,high);
}
int main()
{
    Node * Head=NULL;
    cout<<"Enter Number for root Element of Tree:\n";
    Head=BinaryTree();
    //Burning Tree
   
    cout<<minTime(Head)<<"sec";

    return 0;
}