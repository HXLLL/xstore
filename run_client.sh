. ./env.sh
sudo env LD_LIBRARY_PATH=$LD_LIBRARY_PATH gdb --args ./ycsb -workloads ycsba -threads 1 -server_host 192.168.2.1 -nic_base 2
