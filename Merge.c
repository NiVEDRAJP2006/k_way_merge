#include <stdio.h>

#define K 3
#define MAX 20

int heapComparisons = 0;
int pairComparisons = 0;

/* =========================
   HEAP NODE
   ========================= */
typedef struct {
    int value;
    int list_no;
    int index;
} HeapNode;


/* =========================
   MIN HEAP FUNCTIONS
   ========================= */

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode heap[], int n, int i)
{
    while (1)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n)
        {
            heapComparisons++;

            if (heap[left].value < heap[smallest].value)
                smallest = left;
        }

        if (right < n)
        {
            heapComparisons++;

            if (heap[right].value < heap[smallest].value)
                smallest = right;
        }

        if (smallest != i)
        {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        }
        else
        {
            break;
        }
    }
}

void buildMinHeap(HeapNode heap[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(heap, n, i);
}

void printHeap(HeapNode heap[], int n)
{
    printf("[ ");

    for (int i = 0; i < n; i++)
        printf("%d ", heap[i].value);

    printf("]");
}


/* =========================
   K-WAY MERGE USING MIN HEAP
   ========================= */

void kWayMerge(int lists[K][MAX], int sizes[K])
{
    HeapNode heap[K];
    int heapSize = 0;

    int output[K * MAX];
    int outputSize = 0;

    /* Insert first element of every list */
    for (int i = 0; i < K; i++)
    {
        heap[heapSize].value = lists[i][0];
        heap[heapSize].list_no = i;
        heap[heapSize].index = 0;

        heapSize++;
    }

    /* Build min heap */
    buildMinHeap(heap, heapSize);

    printf("\n===== K-WAY MERGE USING MIN HEAP =====\n");

    printf("Initial Heap: ");
    printHeap(heap, heapSize);
    printf("\n\n");

    while (heapSize > 0)
    {
        HeapNode root = heap[0];

        output[outputSize++] = root.value;

        int listNo = root.list_no;
        int index = root.index;

        /* If more elements remain in the same list */
        if (index + 1 < sizes[listNo])
        {
            heap[0].value = lists[listNo][index + 1];
            heap[0].list_no = listNo;
            heap[0].index = index + 1;
        }
        else
        {
            /* Remove exhausted list */
            heapSize--;

            if (heapSize > 0)
                heap[0] = heap[heapSize];
        }

        if (heapSize > 0)
            minHeapify(heap, heapSize, 0);

        printf("Output %2d -> %d    Heap: ",
               outputSize, root.value);

        printHeap(heap, heapSize);

        printf("\n");
    }

    printf("\nFinal Output: ");

    for (int i = 0; i < outputSize; i++)
        printf("%d ", output[i]);

    printf("\n");

    printf("Number of key comparisons = %d\n", heapComparisons);
}


/* =========================
   PAIRWISE MERGE
   ========================= */

int merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < n1 && j < n2)
    {
        pairComparisons++;

        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];

    return k;
}

void pairwiseMerge(int lists[K][MAX], int sizes[K])
{
    int temp[MAX * K];
    int result[MAX * K];

    printf("\n===== PAIRWISE MERGING =====\n");

    /* Merge L1 and L2 */
    int size12 = merge(
        lists[0], sizes[0],
        lists[1], sizes[1],
        temp
    );

    printf("After merging L1 and L2: ");

    for (int i = 0; i < size12; i++)
        printf("%d ", temp[i]);

    printf("\n");

    /* Merge result with L3 */
    int finalSize = merge(
        temp, size12,
        lists[2], sizes[2],
        result
    );

    printf("After merging with L3: ");

    for (int i = 0; i < finalSize; i++)
        printf("%d ", result[i]);

    printf("\n");

    printf("Number of key comparisons = %d\n",
           pairComparisons);
}


/* =========================
   MAIN
   ========================= */

int main()
{
    int lists[K][MAX] =
    {
        {10, 30, 50, 70},
        {20, 40, 60, 80},
        {15, 35, 55, 75}
    };

    int sizes[K] = {4, 4, 4};

    kWayMerge(lists, sizes);

    pairwiseMerge(lists, sizes);

    printf("\n===== FINAL COMPARISON =====\n");

    printf("Min Heap comparisons : %d\n",
           heapComparisons);

    printf("Pairwise comparisons : %d\n",
           pairComparisons);

    return 0;
}
