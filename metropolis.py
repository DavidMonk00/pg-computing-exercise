import numpy as np
import copy


track = np.array([
    [0, 2, 4.25],
    [1, 2.5, 90.25],
    [2, 2, 18.75],
    [3, 2.5, 66.75],
    [4, 2, 41.75],
    [5, 2.5, 43.75],
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


def metrolpolis(track, r, alpha, N):
    counter = 0
    P = [track[0][:2], track[7][:2]]
    e_prev = [abs(i[2] - distanceFromLine(i[:2], P)/r[0]) for i in track]
    for i in range(N):
        counter += 1
        r_new = r[0] + alpha*np.random.random()*np.random.choice([-1, 1])
        P_new = copy.deepcopy(P)
        for i in P_new:
            i[1] += 0.1*np.random.random()*np.random.choice([-1, 1])
        e = [abs(i[2]*r_new - distanceFromLine(i[:2], P_new)) for i in track]
        if (np.mean(e) < np.mean(e_prev)):
            r[0] = r_new
            e_prev = e
            P = copy.deepcopy(P_new)
        elif(np.random.random() < 0.001):
            r[0] = r_new
            e_prev = e
            P = copy.deepcopy(P_new)
        if (np.mean(e) < 0.01):
            break
    print(r[0], counter)
    return e


def main():
    r = [0.005, track[0][2]]
    for i in [10, 100, 1000, 10000]:
        e = metrolpolis(track, r, 0.001, 150)
        print(np.mean(e))


if __name__ == '__main__':
    main()
