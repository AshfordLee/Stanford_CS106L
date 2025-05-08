#include<iostream>

int main()
{
    // int numOne{12.0};
    //用花括号初始必须格式匹配，不然会包裹
    int numOne{12};
    float numTwo{12.0};

    std::cout<<"numOne is: "<<numOne<<std::endl;
    std::cout<<"numTwo is: "<<numTwo<<std::endl;
}