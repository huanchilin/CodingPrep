#include <string>
#include <iostream>

using namespace std;

template <typename T>
class stackNode
{
public:
    stackNode(){};
    stackNode(T x) { data = x; };

    T data;
    stackNode<T> *next = nullptr;
    T localMin;
};

// to keep min value as O(1) to check, we can store a locak val at the node, and update that
// to global values
template <typename T>
class customStack
{
public:
    customStack(){};
    customStack(T data)
    {
        auto nd = new stackNode<T>(data);
        head = nd;
        minVal = nd->data;
    }

    stackNode<T> *top()
    {
        if (!head)
            return nullptr;
        return head;
    };

    void pop()
    {
        if (!head)
            return;
        auto nxt = head->next;

        if (nxt && minVal < nxt->localMin)
        {
            minVal = nxt->localMin;
        }

        delete head;
        head = nxt;
    };

    void push(stackNode<T> *node)
    {
        if (!head)
        {
            head = node;
            node->localMin = node->data;
            minVal = node->localMin;
            return;
        }

        if (node->data < minVal)
        {
            node->localMin = node->data;
            minVal = node->data;
        }
        else
        {
            node->localMin = minVal;
        }
        node->next = head;
        head = node;
    };

    bool isEmpty()
    {
        return head != nullptr;
    };

    T min()
    {
        return minVal;
    }

private:
    stackNode<T> *head = nullptr;
    T minVal;
};

template <typename T>
class queueNode
{
public:
    queueNode(){};
    queueNode(T x) { data = x; };

    T data;
    queueNode<T> *next = nullptr;
};

template <typename T>
class customQueue
{
public:
    customQueue(){};
    customQueue(T data)
    {
        auto nd = new queueNode<T>(data);
        head = nd;
        tail = nd;
    };

    queueNode<T> *top()
    {
        if (!head)
            return nullptr;
        return head;
    };

    void pop()
    {
        if (!head)
            return;
        auto nd = head->next;

        head = nd;
    };

    void push(queueNode<T> *node)
    {
        if (!head)
        {
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    };

private:
    queueNode<T> *head = nullptr;
    queueNode<T> *tail = nullptr;
};

#include <vector>
#include <stack>

// when asked about using a capacity on a stack, we can implement vector and push back to
// another stack. Remember that divide to whichStack and vector size condition
class SetOfStack
{
public:
    SetOfStack(const int th) { threshold = th; };
    SetOfStack(const int th, int x)
    {
        threshold = th;

        std::stack<int> stk;
        stk.push(x);
        vtStack.push_back(stk);
        size++;
    };

    void push(int x)
    {
        int whichStack = (++size) / threshold;
        if (whichStack == vtStack.size())
        {
            std::stack<int> stk;
            stk.push(x);
            vtStack.push_back(stk);
        }
        else
            vtStack.at(whichStack).push(x);
    };

    void pop()
    {
        if (size == 0)
            return;
        int whichStack = (size) / threshold;
        vtStack.at(whichStack).pop();
        size--;

        if (vtStack.at(whichStack).size() == 0)
            vtStack.erase(vtStack.begin() + whichStack);
    };

    int top()
    {
        if (size == 0)
            return INT_MIN;
        int whichStack = (size) / threshold;
        return vtStack.at(whichStack).top();
    }

    bool isEmpty() { return size == 0; }

private:
    std::vector<std::stack<int>> vtStack;
    int threshold;
    int size = 0;
};

#include <stack>

// a more optimal way to implement this is to lazy reverse, which is we dont need to dump every
// thing back to first stack if we dont need to. we can set a flag to remind to dump.
class MyQueue
{
public:
    MyQueue(){};

    void push(int x) { one.push(x); };
    void pop()
    {
        if (one.empty())
            return;

        while (!one.empty())
        {
            auto entity = one.top();
            two.push(entity);
            one.pop();
        }
        two.pop();

        while (!two.empty())
        {
            auto entity = two.top();
            one.push(entity);
            two.pop();
        }
    };
    int top()
    {
        if (one.empty())
            return INT_MIN;

        int retVal;
        while (!one.empty())
        {
            auto entity = one.top();
            two.push(entity);
            one.pop();
        }
        retVal = two.top();

        while (!two.empty())
        {
            auto entity = two.top();
            one.push(entity);
            two.pop();
        }
        return retVal;
    };

private:
    std::stack<int> one, two;
};

#include <stack>

using namespace std;

stack<int> sortStack(stack<int> &input)
{
    if (input.empty())
        return stack<int>();
    if (input.size() == 1)
        return input;

    stack<int> out;
    auto entity = input.top();
    input.pop();
    out.push(entity);

    while (!input.empty())
    {
        entity = input.top();
        input.pop();

        // dump all out smaller values to input
        while (!out.empty() && out.top() <= entity)
        {
            auto dump = out.top();
            out.pop();
            input.push(dump);
        }

        // push entity to out
        out.push(entity);

        // return dumps to out
        while (!input.empty() && input.top() <= entity)
        {
            entity = input.top();
            input.pop();
            out.push(entity);
        }
    }

    return out;
}

int main()
{
    stack<int> stk;
    stk.push(3);
    stk.push(5);
    stk.push(1);
    stk.push(6);
    stk.push(2);

    auto out = sortStack(stk);
    while (!out.empty())
    {
        std::cout << out.top() << " ";
        out.pop();
    }
    cout << std::endl;
    return 0;
}