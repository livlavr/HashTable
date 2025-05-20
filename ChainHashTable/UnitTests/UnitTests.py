import random
import string
import subprocess
import sys

def random_word():
    length = random.randint(1, 31)
    alphabet = string.ascii_lowercase
    return ''.join(random.choices(alphabet, k=length))

def generate_test(n):
    test = [str(n)]
    for _ in range(n):
        op = random.choices(['+', '-', '?'], weights=[4, 2, 4])[0]
        word = random_word()
        test.append(f"{op} {word}\n{'?'} {word}")
    return '\n'.join(test) + '\n'

def run_reference(test_input):
    result = subprocess.run(
        ['python3', '../../ChainHashTable/UnitTests/Reference.py'],
        input=test_input,
        capture_output=True,
        text=True
    )
    return result.stdout

def run_your_program(test_input):
    result = subprocess.run(
        ['./HashTableUnitTest'],
        input=test_input,
        capture_output=True,
        text=True
    )
    return result.stdout

def main():
    random.seed(42)
    test_count = 0
    while True:
        test_count += 1
        n = random.randint(1, 20)
        test_input = generate_test(n)

        expected = run_reference(test_input)
        actual = run_your_program(test_input)

        if expected != actual:
            print(f"FAILED TEST #{test_count}")
            print("Input:")
            print(test_input)
            print("Expected Output:")
            print(expected)
            print("Actual Output:")
            print(actual)
            with open(f"failed_test_{test_count}.txt", 'w') as f:
                f.write(test_input)
            break
        else:
            print(f"Test #{test_count} passed", end='\r')

if __name__ == "__main__":
    main()
