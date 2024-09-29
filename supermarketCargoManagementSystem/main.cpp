#include <iostream>
#include "pageDependencies.h"
using namespace std;
// ReSharper disable once CppDFAConstantFunctionResult

/**
 * @brief 超市货物管理系统
 * @file main.cpp
 * @details
 * @version （CPP26）超市货物管理系统 1.0
 * @author chaHaiJiLan
 */
int main() {
    bool flag = true;
    int choose = 4, choice;
    while (true) {
        CLS
        menu(choose, flag);
        cin >> choice;
        switch (choice) {
            case SIGN_IN_PAGE: CLS
                signInMenu();
                break;
            case SIGN_UP_PAGE: CLS
                signUpMenu();
                break;
            case ABOUT_PAGE: CLS
                aboutMenu();
                break;
            case EXIT_PAGE: CLS
                cout << "欢迎下次使用" << endl;
                SLEEP
                return 0;
            default:
                if (choose == 1) { CHOOSE_ERROR }
                cout << "模块  施工中" << endl;
                SLEEP
                --choose;
                break;
        }
        if (3 >= choice && choice >= 0) {
            choose = 4;
        }
        /*
       * cin.clear()
       * 处理非法输入：当用户输入不符合预期时，例如输入了字符串而不是数字，流会进入错误状态。
       * 恢复流状态：在处理完错误后，可以使用std::cin.clear()来清除错误状态，以便继续接收用户的输入。
       */
        cin.clear();
        // 忽略剩余的输入，直到遇到换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
