#include <iostream>
#include <cstring>
#include <functional>
#include <vector>
#include <cmath>
#include <iomanip>

#include "md5.hpp"


void print_word(const word w)
{
    //cout<<hex;
    for(int j=0;j<4;j++)
    {
        /*unsigned short c=(w>>(j*8))&0xff;
        cout<<c;*/
    }
    std::cout<<w<<" ";
    std::cout<<std::endl;
}

void print(const block b)
{
        std::cout<<std::setw(8)<<std::setfill('0')<<std::hex;
        for(int j=0;j<BLOCK_SIZE;j++)
        for(int i=0;i<WORDS_SIZE;i++)
            std::cout<<std::setw(8)<<std::setfill('0')<<b[j][i]<<" ";
        std::cout<<std::endl;
}

void print_hash(const words w)
{
    std::cout<<std::hex;
    for(int i=0;i<WORDS_SIZE;i++)
    {
        //cout<<w[i];
        for(int j=0;j<4;j++)
        {
            unsigned short c=(w[i]>>(j*8))&0xff;
            std::cout<<std::setw(2)<<std::setfill('0')<<c;
        }
        //cout<<" ";
    }
    std::cout<<std::endl;
}


const words MD5::IV=
words{ 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
const int MD5::ROUND=4;
const int MD5::STEP=16;
const std::function<word(const word,const word,const word)> MD5::func[]={ff,gg,hh,ii};

std::vector<std::vector<int>> MD5::block_index(ROUND, std::vector<int>(STEP));
std::vector<std::vector<word>> MD5::k(ROUND, std::vector<word>(STEP));
std::vector<std::vector<int>> MD5::s(ROUND, std::vector<int>(STEP));
void MD5::init()
{
    for(int i=0;i<STEP;i++)
    {
        block_index[0][i]=i;
        block_index[1][i]=(i*5+1)%16;
        block_index[2][i]=(i*3+5)%16;
        block_index[3][i]=(i*7)%16;
    }

    int ss[][4]={
        {7,12,17,22},
        {5,9,14,20},
        {4,11,16,23},
        {6,10,15,21}
        };
    
    for(int j=0;j<ROUND;j++)
    for(int i=0;i<4;i++)
        s[j][i]=ss[j][i];
    for(int j=0;j<ROUND;j++)
    for(int i=4;i<STEP;i++)
        s[j][i]=s[j][i%4];

    for(int i=0;i<ROUND*STEP;i++)
        k[i/STEP][i%STEP]=std::floor(std::abs(sin(i+1))*((long long)(1)<<32));
}

words MD5::md5_compute(words v, const block b)
{
    words vv(v);
    for(int i=0;i<4;i++)
        md5_round(v, b, i);
    for(int i=0;i<WORDS_SIZE;i++)
        vv[i]+=v[i];
    return vv;
}

void MD5::md5_round(words &v, const block b, const int rnd)
{
    for(int i=0;i<16;i++)
        md5_step(v, b, rnd, i);
}

void MD5::md5_step(words &v, const block b, const int rnd, const int step)
{
    int a=(16-step)%4,bb=(17-step)%4;
    int bi=block_index[rnd][step];
    v[a]+=func[rnd](v[bb], v[(18-step)%4], v[(19-step)%4]);
    v[a]+=b[bi/4][bi%4];
    v[a]+=k[rnd][step];
    v[a]=rotate(v[a], s[rnd][step]);
    v[a]+=v[bb];

    //print_hash(v);
}


//static変数の初期化
MD5 initializer=MD5();
