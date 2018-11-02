#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "boost/smart_ptr.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

struct counted_data
{
    int m_count=0;
};

void intrusive_ptr_add_ref(counted_data *p)
{
    ++p->m_count;
}

void intrusive_ptr_release(counted_data *p)
{
    if(--p->m_count==0)
    {
        delete p;
    }
}

int main()
{
    typedef boost::intrusive_ptr<counted_data> counted_ptr;
    counted_ptr p(new counted_data);
    assert(p);
    assert(p->m_count==1);
    counted_ptr p2(p);
    assert(p->m_count==2);
    counted_ptr weak_p(p.get(),false);
    p2.reset();
    assert(!p2);
    assert(p->m_count==1);
    // typedef std::vector<boost::shared_ptr<int>> vs;
    // vs v(10);
    // int i=0;
    // for(auto pos=v.begin();pos<v.end();++pos)
    // {
    //     *pos = boost::make_shared<int>(++i);
    //     std::cout<<*(*pos)<<",";
    // }
    // std::cout<<std::endl;
    // boost::shared_ptr<int>p=v[9];
    // *p=100;
    // std::cout<<*v[9]<<std::endl;
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