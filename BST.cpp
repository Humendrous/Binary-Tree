#include<iostream>
using namespace std;

class Node
{
    public:
    int data;
    Node *left,*right;
    Node(int value)
    {
        data=value;
        left=right=NULL;
    }
};
Node *BST(Node *root, int target)
{
    if(!root)
    {
        Node *temp =new Node(target);
        return temp;
    }
    if(target<root->data)
    {
        root->left=BST(root->left,target);

    }
    else{
        root->right=BST(root->right,target);
    }

    return root;
}
void inorder(Node *root)
{
    if(!root)
    {
        return ;
    }
    inorder(root->left);
    cout<<root->data <<" ";
    inorder(root->right);
}
bool search(Node *root, int target)
{
    if(!root)
    return 0;

    if(root->data== target)
    {
        return true;
    }
    if(root->data<target)
    {
        search(root->right,target);
    } 
    else
    {
        search(root->left,target);
    }
}
Node *deleteNode(Node *root ,int target)
{
   if(!root)
   {
    return NULL;
   }
   if(root->data>target)
   {
    root->left=deleteNode(root->left,target);
    return root;
   }
   else if(root->data<target)
   {
    root->right=deleteNode(root->right,target);
    return root;
   }
   else
   {
      //Leaf Node
      if(!root->left && !root->right){
        delete root;
        return NULL;
      }
      //Left child exist 
      else if(!root->right)
      {
        Node *temp=root->left;
        delete root;
        return temp;
      }
      //Right child exist
      else if(!root->left)
      {
        Node *temp=root->right;
        delete root;
        return temp;
      }
      //If both left and right exist
      else
      {
        //find greatest element from left
        Node *child=root->left;
        Node* parent=root;

        while(child->right)
        {
             parent =child;
             child=child->right;
        }
        if( root != parent)
        {
            parent->right=child->left;
            child->left=root->left;
            child->right=root->right;
            delete root;
            return child;
        }
        else{
            child->right=root->right;
            delete root;
            return child;
        }
      }
   }
}
int main()
{
    int arr[]={5,3,4,7,9,10,12,15};
    Node *root=NULL;

    for(int i=0;i<8;i++)
    {
        root=BST(root,arr[i]);
    }
    int target=12;
    // cout<<search(root,target)<<endl;
    root=deleteNode(root,target);
    inorder(root);
}
