
#include <iostream>
#include <fstream>

#include "md5.hpp"

class FileReader
{
    private:
        std::ifstream fin;
        long long length=0;

    public:
    FileReader(std::string filename):fin(std::ifstream(filename.c_str(), std::ios::in|std::ios::binary))
    {
        if(!fin)
        {
            std::cerr<<"File : " << filename << " was not found."<<std::endl;;
            std::terminate();
            //throw std::exception();
        }
    }
    
    block read_block()
    {
        block b = block(BLOCK_SIZE, words(WORDS_SIZE));

        for(int i=0;i<BLOCK_SIZE;i++)
        {
            for(int j=0;j<WORDS_SIZE;j++)
            {
                for(int k=0;k<4;k++)    //32bit / 8bit
                {
                    char c;
                    if(!fin.eof())
                    {
                        fin.read((char*)&c,sizeof(char));

                        if(!fin.eof())
                            length+=8;
                        else
                            c=0;
                    }
                    else
                    {
                        c=0;
                    }
                    b[i][j]+=(word)(c)<<(k*8);
                }
            }
        }
        return b;
    }

    long long get_length()
    {
        return length;
    }

    bool is_readable()
    {
        return !fin.eof();
    }
};