#include <string>
#include <iostream>

using namespace std;

#include <unordered_set>
#include <list>

template <typename T>
class GraphNode
{
public:
    GraphNode(){};
    GraphNode(const T &x) { data = x; };

    void attach(GraphNode<T> *node) { children.push_back(node); };

    bool visited = false;
    vector<GraphNode<T> *> children;

    T data;

private:
};

#include <queue>
// simple traversal question using BFS or DFS with recursion is good
bool routeBtwNodes(GraphNode<int> *a, GraphNode<int> *b)
{
    if (!a || !b)
        return false;

    if (a->visited)
        return false;

    a->visited = true;
    if (a == b)
        return true;

    auto iter = a->children.begin();

    bool ret = false;
    while (iter != a->children.end() && !ret)
    {
        ret = routeBtwNodes(*iter, b);

        iter++;
    }
    // queue<GraphNode *> que;

    // // start from a
    // que.push(a);
    // while (!que.empty())
    // {
    //     auto nd = que.front();
    //     que.pop();

    //     if (!nd->visited)
    //     {
    //         if (nd == b)
    //             return true;
    //         else
    //         {
    //             nd->visited = true;

    //             auto iter = nd->children.begin();
    //             while (iter != nd->children.end())
    //             {
    //                 que.push(*iter);
    //                 iter++;
    //             }
    //         }
    //     }
    // }

    return ret;
}

template <typename T>
class LinkedNode
{
public:
    LinkedNode(){};
    LinkedNode(T x) { data = x; }

    T data;
    LinkedNode<T> *next = nullptr;

private:
};

template <typename T>
class LinkedList
{
public:
    LinkedList(){};
    LinkedList(T x)
    {
        auto node = new LinkedNode<T>(x);
        head = node;
        current = node;
        nSz++;
    };

    void attach(LinkedNode<T> *node)
    {
        if (!node)
            return;
        current->next = node;
        current = node;
        nSz++;
    };

    LinkedNode<T> *head = nullptr;
    LinkedNode<T> *current = nullptr;
    int nSz = 0;
};

class TreeNode
{
public:
    TreeNode(int x) { data = x; };

    void attachLeft(TreeNode *&leftNode)
    {
        if (!leftNode)
            return;
        this->left = leftNode;
        leftNode->parent = this;
    };
    void attachRight(TreeNode *&rightNode)
    {
        if (!rightNode)
            return;
        this->right = rightNode;
        rightNode->parent = this;
    };

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode *parent = nullptr;
    int data;
    bool visited = false;
};

TreeNode *buildBST(int arr[], int l, int r)
{
    if (r < l)
        return nullptr;

    int mid = l + (r - l + 1) / 2; // 0 1 2 3 4

    auto treeNode = new TreeNode(arr[mid]);
    treeNode->left = buildBST(arr, l, mid - 1);
    treeNode->right = buildBST(arr, mid + 1, r);

    return treeNode;
};

// use DFS to attach linked list. we use level and vector size to determine if this is a new depth of
// the tree or we can simply attach. recursion could start with first level returning the object
// second level a void funtion to return nothing as terminating condition.
void listOfTreeDepth(vector<LinkedList<TreeNode *>> &vt, int level, TreeNode *node)
{
    if (!node)
        return;

    LinkedList<TreeNode *> *lst;
    if (vt.size() == level)
    {
        lst = new LinkedList<TreeNode *>(node);
        vt.push_back(*lst);
    }
    else
    {
        lst = &vt.at(level);
        auto lnkNode = new LinkedNode<TreeNode *>(node);
        lst->attach(lnkNode);
    }

    if (node->left)
        listOfTreeDepth(vt, level + 1, node->left);
    if (node->right)
        listOfTreeDepth(vt, level + 1, node->right);
};

vector<LinkedList<TreeNode *>> listOfTreeDepth(TreeNode *root)
{
    vector<LinkedList<TreeNode *>> vt;
    listOfTreeDepth(vt, 0, root);

    return vt;
};

// we try to get the max height between left and right node
int isBalancedTree(TreeNode *root, int level)
{
    if (!root)
        return level - 1;

    int left, right;
    if (!root->left)
    {
        left = level;
    }
    else
    {
        left = isBalancedTree(root->left, level + 1);
    }

    if (!root->right)
    {
        right = level;
    }
    else
    {
        right = isBalancedTree(root->right, level + 1);
    }

    return left > right ? left : right;
}

