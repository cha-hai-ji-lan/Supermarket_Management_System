// ReSharper disable CppUnusedIncludeDirective
#ifndef PAGEDEPENDENCIES_H
#define PAGEDEPENDENCIES_H
#include <fstream>
#include <iomanip>
#include <limits>
#include <windows.h>
#define SLEEP Sleep(600);
#define CLS system("cls");
#define WAIT system("pause");

#define ABOUT_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\about.txt)"
#define USER_FILE_PATH R"(..\supermarketCargoManagementSystem\bridge\user.txt)"
#define OPEN_ERROR(_X) if (!_X.is_open()) { std::cout << "�ļ���ʧ��" << std::endl; SLEEP return;}
#define READ_USER_FILE(_T, _X) std::ifstream _X(_T, std::ios::in); OPEN_ERROR(_X)
#define WRITE_USER_FILE(_T, _X) std::ofstream _X(_T, std::ios::app); OPEN_ERROR(_X)

#define CHOOSE_BUTTON std::cout << "[ѡ��]->";
#define CHOOSE_ERROR std::cout << "ʧ�ܴ��������Զ��˳��� " << std::endl; SLEEP; return 0;
#define CHOOSE_ERROR_INNER std::cout << "ʧ�ܴ��������Զ��˳��� " << std::endl; SLEEP; return;

#define DIVIDE_LINE std::cout << std::setfill('=')<< "=="<< std::setw(20)<<'='<< std::setw(26) << "=========" << "==" << std::endl;
#define DIVIDE_LINE_1 std::cout << "||" << std::setfill('=') << std::setw(11) << '=' << std::setw(35) << \
                            std::left << " ****���л������ϵͳ**** " << "||" << std::endl;
#define DIVIDE_LINE_2(_X) std::cout << std::setfill(' ') << "||" << std::setw(19) << ' ' << std::setw(27) << _X << "||" << std::endl;
#define DIVIDE_LINE_3(_X)std::cout << std::setfill('=') << "||" << std::setw(17) << \
                         '=' << std::right << "����[" << _X <<std::setw(23) << \
                          std::setfill('=') << std::left << "]�λ���" << "||" << std::endl;
#define DIVIDE_SINGLE_LINE std::cout << "||+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+||"<< std::endl;
#define OBJ_GENERIC_TITLE(_X)  DIVIDE_LINE DIVIDE_LINE_1 DIVIDE_LINE DIVIDE_LINE_2(_X)  DIVIDE_LINE

#define FORMAT_1_(_X) "||" << std::setw(11) << std::setfill(' ') << std::left  <<_X << "||"
#define FORMAT_2_(_X)  std::setw(11) << std::setfill(' ') << std::left << _X << "||"
#define FORMAT_MOD_PAGE_(_X, _Y, _Z) FORMAT_1_(_X) << FORMAT_2_(_Y) << FORMAT_2_(_Z)

/**
 * @brief  ҳ��ѡ��ö��
 * @details ö�ٳ�����Ϊһ�ֳ��������������ö���б��ǲ��ݸ�ֵ�ġ� ÿһ���������ֵ���δ�0�� 1�� 2������������
 */
enum {
    // ҳ��ѡ��
    EXIT_PAGE,
    SIGN_IN_PAGE,
    SIGN_UP_PAGE,
    ABOUT_PAGE,
};

enum {
    // ģ��ѡ��
    END,
    ADD_GOODS,
    QUERY_GOODS,
    SELL_GOODS,
    EXIT,
    ADD_IN_BULK,
    QUERY_SHELVES,
    SELL_IN_BULK,
};

/**
 * @param account �����û���д����˺���Ϣ��
 * @param password ���ڽ����û���д����˺����롣
 * @attention  �ú���Ϊ��ȡ�ļ��������ú������ȡ�û���д����˺������룬���ж��Ƿ����û���������˺�������ƥ�䡣
 */
void readFile(const std::string &account, const std::string &password);

void writeFile(const std::string &account, const std::string &password);

void informationDispose(auto func);

void module();

void menu(int num, bool &flag);

void signInMenu();

void signUpMenu();

void aboutMenu();

void innerMenu();

void innerPage_(int num);


void add();

void query();

void sell();

void addPlus();

void queryShelves();

void sellPlus();

#endif //PAGEDEPENDENCIES_H
