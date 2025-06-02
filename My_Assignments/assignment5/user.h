/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
  // 构造函数
  User(const std::string& name);
  
  // 特殊成员函数
  ~User();  // 析构函数
  User(const User& user);  // 拷贝构造函数
  User& operator=(const User& user);  // 拷贝赋值运算符
  User(User&& user) = delete;  // 删除移动构造函数
  User& operator=(User&& user) = delete;  // 删除移动赋值运算符
  
  // 成员函数
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);
  
  // 运算符重载（成员函数）
  User& operator+=(User& rhs);
  bool operator<(const User& rhs) const;
  
  // 运算符重载（友元函数）
  friend std::ostream& operator<<(std::ostream& os, const User& user);

  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */

private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};