// remeber to terminate when hight difference is greater than 1, and we need to test all left and right nodes
bool isBalancedTree(TreeNode *root)
{
    if (!root)
        return false;
    int left = isBalancedTree(root->left, 1);
    int right = isBalancedTree(root->right, 1);

    if (abs(left - right) > 1)
        return false;
    else
        return isBalancedTree(root->left) && isBalancedTree(root->right);
}

// we can traverse through the tree and see if all left node is smaller or equal to the root and all right are greater,
// remember the case still stand for sub nodes
bool isBST(TreeNode *root, int min, int max)
{
    if (!root)
        return true;

    if (root->data <= min || root->data > max)
        return false;

    if (!isBST(root->left, min, root->data) || !isBST(root->right, root->data, max))
        return false;

    return true;
}

bool isBST(TreeNode *root)
{
    if (!root)
        return false;

    return isBST(root, INT_MIN, INT_MAX);
}

TreeNode *leftMostChild(TreeNode *root)
{
    if (!root)
        return nullptr;

    auto node = root;
    while (node)
    {
        node = node->left;
    }

    return node;
}

// for in order traversal, we visit left->node->right. So the next node to visit if there is
// a right node presence. when there is the right node, we go to the left most of the right
// node. If there is no right node, that means we are already at the right most node, we need
// to visit the parent. Where we climb up to the parent, until we are the left node or nullptr
// to get the parent node
TreeNode *nextInOrderNode(TreeNode *root)
{
    if (!root)
        return nullptr;

    if (root->right)
    {
        return leftMostChild(root->right);
    }
    else
    {
        auto p = root->parent;
        auto n = root;

        while (n && n != p->left)
        {
            auto temp = p->parent;
            n = p;
            p = temp;
        }
        return p;
    }
}

#include <unordered_map>
#include <stack>

// For build dependency, we first traverse through the pair and construct our graph,
// then we go through the graph hash map, and stack their children with DFS. We store
// the root lastly on stack because root is supposed to be build first. Lastly we
// attach the missing project on the project vector to the head of the stack.
void DoDFSDependency(std::stack<std::string> &stack, GraphNode<std::string> *&node)
{
    if (node == nullptr)
        return;
    if (node->visited)
        return;

    node->visited = true;

    auto setIter = node->children.begin();
    while (setIter != node->children.end())
    {
        DoDFSDependency(stack, (*setIter));
        setIter++;
    }
    stack.push(node->data);
}

stack<std::string> buildOrder(const std::vector<std::string> &projects, const std::vector<std::pair<std::string, std::string>> &projectPair)
{
    std::unordered_map<std::string, GraphNode<std::string> *> map;

    for (auto pr : projectPair)
    {
        auto iter = map.find(pr.first);
        if (iter == map.end())
        {
            auto graph = new GraphNode<std::string>(pr.first);
            map.insert({pr.first, graph});

            auto sndIter = map.find(pr.second);
            if (sndIter == map.end())
            {
                auto scndGraph = new GraphNode<std::string>(pr.second);
                map.insert({pr.second, scndGraph});
                graph->attach(scndGraph);
            }
            else
            {
                graph->attach(sndIter->second);
            }
        }
        else
        {
            auto sndIter = map.find(pr.second);
            if (sndIter == map.end())
            {
                auto scndGraph = new GraphNode<std::string>(pr.second);
                map.insert({pr.second, scndGraph});
                iter->second->attach(scndGraph);
            }
            else
            {
                iter->second->attach(sndIter->second);
            }
        }
    }
    stack<std::string> stk;
    auto mapIter = map.begin();
    while (mapIter != map.end())
    {
        DoDFSDependency(stk, mapIter->second);
        mapIter++;
    }

    for (auto project : projects)
    {
        auto iter = map.find(project);
        if (iter == map.end())
        {
            stk.push(project);
        }
    }
    return stk;
};

