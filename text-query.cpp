#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>

#include "text-query.h"
#include "utilities.h"

using namespace std;

Text_query::Text_query(std::ifstream &file) :
    file_(new stored_file_t)
{
    //std::cout << __PRETTY_FUNCTION__ << std::endl;

    line_no_t line_no = 0;

    std::string str;

    while (std::getline(file, str))
    {
        ++line_no;

        file_->push_back(str);

        std::istringstream iss(str);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());

        std::cout << "Text_query ctor, processing line: '" << str << "'" << endl;

        for (auto &it : results)
        {
            /*
             * non Debug-delete version
             *
            if (wm_[it] == nullptr)
            {
                std::cout << "no entry for " << it << endl;
                wm_[it] = std::make_shared<std::set<line_no_t>>();
            }
            */
            /*
             * this works but is pretty obtuse. from what I can tell, it's not possible
             * to provide a deleter to make_shared:
             * https://stackoverflow.com/questions/34243367/how-to-pass-deleter-to-make-shared
             */
            if (wm_.find(it) == wm_.end())
            {
                // TODO: FUNC_LINE
                wm_.emplace(it, std::shared_ptr<std::set<line_no_t>>(new std::set<line_no_t>));
            }

            std::cout << __func__ << " word in line:" << it << std::endl;
            //std::cout << "results: " << it << endl;
            // for a given word, add the line_no to the words line number set
            // wm_ is <string, sptr<set<line_no>>>
            wm_[it]->insert(line_no);
        }
    }

    std::cout << endl << "Text_query ctor wordmap:" << endl;
    for (auto& it : wm_)
    {
        std::cout << it.first << " ";
        for (auto& l : *it.second)
        {
            std::cout << l << " ";
        }
        std::cout << endl;
    }
}

Query_result Text_query::query(const std::string &str) const
{
    cout << "line:" << __LINE__ << " str:" << str << " " << __PRETTY_FUNCTION__ << endl;

    static std::shared_ptr<std::set<line_no_t>> no_data(new std::set<line_no_t>);

    if (wm_.find(str) == wm_.end())
    {
        std::cout << str << " not in file" << endl;
        // we could return here with some default or just let the map enty be created
        // (for now doing second option)
        return Query_result(str, no_data, file_);
    }

    auto loc = wm_.find(str);

    // this fails to compile, wm_[str] is a member of Text_query and could be modified (I'm not certain 
    // of the exact problem, I tried a few things but couldn't fix it so used what the book has - fail)
    //return Query_result(str, wm_[str], file_);

    // loc->second is the the set of line numbers containing the word
    return Query_result(str, loc->second, file_);

    //Query_result res(str, wm_[str], file_);
    //return res;
}
