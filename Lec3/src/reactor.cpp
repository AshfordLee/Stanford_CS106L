#include<iostream>

class Reactor{

public:
        Reactor(double temperature):temperature(temperature){}

        void checkCool()
        {
            if (temperature>100.0)
            {
                std::cout<<"Emergency cooling! "<<std::endl;
            }

            else {
                std::cout<<"Temperature is normal. No emergency cooling required"<<std::endl;
            }
        }
private:
        double temperature;
};

int main()
{
    int criticalTemperature(100.8);
    Reactor reactor(criticalTemperature);
    reactor.checkCool();
    return 0;
}