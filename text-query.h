#ifndef __TEXT_QUERY_H__ 
#define __TEXT_QUERY_H__

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "query-result.h"
#include "types.h"

class Query_result;
class Text_query
{
public:
    // in types.h using line_no = std::vector<std::string>::size_type;

    Text_query(std::ifstream& file);

    Query_result query(const std::string& str) const;

private:
    std::shared_ptr<stored_file_t> file_; // contents of file
    std::map<std::string, std::shared_ptr<std::set<line_no_t>>> wm_;
};

#endif