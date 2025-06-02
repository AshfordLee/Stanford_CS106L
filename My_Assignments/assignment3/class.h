#ifndef SMART_COFFEE_MAKER_H
#define SMART_COFFEE_MAKER_H

#include <string>

class SmartCoffeeMaker {
public:
    // 默认构造函数
    SmartCoffeeMaker();
    
    // 带参数的构造函数
    SmartCoffeeMaker(int waterLevel, std::string coffeeType);
    
    // Getter函数
    int getWaterLevel() const;
    std::string getCoffeeType() const;
    bool isPowerOn() const;
    
    // Setter函数
    void setWaterLevel(int level);
    void setCoffeeType(std::string type);
    void setPower(bool on);
    
    // 其他公共成员函数
    bool makeCoffee();
    void addWater(int amount);

private:
    // 私有成员变量
    int waterLevel;         // 水位（毫升）
    std::string coffeeType; // 咖啡类型
    bool powerOn;          // 电源状态
    
    // 私有成员函数
    bool checkWaterLevel() const;
    void heat();
};

#endif // SMART_COFFEE_MAKER_H
