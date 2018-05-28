#include <memory>
#include <deque>
#include <iostream>

namespace ThorsAnvil
{
    namespace Util
    {

enum Order {Pre_Order, In_Order, Post_Order};

template<typename T>
class BinaryTree
{
    struct Node
    {
        T       data;
        Node*   left    = nullptr;
        Node*   right   = nullptr;

        Node(T const& data)
            : data(data)
        {}
        Node(T&& data)
            : data(std::move(data))
        {}
        template<typename... Args>
        Node(Args&&... args)
            : data(std::forward<Args>(args)...)
        {}
    };

    struct Visitor
    {
        void accept(Node* current)
        {
            if (current != nullptr) {
                processes(current);
            }
        }
        virtual void processes(Node* current) = 0;
        virtual void action(T const& value) = 0;
    };

    Node*   root;

        Node* insert(Node* current, Node* newNode)
        {
            if (current == nullptr) {
                return newNode;
            }
            if (newNode->data < current->data) {
                current->left = insert(current->left, newNode);
            }
            else {
                current->right = insert(current->right, newNode);
            }
            return current;
        }
        bool search(Node* current, T const& value)
        {
            if (current == nullptr) {
                return false;
            }
            if (value == current->data) {
                return true;
            }
            return search( (value < current->data) ? current->left : current->right, value);
        }
    public:
        BinaryTree()
            : root(nullptr)
        {}

        void insert(T const& data)      { root = insert(root, new Node(data)); }
        void insert(T&& data)           { root = insert(root, new Node(std::move(data))); }
        template<typename... Args>
        void insert(Args&&... args)     { root = insert(root, new Node(std::forward(args)...)); }
        bool search(T const& value)     { return search(root, value);}

        struct Visitor_DepthFirst: public Visitor
        {
            Visitor_DepthFirst(Order order)
                : order(order)
            {}
            virtual void processes(Node* current)
            {
                if (order == Pre_Order)  { this->action(current->data); }
                processes(current->left);
                if (order == In_Order)   { this->action(current->data); }
                processes(current->right);
                if (order == Post_Order) { this->action(current->data); }
            }

            private:
                Order order;
        };
        struct Visitor_BreadthFirst: public Visitor
        {
            virtual void processes(Node* current)
            {
                std::deque<Node*>  list(1, current);

                while(!list.empty()) {
                    action(list.front()->data);
                    list.push_back(list.front()->left);
                    list.push_back(list.front()->right);
                    list.pop();
                }
            }
        };

        void traverseTree(Visitor& visitor)
        {
            visitor.accept(root);
        }
};

    }
}

class PrintInOrder: public ThorsAnvil::Util::BinaryTree<int>::Visitor_DepthFirst
{
    public:
        PrintInOrder()
            : Visitor_DepthFirst(ThorsAnvil::Util::In_Order)
        {}
        virtual void action(int const& value) {
            std::cout << value << ", ";
        }
};

int main(int argc, char* argv[])
{
    ThorsAnvil::Util::BinaryTree<int>     tree;
    PrintInOrder                          visitor;
    tree.traverseTree(visitor);
}

