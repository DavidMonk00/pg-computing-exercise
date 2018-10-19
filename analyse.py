import numpy as np
from matplotlib import pyplot as plt


def analyse_output():
    a = [line.strip().split(",") for line in open("./data/output.csv")]
    a = np.array([[float(j) for j in i] for i in a])
    print(np.mean(a[:, 0]), np.std(a[:, 0]))
    print(np.mean(a[:, 1]), np.std(a[:, 1]))
    plt.hist(a[:, 0], bins=30)
    plt.show()
    plt.hist(a[:, 1], bins=60)
    plt.show()


def main():
    a = [int(line.strip()) for line in open("./data/count")]
    print np.mean(a), np.std(a)
    analyse_output()


if __name__ == '__main__':
    main()
