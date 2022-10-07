# Will Townsend
# Programming Assignment 1
# COSC 420
# 
# This programming uses multithreading to estimate pi using the 
# Mote Carlo method. Prompt is as follows:
# 
# Suppose we toss darts randomly at a square dartboard, whose bullseye 
# is at the origin, and whose sides are 2 feet in legth. Suppose also 
# that there's a circle inscribed in the square dart board. The radius 
# of the circle is 1 foot, and its area is 'pi' square feet. If the points 
# that are hit by the darts uniformly distributed (and we always hit the
# square), then the number of darts that hit inside should satisfy the equation:
#
# (# of darts in circle)/(total # of darts) = 'pi'/4
# 
# since the ratio of the area of the circle to the area of the square is 'pi'/4.

import math
import random
import time
import threading
import matplotlib.pyplot as plt

# the actual Monte Carlo to estimate pi (will eventually just return # of hits)
def piEstimate(tosses):
    circleHits = 0
    for i in range(0,tosses,1):
        x = random.uniform(-1.0, 1.0)
        y = random.uniform(-1.0, 1.0)
        test = x**2+y**2
        if test <= 1:
            circleHits+=1
    return 4*(circleHits/tosses)

tests = [10,100,1000,10000,100000,1000000,10000000,100000000]
for x in tests:
    begin = time.time()
    approx = piEstimate(x)
    print('Monte Carlo ({}) {}'.format(x, approx))
    print('Absolute Error {}'.format(abs(math.pi-approx)))
    print('Runtime: {:5.5f} sec\n'.format(time.time()-begin))

print('\nActual Pi: {}'.format(math.pi))
