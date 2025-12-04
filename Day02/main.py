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


if len(sys.argv) != 2:
    error(f"USAGE: python3 {sys.argv[0]} <input_file>")

ranges = get_ranges_from_file(sys.argv[1])
starts = [r[0] for r in ranges]
ends = [r[1] for r in ranges]
min_len = min(len(str(r[0])) for r in ranges)
max_len = max(len(str(r[1])) for r in ranges)


def is_in_ranges(n: int) -> bool:
    i = bisect.bisect_right(starts, n) - 1
    if i < 0:
        return False
    return n <= ends[i]


def part_1() -> int:
    acc = 0

    for line in range(min_len, max_len + 1):

        if line % 2 == 1:
            continue

        k = line // 2

        start = 10 ** (k - 1)
        end = 10**k

        for motif in range(start, end):
            s = str(motif)
            candidate = int(s + s)
            if is_in_ranges(candidate):
                acc += candidate

    return acc


def part_2() -> int:

    acc = 0
    seen = set()

    for line in range(min_len, max_len + 1):

        divisors = [k for k in range(1, line) if line % k == 0 and line // k >= 2]

        for k in divisors:
            m = line // k

            start = 10 ** (k - 1)
            end = 10**k

            for motif_num in range(start, end):
                motif = str(motif_num)
                candidate = int(motif * m)

                if candidate not in seen and is_in_ranges(candidate):
                    acc += candidate
                    seen.add(candidate)

    return acc


print(part_1())
print(part_2())
