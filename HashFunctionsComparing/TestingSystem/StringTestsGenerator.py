#!/opt/homebrew/bin/python3

import random
import string

chars = string.ascii_lowercase
strings = [''.join(random.choices(chars, k=random.randint(5, 20))) for _ in range(1000000)]
with open('TestsSrc/StringTests.txt', 'w') as f:
    f.write("1000000\n")
    f.write('\n'.join(strings))
