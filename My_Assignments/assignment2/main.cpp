/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

std::string kYourName = "John Doe"; // 请将此处改为您的真实姓名

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
    std::set<std::string> applicants;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "无法打开文件：" << filename << std::endl;
        return applicants;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            applicants.insert(line);
        }
    }

    file.close();
    return applicants;
}

// 辅助函数：获取名字的首字母
std::string get_initials(const std::string& name) {
    std::string initials;
    bool new_word = true;
    
    for (char c : name) {
        if (new_word && std::isalpha(c)) {
            initials += std::toupper(c);
            new_word = false;
        } else if (c == ' ') {
            new_word = true;
        }
    }
    
    return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
    std::queue<const std::string*> matches;
    std::string target_initials = get_initials(name);
    
    for (const auto& student : students) {
        if (get_initials(student) == target_initials) {
            matches.push(&student);
        }
    }
    
    return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
    if (matches.empty()) {
        return "NO MATCHES FOUND.";
    }

    // 获取队列大小
    size_t size = matches.size();
    
    // 使用当前时间作为随机种子
    srand(time(nullptr));
    
    // 随机选择一个位置（0到size-1之间）
    size_t target_pos = rand() % size;
    
    // 将队列中的元素循环移动，直到目标位置到达队首
    for (size_t i = 0; i < target_pos; i++) {
        const std::string* temp = matches.front();
        matches.pop();
        matches.push(temp);
    }
    
    // 返回选中的匹配对象
    const std::string* match = matches.front();
    matches.pop();
    return *match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
