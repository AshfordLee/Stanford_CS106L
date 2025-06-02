#include "class.h"
#include <iostream>

// 默认构造函数
SmartCoffeeMaker::SmartCoffeeMaker() 
    : waterLevel(0), coffeeType("未设置"), powerOn(false) {}

// 带参数的构造函数
SmartCoffeeMaker::SmartCoffeeMaker(int waterLevel, std::string coffeeType)
    : waterLevel(waterLevel), coffeeType(coffeeType), powerOn(false) {}

// Getter函数
int SmartCoffeeMaker::getWaterLevel() const {
    return waterLevel;
}

std::string SmartCoffeeMaker::getCoffeeType() const {
    return coffeeType;
}

bool SmartCoffeeMaker::isPowerOn() const {
    return powerOn;
}

// Setter函数
void SmartCoffeeMaker::setWaterLevel(int level) {
    if (level >= 0) {
        waterLevel = level;
    }
}

void SmartCoffeeMaker::setCoffeeType(std::string type) {
    coffeeType = type;
}

void SmartCoffeeMaker::setPower(bool on) {
    powerOn = on;
}

// 其他公共成员函数
bool SmartCoffeeMaker::makeCoffee() {
    if (!powerOn) {
        std::cout << "请先打开电源！" << std::endl;
        return false;
    }
    
    if (!checkWaterLevel()) {
        std::cout << "水位不足，请加水！" << std::endl;
        return false;
    }
    
    heat();
    waterLevel -= 200; // 每杯咖啡使用200ml水
    std::cout << "您的" << coffeeType << "咖啡已准备完成！" << std::endl;
    return true;
}

void SmartCoffeeMaker::addWater(int amount) {
    if (amount > 0) {
        waterLevel += amount;
        std::cout << "已添加" << amount << "ml水，当前水位：" << waterLevel << "ml" << std::endl;
    }
}

// 私有成员函数
bool SmartCoffeeMaker::checkWaterLevel() const {
    return waterLevel >= 200; // 需要至少200ml水来制作一杯咖啡
}

void SmartCoffeeMaker::heat() {
    std::cout << "正在加热..." << std::endl;
}
