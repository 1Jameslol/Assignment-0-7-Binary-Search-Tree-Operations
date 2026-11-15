# Assignment 07: Binary Search Tree Operations

Build and run with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o bst
./bst
```

`main.cpp` implements a binary search tree from scratch using dynamically allocated nodes. It demonstrates:

- insertion of 10 distinct integers;
- searching for a present key and an absent key;
- inorder, preorder, postorder, and height operations;
- removal of a leaf, a node with one child, and a node with two children; and
- sorted inorder output after every removal.

For a tree of height `h`, search, insertion, and removal each take `O(h)`. In a reasonably balanced tree, `h` is `O(log n)`, so the average complexity is `O(log n)`. In the worst case the tree can become a chain, making `h = O(n)` and each operation `O(n)`.
