//
// Created by 86188 on 2024/8/24.
//

#ifndef TIMEPURE_H
#define TIMEPURE_H
#include <chrono>
#include <string>
#include <ctime>
#include <vector>

enum  {
    Jan = 1,
    Feb = 2,
    Mar = 3,
    Apr = 4,
    May = 5,
    Jun = 6,
    Jul = 7,
    Aug = 8,
    Sep = 9,
    Oct = 10,
    Nov = 11,
    Dec = 12
};

inline std::vector<std::string> timestamp() {
    //  * [string& assign(const string& str, size_t pos, size_t n); // string类型字符串的 pos后的 前n个字符 赋值给当前的字符串。]
    // 获取当前时间点
    const auto now = std::chrono::system_clock::now();
    // 转换为 time_t 类型
    const std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // 使用 ctime 函数转换为字符串
    const std::string now_s = std::ctime(&now_c);
    const std::string sub1 = now_s.substr(20, 4); // 获取年份切片
    const std::string sub2 = now_s.substr(4, 3); // 获取月份切片
    const std::string sub3 = now_s.substr(8, 2); // 获取日期切片
    std::vector<std::string> time_now;
    time_now.push_back(sub1);
    time_now.push_back(sub2);
    time_now.push_back(sub3);
    return time_now;
}

#endif //TIMEPURE_H
