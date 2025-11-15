#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;

class Node
{
    public:
    int data,Height;
    Node *left, *right;
    Node(int value)
    {
        data=value;
        Height=1;
        left=right=NULL;
    }
};
int getHeight(Node *root)
{
    if(!root)
    return 0;

    return root->Height;
};
int getbalance(Node *root)
{
   return getHeight(root->left)-getHeight(root->right); 
};
//Right rotation
Node *rightrotation(Node *root)
{
   Node *child = root->left;
   Node *childright=child->right;
   child->right= root;
   root->left=childright;

   root->Height= 1+ max(getHeight(root->left),getHeight(root->right));
   child->Height= 1+ max(getHeight(child->left),getHeight(child->right));

   return child;
}
//Left rotation
Node *leftrotation(Node *root)
{
   Node *child = root->right;
   Node *childleft=child->left;
   child->left= root;
   root->right=childleft;

   root->Height= 1+  max(getHeight(root->left),getHeight(root->right));
   child->Height= 1+ max(getHeight(child->left),getHeight(child->right));

   return child;
}
Node *insert(Node *root,int key)
{
    //does'nt exist
    if(!root)
    return new Node(key);

    //Exist
    if(key<root->data)//left side
    {
    root->left=insert(root->left,key);
    }

    else if(key>root->data){
        root->right=insert(root->right,key);  
    }
    else
    {
    return root;//duplicate elements are not allowed
    }
    //update height
    root->Height=1+ max(getHeight(root->left),getHeight(root->right));
    //Balancing check

    int balance=getbalance(root);

    //left left
    if(balance>1 && key<root->left->data)
    {
       return rightrotation(root);//top
    }
    //Right Right
    else if(balance<-1 && root->right->data<key)
    {
       return leftrotation(root);//top
    }
    //Left Right
    else if(balance>1 && key>root->left->data)
    {
       root->left= leftrotation(root->left);//middle
       return rightrotation(root);//top 
    }
    //Right left
    else if(balance <-1 && root->right->data>key)
    {
       root->right= rightrotation(root->right);//middle
        return leftrotation(root);//top
    }
    //no imbalance
    else
    {
        return root;
    }
}
void preorder(Node *root)
{
    if(!root)
    return;

    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node *root)
{
    if(!root)
    return ;

    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
int main()
{
    Node *root=NULL;
    root=insert(root,10);
    root=insert(root,20);
    root=insert(root,40);
    root=insert(root,25);
    root=insert(root,15);
    root=insert(root,60);
    root=insert(root,80);
    root=insert(root,75);
    root=insert(root,100);
    root=insert(root,5);

    cout<<"Preorder of Avl Tree"<<endl;
    preorder(root);
    cout<<endl;

    cout<<"Inorder of Avl Tree\n";
    inorder(root);
}