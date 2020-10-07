#pragma once

#include "common.hpp"
#include "statics.hpp"
#include "utils/all.hpp"

#include "r2/src/timer.hpp"

#include <vector>
#include <unistd.h>

namespace fstore {

namespace bench {

class Reporter {
 public:
  static double report_thpt(std::vector<Statics> &statics, int epoches) {

    std::vector<Statics> old_statics(statics.size());

    r2::Timer timer;
    for(int epoch = 0;epoch < epoches;epoch += 1) {
      sleep(1);

      u64 sum = 0;
      u64 sum1 = 0;

      // now report the throughput
      for(uint i = 0;i < statics.size();++i) {
        auto temp = statics[i].data.counter;
        sum += (temp - old_statics[i].data.counter);
        old_statics[i].data.counter = temp;

        temp = statics[i].data.counter1;
        sum1 += (temp - old_statics[i].data.counter1);
        old_statics[i].data.counter1 = temp;
      }

      double passed_msec = timer.passed_msec();
      double res = static_cast<double>(sum) / passed_msec * 1000000.0;

      double res1 = static_cast<double>(sum1) / passed_msec * 1000000.0;
      r2::compile_fence();
      timer.reset();

      DISPLAY(2) << "epoch @ " << epoch
                 << ": thpt: " << fstore::utils::format_value(res,0) << " reqs/sec; "
                 << "others: " << fstore::utils::format_value(res1,0) << " num/sec;"
                 << passed_msec << " msec passed since last epoch." ;
    }
    return 0.0;
  }

};

} // namespace bench

} // namespace fstore
