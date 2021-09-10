. ./env.sh
sudo env LD_LIBRARY_PATH=$LD_LIBRARY_PATH ./ycsb -workloads ycsbb -threads 12 -server_host 192.168.2.1
