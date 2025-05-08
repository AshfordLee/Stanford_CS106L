#include<iostream>
#include<math.h>

#define WITH_REF 1

#if WITH_REF
void squareN(int& n)

#else
void squareN(int n)

//用宏定义来实现条件编译
//只会编译两个函数头当中的一个

#endif
{
    n=std::pow(n,2);
}

int main()
{
    int num=5;
    int& reference=num;
    std::cout<<"(1) num is "<<num<<std::endl;
    // squareN(5);
    //这里要传入引用，不能传入右值5
    squareN(num);
    std::cout<<"(2) num is "<<num<<std::endl;
    return 0;

}