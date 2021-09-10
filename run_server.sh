. ./env.sh
sudo env LD_LIBRARY_PATH=$LD_LIBRARY_PATH ./fserver -db_type ycsb -model_config=ae_scripts/ycsb-model.toml -threads 20
