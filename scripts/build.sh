python3 magic.py config -f build-config.toml
/home/huangxl/cmake-3.21.1-linux-x86_64/bin/cmake -DCMAKE_PREFIX_PATH=/home/huangxl/libtorch/share/cmake/Torch/ .
make boost
cd deps/jemalloc/
autoconf
cd ../..
make jemalloc
cmake .
make