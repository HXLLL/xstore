#!/usr/bin/env python

from gnuplot import *

"""
Experiment setup
24 threads, 1 server, 15 clients, 1 coroutine per client
`cmd: ./run.py  -st 24 -cc 1 -w ycsba -t 24  -sa "-db_type ycsbh -ycsb_num 10000000" -ca='-total_accts=10000000 -need_hash -eval_type=sc -tree_depth=6' -e 60 -n 15 -c s -a "ycsb" -s val00`

learned.toml
`
[[stages]]
type = "lr"
parameter = 1

[[stages]]
type = "lr"
## typically, they use much larger models
#parameter = 400000
parameter = 1000000
`

"""

xstore = {
    1: (3750855.56,6.54774),
    2 : (7150276.82, 6.58275),
    4 : (13567294.79,6.82185),
    6 : (19699885.95,7.10576),
#    8: (23988259, 7.86658),
    15 : (24827238.63,14.2637),
    152 : (29380676.62,25.5826),
    154:  (29424242.72,50.635),
    156 : ( 28562286.61, 75.0706),
    }

rpc = {
    1: (4866489.74,6.11602),
#    2: (),
    15: (22449122.09,15.7837),
    156: (23295129.07,85.7702),
    }

xstore = {
    11 : (3623298.93,6.3392),
    21 : (7082760.25,6.49203),
    41 : (13562615.16,6.96724),
    61 : (19319857.55,6.91944),
    62 : (26937511.86,10.8697),
    64 : (29277256.82,18.497),
    66 : (29658386.84,28.1448),
    68 : (29066344.39,35.8582),
    }

rpc = {
    11 : (5574072.60,3.99639),
    21 : (10742527.60,4.34827),
    41 : (18878668.91,4.92472),
    61 : (22067245.93,6.4352),
    62 : (27161447.98,10.7301),
    64 : (28360735.97,20.404),
    66 : (28535142.36,31.6442),
    68 : (27632411.46,42.9006),
    }

btree = {
    11 : (1392750.51,16.4555),
    21 : (2698868.02,17.3585),
    41 : (4455245.11,21.1632),
    61 : (5261073.36,28.6845),
    62 : (6703721.94,44.4585),
    64 : (7881429.73,72.8179),
    66 : (7723429.55,111.776),
    68 : (7886837.53,150.298)
    }

ylim = 72

def main():
    # convert the results to gnuplot format
    output_res_2("ycsbb",xstore,rpc,btree)

if __name__ == "__main__":
    main()
