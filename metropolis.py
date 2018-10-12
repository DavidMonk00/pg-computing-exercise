import numpy as np


track = np.array([
    [0, 2, 4.25],
    [1, 2.5, 90.25],
    [2, 2, 18.75],
    [3, 2.5, 66.75],
    [4, 2, 471.75],
    [5, 2.5, 469.75],
    [6, 2, 64.75],
    [7, 2.5, 20.75]
])


def distanceFromLine(point, line):
    d = abs((line[1][1] - line[0][1]) * point[0] -
            (line[1][0] - line[0][0]) * point[1] + line[1][0] * line[0][1] -
            line[1][1] * line[0][0]) / np.sqrt(
                (line[1][1] - line[0][1])**2 + (line[1][0] - line[0][0])**2
            )
    return d


def main():
    v = 0.005
    P = [track[0][:2], track[7][:2]]
    P[0][1] -= 0.1
    e = [abs(i[2] - distanceFromLine(i[:2], P)/v) for i in track]
    print(np.mean(e))


if __name__ == '__main__':
    main()
