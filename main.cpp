#include <string>
#include <iostream>

using namespace std;

template <typename T> class LinkNode {

    public:
        LinkNode(){};
        LinkNode(T x) {data = x;};

        LinkNode* next = nullptr;
        T data;
};

template <typename T> class LinkedList {
    public:
        LinkedList(){};
        LinkedList(LinkNode<T> *p) {head = p;};

    public:
        LinkNode<T>* head = nullptr;
};

#include <unordered_set>
// Remember when delete we remain at the same node, so that we can check the next of the next.
// For without temporary cached, we can use two pointers, one at the current, one at the next
// and iterate over the whole list
void removeDuplicate(LinkedList<int>*& list) {
    if (list->head == nullptr) return;

    unordered_set<int> set;
    auto node = list->head;

    set.insert(node->data);
    while (node->next != nullptr) {
        if (set.find(node->next->data) == set.end()) {
            set.insert(node->next->data);
            node = node->next;
        }
        else {
            node->next = node->next->next;
        }
    }
}

LinkNode<int>* traverseList(int step, LinkNode<int>* node) {
    if (step == 0) return node;
    int remainStep = step;
    auto returnNd = node;
    while(remainStep > 0) {
			remainStep--;
			returnNd = returnNd->next;

		}
    return returnNd;
}

// another way to do this is first iterate through k with one node from head; 
// the second node start from the head and iterate while first node reach the end;
LinkNode<int>* returnKthToLast(LinkNode<int>* node, int k) {
    if (node == nullptr) return nullptr;

	auto oneStepPtr = node; 
	auto twoStepPtr = node; 

	int wholeLength(1), halfLength(1);
	while (twoStepPtr->next && 
            twoStepPtr->next->next != nullptr) {
		oneStepPtr  = oneStepPtr->next;
		halfLength++;
		twoStepPtr = twoStepPtr->next->next;
		wholeLength+=2;
	}

    // if it is not divided by 2, we all need to step up one
	if (twoStepPtr->next != nullptr) {
		wholeLength++; // that is the total length
        halfLength++;
        oneStepPtr  = oneStepPtr->next;
		twoStepPtr = twoStepPtr->next;
	}
	
    // boundar conditions check!
    if (k > wholeLength) return nullptr;
    if (k == wholeLength) return node;

	int remainStep(0);
	LinkNode <int>* returnNd;
    // if k is in between the 2nd half of the list
	if (k <= wholeLength - halfLength + 1) {
        // this is the tricky part. we need to know how many step to take from half
		remainStep =  wholeLength - k - halfLength + 1;
		returnNd = oneStepPtr;
		returnNd = traverseList(remainStep, returnNd);
		return returnNd;
	}
	else {
		remainStep = wholeLength - k;
		returnNd = node;
        returnNd = traverseList(remainStep, returnNd);
		return returnNd;
	}
}

#include <array>
#include <vector>
// the not so optimal way is below. which store all greater and less or equal to to two
// vector containers. And connect them. The boundary conditions are tricky this way
LinkNode<int>* partition1(LinkNode<int>* node, const int n) {
	if (node == nullptr) return nullptr;

	auto nd = node;
	std::vector<LinkNode<int>*> gt, le;

    // cache the data of all greater or less and equal to vectors
	int gtIndex = 0, leIndex = 0;
	nd = node; 
	while (nd != nullptr) {
		if (nd->data > n) {
			gtIndex++;
			gt.push_back(nd);
		}
		else {
			leIndex ++;
			le.push_back(nd);
		}
		nd = nd->next;
	}
	
    // starting with less
	auto hd = le[0]; 
    nd = le[0];
	if (hd != nullptr) {
        for (int i(1); i < le.size(); i++) {
            nd->next = le[i];
            nd = nd->next;
        }
	}

    // then greater. CHECK IF IT IS BOUNDARY
	if (hd == nullptr) {
        hd = gt[0];
        nd = gt[0];
    }
    // IF GREATER IS ZERO
    else if (gt.size() == 0) {
        return hd;
    }
    // CONNECT TO GREATER
    else {
        nd->next = gt[0];
        nd = nd->next;
    }
        
    for (int i(1); i < gt.size(); i++) {
        nd->next = gt[i];
		nd = nd->next;
	}
    //END WITH A NULLPTR TAIL
    nd->next = nullptr;
	return hd;
}

