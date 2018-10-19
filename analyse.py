import numpy as np
#from matplotlib import pyplot as plt


def analyse_output():
    a = [line.strip().split(",") for line in open("./data/output.csv") if (line != "0,0\n")]
    a = np.array([[float(j) for j in i] for i in a])
    print "Gradient = %.04f +/- %.04f"%(np.mean(a[:, 0]), np.std(a[:, 0]))
    print "Drift velocity = %.05f +/- %.05f"%(np.mean(a[:, 1]), np.std(a[:, 1]))
    # plt.hist(a[:, 0], bins=60)
    # plt.show()
    # plt.hist(a[:, 1], bins=60)
    # plt.show()


def main():
    a = [int(line.strip()) for line in open("./data/count")]
    print "Mean iterations: %.01f | std: %.01f"%(np.mean(a), np.std(a))
    print "Track rejection: %.02f%% "%(float(a.count(250))/len(a)*100)
    # plt.hist(a, bins=100)
    # plt.show()
    analyse_output()


if __name__ == '__main__':
    main()
