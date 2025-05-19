import random
import string

chars = string.ascii_letters
strings = [''.join(random.choices(chars, k=random.randint(3, 31))) for _ in range(100000)]
with open('TestsSrc/Tests.txt', 'w') as f:
    f.write("100000\n")
    f.write('\n'.join(strings))
