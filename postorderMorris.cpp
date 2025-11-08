//LRN reverse NRL
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
vector<int>morristraversal_postorder(Node *root)
{
    vector<int>ans;
    while(root)
    {
        //left doesn't Exist
        if(!root->right)
        {   
            ans.push_back(root->data);
            root=root->left;
            
        }
        //Left part Exist 
        else
        {
            Node*curr=root->right;
            while(curr->left && curr->left !=root)
            {
                curr=curr->left;
            }
            //Left subtree not Traversed
        
             if(curr->left==NULL)
             { ans.push_back(root->data);
                curr->left=root;
                root=root->right;
             }
            //Left subtree Traversed
            else
            {
                curr->left=NULL;
                
                root=root->left;
              
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
    ans= morristraversal_postorder(Head);
    for(int i=0;i<ans.size();i++)
    {
       cout<<ans[i]<<" ";
    }
}