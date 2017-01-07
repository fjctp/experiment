
from multiprocessing import Pool
from multiprocessing import current_process

def calc(n):
  sum = 0
  for i in range(n):
    sum = sum + i;
  print('%s, %s'%(n, sum))

def init():
  print("start %s"%current_process().name)

if __name__ == '__main__':

  p = Pool(initializer=init)
  p.map(calc, [10000,2000,300,400,500,600,700,800,900,1000,1010])
  p.close()
  p.join()
