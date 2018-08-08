#include "fileHelper.h"
#include <fstream>
#include <QDebug>

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
    { // while loop that aborts either at eof or after 100 characters -> preview
        text.push_back(s);
        ++i;
        if(i >= 100)
        {
            break;
        }
    }
    f.close();
    return text;
}

std::vector<int> characterDistribution(std::string filename)
{
    std::vector<int> result (256, 0);
    char s=0; int i=0;
    std::fstream f;
    f.open(filename.c_str(), std::fstream::in);
    while(f.get(s))
    { // while loop that aborts either at eof or after 100 characters -> preview
        try {
        result.at(s+128) += 1; //s is unsigned
        }
        catch(std::out_of_range& e) {
            qDebug() << s+127;
        }
    }
    f.close();
    return result;
}
