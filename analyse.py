import numpy as np
from matplotlib import pyplot as plt
import pandas as pd
import struct


def analyse_output():
    file = open("./data/out.binary")
    n = 2*1000000
    data = struct.unpack('f'*n, file.read(4*n))
    data = np.array(data).reshape(1000000, 2)
    data = data[~np.all(data == 0, axis=1)]
    print "Gradient = %.04f +/- %.04f" % (np.mean(data[:, 0]),
                                          np.std(data[:, 0]))
    print "Drift velocity = %.05f +/- %.05f" % (np.mean(data[:, 1]),
                                                np.std(data[:, 1]))
    # plt.hist(data[:, 0], bins=40)
    # plt.show()
    # plt.hist(data[:, 1], bins=60)
    # plt.show()


def analyse_count():
    df = pd.read_csv("./data/count")
    data = df.values
    nm = data[~np.any(data == 100, axis=1)]
    print "Mean iterations: %.01f | std: %.01f" % (np.mean(nm), np.std(nm))
    print "Track rejection: %.02f%% " % (
        float(np.count_nonzero(data == 100))/len(data)*100
    )
    # plt.hist(nm, bins=100)
    # #plt.yscale('log')
    # plt.show()


def main():
    # analyse_count()
    analyse_output()


if __name__ == '__main__':
    main()
