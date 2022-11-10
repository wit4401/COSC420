# This file helped me to create the files to test my socialNetwork.java
# program using hadoop inserting random relationships into a file data.txt
import random

def rand_nums():
    retval=[]
    while len(retval)<=3:
        num=random.randint(1,10000)
        flag=True
        for i in retval:
            if num==i:
                flag=False
                break
        if flag:
            retval.append(num)
    return retval

file1 = open('data.txt','w')
L=[]

for i in range(1,10001):
    line=""
    rand=rand_nums()
    line= str(i)+" "+str(rand[0])+" "+str(rand[1])+" "+str(rand[2]) + "\n"
    L.append(line)

file1.writelines(L)
file1.close()