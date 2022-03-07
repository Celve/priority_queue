#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<class T, class Compare = std::less<T>>
class priority_queue {
    class Node {
    public:
        Node *child[2];
        int dis;
        T value;

        void Clear() {
            dis = 0;
            child[0] = child[1] = nullptr;
        }

        Node() {
            Clear();
        };

        Node(const Node &other) {
            child[0] = child[1] = nullptr;
            dis = other.dis;
            value = other.value;
        }

        Node (const T &other_value) {
            Clear();
            value = other_value;
        }
    };

    Node *root;
    size_t n;

    void Swap(Node *&x, Node *&y) {
        Node *temp = x;
        x = y;
        y = temp;
    }

    void Construct(Node *&x, Node *y) {
        if (!y)
            return ;
        x = new Node(y);
        Construct(x->child[0], y->child[0]);
        Construct(x->child[1], y->child[1]);
    }

    void Deconstruct(Node *&x) {
        if (!x)
            return ;
        Deconstruct(x->child[0]);
        Deconstruct(x->child[1]);
        delete x;
        x = nullptr;
    }

    void Merge(Node *&x, Node *&y) {
        if (!x || !y) {
            if (!x)
                x = y;
            return ;
        }
        if (y->value < x->value)
            Swap(x, y);
        Merge(x->child[1], y);
        if (!x->child[0]) {
            Swap(x->child[0], x->child[1]);
            x->dis = 1;
            return ;
        }
        int value1 = (x->child[0] != nullptr), value2 = (x->child[1] != nullptr);
        if (x->child[1]->dis > x->child[0]->dis)
            Swap(x->child[0], x->child[1]);
        x->dis = x->child[1]->dis + 1;
    }
public:
	/**
	 * TODO constructors
	 */
	priority_queue() {
        root = nullptr;
    }
	priority_queue(const priority_queue &other) {
        Construct(root, other.root);
        n = other.n;
    }
	/**
	 * TODO deconstructor
	 */
	~priority_queue() {
        Deconstruct(root);
    }
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other) {
        if (this == &other)
            return *this;
        n = other.n;
        Deconstruct(root);
        Construct(root, other.root);
    }
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
        if (!n)
            throw container_is_empty();
        return root->value;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
        Node *temp = new Node(e);
        Merge(root, temp);
        ++n;
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
        if (!n)
            throw container_is_empty();
        --n;
        Node *temp = root;
        Merge(root->child[0], root->child[1]);
        root = root->child[0];
        delete temp;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
        return n;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
        return !n;
	}
	/**
	 * merge two priority_queues with at least O(logn) complexity.
	 * clear the other priority_queue.
	 */
	void merge(priority_queue &other) {
        Merge(root, other.root);
        Deconstruct(other.root);
	}
};

}

#endif
