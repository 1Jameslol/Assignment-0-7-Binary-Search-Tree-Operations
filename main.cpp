#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        explicit Node(int value) : key(value), left(nullptr), right(nullptr) {}
    };

    Node* root_ = nullptr;

    static Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        // Duplicate keys are ignored so every stored key is distinct.
        return node;
    }

    static bool search(const Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        return key < node->key ? search(node->left, key)
                               : search(node->right, key);
    }

    static Node* minimum(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    static Node* remove(Node* node, int key, bool& removed) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove(node->left, key, removed);
        } else if (key > node->key) {
            node->right = remove(node->right, key, removed);
        } else {
            removed = true;

            // Case 1: leaf; case 2: one child.
            if (node->left == nullptr) {
                Node* right_child = node->right;
                delete node;
                return right_child;
            }
            if (node->right == nullptr) {
                Node* left_child = node->left;
                delete node;
                return left_child;
            }

            // Case 3: two children. Replace with the inorder successor.
            Node* successor = minimum(node->right);
            node->key = successor->key;
            bool successor_removed = false;
            node->right = remove(node->right, successor->key, successor_removed);
        }
        return node;
    }

    static void inorder(const Node* node, std::vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
    }

    static void preorder(const Node* node, std::vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->key);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    static void postorder(const Node* node, std::vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->key);
    }

    static int height(const Node* node) {
        if (node == nullptr) {
            return -1;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    static void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    static void print(const std::vector<int>& values) {
        for (std::size_t i = 0; i < values.size(); ++i) {
            if (i != 0) {
                std::cout << ' ';
            }
            std::cout << values[i];
        }
        std::cout << '\n';
    }

public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    ~BinarySearchTree() {
        destroy(root_);
    }

    void insert(int key) {
        root_ = insert(root_, key);
    }

    bool search(int key) const {
        return search(root_, key);
    }

    bool remove(int key) {
        bool removed = false;
        root_ = remove(root_, key, removed);
        return removed;
    }

    std::vector<int> inorder() const {
        std::vector<int> result;
        inorder(root_, result);
        return result;
    }

    std::vector<int> preorder() const {
        std::vector<int> result;
        preorder(root_, result);
        return result;
    }

    std::vector<int> postorder() const {
        std::vector<int> result;
        postorder(root_, result);
        return result;
    }

    int height() const {
        return height(root_);
    }

    void printTraversals() const {
        std::cout << "  Inorder:   ";
        print(inorder());
        std::cout << "  Preorder:  ";
        print(preorder());
        std::cout << "  Postorder: ";
        print(postorder());
        std::cout << "  Height: " << height() << " edges\n";
    }
};

static void showRemoval(BinarySearchTree& tree, int key, const char* caseName) {
    std::cout << "\nRemove " << key << " (" << caseName << "):\n";
    assert(tree.remove(key));
    const std::vector<int> sorted = tree.inorder();
    assert(std::is_sorted(sorted.begin(), sorted.end()));
    tree.printTraversals();
    std::cout << "  Inorder remains sorted: yes\n";
}

int main() {
    BinarySearchTree tree;
    const int values[] = {50, 30, 70, 20, 40, 60, 80, 65, 10, 35};

    for (int value : values) {
        tree.insert(value);
    }

    std::cout << "Binary Search Tree Operations\n\n";
    std::cout << "After inserting 10 distinct integers:\n";
    tree.printTraversals();

    std::cout << "\nSearch 65 (present): " << (tree.search(65) ? "found" : "not found") << '\n';
    std::cout << "Search 99 (absent): " << (tree.search(99) ? "found" : "not found") << '\n';

    showRemoval(tree, 10, "leaf");
    showRemoval(tree, 60, "one child (65)");
    showRemoval(tree, 50, "two children (30 and 70)");

    std::cout << "\nComplexity (h = tree height, n = number of nodes):\n"
              << "  Search: average O(log n), worst O(n)\n"
              << "  Insert: average O(log n), worst O(n)\n"
              << "  Remove: average O(log n), worst O(n)\n";
}
