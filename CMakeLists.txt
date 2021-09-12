cmake_minimum_required(VERSION 3.2)
project(xxx)
ADD_DEFINITIONS(-std=c++14)
include(deps/deps.cmake)
include_directories("src")
include_directories("deps")
set(CMAKE_CXX_FLAGS "-O2 -g -mrtm -fgnu-tm")
file(GLOB fserver_SORUCES ""  "server/main.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "server/loaders/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(fserver ${fserver_SORUCES} )
add_dependencies(fserver jemalloc boost )

find_library(jemalloc_lib NAMES jemalloc PATHS ./deps/jemalloc PATH_SUFFIXES lib
               NO_DEFAULT_PATH)

if(NOT jemalloc_lib)

	set(jemalloc_lib "")

endif()


find_library(boost_coroutine_lib NAMES boost_coroutine PATHS ./deps/boost PATH_SUFFIXES lib
               NO_DEFAULT_PATH)

if(NOT boost_coroutine_lib)

	set(boost_coroutine_lib "")

endif()


find_library(boost_system_lib NAMES boost_system PATHS ./deps/boost PATH_SUFFIXES lib
               NO_DEFAULT_PATH)

if(NOT boost_system_lib)

	set(boost_system_lib "")

endif()


find_library(mkl_rt_lib NAMES mkl_rt PATHS /opt/intel/oneapi/mkl/2021.3.0 PATH_SUFFIXES lib/intel64
               NO_DEFAULT_PATH)

if(NOT mkl_rt_lib)

	set(mkl_rt_lib "")

endif()

target_link_libraries(fserver gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} ${mkl_rt_lib} )
file(GLOB micro_SORUCES ""  "benchs/micro/*.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(micro ${micro_SORUCES} )
add_dependencies(micro jemalloc boost )
target_link_libraries(micro gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} ${mkl_rt_lib} )
file(GLOB ycsb_SORUCES ""  "benchs/ycsb/*.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(ycsb ${ycsb_SORUCES} )
add_dependencies(ycsb jemalloc boost )
target_link_libraries(ycsb gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} ${mkl_rt_lib} )
file(GLOB rc_server_SORUCES ""  "benchs/micro/rc_server.cpp"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc"  "deps/rocksdbb/port/stack_trace.cc" )
add_executable(rc_server ${rc_server_SORUCES} )
add_dependencies(rc_server jemalloc boost )
target_link_libraries(rc_server gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB nullc_SORUCES ""  "benchs/micro/null_client.cpp"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc"  "deps/rocksdbb/port/stack_trace.cc" )
add_executable(nullc ${nullc_SORUCES} )
add_dependencies(nullc jemalloc boost )
target_link_libraries(nullc gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB master_SORUCES ""  "benchs/bench_master.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(master ${master_SORUCES} )
add_dependencies(master jemalloc boost )
target_link_libraries(master gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB pp_server_SORUCES ""  "benchs/pingpong/server.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(pp_server ${pp_server_SORUCES} )
add_dependencies(pp_server jemalloc boost )
target_link_libraries(pp_server gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB pp_client_SORUCES ""  "benchs/pingpong/client.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(pp_client ${pp_client_SORUCES} )
add_dependencies(pp_client jemalloc boost )
target_link_libraries(pp_client gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB pp_SORUCES ""  "benchs/pingpong/aclient.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(pp ${pp_SORUCES} )
add_dependencies(pp jemalloc boost )
target_link_libraries(pp gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB ppr_SORUCES ""  "benchs/pingpong/aclient_rdma.cc"  "deps/r2/src/*.cc"  "deps/r2/src/rpc/*.cc"  "deps/r2/src/msg/*.cc" )
add_executable(ppr ${ppr_SORUCES} )
add_dependencies(ppr jemalloc boost )
target_link_libraries(ppr gflags ${jemalloc_lib} pthread ibverbs ${boost_coroutine_lib} ${boost_system_lib} )
file(GLOB zip_SORUCES ""  "benchs/kv/zipfan.cpp" )
add_executable(zip ${zip_SORUCES} )
file(GLOB mc_perf_SORUCES ""  "benchs/mallocs/main.cc"  "src/utils/*.cc"  "deps/r2/src/logging.cc" )
add_executable(mc_perf ${mc_perf_SORUCES} )
add_dependencies(mc_perf jemalloc )
target_link_libraries(mc_perf gflags ${jemalloc_lib} pthread )
file(GLOB tpcc_SORUCES ""  "benchs/kv/tpcc_distribution.cpp"  "deps/r2/src/logging.cc" )
add_executable(tpcc ${tpcc_SORUCES} )
target_link_libraries(tpcc gflags )
file(GLOB micro_local_kv_SORUCES ""  "src/*.cc"  "benchs/kv/local_perf.cc"  "benchs/kv/flags.cc"  "deps/r2/src/logging.cc" )
add_executable(micro_local_kv ${micro_local_kv_SORUCES} )
target_link_libraries(micro_local_kv rocksdb ${mkl_rt_lib} gflags pthread )
file(GLOB micro_dynamic_SORUCES ""  "src/*.cc"  "benchs/kv/dynamic.cc"  "benchs/kv/flags.cc"  "deps/r2/src/logging.cc" )
add_executable(micro_dynamic ${micro_dynamic_SORUCES} )
target_link_libraries(micro_dynamic rocksdb ${mkl_rt_lib} gflags pthread )
file(GLOB ycsb_single_SORUCES ""  "benchs/ycsb/single_node.cpp"  "deps/r2/src/logging.cc" )
add_executable(ycsb_single ${ycsb_single_SORUCES} )
target_link_libraries(ycsb_single gflags pthread )
file(GLOB analysis_SORUCES ""  "src/*.cc"  "benchs/kv/analysis.cpp"  "benchs/kv/flags.cc"  "deps/r2/src/logging.cc" )
add_executable(analysis ${analysis_SORUCES} )
target_link_libraries(analysis rocksdb ${mkl_rt_lib} gflags pthread )
file(GLOB scan_analysis_SORUCES ""  "src/*.cc"  "benchs/kv/scan_analysis.cpp"  "benchs/kv/flags.cc"  "deps/r2/src/logging.cc" )
add_executable(scan_analysis ${scan_analysis_SORUCES} )
target_link_libraries(scan_analysis rocksdb ${mkl_rt_lib} gflags pthread )
include(tests/tests.cmake)

add_custom_target(mytest)
add_dependencies(mytest fserver master ycsb)

## tests
enable_testing()

add_test(NAME test COMMAND coretest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose
                  DEPENDS coretest )

