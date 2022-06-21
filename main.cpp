//
//  main.cpp
//  testXCode
//
//  Created by Huan-Chi Lin on 2021/1/29.
//
// Testing git merging 

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using  namespace std;
bool containsDuplicate(vector<int>& nums)
{
    bool isDuplicate(false);
    
    if (nums.size() == 1)
        return isDuplicate;
    
    unordered_set<int> set;
    for (int i=0; i<nums.size(); i++)
    {
        if (set.find(nums[i]) == set.end())
        {
            set.insert(nums[i]);
        }
        else
        {
            return true;
        }
    }
    
    return isDuplicate;
};

vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    vector<int> ans;
    for(int i = 0, j = 0;i < nums1.size() && j < nums2.size();){
        if(nums1[i] == nums2[j]){
            ans.push_back(nums1[i]);
            i++;
            j++;
        }
        else if(nums1[i] > nums2[j]){
            j++;
        }
        else{
            i++;
        }
    }
    
    return ans;
};
vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
        int nSz1 = nums1.size();
        int nSz2 = nums2.size();
        
        std::unordered_map<int, int> hsMap;
        
        if (nSz1 <= nSz2)
        {
            for (int i(0); i<nSz1; i++)
            {
                hsMap[nums1[i]]++;
            }
        }
        else
        {
            for (int i(0); i<nSz2; i++)
            {
                hsMap[nums2[i]]++;
            }
        }
        
        std::vector<int> returnVt;
        
        if (nSz1 > nSz2)
        {
            for (int i(0); i<nSz1; i++)
            {
                if (hsMap[nums1[i]]-- >0)
                {
                    
                    returnVt.push_back(nums1[i]);
                }
            }
        }
        else
        {
            for (int i(0); i<nSz2; i++)
            {
                std::cout<<hsMap[nums2[i]]<<endl;
                if (hsMap[nums2[i]]-- >0)
                {
                    std::cout<<hsMap[nums2[i]]<<endl;
                    
                    returnVt.push_back(nums2[i]);
                }
            }
        }
       
        return returnVt;
    }

bool isPalindrome(string s) {
        if (s.size() <= 1) return true;
        int i(0), j(static_cast<int>(s.size() - 1));
        
        while (i < j)
        {
            if (!isalpha(s[i]))
            {
                i++;
                continue;
            }
            if (!isalpha(s[j]))
            {
                j--;
                continue;
            }
            
            if (tolower(s[i]) == tolower(s[j]))
            {
                i++; j--;
                std::cout<<"front "<< s[i-1]<<endl;
                std::cout<<"back "<< s[j+1]<<endl;

            }
            else
                return false;
        }
    return true;
    }

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

vector<int> vt;
    vector<int>& storeBT(TreeNode* root)
    {
        if (root == nullptr) {
            vt.push_back(0);
            return vt;
        }
        storeBT(root->left);
        vt.push_back(root->val);
        return storeBT(root->right);
    }
    
    bool isSymmetric(TreeNode* root) {
        storeBT(root);

        int i(0), j(vt.size()-1);
        while (i<=j){
            if (vt.at(i++) != vt.at(j--))
                return false;
        }
         return true;
    }

// question 1
class numberFind
{
public:
    numberFind(const int* numbers, const int n, const int k)
    {
        if (!numbers) return;
        
        m_pNumbers = new int[n];
        memcpy(&m_pNumbers[0], &numbers[0], sizeof(int) * n);
        m_nLength = n;
        K = k;
    };
    
    ~numberFind(){};
    
    int add(int num)
    {
        int* temp = m_pNumbers;
        
        m_nLength++;
        m_pNumbers = new int[m_nLength];
        memcpy(m_pNumbers, temp, sizeof(int) * (m_nLength-1));
        m_pNumbers[m_nLength-1] = num;
        
        delete[] temp;
        
        std::sort(m_pNumbers, m_pNumbers + m_nLength);
        
        return m_pNumbers[m_nLength - K];
    };
    
private:
    int* m_pNumbers = nullptr;
    int m_nLength = 0;
    int K = 0;
};
// question 1

#include <map>
#include <queue>

