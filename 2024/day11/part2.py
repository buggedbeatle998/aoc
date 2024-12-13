from functools import lru_cache


@lru_cache(maxsize=None)
def count_stones(stones, blinks):
    if blinks == 0:
        return 1

    str_stones = str(stones)
    if stones == 0:
        return count_stones(1, blinks-1)
    elif len(str_stones) % 2 == 0:
        mid = len(str_stones) // 2
        left = int(str_stones[:mid])
        right = int(str_stones[mid:])
        return count_stones(left, blinks-1) + count_stones(right, blinks-1)
    else:
        return count_stones(stones * 2024, blinks-1)

print([count_stones(int(stone), 75) for stone in "8435 234 928434 14 0 7 92446 8992692".split()])
