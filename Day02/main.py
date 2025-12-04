import sys
import bisect


def error(msg: str) -> None:
    print(msg, file=sys.stderr)
    exit(84)


def get_file_content(filename: str) -> str:
    with open(filename, "r") as f:
        return f.readline().strip()


def get_ranges_from_file(filename: str) -> list[tuple[int, int]]:
    content = get_file_content(filename)
    ranges = []
    for part in content.split(","):
        start, end = map(int, part.split("-"))
        ranges.append((start, end))

    ranges.sort()
    return ranges


def is_in_ranges(n: int) -> bool:
    i = bisect.bisect_right(starts, n) - 1
    if i < 0:
        return False
    return n <= ends[i]


if len(sys.argv) != 2:
    error(f"USAGE: python3 {sys.argv[0]} <input_file>")

ranges = get_ranges_from_file(sys.argv[1])
starts = [r[0] for r in ranges]
ends = [r[1] for r in ranges]


invalid_sum = 0

min_len = min(len(str(r[0])) for r in ranges)
max_len = max(len(str(r[1])) for r in ranges)

for line in range(min_len, max_len + 1):

    if line % 2 == 1:
        continue

    half = line // 2
    start = 10 ** (half - 1)
    end = 10**half

    for x in range(start, end):
        s = str(x)
        candidate = int(s + s)
        if is_in_ranges(candidate):
            invalid_sum += candidate

print(invalid_sum)
