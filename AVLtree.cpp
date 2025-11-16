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
//ADD deletion in AVL tree
Node *deleteNode(Node *root,int key)
{
    //root doesn,t Exist
    if(!root)
    return NULL;

    //Finding Key on left side
    if(root->data>key){
        root->left=deleteNode(root->left,key);
    }
    //Finding key on right side
    else if(root->data<key)
    {
        root->right=deleteNode(root->right,key);
    }
    else
    {
        //Leaf Node
        if(!root->left && !root->right)
        {
            delete root;
            return NULL;
        }
        //Only one child Exist
        //Left child Exist
        else if(root->left && !root->right)
        {
            Node *temp= root->left;
            delete root;
            return temp;
        }
        //Right child Exist
        else if(root->right && !root->left)
        {
            Node *temp= root->right;
            delete root;
            return temp;
        }
        // WHen both child Exist
        else
        {
            //Right side Smallest element
            Node *curr=root->right;
            while(curr->left)
            {
                curr=curr->left;
            }
            
            root->data= curr->data;
            root->right=deleteNode(root->right,curr->data);

        }
    }
    //Update Height
    root->Height=1 + max(getHeight(root->left),getHeight(root->right));

    // CHeck Balancing
    int balance=getbalance(root);
    
    //Left side
    if(balance>1)
    {
        //LL
        if(getbalance(root->left)>=0)
        {
            return rightrotation(root);
        }
        //LR
        else
        {
            root->left=leftrotation(root);
            return rightrotation(root);
        }
    }
    else if(balance<-1)
    {
        // RR
        if(getbalance(root->right)>=0){
            return leftrotation(root);
        }
        //RL
        else{
            root->right=rightrotation(root);
            return leftrotation(root);
        }
    }
    else{
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