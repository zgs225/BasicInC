# -*- coding: utf-8 -*-


def find_max_subarray(arr):
    """
    寻找给定数据中的最大子数组

    Args:
        arr: list of numbers

    Returns:
        low, high, sum
    """
    return _find_max_subarray(arr, 0, len(arr)-1)


def _find_max_subarray(arr, low, high):
    if low == high:
        return low, high, arr[low]

    mid = (low + high) / 2
    left_low, left_high, left_sum = _find_max_subarray(arr, low, mid)
    right_low, right_high, right_sum = _find_max_subarray(arr, mid+1, high)
    cross_low, cross_high, cross_sum = _find_max_crossing_subarray(arr, low, mid, high)

    if left_sum >= right_sum and left_sum >= cross_sum:
        return left_low, left_high, left_sum
    elif right_sum >= left_sum and right_sum >= cross_sum:
        return right_low, right_high, right_sum
    else:
        return cross_low, cross_high, cross_sum


def _find_max_crossing_subarray(arr, low, mid, high):
    left_max = right_max = None
    left_sum = right_sum = 0
    left_low = right_high = None
    i = mid
    j = mid + 1

    while i >= low:
        left_sum += arr[i]
        if left_max is None or left_sum > left_max:
            left_max = left_sum
            left_low = i
        i -= 1

    while j <= high:
        right_sum += arr[j]
        if right_max is None or right_sum > right_max:
            right_max = right_sum
            right_high = j
        j += 1

    return left_low, right_high, (left_max + right_max)


def find_max_subarray_violately(arr):
    if len(arr) == 1:
        return 1, 1, arr[1]

    left = 0
    right = 1
    _sum = None

    for i in range(0, len(arr)-1):
        for j in range(1, len(arr)):
            _sum2 = sum(arr[i:j+1])
            if _sum is None or _sum2 >= _sum:
                left = i
                right = j
                _sum = _sum2

    return left, right, _sum


if __name__ == '__main__':
    import random

    arr = []

    for _ in range(1000):
        arr.append(random.randint(-100, 100))

    l, h, s = find_max_subarray(arr)
    print l, h, s
    print arr[l:h+1]

    l, h, s = find_max_subarray_violately(arr)
    print l, h, s
    print arr[l:h+1]
