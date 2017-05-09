

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "md5.cpp"
#include "md5reader.cpp"





int main(int argv, char** args)
{
    if(argv==1)
    {
        std::cerr<<"Input filename to open."<<std::endl;
        return 0;
    }
    std::string filename(args[1]);

    FileReader fr(filename);
    //cout<<filename<<endl;

    words vec=MD5::IV;
    while(1)
    {
        block b = fr.read_block();

        //print(b);

        if(fr.is_readable())
        {
            vec = MD5::md5_compute(vec, b);
        }
        else
        {
            long long leng=fr.get_length();
            int padd=(leng)%512;
            b[padd/128][padd%128/32]+=(1<<(padd%32/8*8+7-padd%8));
            if(leng%512>=512-64-1)
            {
                vec = MD5::md5_compute(vec, b);
                //print(b);
                b=block(BLOCK_SIZE, words(WORDS_SIZE));
            }

            b[3][3]+=(leng>>32);
            b[3][2]+=leng%((long long)(1)<<32);
            vec = MD5::md5_compute(vec, b);

            //print(b);
            break;
        }
    }

    print_hash(vec);

}