#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> arr; // Input array
    vector<int> tree; // Segment tree
    int n; // Size of input array

    // Function to build the segment tree
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Function to query sum of elements in a given range
    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return 0;
        if (left <= start && right >= end) return tree[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, left, right) + 
               query(2 * node + 1, mid + 1, end, left, right);
    }

    // Function to update a value at a given index
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

public:
    // Constructor to initialize the segment tree
    SegmentTree(const vector<int>& input) {
        arr = input;
        n = input.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    // Function to query the sum of elements in a given range
    int queryRange(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }

    // Function to update the value at a given index
    void updateIndex(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
};

int main() {
    vector<int> input = {1, 3, 5, 7, 9, 11}; // Sample input array
    SegmentTree st(input); // Creating segment tree object
    
    // Querying sum of elements in range [1, 3]
    cout << "Sum of elements in range [1, 3]: " << st.queryRange(1, 3) << endl;
    
    // Updating value at index 2 to 6
    st.updateIndex(2, 6);
    cout << "Updated. Sum of elements in range [1, 3]: " << st.queryRange(1, 3) << endl;
    
    return 0;
}
