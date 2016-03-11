# Window version
# Rename files in Folder to have a standized name

import os
import shutil
root = 'Path\\To\\Folder'
for i in os.listdir(root):
    if('ssa' in i):
        tmp = i.split('-')
        if len(tmp) > 1:
            ep = tmp[1].zfill(2)

            name = 'Standized Name %s.ssa'%ep
            src = root + '\\' + i
            dst = root + '\\' + name
            
            print('move %s to %s'%(i, name))
            shutil.move(src,dst)
        
