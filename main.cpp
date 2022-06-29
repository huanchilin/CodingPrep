#include <string>

using namespace std;

template <typename T> class LinkNode {

    public:

        LinkNode(T x) {data = x;};

        LinkNode* nodePtr = nullptr;
        LinkNode* leftNode = nullptr;
        LinkNode* rightNode = nullptr;

        T data;
};

int main() {

    string str= "1346";
    return 0;
}