// this method use four pointers to go through the list. and connect them at the go.
// we merge at the end with before end to after start. Make sure we check before start
// is not a nullptr
LinkNode<int>* partition(LinkNode<int>* node, const int n) {
    if (node == nullptr) return nullptr;

    LinkNode<int>* beforeStart = nullptr;
    LinkNode<int>* beforeEnd = nullptr;
    LinkNode<int>* afterStart = nullptr;
    LinkNode<int>* afterEnd = nullptr;

    auto nd = node;
    while (nd != nullptr) {
        if (nd->data <= n) {
            if (beforeStart == nullptr) {
                beforeStart = nd;
                beforeEnd = nd; // tail set
            }
            else {
                beforeEnd->next = nd;
                beforeEnd = nd;
            }
        }
        else {
            if (afterStart == nullptr) {
                afterStart = nd;
                afterEnd = nd; // tail set
            }
            else {
                afterEnd->next = nd;
                afterEnd = nd;
            }
        }
        nd = nd->next;
    }

    if (beforeStart == nullptr)  { // only greater
        afterEnd->next = nullptr;
        return afterStart;
    }
    else {
        beforeEnd->next = afterStart;

        // boundary condition when after start is empty
        if (afterStart)
            afterEnd->next = nullptr;
        else
            beforeEnd->next = nullptr;

        return beforeStart;
    }
        
}

#include <vector>

// start with newing one node with data as remainder
// 912 / 10 = 91...2
// 91 / 10 = 9...1
// 9 / 10 = 0...0
LinkNode<int>* sumLists1(LinkNode<int>* a, LinkNode<int>* B) {
	int aTen(0), bTen(0);
	auto node = a;
	
	vector<int> vtA;
	while (node != nullptr) {
		vtA.push_back(node->data);
		aTen++;
		node = node->next;
	}
	
	node = B;
	vector<int> vtB;
	while (node != nullptr) {
		vtB.push_back(node->data);
        node = node->next;

		bTen++;
	}
	int sumA(0), sumB(0);
	for (int i = vtA.size() - 1; i >=0; i--) {
		sumA += pow(10, --aTen) * vtA[i];
	}
	for (int i = vtB.size() - 1; i >=0; i--) {
		sumB += pow(10, --bTen) * vtB[i];
	}

	int total = sumA + sumB;
	if (total == 0) {
		return nullptr;
	}

    // start with newing one node with data as remainder
    // 912 / 10 = 91...2
    // 91 / 10 = 9...1
    // 9 / 10 = 0...0

	int remain = total;
	int remainder = remain % 10;
    auto newNode = new LinkNode<int>(remainder);
	remain /=10;
	auto ret = newNode;

	while (remain != 0) {
		remainder = remain % 10;
		auto nnd = new LinkNode<int>(remainder);
		remain /=10;
		ret->next = nnd;
		ret = nnd;
	}
	return newNode;
}

// another way to think about this is the fundamentals behind adding, we add and carry 1 over to the next
LinkNode<int>* sumList(LinkNode<int>* a, LinkNode<int>* b, int carry) {
    if (!a && !b && carry == 0) return nullptr;

    auto node = new LinkNode<int>();

    int value = carry;
    if (a) {
        value += a->data;
    }

    if (b) {
        value += b->data;
    }

    node->data = value % 10;
    if (a || b) {
        auto nxtNode = sumList(a == nullptr? nullptr : a->next,
                                b == nullptr? nullptr : b->next,
                                value >= 10? 1 : 0);
        node->next = nxtNode;
    }
    return node;
} 

LinkNode<int>* sumList(LinkNode<int>* a, LinkNode<int>* b) {
    return sumList(a, b, 0);
}

int main() {
    auto node1 = new LinkNode<int>(7);
    auto node2 = new LinkNode<int>(1);
    auto node3 = new LinkNode<int>(6);
    auto node7 = new LinkNode<int>(6);

    auto node4 = new LinkNode<int>(5);
    auto node5 = new LinkNode<int>(9);
    auto node6 = new LinkNode<int>(2);


    node1->next = node2;
    node2->next = node3;
    node3->next = node7;
    node7->next = nullptr;

    node4->next = node5;
    node5->next = node6;
    node6->next = nullptr;

    auto node = sumList(node1, node4);

    cout<< "linked list: ";
    while (node != nullptr) {
        cout<< node->data << " -> ";

        node = node->next;
    }
    cout<<endl;

    return 0;
}