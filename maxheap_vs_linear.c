#include <stdio.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

long insertComparisons = 0;   // comparisons during heap insertion (sift-up)
long linearComparisons = 0;   // comparisons during linear scan

void printHeap() {
    printf("Heap array: [ ");
    for (int i = 0; i < heapSize; i++) printf("%d ", heap[i]);
    printf("]\n");
}

// Insert a value into the max heap, print heap state after insertion
void heapInsert(int value) {
    heap[heapSize] = value;
    int i = heapSize;
    heapSize++;

    // sift-up
    while (i > 0) {
        int parent = (i - 1) / 2;
        insertComparisons++;               // compare child vs parent
        if (heap[parent] < heap[i]) {
            int tmp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = tmp;
            i = parent;
        } else {
            break;
        }
    }

    printf("Inserted %d -> ", value);
    printHeap();
}

// O(1) max retrieval from heap
int heapFindMax() {
    return heap[0];
}

// Linear search for the maximum in an array, counting comparisons
int linearFindMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        linearComparisons++;
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int main() {
    int scores[] = {78, 92, 65, 88, 95, 72, 84, 90};
    int n = sizeof(scores) / sizeof(scores[0]);

    printf("=====================================================\n");
    printf("Part (a): Building Max Heap by inserting scores\n");
    printf("Input sequence: 78, 92, 65, 88, 95, 72, 84, 90\n");
    printf("=====================================================\n");
    for (int i = 0; i < n; i++) {
        heapInsert(scores[i]);
    }
    printf("\nTotal comparisons made during all %d heap insertions: %ld\n", n, insertComparisons);

    printf("\n=====================================================\n");
    printf("Part (b): Finding the highest score\n");
    printf("=====================================================\n");

    int heapMax = heapFindMax();
    printf("Max Heap approach   -> Maximum = %d, comparisons used = 0 (root is always max)\n", heapMax);

    linearComparisons = 0;
    int linMax = linearFindMax(scores, n);
    printf("Linear Search approach -> Maximum = %d, comparisons used = %ld\n", linMax, linearComparisons);

    printf("\n--- Demonstrating an INSERTION of a new score (99) ---\n");
    // Max heap: insert 99 and re-check max (O(1) after insert)
    long compsBefore = insertComparisons;
    heapInsert(99);
    long insertCostHeap = insertComparisons - compsBefore;
    printf("Max Heap: insertion cost = %ld comparisons, new max retrieval cost = 0 comparisons\n", insertCostHeap);

    // Linear array: append 99, then must rescan for max
    int scores2[9];
    for (int i = 0; i < n; i++) scores2[i] = scores[i];
    scores2[n] = 99; // O(1) append, 0 comparisons
    linearComparisons = 0;
    int newLinMax = linearFindMax(scores2, n + 1);
    printf("Linear Array: insertion cost = 0 comparisons (append), new max retrieval cost = %ld comparisons (full rescan), max = %d\n",
           linearComparisons, newLinMax);

    printf("\n=====================================================\n");
    printf("Part (c): Effect of increasing number of students (n)\n");
    printf("=====================================================\n");
    int sizes[] = {8, 16, 32, 64, 128, 256, 512, 1024};
    printf("%-8s %-28s %-28s\n", "n", "MaxHeap: insert+findMax", "LinearArray: insert+findMax");
    for (int s = 0; s < 8; s++) {
        int m = sizes[s];
        // theoretical op counts (worst case), not simulated with random data
        double heapInsertCost = 0;
        for (int k = 1; k <= m; k++) {
            int levels = 0, val = k;
            while (val > 1) { val /= 2; levels++; }
            heapInsertCost += levels; // approx log2(k)
        }
        double linearFindMaxCostTotal = 0;
        for (int k = 1; k <= m; k++) {
            linearFindMaxCostTotal += (k - 1); // each insertion followed by full O(k) rescan
        }
        printf("%-8d %-28.1f %-28.1f\n", m, heapInsertCost, linearFindMaxCostTotal);
    }

    return 0;
}
