# Assignment 2 – Question 3
**PCCST303 – Data Structures and Algorithms**
**Topic:** Max Heap vs. Linear Search for finding the highest student score

## Problem
A university wants to identify the highest student score from the data:
`78, 92, 65, 88, 95, 72, 84, 90`

---

## (a) Max Heap Construction

Each score is inserted one at a time using the standard array-based max-heap
insertion (insert at the end, then sift-up while the parent is smaller).

| Step | Inserted | Heap array after insertion |
|---|---|---|
| 1 | 78 | [78] |
| 2 | 92 | [92, 78] |
| 3 | 65 | [92, 78, 65] |
| 4 | 88 | [92, 88, 65, 78] |
| 5 | 95 | [95, 92, 65, 78, 88] |
| 6 | 72 | [95, 92, 72, 78, 88, 65] |
| 7 | 84 | [95, 92, 84, 78, 88, 65, 72] |
| 8 | 90 | [95, 92, 84, 90, 88, 65, 72, 78] |

Total sift-up comparisons for all 8 insertions: **12**.

---

## (b) Finding the Highest Score

| Method | Result | Comparisons used |
|---|---|---|
| Max Heap (read `heap[0]`) | 95 | **0** |
| Linear Search (scan all 8 scores) | 95 | **7** |

**Insertion of a new score (99), then re-finding the max:**

| Method | Insertion cost | Cost to get new max | New max |
|---|---|---|---|
| Max Heap | 3 comparisons (sift-up) | 0 comparisons (root) | 99 |
| Linear Array | 0 comparisons (append) | 8 comparisons (full rescan) | 99 |

This is the key trade-off: a max heap pays a small, bounded cost *at insertion
time* so that *every subsequent* "who is the highest scorer?" query is O(1).
A plain array pays nothing at insertion but must re-scan the whole array
every time the maximum is needed again.

---

## (c) Effect of Increasing the Number of Students (n)

Cumulative comparisons if we insert n scores one-by-one and, after **every**
insertion, ask "what is the current highest score?" (a realistic scenario for
a system that continuously admits new students and repeatedly needs the
top scorer):

| n | Max Heap: total insert comparisons | Linear Array: total rescan comparisons (find-max after every insert) |
|---|---|---|
| 8 | 13 | 28 |
| 16 | 38 | 120 |
| 32 | 103 | 496 |
| 64 | 264 | 2,016 |
| 128 | 649 | 8,128 |
| 256 | 1,546 | 32,640 |
| 512 | 3,595 | 130,816 |
| 1024 | 8,204 | 523,776 |

(Max-heap column ≈ Σ log₂(k) for k = 1..n; linear-array column ≈ Σ(k−1) for
k = 1..n, since a full O(k) rescan follows each of the n insertions.)

The linear-array cost grows **quadratically** (O(n²) over n insert+find-max
cycles), while the heap cost grows only as **O(n log n)**. The gap widens
sharply as n grows — at n = 1024 the heap does ~8.2 thousand comparisons
versus ~524 thousand for the array, a 64× difference.

### Time / Space Complexity Summary

| Operation | Max Heap | Linear Search / Array |
|---|---|---|
| Insert a new score | O(log n) | O(1) |
| Find the maximum | **O(1)** | O(n) |
| Insert + find-max repeated n times | O(n log n) | **O(n²)** |
| Space | O(n) | O(n) |

Both structures use O(n) space (a simple array), so space is not the
differentiator here — the deciding factor is how the *find-maximum*
operation scales.

---

## Conclusion

For a system that must **continuously insert new student scores and
repeatedly report the current highest score**, the **Max Heap is the
clearly superior data structure**:

- Retrieving the maximum is O(1) at all times (just read the root), whereas
  a linear scan costs O(n) *every single time* the maximum is requested.
- Insertion into a heap costs only O(log n), a small and predictable price
  compared to the O(n) it saves on every subsequent max-query.
- As the number of students grows, the combined cost of "insert then find
  max" grows as O(n log n) for the heap versus O(n²) for the linear-array
  approach — the linear approach becomes impractical at scale, while the
  heap stays efficient.

The only scenario where a plain array would be preferable is if scores are
inserted far more often than the maximum is ever queried (insertion-heavy,
query-light workload) — but for a university system that needs the
top scorer on demand, the Max Heap is the appropriate and scalable choice.
