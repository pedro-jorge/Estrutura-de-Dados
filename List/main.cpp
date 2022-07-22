#include <iostream>
#include <memory>

template <class T>
class Node {
private:
    Node *prev, *next;
    T *obj;

public:
    Node(T *_obj, Node *_prev, Node *_next) {
        prev = _prev;
        next = _next;
        obj = _obj;
    }

    [[nodiscard]] auto Prev() const noexcept { return prev; }
    [[nodiscard]] auto Next() const noexcept { return next; }
    [[nodiscard]] T Obj() const noexcept { return *obj; }

    auto setNext(Node *_next) { next = _next; }
    auto setPrev(Node *_prev) { prev = _prev; }
    auto setObj(T *_obj) { obj = _obj; }
};

template <class T>
class List {
private:
    Node<T> *head;
    int size;
    bool empty;

    static auto createNode(T *obj = nullptr, Node<T> *prev = nullptr, Node<T> *next = nullptr) {
        return Node<T> *node{obj, prev, next};
    }

public:
    List() {
        head = nullptr;
        size = 0;
        empty = true;
    }

    auto append(T obj) {
        if(head == nullptr)
            head = createNode(&obj);

        else {
            auto node = head;
            while (node->Next() != nullptr)
                node = node->Next();
            node->setNext(createNode(std::make_shared<T>(obj), node));
        }

        if(empty) empty = false;
        size++;
    }

    auto append(int index, T obj) {
        if (index > size - 1)
            return;

        auto node = head;
        for (int i = 0; i < index-1; i++)
            node = node->Next();

        auto newNode = createNode(std::make_shared<T>(obj), node->Prev(), node);

        node->Prev()->setNext(newNode);
        node->setPrev(newNode);

        if(empty) empty = false;
        size++;
    }

    auto clear() {
        auto node = head;

        for(int i=0; i<size; i++) {
            node = node->Next();
            delete node->Prev();
            std::cout << node->Prev().use_count();
        }

        std::cout << "clear";
        size = 0;
        empty = true;
    }

    auto contains(T obj) {
        auto node = head;
        while(node != nullptr && node->Obj() != obj)
            node = node->Next();

        return node != nullptr;
    }

    auto indexof(T obj) {
        auto node = head;
        int i = 0;
        while(node->Obj() != obj && node != nullptr)
            node = node->Next();

        return node == nullptr ? -1 : i;
    }

    auto remove(int index) {
        auto node = head;
        for(int i=0; i<index; i++) {
            node = node->Next();
            if(node == nullptr) return;
        }

        node->Prev()->setNext(node->Next());
        node->Next()->setPrev(node->Prev());
    }

    auto print() {
        auto node = head;
        while(node != nullptr) {
            std::cout << node->Obj();
            node = node->Next();
        }
        std::cout << '\n';
    }
};

int main() {
    List<int> l;
    for(int i=0; i<20; i++)
        l.append(i);

    l.clear();
    //l.print();

    return 0;
}
