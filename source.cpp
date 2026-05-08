#include "header.h"

namespace my_tree {

    //Конструктор по умолчанию
    bst::bst() {
        root = nullptr;
    }

    //Конструктор копирования
    bst::bst(const bst& oth) {
        root = copyRecursive(oth.root);
    }

    //Конструктор перемещения
    bst::bst(bst&& oth) noexcept {
        root = oth.root;
        oth.root = nullptr;
    }

    //Деструктор
    bst::~bst() {
        del(root);
    }

    //Добавление узла
    void bst::insert(int val) {
        ins(root, val);
    }

    //Удаление узла
    void bst::del_node(int val) {
        remove_node(root, val);
    }

    //Удаление дерева
    void bst::destroy() {
        del(root);
    }

    //Поиск
    bool bst::find(int val) const {
        return find_help(root, val);
    }

    // (i, j, k) Обходы
    void bst::InOrder() const {
        InOrderH(root, std::cout);
    }
    void bst::PreOrder() const {
        PreOrderH(root, std::cout);
    }
    void bst::PostOrder() const {
        PostOrderH(root, std::cout);
    }

    //Сохранение в файл
    void bst::SaveToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (fout.is_open()) {
            PreOrderH(root, fout);
            fout.close();
        }
    }

    //Чтение из файла
    void bst::ReadFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (fin.is_open()) {
            destroy();
            int val;
            while (fin >> val) {
                insert(val);
            }
            fin.close();
        }
    }

    //Приватные вспомогательные методы

    bst::Node* bst::min(Node* curr) const {             //Минимальный элемент
        if (curr == nullptr) return nullptr;
        if (curr->left == nullptr) {
            return curr;
        }
        return min(curr->left);
    }

    bst::Node* bst::remove_node(Node*& curr, int val) { //Удаление узла
        if (curr == nullptr) return nullptr;

        if (val > curr->data) {
            curr->right = remove_node(curr->right, val);
            return curr;
        }
        if (val < curr->data) {
            curr->left = remove_node(curr->left, val);
            return curr;
        }
        if (val == curr->data) {
            //нет детей
            if (curr->right == nullptr && curr->left == nullptr) {
                delete curr;
                curr = nullptr;
                return curr;
            }
            //один ребенок
            if (curr->left == nullptr || curr->right == nullptr) {
                if (curr->left == nullptr) {
                    Node* temp = curr->right;
                    delete curr;
                    curr = temp;
                    return curr;
                }
                else {
                    Node* temp = curr->left;
                    delete curr;
                    curr = temp;
                    return curr;
                }
            }
            //два ребенка
            Node* minim = min(curr->right);
            curr->data = minim->data;
            curr->right = remove_node(curr->right, minim->data);
            return curr;
        }
        return curr;
    }

    bool bst::find_help(Node* curr, int val) const {    //Поиск элемента
        if (curr == nullptr) return false;
        if (val == curr->data) {
            return true;
        }
        if (val > curr->data) {
            return find_help(curr->right, val);
        }
        else {
            return find_help(curr->left, val);
        }
    }

    void bst::ins(Node*& curr, int val) {               //Инсерт
        if (curr == nullptr) {
            curr = new Node(val);
        }
        else {
            if (val < curr->data) {
                ins(curr->left, val);
            }
            else if (val > curr->data) {
                ins(curr->right, val);
            }
        }
    }

    void bst::del(Node*& del_root) {                   //удаление дерева
        if (del_root != nullptr) {
            del(del_root->left);
            del(del_root->right);
            delete del_root;
            del_root = nullptr;
        }
    }

    bst::Node* bst::copyRecursive(const Node* nodeToCopy) const{    //копирование элемента
        if (nodeToCopy == nullptr) return nullptr;
        Node* newNode = new Node(nodeToCopy->data);
        newNode->left = copyRecursive(nodeToCopy->left);
        newNode->right = copyRecursive(nodeToCopy->right);
        return newNode;
    }

    void bst::InOrderH(Node* curr, std::ostream& os) const {        //симметричный обход
        if (curr == nullptr) return;
        InOrderH(curr->left, os);
        os << curr->data << " ";
        InOrderH(curr->right, os);
    }

    void bst::PreOrderH(Node* curr, std::ostream& os) const {       //прямой обход
        if (curr == nullptr) return;
        os << curr->data << " ";
        PreOrderH(curr->left, os);
        PreOrderH(curr->right, os);
    }

    void bst::PostOrderH(Node* curr, std::ostream& os) const {      //обратный обход
        if (curr == nullptr) return;
        PostOrderH(curr->left, os);
        PostOrderH(curr->right, os);
        os << curr->data << " ";
    }

    std::ostream& operator<<(std::ostream& os, const bst& tree) {   //<<
        tree.InOrderH(tree.root, os);
        return os;
    }

}
