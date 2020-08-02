import heapq
import copy


class SortAlgos:
    def bubble_sort(self, arr):
        n = len(arr)
        for i in range(n - 1):
            for j in range(n - 1 - i):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
        return arr

    def selection_sort(self, arr):
        n = len(arr)
        for i in range(n - 1):
            min_index = i
            for j in range(i + 1, n):
                if arr[min_index] > arr[j]:
                    min_index = j
            if i != min_index:
                arr[i], arr[min_index] = arr[min_index], arr[i]
        return arr

    def insertion_sort(self, arr):
        n = len(arr)
        for i in range(1, n):
            pre_index = i - 1
            current = arr[i]
            while pre_index >= 0 and arr[pre_index] > current:
                arr[pre_index + 1] = arr[pre_index]
                pre_index -= 1
            arr[pre_index+1] = current
        return arr


class QuickSort:
    def quick_sort(self, arr, begin, end):
        if begin >= end:
            return
        pivot_index = self.quick_sort_partition(arr, begin, end)
        # print(f'arr now is {arr}')
        # print(f'pivot is {pivot_index, arr[pivot_index]}')
        self.quick_sort(arr, begin, pivot_index - 1)
        self.quick_sort(arr, pivot_index + 1, end)
        return arr

    def quick_sort_partition(self, arr, begin, end):
        pivot = end
        counter = begin
        for i in range(begin, end):
            if arr[i] < arr[pivot]:
                arr[i], arr[counter] = arr[counter], arr[i]
                counter += 1
        arr[pivot], arr[counter] = arr[counter], arr[pivot]
        return counter


class MergeSort:
    def merge_sort(self, arr, left, right):
        if right <= left: return
        mid = (left + right) >> 1
        # print(f'arr is {arr}')
        self.merge_sort(arr, left, mid)
        self.merge_sort(arr, mid+1, right)
        self.merge(arr, left, mid, right)
        return arr

    def merge(self, arr, left, mid, right):
        temp = [0 for _ in range(right - left + 1)]
        i, j, k = left, mid+1, 0
        while i <= mid and j <= right:
            if arr[i] <= arr[j]: temp[k] = arr[i]; i += 1
            else: temp[k] = arr[j]; j += 1
            k += 1
        while i <= mid:
            temp[k] = arr[i]
            k += 1; i += 1
        while j <= right:
            temp[k] = arr[j]
            k += 1; j += 1
        for p in range(len(temp)):
            arr[left + p] = temp[p]


class HeapSort:
    def heap_sort(self, arr):
        heap_arr = copy.deepcopy(arr)
        heapq.heapify(heap_arr)
        for i in range(len(arr)):
            arr[i] = heapq.heappop(heap_arr)
        return arr


if __name__ == "__main__":
    arr = [5, 2, 1, 9, 7, 6, 8, 10, 4, 15, 12, 11]
    arr_to_check = [5, 2, 1, 9, 7, 6, 8, 10, 4, 15, 12, 11]
    # s = SortAlgos()
    # bubble_sort_arr = s.bubble_sort(arr)
    # print(f'result is {bubble_sort_arr == sorted(arr_to_check)}')

    # s = SortAlgos()
    # selction_sort_arr = s.selection_sort(arr)
    # print(f'selection sort result is {selction_sort_arr == sorted(arr_to_check)}')

    # s = SortAlgos()
    # insertion_sort_arr = s.insertion_sort(arr)
    # print(insertion_sort_arr)
    # print(f'insertion sort result is {insertion_sort_arr == sorted(arr_to_check)}')

    # qs = QuickSort()
    # quick_sort_arr = qs.quick_sort(arr, 0, len(arr) - 1)
    # print(f'quick sort result is {quick_sort_arr == sorted(arr_to_check)}')

    ms = MergeSort()
    merge_sort_arr = ms.merge_sort(arr, 0, len(arr) - 1)
    print(f'merge sort result is {merge_sort_arr == sorted(arr_to_check)}')

    # hs = HeapSort()
    # heap_sort_arr = hs.heap_sort(arr)
    # print(f'heap sort result is {heap_sort_arr == sorted(arr_to_check)}')
