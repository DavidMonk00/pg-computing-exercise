import numpy as np
from struct import unpack
from sys import argv


class Analytics:
    n = 2000000

    def analyseOutput(self):
        file = open("./data/out.binary", "rb")
        data = unpack('f'*self.n, file.read(4*self.n))
        data = np.array(data).reshape(1000000, 2)
        self.data = data[~np.all(data < 1e-10, axis=1)]
        print "Gradient = %.04f +/- %.04f" % (np.mean(self.data[:, 0]),
                                              np.std(self.data[:, 0]))
        print "Drift velocity = %.05f +/- %.05f" % (np.mean(self.data[:, 1]),
                                                    np.std(self.data[:, 1]))

    def analyseCount(self):
        try:
            import pandas as pd
        except ImportError:
            raise ImportError("This is 2018...")
        df = pd.read_csv("./data/count")
        data = df.values
        self.nm = data[~np.any(data == 100, axis=1)]
        print "Mean iterations: %.01f | std: %.01f" % (np.mean(self.nm),
                                                       np.std(self.nm))
        print "Track rejection: %.02f%% " % (
            float(np.count_nonzero(data == 100))/len(data)*100
        )
        try:
            from matplotlib import pyplot as plt
            plt.hist(self.nm, bins=100)
            # plt.yscale('log')
            plt.show()
        except ImportError:
            raise ImportError("Why is matplotlib not installed??")

    def plotGradient(self):
        try:
            from matplotlib import pyplot as plt
        except ImportError:
            raise ImportError("Why is matplotlib not installed??")
        try:
            plt.hist(self.data[:, 0], bins=40)
            plt.show()
        except AttributeError:
            self.analyseOutput()
            plt.hist(self.data[:, 0], bins=40, normed=True)
            plt.show()

    def plotDriftVelocity(self):
        try:
            from matplotlib import pyplot as plt
        except ImportError:
            raise ImportError("Why is matplotlib not installed??")
        try:
            plt.hist(self.data[:, 1], bins=40)
            plt.show()
        except AttributeError:
            self.analyseOutput()
            plt.hist(self.data[:, 1], bins=40, normed=True)
            plt.show()


def main():
    a = Analytics()
    a.analyseOutput()
    try:
        if (argv[1] == "plot"):
            a.plotGradient()
            a.plotDriftVelocity()
    except IndexError:
        pass


if __name__ == '__main__':
    main()