TreeNode*& MirrorTree(TreeNode* node)
{
    TreeNode* copyNode = new TreeNode(node->val);
    
    std::queue<std::pair<TreeNode*, TreeNode*>> que;
    auto copyC = copyNode;
    
    que.push({node, copyC});
    
    while (!que.empty())
    {
        auto c = que.front();
        que.pop();
        
        if (c.first->left)
        {
            auto rightNode = new TreeNode(c.first->left->val);
            c.second->right  = rightNode;
            que.push({c.first->left, c.second->right});
        }
        if (c.first->right)
        {
            auto leftNode = new TreeNode(c.first->right->val);
            c.second->left  = leftNode;
            que.push({c.first->right, c.second->left});
        }
    }
    
    return copyNode;
}

bool checkBinary(TreeNode* tree1, TreeNode* tree2)
{
    if (!tree1 && !tree2) return true;
    
    if (tree1 && tree2)
        if (tree1->val == tree2->val)
            return (checkBinary(tree1->left, tree2->left) && checkBinary(tree1->right, tree2->right));
    
    return false;
}

bool canSegmentString(string words, std::vector<string> dictionary)
{
    while (words.size() > 0)
    {
        size_t oldSize = words.size();
        for (auto word : dictionary)
        {
            auto it = words.find(word);
            {
                if (it != std::string::npos)
                {
                    words.erase(it, it + word.size());
                }
                
            }
        }
        size_t currSize = words.size();
        if (currSize == oldSize) return false;
    }
    
    return  true;
}

int largest_sub_array(int k, int* pArr, int length)
{
    int sum(pArr[0]);
    int MaxSoFar(0);
    for (int i = 1; i< length; i++)
    {
        sum = max(pArr[i], sum + pArr[i]);
        MaxSoFar = max(sum, MaxSoFar);
    }
    
    return MaxSoFar;
}

bool checkRealNum(string str)
{
    int countDot = 0;
    
    if ((str[0] - '0' < '0' || str[0] -
         0 >'9') && str[0] != '.') return false;
    
    for (int i(0); i<str.size(); i++)
    {
        if ('.' == str[i])
        {
            countDot++;
            
            if (countDot > 1) return false;
        }
        if (str[i] - '0' < '0' || str[i] -
            0 >'9') return false;
    }
    
    if ('.' == str.back()) return false;
    return true;
}

struct Node {
    int data;
    Node* next;
};

Node*& reverse(Node* linkedLst)
{
    Node* pre(nullptr);
    Node* cur(linkedLst);
    Node* nxt(linkedLst->next);
    
    while (cur->next != nullptr)
    {
        cur->next = pre;
        pre = cur;
        cur = nxt;
        nxt = nxt->next;
    }
    
    cur->next = pre;
    
    return cur;
}

#include <stack>
bool hasSum(TreeNode* node, int number)
{
    if (node == nullptr) return false;
    if (node != nullptr && node->val == number) return false;
    
    std::stack<std::pair<TreeNode*, int>> stk;
    
    stk.push({node, number - node->val});
    
    while (!stk.empty())
    {
        auto nd = stk.top();
        stk.pop();
        
        if (nd.first->left)
        {
            if (nd.first->left->val == nd.second) return true;
            else stk.push({nd.first->left, nd.second - nd.first->left->val});
        }
        if (nd.first->right)
        {
            if (nd.first->right->val == nd.second) return true;
            else stk.push({nd.first->right, nd.second - nd.first->right->val});
        }
    }
    return false;
    
}

//std::vector<std::vector<int>>& merge(std::vector<std::vector<int>>)
//{
//    std::vector<std::vector<int>> ans;
//
//
//
//    return ans;
//}

std::pair<int, int>& find_low_high_index(std::vector<int> arr, int key)
{
    std::pair<int, int> ans{-1, -1};
    
    int front =0;
    int back = arr.size() - 1;
    int mid = (front + back) / 2;
    
    while (front <= back)
    {
        if (arr[mid] >= key)
        {
            front = front; back = mid - 1;
            mid = (front + back) / 2;
        }
        else if (arr[mid] < key)
        {
            front = mid + 1; back = back;
            mid = (front + back) / 2;
        }
    }
    if (arr[front] == key) ans.first = front;
    else return ans;
    
    front = 0; back = arr.size() - 1; mid = (front + back) / 2;
    
    while (front <= back)
    {
        if (arr[mid] > key)
        {
            front = front; back = mid - 1;
            mid = (front + back) / 2;
        }
        else if (arr[mid] <= key)
        {
            front = mid + 1; back = back;
            mid = (front + back) / 2;
        }
    }
    if (arr[back] == key) ans.second = front;
    
    return ans;
}

