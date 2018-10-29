#include<stdio.h>
#include<iostream>
class Vector                        //定义向量类Vector
{public:
    int *p;                         //定义整型指针
    int Size;                       //成员参数Size表示向量维数，即一维数组大小
    Vector(int Size,int *Datas);    //定义构造函数
    ~Vector();                      //定义析构函数
    Vector * Add(Vector &another);   //定义成员函数计算向量和
    Vector * Sub(Vector &another);   //定义成员函数计算向量差
};

Vector::Vector(int Size,int *Datas)  //构造函数
{
    Vector::Size=Size;
    Vector::p=new int[Size];
    int i;
    for (i=0;i<Size;i++)
    {
        p[i]=Datas[i];  
    }
}

Vector::~Vector()
{
    delete p;
}

Vector* Vector::Add(Vector &another)
{
    if(Vector::Size!=another.Size)
    {
      return NULL;
    }
    else
    {
       Vector *result;                  //定义Vector类指针表示运算结果
       result= new Vector(Size,p);      //为结果分配空间
       int i;
       for(i=0;i<Size;i++)
       {
           result->p[i]=Vector::p[i]+another.p[i];

       }
       return result;   
    }
}


Vector *Vector::Sub(Vector &another)
{
    if(Vector::Size!=another.Size)
    {
       return NULL;
    }
    else
    {
        Vector *result;
        result = new Vector(Size,p);
        int i;
        for (i=0;i<Size;i++)
        {
            result->p[i]=Vector::p[i]-another.p[i];     
        }
        return result;

    }
}

int main()
{
    int A[4]={1,2,3,4},B[4]={5,1,2,8};
    Vector VA(4,A),VB(4,B),*VC;
    VC=VA.Add(VB);
    std::cout<<(*VC).p[0]<<","<<(*VC).p[1]<<","<<(*VC).p[2]<<","<<(*VC).p[3]<<std::endl;
    VC=VA.Sub(VB);
    std::cout<<(*VC).p[0]<<","<<(*VC).p[1]<<","<<(*VC).p[2]<<","<<(*VC).p[3]<<std::endl;

}