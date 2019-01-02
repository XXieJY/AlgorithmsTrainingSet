#include <map>
using namespace std;

class Solution {
private:
    map<int, int> indexForInorders;
public:
    TreeNode* reConstructBinaryTree(vector<int> &preorder, vector<int> &inorder)
    {
        for(int i = 0; i < inorder.size(); i++)
            indexForInorders[inorder[i]] = i;
        return buildTree(preorder, 0, preorder.size() - 1, 0);
    }

    TreeNode *buildTree(vector<int> &preorder, int pLeft, int pRight, int inL)
    {
        if (pLeft > pRight)
            return NULL;
        TreeNode* root = new TreeNode(preorder[pLeft]);
        int inIndex = indexForInorders.at(root->val);
        int leftTreeSize = inIndex - inL;
        root->left = buildTree(preorder, pLeft+1, pLeft+leftTreeSize, inL);
        root->right = buildTree(preorder, pLeft+leftTreeSize+1, pRight, inL+leftTreeSize+1);
        return root;
    }
};
