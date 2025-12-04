import sys


def error(msg: str):
    print(msg, file=sys.stderr)
    exit(84)


if sys.argv.__len__() < 2:
    error(f"USAGE: {sys.argv[0]} <input file>")

with open(sys.argv[1], "r") as stream:
    lines = stream.readline().strip()
    stream.close()

ranges = lines.split(",")
invalid_ids = []
for r in ranges:
    start, end = map(int, r.split("-"))
    for num in range(start, end + 1):
        s = str(num)
        length = len(s)
        if length % 2 == 0:
            half = length // 2
            if s[:half] == s[half:]:
                invalid_ids.append(num)

print(sum(invalid_ids))
