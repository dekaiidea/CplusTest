#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "boost/smart_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

int main()
{
    typedef std::vector<boost::shared_ptr<int>> vs;
    vs v(10);
    int i=0;
    for(auto pos=v.begin();pos<v.end();++pos)
    {
        *pos = boost::make_shared<int>(++i);
        std::cout<<*(*pos)<<",";
    }
    std::cout<<std::endl;
    boost::shared_ptr<int>p=v[9];
    *p=100;
    std::cout<<*v[9]<<std::endl;
    // std::string a = "make_shared";
    // printf("%s" , a.c_str());
    // auto sp = boost::make_shared<std::string>("make_shared");
    // auto spv = boost::make_shared<std::vector<int>>(10,2);
    // assert(spv->size()==10);
    // int *pNum=(int*) malloc(23*sizeof(int)); //3*8,4*6,6*4,2,12
    // int i;
     
    // for (i=0;i<25;i++)
    // {
    //     pNum[i]=i;
     
     
    // for (i=0;i<25;i++)
    // {
    //   printf("%d,", pNum[i]); //pNum=pNum+25;
    //   //std::cout<<i<<pNum[i]<<std::endl;
    // }
    return 0;
}