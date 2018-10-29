# Introduction

## The Algorithm
A track can be defined by three parameters: the gradient, y-intercept and drift
velocity. The former two parameters can be controlled by considering two
independent points on the track and varying the y co-ordinates of these points.
The drift velocity is then varied independently. These three parameters thus
form a three-dimensional parameter space in which the error is minimised:

![e = F(y0, y1, v)](/home/david/computing/project/doc/CodeCogsEqn2.png)

The error for a fitted track is calculated by the distance of each wire to the
fitted track and subtracting this from the hit radius, calculated by multiplying
the drift time by the drift velocity. This error is then minimsed to achieve a
fitted track.

![e = sum(v*ti - di)](/home/david/computing/project/doc/CodeCogsEqn1.png)

In order to perform the track fitting, a modified Metropolis-Hastings has been
impelented. The full Metropolis-Hastings algorithm has been simplified such that
the probability that a step which increases the error is accepted is zero. this
has been chosen to increase the performance of the algorithm with the assumption
that the error function has no local minima. This assumption holds for all
tracks which there exists only one solution and all other tracks are rejected.

---

## Installation Notes

### Prerequisites:
- Python analysis requires `numpy` and `matplotlib`
- C++11 compatible compiler

### Optional Libraries
- Algorithm efficiency analysis requires the `pandas` library


---

## Running the Algorithm
- Copy project directory
- Go to the directory: `cd project`
- Compile the project: `make`
- Run fitting algorithm: `./bin/main`
- Run analysis (add 'plot' as an argument for plotting): `python analyse.py`
