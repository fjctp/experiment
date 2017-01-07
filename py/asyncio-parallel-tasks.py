#!/usr/bin/env python

import asyncio
import logging

async def worker(loop, name, sec):
    await asyncio.sleep(sec)
    print('{} hello'.format(name))

def main():
    logging.getLogger('asyncio').setLevel(logging.WARNING)
    loop = asyncio.get_event_loop()
    
    tasks = [
        asyncio.ensure_future(worker(loop, 'A', 3)),
        asyncio.ensure_future(worker(loop, 'B', 4)),
        asyncio.ensure_future(worker(loop, 'C', 2)),]
    try:
#        loop.run_forever()
        loop.run_until_complete(asyncio.gather(*tasks))
    finally:
        loop.close()

if __name__=='__main__':
    main()
