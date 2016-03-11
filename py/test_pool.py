#!/usr/bin/python3

from multiprocessing import Pool
from time import sleep
from time import ctime

def f(x):
  print("%s Sleep for %ssec"%(ctime(), x))
  sleep(x)
  print("%s Sleep for %ssec Done"%(ctime(), x))

if __name__ == "__main__":
  p = Pool(2)
  for i in range(10):
    p.apply_async(f, args=(i,))
  print("%s Start"%ctime())
  p.close()
  p.join()  
