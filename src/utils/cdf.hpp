#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "./dist_report.hh"

namespace fstore {

namespace utils {

template <typename V>
class CDF {
 public:
  CDF(const std::string &data_name) : name(data_name) {
  }

  DistReport<V> others;

  V& operator[](uint i) {
    return all_data[index_transfer(i)];
  }

  void insert(const V&v) {
    others.add(v);
    all_data.push_back(v);
  }

  void finalize() {
    std::sort(all_data.begin(),all_data.end());
  }

  /*!
    Dump the whole DataMap as the python numpy format, which has the following format:
    X = [1,2,...,100]
    Y = [1% data,2% data,...100% data]
  */
  std::string dump_as_np_data(const std::string &ylabel = "Y",
                              const std::string &xlabel = "X") const {
    if(all_data.size() == 0)
      return "[]";

    std::ostringstream osx; osx << "X = [";
    std::ostringstream osy; osy << "Y = [";
    for(uint i = 1;i <= 99;++i) {
      osx << i << ",";
      osy << all_data[index_transfer(i)] << ",";
    }
    osx << "]"; osy << "]";
    osx << std::endl << osy.str();
    osx << std::endl << "title = \"" << name  << "\"" << std::endl;
    osx << "ylabel = \"" << ylabel << "\"" << std::endl;
    osx << "xlabel = \"" << xlabel << "\"" << std::endl;
    return osx.str();
  }

  static std::string dump_from_vec(std::vector<V> &data,
                                   const std::string &name,
                                   const std::string &ylabel = "Y",
                                   const std::string &xlabel = "X") {
    CDF<V> temp(name);
    temp.all_data = std::move(data);
    temp.finalize();
    return temp.dump_as_np_data(ylabel,xlabel);
  }

 public:
  const std::string name;

 private:
  std::vector<V> all_data;

 private:
  /*!
    Transform the percentage ( 10%) to the position in the all_data.
    \param: percentage in the data.
   */
  uint index_transfer(uint percentage) const {
    assert(percentage >= 0 && percentage <= 100);
    auto idx =  std::floor((static_cast<double>(percentage) / 100.0) * all_data.size());
    if(idx >= all_data.size())
      idx = all_data.size() - 1;
    return idx;
  }
};

} // end namespace utils

}
