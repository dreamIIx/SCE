typedef struct TreeNode
{
    ::std::string       value;
    TreeNode*           right;
    TreeNode*           left;
} *pTreeNode;

pTreeNode insertTreeNode(pTreeNode, const ::std::string&);
pTreeNode seekMostLeftAndRemove(pTreeNode);
pTreeNode findTreeNode(pTreeNode, const ::std::string&);
pTreeNode removeTreeNode(pTreeNode, const ::std::string&);
pTreeNode eraseTree(pTreeNode);
int sizeTree(pTreeNode);
void printTree(pTreeNode);
void printTreeLevel(pTreeNode, int);

pTreeNode insertTreeNode(pTreeNode root, const ::std::string& str)
{
    if (root == nullptr)
    {
        root = new TreeNode();
        ER_IFN(root,, return nullptr; )
        root->value = str;
        root->right = nullptr;
        root->left = nullptr;
        return root;
    }
    if (root->value > str)
    {
        root->left = insertTreeNode(root->left, str);
        return root;
    }
    if (root->value < str)
    {
        root->right = insertTreeNode(root->right, str);
        return root;
    }
    return root;
}

pTreeNode seekMostLeftAndRemove(pTreeNode node)
{
    if (node == nullptr || node->left == nullptr) return node;
    pTreeNode res = seekMostLeftAndRemove(node->left);
    assert(res);
    if (node->left == res)   node->left = res->right;
    return res;
}

pTreeNode findTreeNode(pTreeNode root, const ::std::string& str)
{
    int res = 0;
    if (root == nullptr || !(res = (root->value == str))) return root;
    if (res > 0) return findTreeNode(root->left, str);
    return findTreeNode(root->right, str);
}

pTreeNode removeTreeNode(pTreeNode root, const ::std::string& str)
{
    if (root == nullptr) return root;
    if (root->value > str)
    {
        root->left = removeTreeNode(root->left, str);
    }
    else if (root->value < str)
    {
        root->right = removeTreeNode(root->right, str);
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            pTreeNode res = root->right;
            delete root;
            return res;
        }
        else if (root->right == nullptr)
        {
            pTreeNode res = root->left;
            delete root;
            return res;
        }
        else
        {
            pTreeNode mostLeft = seekMostLeftAndRemove(root->right);
            if (mostLeft == root->right)
            {
                root->right = mostLeft->right;
            }
            root->value = ::std::move(mostLeft->value);
            delete mostLeft;
            return root;
        }
    }
    return root;
}

pTreeNode eraseTree(pTreeNode root)
{
    if (root == nullptr) return root;
    if (root->right)
    {
        root->right = eraseTree(root->right);
    }
    if (root->left)
    {
        root->left = eraseTree(root->left);
    }
    delete root;
    return root;
}

int sizeTree(pTreeNode root)
{
    if (root == nullptr) return 0;
    return 1 + ((root->left) ? (sizeTree(root->left)) : 0) + ((root->right) ? (sizeTree(root->right)) : 0);
}

void printTree(pTreeNode root)
{
    if (!root)
    {
        ::std::cout << 'x';
        return;
    }
    ::std::cout << '(' << root->value;
    printTree(root->left);
    printTree(root->right);
    ::std::cout << ')';
}

void printTreeLevel(pTreeNode root, int level)
{
    if (root == nullptr) return;
    if (!level) ::std::cout << root->value << ' ';
    else
    {
        if (root->left)     printTreeLevel(root->left, level - 1);
        if (root->right)    printTreeLevel(root->right, level - 1);
    }
}