// this problem check if parent owns the branch. we first check if a is sub tree
// of b and b is of a. then we move a to its sibling and check if it is b.
// then we move up the ladder to check a's parent
bool checkCover(TreeNode *parent, TreeNode *branch)
{
    if (!parent || !branch)
        return false;
    if (parent == branch)
        return true;

    return (checkCover(parent->left, branch) || checkCover(parent->right, branch));
}

TreeNode *getSibiling(TreeNode *node)
{
    if (!node)
        return nullptr;
    if (!node->parent)
        return nullptr;

    if (node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

TreeNode *findFirstCommonAncestorOnBT(TreeNode *nodeA, TreeNode *nodeB)
{
    if (checkCover(nodeA, nodeB))
        return nodeA;
    else if (checkCover(nodeB, nodeA))
        return nodeB;

    auto parent = nodeA->parent;
    auto sibiling = getSibiling(nodeA);

    while (!checkCover(sibiling, nodeB))
    {
        sibiling = getSibiling(parent);
        parent = parent->parent;
    }
    return parent;
}

// this problem we need to go through all left and right nodes
// then we weave them together. remember that we are using pointers
// meaning that we need to init a new node everytime or we will
// be changing the weaved values
vector<LinkedNode<int> *> getAllBTArray(TreeNode *root)
{
    vector<LinkedNode<int> *> ret;
    if (!root)
    {
        ret.push_back(nullptr);
        return ret;
    }

    auto leftList = getAllBTArray(root->left);
    auto rightList = getAllBTArray(root->right);

    // combine
    ret.clear();
    for (auto left : leftList)
    {
        if (left)
        {
            for (auto right : rightList)
            {
                if (right)
                {
                    left->next = right;
                    ret.push_back(left);
                }
            }
        }
    }
    for (auto right : rightList)
    {
        if (right)
        {
            for (auto left : leftList)
            {
                if (left)
                {
                    right->next = left;
                    ret.push_back(right);
                }
            }
        }
    }

    if (ret.size() == 0)
    {
        auto rootNode = new LinkedNode<int>(root->data);
        ret.push_back(rootNode);
    }
    else
    {
        for (auto &lst : ret)
        {
            auto rootNode = new LinkedNode<int>(root->data);
            rootNode->next = lst;
            lst = rootNode;
        }
    }
    return ret;
}

#include <queue>
// this problem check if smalltree is of big tree. we can get string and recursively
// make the string and check if small string can be found of big. or we can find the
// identical node data and traverse to see if all data are the same.
string getString(TreeNode *treeNode)
{
    string str;
    if (!treeNode)
        str = "X";
    str = to_string(treeNode->data);

    return str + " " + getString(treeNode->left) + getString(treeNode->right);
}

bool matchTree(TreeNode *bigTree, TreeNode *smallTree)
{
    if (!bigTree && !smallTree)
        return true;
    else if (!bigTree || !smallTree)
        return false;
    else if (bigTree->data != smallTree->data)
        return false;
    else
        return matchTree(bigTree->left, smallTree->left) &&
               matchTree(bigTree->right, smallTree->right);
}

bool isEqualTree(TreeNode *tree1, TreeNode *tree2)
{
    if (!tree1)
        return false;
    if (tree1)
    {
        if (matchTree(tree1, tree2))
            return true;
    }
    return isEqualTree(tree1->left, tree2) || isEqualTree(tree1->right, tree2);
}

bool isSubTree(TreeNode *bigTree, TreeNode *smallTree)
{
    return isEqualTree(bigTree, smallTree);
}

#include <unordered_set>
#include <queue>

// practice bfs recursively. we need to use a que. when we call the function, check queue is empty. we use unordered set to
// to prevent stuck in the loop. we push neighbor in the queue when we iterate and lastly call the function again.
void DoBFSRecurseive(LinkedNode<int> *&list, std::queue<GraphNode<int> *> &que, std::unordered_set<GraphNode<int> *> &visitedSet)
{
    if (que.empty())
        return;

    auto graphNode = que.front();
    que.pop();
    if (visitedSet.find(graphNode) != visitedSet.end())
        return;

    auto node = new LinkedNode<int>(graphNode->data);
    if (!list)
        list = node;
    else
    {
        list->next = node;
        list = node;
    }
    visitedSet.insert(graphNode);

    auto iter = graphNode->children.begin();
    while (iter != graphNode->children.end())
    {
        que.push((*iter));
        iter++;
    }

    DoBFSRecurseive(list, que, visitedSet);
}

LinkedNode<int> *DoBFSRecurseive(GraphNode<int> *root)
{
    std::unordered_set<GraphNode<int> *> visitedSet;
    std::queue<GraphNode<int> *> que;

    if (root == nullptr)
        return nullptr;

    visitedSet.insert(root);
    que.push(root);
    LinkedNode<int> *lst = nullptr;
    DoBFSRecurseive(lst, que, visitedSet);

    return lst;
}

// practice bfs iteratively. que is the data structure and condition is que is empty.
void DoBFSIterative(LinkedNode<int> *&list, GraphNode<int> *root, std::queue<GraphNode<int> *> que, unordered_set<GraphNode<int> *> &set)
{
    if (root == nullptr)
        return;
    while (!que.empty())
    {
        auto node = que.front();
        que.pop();

        auto linkedNode = new LinkedNode<int>(root->data);

        if (list == nullptr)
        {
            list = linkedNode;
        }
        else
        {
            list->next = linkedNode;
            list = linkedNode;
        }

        set.insert(node);

        auto iter = node->children.begin();
        while (iter != node->children.end())
        {
            que.push((*iter));
            iter++;
        }
    }
}

LinkedNode<int> *DoBFSIterative(GraphNode<int> *root)
{
    if (root == nullptr)
        return nullptr;

    LinkedNode<int> *lst = nullptr;
    std::queue<GraphNode<int> *> que;
    que.push(root);
    unordered_set<GraphNode<int> *> set;
    set.insert(root);

    DoBFSIterative(lst, root, que, set);
    return lst;
}

// practive dfs iteratively. dfs uses stack, conditions is stack is empty.
void DoDFSIterative(LinkedNode<int> *&lst, GraphNode<int> *graphNode, std::unordered_set<GraphNode<int> *> set, std::stack<GraphNode<int> *> &stk)
{
    if (graphNode == nullptr)
        return;

    stk.push(graphNode);
    while (!stk.empty())
    {
        auto node = stk.top();
        stk.pop();

        if (set.find(node) == set.end())
        {
            set.insert(node);

            LinkedNode<int> *linkedNd = new LinkedNode<int>(node->data);

            if (lst == nullptr)
            {
                lst = linkedNd;
            }
            else
            {
                lst->next = linkedNd;
                lst = linkedNd;
            }

            auto iter = node->children.begin();
            while (iter != node->children.end())
            {
                stk.push((*iter));
                iter++;
            }
        }
    }
}

// practive to do dfs recursively. dfs function can be called when we itertate through the neighbor. we use an
// unordered_set to check in case traversing get stuck in the loop
void DoDFSRecursive(LinkedNode<int> *&lst, GraphNode<int> *graphNode, std::unordered_set<GraphNode<int> *> set)
{
    if (graphNode == nullptr)
        return;

    if (set.find(graphNode) != set.end())
        return;

    set.insert(graphNode);

    auto linkNd = new LinkedNode<int>(graphNode->data);
    if (lst == nullptr)
    {
        lst = linkNd;
    }
    else
    {
        lst->next = linkNd;
        lst = linkNd;
    }

    auto iter = graphNode->children.begin();
    while (iter != graphNode->children.end())
    {
        DoDFSRecursive(lst, (*iter), set);
        iter++;
    }
}

#include <queue>

// we use dfs to visit node and accumulate the sum since it want parents to child. we cached our cachedVal so when
// we return to the parent node, we still remember the value. We use reference once the sum is equal to the cached
// value.
void getSumOfPath(int &sum, int cachedVal, TreeNode *node, int comparedVal)
{
    int tempCachedSum = cachedVal + node->data;
    if (tempCachedSum == comparedVal)
    {
        sum++;
    }

    if (node->left)
        getSumOfPath(sum, tempCachedSum, node->left, comparedVal);
    if (node->right)
        getSumOfPath(sum, tempCachedSum, node->right, comparedVal);
}

int getSumOfPath(TreeNode *root, int comparedVal)
{
    if (root == nullptr)
        return 0;

    int sum = 0;
    getSumOfPath(sum, 0, root, comparedVal);
    return sum;
}
