#include <iostream>
#include <vector>
#include <climits>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& data) {
        n = data.size();
        tree.resize(2 * n);
        lazy.resize(2 * n, 0);
        build(data);
    }

    void update(int pos, int value) {
        pos += n;
        tree[pos] = value;
        while (pos > 1) {
            pos /= 2;
            tree[pos] = min(tree[2 * pos], tree[2 * pos + 1]);
        }
    }

    int rangeMinQuery(int left, int right) {
        left += n;
        right += n;
        int minimum = INT_MAX;
        while (left <= right) {
            if (left % 2 == 1) {
                minimum = min(minimum, tree[left]);
                left++;
            }
            if (right % 2 == 0) {
                minimum = min(minimum, tree[right]);
                right--;
            }
            left /= 2;
            right /= 2;
        }
        return minimum;
    }

    void rangeUpdate(int left, int right, int value) {
        left += n;
        right += n;
        while (left <= right) {
            if (left % 2 == 1) {
                tree[left] += value;
                lazy[left] += value;
                left++;
            }
            if (right % 2 == 0) {
                tree[right] += value;
                lazy[right] += value;
                right--;
            }
            left /= 2;
            right /= 2;
        }
        propagate();
    }

    void rangeMultiIncrement(int left, int right, int value) {
        left += n;
        right += n;
        while (left <= right) {
            if (left % 2 == 1) {
                tree[left] += value;
                lazy[left] += value;
                left++;
            }
            if (right % 2 == 0) {
                tree[right] += value;
                lazy[right] += value;
                right--;
            }
            left /= 2;
            right /= 2;
        }
        propagate();
    }

private:
    int n;
    std::vector<int> tree;
    std::vector<int> lazy;

    void build(const std::vector<int>& data) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = data[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void propagate() {
        for (int i = 1; i < n; ++i) {
            if (lazy[i] != 0) {
                tree[2 * i] += lazy[i];
                lazy[2 * i] += lazy[i];
                tree[2 * i + 1] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
                lazy[i] = 0;
            }
        }
    }
};

// Example usage:
int main() {
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(data);

    // Range minimum query from index 1 to 5 (inclusive)
    std::cout << "Range minimum from index 1 to 5: " << segTree.rangeMinQuery(1, 5) << std::endl;

    // Update element at index 2 to -1
    segTree.update(2, -1);

    // Range minimum query from index 1 to 5 (inclusive)
    std::cout << "Range minimum from index 1 to 5 after update: " << segTree.rangeMinQuery(1, 5) << std::endl;

    // Range update increment from index 1 to 4 by 3
    segTree.rangeUpdate(1, 4, 3);

    // Range minimum query from index 1 to 5 (inclusive)
    std::cout << "Range minimum from index 1 to 5 after range update: " << segTree.rangeMinQuery(1, 5) << std::endl;

    // Range multi-increment from index 2 to 5 by 2
    segTree.rangeMultiIncrement(2, 5, 2);

    // Range minimum query from index 1 to 5 (inclusive)
    std::cout << "Range minimum from index 1 to 5 after multi-increment: " << segTree.rangeMinQuery(1, 5) << std::endl;

    return 0;
}
