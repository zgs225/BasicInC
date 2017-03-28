# -*- coding: utf-8 -*-


def heapsort(arr):
    """
    堆排序
    """
    _build_max_heap(arr)
    i = len(arr) - 1
    heap_size = i

    while i > 1:
        arr[i], arr[1] = arr[1], arr[i]
        _max_heapify(arr, heap_size, 1)
        heap_size -= 1
        i -= 1


def _build_max_heap(arr):
    i = len(arr) / 2
    size = len(arr)
    while i > 0:
        _max_heapify(arr, size, i)
        i -= 1


def _max_heapify(arr, size, i):
    l = _left(i)
    r = _right(i)

    if l < size and arr[l] > arr[i]:
        largest = l
    else:
        largest = i

    if r < size and arr[r] > arr[largest]:
        largest = r

    if i != largest:
        arr[i], arr[largest] = arr[largest], arr[i]
        _max_heapify(arr, size, largest)


def _left(i):
    return ((i + 1) << 1) - 1


def _right(i):
    return (i + 1) << 1


if __name__ == '__main__':
    import random
    import datetime

    arr = []
    count = 100000
    for _ in range(count):
        arr.append(random.randint(-count, count))
    begin = datetime.datetime.now()
    heapsort(arr)
    end = datetime.datetime.now()
    delta = end - begin
    print 'sort count elements take %f seconds' % delta.total_seconds()