//std::vector<int>& findTriplet(std::vector<int> numbers) use unordered map for loop from 0 < i < size -2 and
// i+1 < j< size
//{
//    std::unordered_map<int, std::vector<int>> hsMap;
//
//    for (int i(0); i<numbers.size(); i++)
//    {
//        std::vector<int> vtNums;
//        for (int j(0); j<numbers.size(); j++)
//            vtNums.push_back(
//    }
//}

Node* FindInterSection(Node* tree1, Node* tree2)
{
    std::unordered_set<Node*> hsSet;
    auto node = tree1;
    
    hsSet.insert(node);
    while (node->next != nullptr) {
        node = node->next;
        hsSet.insert(node);
    }
    hsSet.insert(node);
    
    auto node2 = tree2;
    while (node2->next != nullptr)
    {
        if (hsSet.find(node2->next) != hsSet.end())
            return node2->next;
        else
        {
            node2 = node2->next;
        }
    }
    return nullptr;
}

void MoveZeroToLeft(int*& pArr, int n)
{
    int lastCount(n-1);
    for (int i(n-1); i>=0; i--)
    {
        if (pArr[i] != 0)
        {
            swap(pArr[i], pArr[lastCount]);
            lastCount--;
        }
    }
}

void SortedMerge(Node* node1, Node* node2)
{
    if (node1 == nullptr && node2 == nullptr) return;
    if (node1 == nullptr)
    {
        node1 = node2; return;
    }
    if (node2 == nullptr)
    {
        return;
    }
    
    Node* temp = new Node();
    auto n1 = node1;
    auto n2 = node2;
    auto c = temp;
    while (n1->next != nullptr || n2->next != nullptr)
    {
        if (n1->data< n2->data)
        {
            c->next = n1;
            n1 = n1->next;
        }
        else
        {
            c->next = n2;
            n2 = n2->next;
        }
        c = c->next;
    }
    
    if (n1->next == nullptr)
    {
        c->next = n2;
    }
    else if (n2->next == nullptr)
    {
        c->next = n1;
    }
    
    node1 = temp->next;
}

void LevelOrder(std::vector<std::vector<int>>& vtBin, TreeNode* node)
{
    if (node == nullptr) return;
    
    std::queue<TreeNode*> que;
    que.push(node);
    
    
    while (!que.empty()) {
        std::vector<int> temp;
        int nSz(que.size());
        for (int i(0); i<nSz; i++)
        {
            auto nd = que.front();
            que.pop();
            temp.push_back(nd->val);
            
            if (nd->left) que.push(nd->left);
            if (nd->right) que.push(nd->right);
        }
        vtBin.push_back(temp);
    }
}

int bestSell(std::vector<int> numbers)
{
    if (numbers.size() == 0) return 0;
    if (numbers.size() == 1) return numbers.at(0);
    
    int sum(numbers.at(0));
    int maxSoFar(numbers.at(0));
    
    for (int i(1); i< numbers.size(); i++)
    {
        sum = std::max(sum, sum + numbers.at(i));
        maxSoFar = std::max(sum, maxSoFar);
        
    }
    return maxSoFar;
}

double myPow(double x, int n)
{
    double XX(0);
    if (n == 0) return 1.0;
    else if (n > 0) XX = x;
    else XX = 1 / x;
    
    int N = abs(n);
    
    double* dp = new double[N];
    dp[0] = XX;
    if (N == 1) return dp[0];
    
    for (int i(1); i< N; i++)
    {
        dp[i] = XX * dp[i-1];
    }
    
    return dp[N-1];
}

int SearchHeader(vector<vector<int>>& mat, int target, int l, int r)
{
   
    int mid = (l + r) / 2;

    while (l <= r)
    {
        if (target >= mat[mid][0])
            if (mid == mat.size() - 1) {
                return mid;
            }
            else if (target < mat[mid + 1][0])
                return mid;
        
        if (target < mat[mid][0]) return SearchHeader(mat, target, l, mid - 1);
        
        if (target >= mat[mid][0]) return SearchHeader(mat, target, mid + 1, r);
    }
    return l;
}

