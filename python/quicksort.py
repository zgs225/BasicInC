# -*- coding: utf-8 -*-

def quicksort(arr):
    """docstring for quicksort"""
    _quicksort(arr, 0, len(arr)-1)


def _quicksort(arr, p, r):
    if p < r:
        q = _partion(arr, p, r)
        _quicksort(arr, p, q-1)
        _quicksort(arr, q+1, r)


def _partion(arr, p, r):
    x = arr[r]
    i = p - 1
    j = p

    while j < r:
        if arr[j] <= x:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        j += 1

    arr[i+1], arr[r] = arr[r], arr[i+1]

    return i + 1


if __name__ == '__main__':
    arr = [13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11]
    print arr

    print 'after quicksort:'
    quicksort(arr)
    print arr
