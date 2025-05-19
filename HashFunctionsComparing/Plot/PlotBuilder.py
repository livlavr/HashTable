import numpy as np
import matplotlib.pyplot as plt

def main():
    files = {
        '../TestsResults/SumHashResults.txt': 'SumHash',
        '../TestsResults/PolynomialHashResults.txt': 'PolynomialHash',
        '../TestsResults/Crc32HashResults.txt': 'Crc32Hash',
        '../TestsResults/Crc32HashOptimizedResults.txt': 'Crc32HashOptimized',
        '../TestsResults/Crc32HashIntrinsicsResults.txt': 'Crc32HashIntrinsics',
    }

    for path, name in files.items():
        try:
            parts = open(path).read().split()
        except FileNotFoundError:
            print(f'Не найден {path}')
            continue

        n = int(parts[0])
        runtime = float(parts[1])
        data = list(map(int, parts[2:]))
        loads = np.zeros(n, int)
        for i, cnt in zip(data[0::2], data[1::2]):
            loads[i] = cnt

        sigma = np.std(loads)
        x = np.arange(n)

        plt.figure(figsize=(8,4))
        plt.bar(x, loads, color='orange')
        plt.grid(True, linestyle='--', alpha=0.5)
        plt.title(name)
        plt.xlabel('Индекс ячейки')
        plt.ylabel('Количество элементов')
        plt.text(0.95, 0.01, f'σ={sigma:.2f}, t={runtime:.0f} ticks',ha='right', va='bottom', transform=plt.gca().transAxes)
        plt.tight_layout()
        plt.savefig(f'img/{name}.png', dpi=300)
        plt.close()
        print(f'Сохранён {name}.png')

if __name__ == "__main__":
    main()
