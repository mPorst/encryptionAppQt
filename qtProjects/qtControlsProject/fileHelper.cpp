#include "fileHelper.h"
#include <fstream>

unsigned int FileSize(std::fstream* f)
{
	f->seekg(0, std::ios_base::beg);
	std::ifstream::pos_type begin_pos = f->tellg();
	f->seekg(0, std::ios_base::end);
	std::ifstream::pos_type end_pos = f->tellg();
	f->seekg(0, std::ios_base::beg); // need to return to beginning status
    return static_cast<unsigned int>(end_pos - begin_pos);
}

std::string fileText(std::string filename)
{
    std::string text("");
    char s; int i=0;
    std::fstream f;
    f.open(filename.c_str(), std::fstream::in);
    while(f.get(s))
    { // while loop that aborts either at eof or after 500 characters -> preview
        text.push_back(s);
        ++i;
        if(i >= 500)
        {
            break;
        }
    }
    f.close();
    return text;
}
