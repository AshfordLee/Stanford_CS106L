#include<iostream>
#include<utility>
#include<cmath>

using Zeros=std::pair<double,double>;
using Solution=std::pair<bool,Zeros>;

/**
 * Solves the equation ax^2 + bx + c = 0
 * @param a The coefficient of x^2
 * @param b The coefficient of x
 * @param c The constant term
 * @return A pair. The first element (bool) indicates if the equation has a solution.
 *                 The second element is a pair of the roots if they exist.
 */

 //std::pair<bool,std::pair<double,double>> solveQuadratic(double a, double b, double c);
 Solution solveQuadratic(double a,double b,double c)
 {
    double delta=b*b-4*a*c;
    
    if (delta<0)
    {
        return {false,{106,106}};
    }

    double root=sqrt(delta);
    double x1=(-b-root)/(2*a);
    double x2=(-b+root)/(2*a);

    return {true,{x1,x2}};
 }

 int main()
 {
    double a,b,c;
    std::cout<<"Enter the coefficients of the quadratic equation: ";
    std::cin>>a;
    std::cin>>b;
    std::cin>>c;

    Solution answer=solveQuadratic(a,b,c);

    if(answer.first==true)
    {
        std::pair<double,double> solutions=answer.second;
        std::cout<<"The solutions are: "<<solutions.first<<" and "<<solutions.second<<std::endl;
    }

    else {
    {
        std::cout<<"No real solutions"<<std::endl;
    }
    }
 }