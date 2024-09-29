/**
 * @file constSpace.h
 * @author chaHaiJiLan
 * @brief �����ռ�
 * @version 0.1
 * @date 2024-08-19
 * @details �˳����ռ����ڱ�עһЩ��������������Ҳ�������ļ���д���������
 * @attention ���ļ�ֻ֧�� C++17 ���ϰ汾�������C++26�� �����������Ͱ汾���� ������Ҫ�������޸� �������� �躣��������
 * @copyright Copyright (c) 2024 Individual author chaHaiJiLan. Everyone is available.
 */

#ifndef CONSTSPACE_H
#define CONSTSPACE_H
const std::string HEAD_NAME_ = "��Ʒ����";
const std::string HEAD_NUM_ = "��Ʒ����";
const std::string HEAD_SHELF_LIFE_ = "������(��)";
const std::string HEAD_COLOUR_ = "��Ʒ��ɫ";

#define MAX_BYTES 2048
#define UNUSE  [[maybe_unused]]
#define FOOD_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\food.txt)"
#define DAILY_GOODS_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\dailyGoods.txt)"
#define ELECTRICAL_APPLIANCE_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\electricalAppliance.txt)"

#define JUDGE_FILE_OPEN(x) if (!x.is_open()) { std::cout << "�ļ���ʧ��" << std::endl; return nullptr;}
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
