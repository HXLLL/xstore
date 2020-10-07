#!/usr/bin/env python

"""

the configuration uses similar to ycsbd.py

./run.py  -st 24 -cc 1 -w ycsba -t 24  -sa "-db_type dummy -ycsb_num 10000000" -ca='-total_accts=10000000 -need_hash -workloads=dynamic_scan' -e 60 -n 15 -c s -a "micro" -s val00

"""

from common import *
from gnuplot import *

xstore_points = [(1.04006e+06,0,0,),(4.39332e+06,0,0,),(4.15846e+06,0,0,),(4.265e+06,0,0,),(3.84876e+06,0,0,),(4.00662e+06,0,0,),(3.99326e+06,0,0,),(3.88143e+06,0,0,),(4.03878e+06,0,0,),(3.80569e+06,0,0,),(3.81935e+06,0,0,),(3.96669e+06,0,0,),(3.75071e+06,0,0,),(3.87292e+06,0,0,),(3.97893e+06,0,0,),(3.72453e+06,0,0,),(3.87881e+06,0,0,),(3.79708e+06,0,0,),(3.70682e+06,0,0,),(3.80412e+06,0,0,),(3.92211e+06,0,0,),(3.72072e+06,0,0,),(3.79372e+06,0,0,),(3.91805e+06,0,0,),(3.6808e+06,0,0,),(3.76694e+06,0,0,),(3.78071e+06,0,0,),(3.66644e+06,0,0,),(3.78931e+06,0,0,),(3.81788e+06,0,0,),(3.66732e+06,0,0,),(3.7897e+06,0,0,),(3.85497e+06,0,0,),(3.66103e+06,0,0,),(3.75703e+06,0,0,),(3.74136e+06,0,0,),(3.65329e+06,0,0,),(3.72726e+06,0,0,),(3.80936e+06,0,0,),(3.6283e+06,0,0,),(3.69116e+06,0,0,),(3.76313e+06,0,0,),(3.62545e+06,0,0,),(3.65098e+06,0,0,),(3.72548e+06,0,0,),(3.7852e+06,0,0,),(3.64198e+06,0,0,),(3.70614e+06,0,0,),(3.77872e+06,0,0,),(3.58465e+06,0,0,),(3.64247e+06,0,0,),(3.73922e+06,0,0,),(3.62628e+06,0,0,),(3.61266e+06,0,0,),(3.70294e+06,0,0,),(3.69094e+06,0,0,),(3.55629e+06,0,0,),(3.64294e+06,0,0,),(3.72548e+06,0,0,),(3.59249e+06,0,0,),]

rpc_points = [(222455,0,0,),(2.19827e+06,0,0,),(2.19085e+06,0,0,),(2.19055e+06,0,0,),(2.18365e+06,0,0,),(2.17985e+06,0,0,),(2.18033e+06,0,0,),(2.17324e+06,0,0,),(2.17773e+06,0,0,),(2.17451e+06,0,0,),(2.17693e+06,0,0,),(2.1765e+06,0,0,),(2.17347e+06,0,0,),(2.17267e+06,0,0,),(2.17092e+06,0,0,),(2.17019e+06,0,0,),(2.16716e+06,0,0,),(2.16904e+06,0,0,),(2.16356e+06,0,0,),(2.16809e+06,0,0,),(2.16999e+06,0,0,),(2.16657e+06,0,0,),(2.1662e+06,0,0,),(2.16873e+06,0,0,),(2.16654e+06,0,0,),(2.16581e+06,0,0,),(2.16672e+06,0,0,),(2.16216e+06,0,0,),(2.16045e+06,0,0,),(2.16431e+06,0,0,),(2.16842e+06,0,0,),(2.16455e+06,0,0,),(2.16293e+06,0,0,),(2.16032e+06,0,0,),(2.15999e+06,0,0,),(2.16065e+06,0,0,),(2.16517e+06,0,0,),(2.16157e+06,0,0,),(2.15882e+06,0,0,),(2.16091e+06,0,0,),(2.16168e+06,0,0,),(2.15861e+06,0,0,),(2.15696e+06,0,0,),(2.1587e+06,0,0,),(2.15914e+06,0,0,),(2.15492e+06,0,0,),(2.15382e+06,0,0,),(2.15249e+06,0,0,),(2.14859e+06,0,0,),(2.15265e+06,0,0,),(2.15124e+06,0,0,),(2.15132e+06,0,0,),(2.15423e+06,0,0,),(2.15216e+06,0,0,),(2.15451e+06,0,0,),(2.14961e+06,0,0,),(2.15098e+06,0,0,),(2.15113e+06,0,0,),(2.15264e+06,0,0,),(2.15241e+06,0,0,),]

xstore_thpts = extract_one_dim(xstore_points,0)
rpc_thpts    = extract_one_dim(rpc_points,0)

ylabel = "Thpt (K reqs/sec)"
ylim = 5000

legends = ["Xstore","RPC"]

## pre_processing the data
xstore_thpts = divide_all(xstore_thpts[1:-1],1000)
rpc_thpts = divide_all(rpc_thpts[1:-1],1000)
data = [xstore_thpts,rpc_thpts]

def main():
    output_aligned_lines("ycsbe",data,legends)

if __name__ == "__main__":
    main()
