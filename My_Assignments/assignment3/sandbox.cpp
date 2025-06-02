/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.h"
#include <iostream>

void sandbox() {
    // 使用默认构造函数创建实例
    SmartCoffeeMaker defaultMaker;
    std::cout << "默认咖啡机状态：" << std::endl;
    std::cout << "水位：" << defaultMaker.getWaterLevel() << "ml" << std::endl;
    std::cout << "咖啡类型：" << defaultMaker.getCoffeeType() << std::endl;
    std::cout << "电源状态：" << (defaultMaker.isPowerOn() ? "开" : "关") << std::endl;
    
    // 使用带参数的构造函数创建实例
    SmartCoffeeMaker customMaker(500, "拿铁");
    std::cout << "\n自定义咖啡机状态：" << std::endl;
    std::cout << "水位：" << customMaker.getWaterLevel() << "ml" << std::endl;
    std::cout << "咖啡类型：" << customMaker.getCoffeeType() << std::endl;
    
    // 测试功能
    customMaker.setPower(true);
    customMaker.makeCoffee();
    std::cout << "剩余水量：" << customMaker.getWaterLevel() << "ml" << std::endl;
}