#include "header.h"

using namespace my_tree;

int main() {
    try {
        //Тест конструктора по умолчанию
        bst tree;

        //Тест добавления узлов
        std::cout << "--- Testing Insertion ---" << std::endl;
        int values[] = {50, 30, 70, 20, 40, 60, 80};
        for (int x : values) {
            tree.insert(x);
        }
        std::cout << "Values inserted: 50, 30, 70, 20, 40, 60, 80" << std::endl;

        // 3. Тест вывода в поток и симметричного обхода
        std::cout << "\n--- Testing Operator<< (In-Order) ---" << std::endl;
        std::cout << "Tree content: " << tree << std::endl;

        //Тест обходов
        std::cout << "\n--- Testing Traversals ---" << std::endl;
        std::cout << "Pre-order (Direct): "; tree.PreOrder(); std::cout << std::endl;
        std::cout << "In-order (Symmetric): "; tree.InOrder(); std::cout << std::endl;
        std::cout << "Post-order (Reverse): "; tree.PostOrder(); std::cout << std::endl;

        //Тест поиска
        std::cout << "\n--- Testing Find ---" << std::endl;
        std::cout << "Find 40: " << (tree.find(40) ? "Found" : "Not Found") << std::endl;
        std::cout << "Find 1487: " << (tree.find(1487) ? "Found" : "Not Found") << std::endl;

        //Тест удаления узла
        std::cout << "\n--- Testing Delete Node ---" << std::endl;
        std::cout << "Deleting 20 (leaf), 30 (one child), 50 (root)..." << std::endl;
        tree.del_node(20);
        tree.del_node(30);
        tree.del_node(50);
        std::cout << "Tree after deletion: " << tree << std::endl;

        //Тест конструктора копирования
        std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
        {
            bst copyTree(tree);
            std::cout << "Copied tree: " << copyTree << std::endl;
        }

        //Тест конструктора перемещения
        std::cout << "\n--- Testing Move Constructor ---" << std::endl;
        bst movedTree = std::move(tree);
        std::cout << "Moved tree: " << movedTree << std::endl;
        // tree теперь пустое

        //Тест сохранения и чтения
        std::cout << "\n--- Testing File ---" << std::endl;
        movedTree.SaveToFile("tree_data.txt");
        std::cout << "Tree saved to tree_data.txt" << std::endl;

        bst fileTree;
        fileTree.ReadFromFile("tree_data.txt");
        std::cout << "Tree loaded from file: " << fileTree << std::endl;

        //Тест удаления дерева
        std::cout << "\n--- Testing Destroy ---" << std::endl;
        fileTree.destroy();
        std::cout << "Tree after destroy: [" << fileTree << "]" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}