/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(root==NULL)
            return result;
        vector<TreeNode*> vector_node;
        while(1){
            if(root->left==NULL)
                result.push_back(root->val);
            else{
                vector_node.push_back(root);
                root=root->left;
                continue;
            }
            if(root->right==NULL){
                if(vector_node.empty()==true)
                    return result;
                else{
                    root=vector_node.back();
                    root->left=NULL;
                    vector_node.pop_back();
                    result.push_back(root->val);
                    if(root->right==NULL){
                        if(vector_node.empty()==true)
                            return result;
                        else{
                            root=vector_node.back();
                            root->left=NULL;
                            vector_node.pop_back();
                        }
                    }
                    else
                        root=root->right;
                }
            }
            else{
                root=root->right;
            }
        }
    }
};
