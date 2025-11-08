//Inorder= LNR
#include<iostream>
#include<vector>
using namespace std;

class Node
{public:
    int data;
    Node*left,*right;

    Node(int value)
    {
        data=value;
        left=right=NULL;
    }
};
Node *Binarytree(){
    int x;
    cin>>x;
    if(x==-1)
    return NULL;

    Node*temp=new Node(x);
    cout<<"This number goes into left subtree of"<<x<<endl;
    temp->left=Binarytree();
    cout<<"This number goes into right subtree of"<<x<<endl;
    temp->right=Binarytree();

    return temp;

}
vector<int>morristraversal_INorder(Node *root)
{
    vector<int>ans;
    while(root)
    {
        //left doesn't Exist
        if(!root->left)
        {
            ans.push_back(root->data);
            root=root->right;
        }
        //Left part Exist 
        else
        {
            Node*curr=root->left;
            while(curr->right && curr->right !=root)
            {
                curr=curr->right;
            }
            //Left subtree not Traversed
        
             if(curr->right==NULL)
             {
                curr->right=root;
                root=root->left;
             }
            //Left subtree Traversed
            else
            {
                curr->right=NULL;
                ans.push_back(root->data);
                root=root->right;
            }
        }
    }
    return ans;
}
int main(){
    Node *Head=NULL;
    cout<<"Enter root Number for Binary Tree:\n";

    Head=Binarytree();
    cout<<"You Entered in Binary Tree Number this"<<endl;
    vector<int>ans;
    ans= morristraversal_INorder(Head);
    for(int i=0;i<ans.size();i++)
    {
       cout<<ans[i]<<" ";
    }
}