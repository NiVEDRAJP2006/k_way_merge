# K-Way Merge Using Min Heap and Pairwise Merging

## Objective

To implement and compare two approaches for merging
multiple already sorted transaction lists:

1. K-way merge using a Min Heap
2. Pairwise merging

---

## Input

Three sorted transaction lists are given:

L1 = 10, 30, 50, 70

L2 = 20, 40, 60, 80

L3 = 15, 35, 55, 75

---

## Expected Output

10 15 20 30 35 40 50 55 60 70 75 80

---

## Algorithms

### 1. K-Way Merge Using Min Heap

The first element from each sorted list is inserted into
a Min Heap.

The minimum element is repeatedly removed from the heap.
The next element from the same list is then inserted.

Time Complexity: O(N log K)

Space Complexity: O(K)

---

### 2. Pairwise Merging

First L1 and L2 are merged.

Then the resulting list is merged with L3.

Time Complexity: O(NK) for sequential merging

Space Complexity: O(N)

---

## Experimental Results

| Parameter | Min Heap | Pairwise |
|-----------|----------|----------|
| Lists | 3 | 3 |
| Elements | 12 | 12 |
| Comparisons | 21 | 18 |
| Space | O(K) | O(N) |
| Time | O(N log K) | O(NK) |

---

## Final Conclusion

For the given small input, pairwise merging performs
18 comparisons while the Min Heap approach performs
21 comparisons.

However, when the number of sorted files increases,
the Min Heap K-way merge scales better because its
time complexity is O(N log K).

Therefore, the Min Heap approach is suitable for
merging a large number of sorted files.
