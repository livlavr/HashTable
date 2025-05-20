import sys

s = set()
line = sys.stdin.readline().strip()
n = int(line)

for _ in range(n):
    parts = sys.stdin.readline().strip().split(maxsplit=1)
    if len(parts) != 2:
        continue

    op, key = parts
    if op == '+':
        s.add(key)
    elif op == '-':
        s.discard(key)
    elif op == '?':
        print("YES" if key in s else "NO")
