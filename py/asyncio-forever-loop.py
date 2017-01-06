#!/usr/bin/env python

import asyncio
import logging

async def periodic_worker(loop):
    wait_sec = 1.0
    while True:
        t0 = loop.time()
        await asyncio.sleep(wait_sec)
        delta_t = loop.time()-t0
        print('Delta T: %.3fs, Error: %.2fms'%(delta_t, (delta_t-wait_sec)*1000))

def main():
    logging.getLogger('asyncio').setLevel(logging.WARNING)
    loop = asyncio.get_event_loop()
    
    task = asyncio.ensure_future(periodic_worker(loop), loop=loop)
    try:
        loop.run_forever()
    finally:
        loop.close()

if __name__=='__main__':
    main()
