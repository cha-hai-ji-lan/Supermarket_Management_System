/**
 * @file constSpace.h
 * @author chaHaiJiLan
 * @brief 常量空间
 * @version 0.1
 * @date 2024-08-19
 * @details 此常量空间用于标注一些基本常量，并且也包含了文件读写的相关内容
 * @attention 此文件只支持 C++17 以上版本（最好是C++26） 作者懒得做低版本适配 如有需要亲自行修改 ———— 茶海霁澜敬上
 * @copyright Copyright (c) 2024 Individual author chaHaiJiLan. Everyone is available.
 */

#ifndef CONSTSPACE_H
#define CONSTSPACE_H
const std::string HEAD_NAME_ = "商品名称";
const std::string HEAD_NUM_ = "商品数量";
const std::string HEAD_SHELF_LIFE_ = "保质期(天)";
const std::string HEAD_COLOUR_ = "商品颜色";

#define MAX_BYTES 2048
#define UNUSE  [[maybe_unused]]
#define FOOD_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\food.txt)"
#define DAILY_GOODS_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\dailyGoods.txt)"
#define ELECTRICAL_APPLIANCE_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\electricalAppliance.txt)"

#define JUDGE_FILE_OPEN(x) if (!x.is_open()) { std::cout << "文件打开失败" << std::endl; return nullptr;}
#define READER(_x) char _x[MAX_BYTES] = {0};
#define FILE_CLOSE(x) x.close();

#define WRITE_FOOD(_t, _x) std::ofstream _x(_t, std::ios::out); JUDGE_FILE_OPEN(_x)
#define WRITE_DAILY_GOODS(_t, _x) std::ofstream _x(_t, std::ios::out); JUDGE_FILE_OPEN(_x)
#define WRITE_ELECTRICAL_APPLIANCE(_t, _x) std::ofstream _x(_t, std::ios::out); JUDGE_FILE_OPEN(_x)

#define READ_FOOD(_t, _x) std::ifstream _x(_t, std::ios::in); JUDGE_FILE_OPEN(_x)
#define READ_DAILY_GOODS(_t, _x) std::ifstream _x(_t, std::ios::in); JUDGE_FILE_OPEN(_x)
#define READ_ELECTRICAL_APPLIANCE(_t, _x) std::ifstream _x(_t, std::ios::in); JUDGE_FILE_OPEN(_x)

#define OBJ_STD_HEAD_(_x) "||" << std::setw(10) << std::setfill('=') << std::left << _x << "||"
#define FORMAT_PART_1_(_x) "||" << std::setw(10) << std::setfill(' ') << std::left  <<_x << "||"
#define FORMAT_PART_2_(_x) "  " << std::setw(10) << std::setfill(' ') << std::left << _x << "||"

#define FORMAT_MOD_1_(_x, _y) FORMAT_PART_1_(_x) << FORMAT_PART_2_(_y)
#define FORMAT_MOD_2_(_x, _y, _z) FORMAT_PART_1_(_x) << FORMAT_PART_2_(_y) << FORMAT_PART_2_(_z)

#define LIST_HEAD_TOW_BLOCK_(_x) "[" << std::setw(17) << std::setfill(' ') << std::right << _x\
                                 << std::setw(10) << std::setfill(' ') << std::right  <<"]"
#define LIST_HEAD_THREE_BLOCK_(_x) "[" << std::setw(24) << std::setfill(' ') << std::right << _x\
                          << std::setw(17) << std::setfill(' ') << std::right  <<"]"


#endif //CONSTSPACE_H