//int binSearchRow(vector<int>& mat, int target)
//{
//    int l(0);
//    int r(mat.size() - 1);
//
//    while (l <= r)
//    {
//        int mid = (l + r) / 2;
//
//        if (target == mat[mid]) return mid;
//        if (target >= mat[mid]) l = mid + 1;
//        if (target < mat[mid]) r = mid-1;
//    }
//
//    return -1;
//}
//
//bool searchMatrix(vector<vector<int>>& nums, int target)
//{
//    int rowAt = SearchHeader(nums, target, 0, nums.size() - 1);
//    int colAt = binSearchRow(nums[rowAt], target, 0, nums[rowAt].size()-1);
//
//    return (target == nums[rowAt][colAt]);
//}



int Partition(int* pArr, int front, int back)
{
    int pivot = pArr[back];
    int i(front - 1);
    
    for (int j(front); j<= back; j++)
    {
        if (pArr[j] < pivot)
        {
            i++;
            std::swap(pArr[j], pArr[i]);
        }
    }
    i++;
    swap(pArr[i], pArr[back]);
    
    return i;
}

void QuickSort(int* pArr, int front, int end)
{
    if (front < end)
    {
        int pivot = Partition(pArr, front, end);
        QuickSort(pArr, front, pivot-1);
        QuickSort(pArr, pivot + 1, end);
    }
}

int Max = 99999;
void Merge(int* pArr, int front, int mid, int end)
{
    vector<int> lVt(&pArr[front], &pArr[front] + (mid - front)+1);
    vector<int> rVt(&pArr[mid+1], &pArr[mid+1] + (mid+1 - end)+1);

    lVt.insert(lVt.end(), Max);
    rVt.insert(rVt.end(), Max);
    
    int idxLeft(0), idxRight(0);
    
    for (int i(front); i<=end; i++)
    {
        if (lVt[idxLeft] <= rVt[idxRight])
        {
            pArr[i] = lVt[idxLeft];
            idxLeft++;
        }
        else
        {
            pArr[i] = lVt[idxRight];
            idxRight++;
        }
    }
    
}

void MergeSort(int* pArr, int front, int end)
{
    if (front < end)
    {
        int mid = (front + end) / 2;

        MergeSort(pArr, front, mid);
        MergeSort(pArr, mid + 1, end);
        Merge(pArr, front, mid, end);
    }
}


int main(int argc, const char * argv[]) {
    // std::string s = "A man, a plan, a canal: Panama";
    // bool isTrue = isPalindrome(s);
    
//    TreeNode* root = new TreeNode(1);
//    TreeNode* node1 = new TreeNode(2);
//    TreeNode* node2 = new TreeNode(2);
//    TreeNode* node3 = new TreeNode(2);
//    TreeNode* node4 = new TreeNode(2);
//    root->left = node1;
//    root->right = node2;
//    node1->left = node3;
//    node2->left = node4;
//
//    bool anss = isSymmetric(root);
    
    
    
   int* test = new int[9]{9,4,1,7,7,3,8,5,6};
    vector<int> lVt;
    QuickSort(test, 0, 8);
    // MergeSort(test, 0, 8);
    
    
//    MoveZeroToLeft(test, 9);
//
    for (int i(0); i<9; i++)
    std::cout<<test[i] << " ";
    
 
    // std::pair<int,int> ans = find_low_high_index({5, 7, 7, 8, 8, 10}, 8);
    
    return 0;
}

class String {
public:
    String(const char *str = NULL);
    String(const String &other);
    ~String();
    String & operate = (const String &other);
    const char* GetData() {return m_data;};
    
private:
    char *m_data = nullptr; // 用于保存字符串
};

String::String(const char *str = NULL)
{
    int nSz = sizeof(str) / sizeof(char);
    m_data = new char[nSz];
    
    memcpy(m_data, str, sizeof(char) * nSz);
}

String::String(const String &other)
{
    int nSz =sizeof(other.GetData()) / sizeof(char);
    m_data = new char[nSz];
    memcpy(m_data, str, sizeof(char) * nSz);
    
}

String::~String()
{
    delete [] m_data;
    m_data = nullptr;
}

String::String & operate = (const String &other)
{
    if (other.GetData() == nullptr) return *this;
    
    delete [] m_data;
    m_data = nullptr;
    
    int nSz =sizeof(other.GetData()) / sizeof(char);
    m_data = new char[nSz];
    memcpy(m_data, str, sizeof(char) * nSz);
    
    return *this;
}

int GetNumBit(const &String)
{
    int count = 0;
    for (auto i : words)
    {
        if (i == '1')
            count++;
    }
    
    return count;
}
