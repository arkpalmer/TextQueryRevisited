#ifndef __QUERY_RESULT_H__ 
#define __QUERY_RESULT_H__

#include <iostream>
#include <memory>
#include <set>
#include <string>

#include "types.h"

class Query_result
{
public:
    friend std::ostream& print(std::ostream& os, Query_result& qr);

    Query_result() : sought_("temp, remove this ctor") { std::cout << "temp, remove this ctor" << std::endl;}

    Query_result(const std::string& sought,
                 std::shared_ptr<std::set<line_no_t>> lines,
                 std::shared_ptr<stored_file_t> file) :
                 sought_(sought), lines_(lines), file_(file) {}

    //std::set<line_no_t>::iterator begin() { return lines_->begin(); }
    auto begin() { return lines_->begin(); }
    auto end()   { return lines_->end(); }

    auto get_file() { return file_; }

private:
    std::string sought_;
    std::shared_ptr<std::set<line_no_t>> lines_;
    std::shared_ptr<stored_file_t> file_;
};

#endif