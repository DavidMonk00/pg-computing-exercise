import numpy as np
from matplotlib import pyplot as plt


def main():
    a = [line.strip().split(",") for line in open("./data/output.csv")]
    a = np.array([[float(j) for j in i] for i in a])
    print(np.mean(a[:, 0]), np.std(a[:, 0]))
    print(np.mean(a[:, 1]), np.std(a[:, 1]))
    plt.hist(a[:, 0], bins=30)
    plt.show()
    plt.hist(a[:, 1], bins=60)
    plt.show()


if __name__ == '__main__':
    main()
