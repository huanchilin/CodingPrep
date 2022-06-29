template <typename T> class LinkNode {

    public:

        LinkNode(T x) {data = x;};

        LinkNode* nodePtr = nullptr;
        LinkNode* leftNode = nullptr;
        LinkNode* rightNode = nullptr;

        T data;
};