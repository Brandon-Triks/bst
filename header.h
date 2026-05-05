#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>

namespace my_tree {

    class bst {
    private:
        struct Node {
            int data;
            Node* left;
            Node* right;
            explicit Node(int k) {
                data = k;
                left = nullptr;
                right = nullptr;
            }
        };

        Node* root;

        //Вспомогательные приватные методы
        Node* min(Node* curr) const;
        Node* remove_node(Node*& curr, int val);
        bool find_help(Node* curr, int val) const;
        void ins(Node*& curr, int val);
        void del(Node*& del_root);
        Node* copyRecursive(const Node* nodeToCopy) const;
        
        void InOrderH(Node* curr, std::ostream& os) const;
        void PreOrderH(Node* curr, std::ostream& os) const;
        void PostOrderH(Node* curr, std::ostream& os) const;

    public:
        bst();
        bst(const bst& oth);
        bst(bst&& oth) noexcept;
        ~bst();

        void insert(int val);
        void del_node(int val);
        void destroy();
        bool find(int val) const;

        void PreOrder() const;
        void InOrder() const;
        void PostOrder() const;

        void SaveToFile(const std::string& filename) const;
        void ReadFromFile(const std::string& filename);

        friend std::ostream& operator<<(std::ostream& os, const bst& tree);
    };

}

#endif