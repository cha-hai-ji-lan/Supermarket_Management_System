#include <iostream>
#include "pageDependencies.h"
using namespace std;
// ReSharper disable once CppDFAConstantFunctionResult

/**
 * @brief ���л������ϵͳ
 * @file main.cpp
 * @details
 * @version ��CPP26�����л������ϵͳ 1.0
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
                cout << "��ӭ�´�ʹ��" << endl;
                SLEEP
                return 0;
            default:
                if (choose == 1) { CHOOSE_ERROR }
                cout << "ģ��  ʩ����" << endl;
                SLEEP
                --choose;
                break;
        }
        if (3 >= choice && choice >= 0) {
            choose = 4;
        }
        /*
       * cin.clear()
       * ����Ƿ����룺���û����벻����Ԥ��ʱ�������������ַ������������֣�����������״̬��
       * �ָ���״̬���ڴ��������󣬿���ʹ��std::cin.clear()���������״̬���Ա���������û������롣
       */
        cin.clear();
        // ����ʣ������룬ֱ���������з�
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
