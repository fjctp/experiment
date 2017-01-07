#!/usr/bin/python3
import os.path
from time import ctime
from multiprocessing import Pool
from subprocess import call

# Define variables
HOME = "/home/pi/workplace"
BIN = os.path.join(HOME, "bin")
PY = os.path.join(HOME, "py")
CONVERTER_EXE = os.path.join(BIN, "convert_video")
VIDEOS_LIST_FILE_PATH = os.path.join(PY, "videos_list") # a list of videos for converting

MAX_TASKS_PER_CHILD = 4
THREADS_USED = "4"
PARALLEL_PROCESS_USED = 1

def on_complete(result):
    print("%s Done!"%ctime())

def worker(path, ext):
    args = [CONVERTER_EXE, THREADS_USED, path, ext]
    print("%s Started: %s"%(ctime(), args))
    call(args)

if __name__ == "__main__":
    with open(VIDEOS_LIST_FILE_PATH, "r") as f:
        p = Pool(processes=PARALLEL_PROCESS_USED, maxtasksperchild=MAX_TASKS_PER_CHILD)
        for line in f:
            src_abs_file_path = line.replace("\n", "").replace("\r", "")
            (root, ext) = os.path.splitext(src_abs_file_path)
            dst_abs_file_path = src_abs_file_path.replace(ext, ".mp4")
            if(os.path.exists(dst_abs_file_path) != True):
                p.apply_async(worker, args=(src_abs_file_path, ext), callback=on_complete)
        print("%s Batch Started"%ctime())

    p.close() # stop accepting new job
    p.join() # join the main thread so that the main wont be closed
