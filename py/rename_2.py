# Linux version
# Rename mp4 files in a folder
# Skip only digits in the mp4 file name

import os
import shutil
import re

i = 0
folder = r'Path/To/Folder'
for file in os.listdir(folder):
    ext = file[-4:]
    #print('at %s, ext: %s'%(file, ext))
    if (ext == '.mp4'):
        m = re.search("(\d+)", file)
        #print(m)
        i = m.group(1)
        src = os.path.join(folder, file)
        dst = os.path.join(folder, str(i) + '.mp4')
        print('%s > %s'%(src, dst))
        shutil.move(src, dst)
    
