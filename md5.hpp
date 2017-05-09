#ifndef INCLUDE_MD5HEADER
#define INCLUDE_MD5HEADER

#include <vector>
#include <functional>

using word=unsigned int;
using words=std::vector<word>;
using block=std::vector<words>;

const int WORDS_SIZE=4;
const int BLOCK_SIZE=4;

class MD5
{
    public:
        static const words IV;
        static const int ROUND;
        static const int STEP;

        static words md5_compute(words v, const block b);
        static void init();
        MD5()
        {
            MD5::init();
        }

    private:
        static const std::function<word(const  word,const  word,const word)> func[4];
        static std::vector<std::vector<int>> block_index;
        static std::vector<std::vector<word>> k;
        static std::vector<std::vector<int>> s;

        static void md5_round(words &v, const block b, const int round);
        static void md5_step(words &v, const block b, const int round, const int step);

        static word ff(const word b, const word c, word d)
        {
            return ((b&c)|((~b)&d));
        }
        static word gg(const word b, const word c, word d)
        {
            return ((b&d)|(c&(~d)));
        }
        static word hh(const word b, const word c, word d)
        {
            return (b^c^d);
        }
        static word ii(const word b, const word c, word d)
        {
            return (c^(b|(~d)));
        }
        static word rotate(const word a, const int r)
        {
            return (a<<r)|(a>>(32-r));
        }

};


#endif //INCLUDE_MD5HEADER
