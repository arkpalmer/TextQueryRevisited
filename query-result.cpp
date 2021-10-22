#include <iostream>

#include "query-result.h"

using namespace std;

std::ostream& print(std::ostream& os, Query_result& qr)
{
    os << qr.sought_ << " occurs " << qr.lines_->size() << " times." << endl;

    for (auto& it : *qr.lines_)
    {
        cout << "(line " << it << ") " << 
                (*qr.file_)[it-1] << endl; // we start the line count at 1 (this is bogus what does book do?)
    }

    return os;
}