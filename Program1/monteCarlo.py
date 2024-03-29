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

# the actual Monte Carlo to estimate pi (will eventually just return # of hits)
def piEstimate(tosses):
    global hits
    circleHits = 0
    for i in range(0,tosses,1):
        x = random.uniform(-1.0, 1.0)
        y = random.uniform(-1.0, 1.0)
        test = x**2 + y**2
        if test <= 1:
            circleHits += 1
    hits += circleHits #add to global variable for parallel implementation
    return circleHits # return vale for serial portion

if __name__=="__main__":
    print('Enter # of Tosses: ',end='')
    tosses = int(input())
    print('Enter # of Threads: ',end='')
    threadNum = int(input())
    
    delta = round(tosses/threadNum)
    remainder = tosses%threadNum
    
    parallelTimes=[]
    serialTimes=[]
    print('')
    for i in range(0,10):
        threads = []
        # if statement for threads dividing evenly into the number of tosses
        if remainder == 0:
            # creates our thread list and assigns how many tosses to simulate
            for j in range(0,threadNum,1):
                threads.append(threading.Thread(target=piEstimate,args=(delta,)))
        else: # if the threads do not divide evenly into number of tosses
            arr = [] # initialize array for the number of tosses to be assigned to each thread
            # apply delta to every index
            for j in range(0,threadNum,1):
                arr.append(delta)
            # gets the correct number of tosses for each thread by dividing out the remainder
            for j in range(0,remainder):
                arr[j] += 1
            #creates the threads
            for j in range(0,threadNum,1):
                threads.append(threading.Thread(target=piEstimate,args=(arr[j],)))
    
        hits = 0
        begin = time.time() # stores current time
        # start each respective thread and calls the join function to wait until all threads are complete
        for x in threads:
            x.start() 
            x.join()
        print('parallel pi estimate #{}: {}'.format(i+1,4*hits/tosses))
        end = time.time() # stores time after execution
        parallelTimes.append(end-begin)

        beign=time.time()
        result = 4*(piEstimate(tosses)/tosses)
        print('serial pi estimate #{}: {}\n'.format(i+1,result))
        end=time.time()
        serialTimes.append(end-begin)
    
    serialSum=0
    for time in serialTimes:
        serialSum+=time
    sAvg=serialSum/len(serialTimes) 
    print('Average Serial Runtime: {}'.format(sAvg))

    parallelSum=0
    for time in parallelTimes:
        parallelSum+=time
    pAvg=parallelSum/len(parallelTimes)
    print('Average Parallel Runtime: {}'.format(pAvg))

    print('Speedup: {}'.format(sAvg/pAvg))
    print('Efficiency: {}'.format(sAvg/(threadNum*pAvg)))


