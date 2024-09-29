#include "objSupermarketInner.h"
#include  "pageDependencies.h"
#include <iostream>


void readFile(const std::string &account, const std::string &password) {
    READ_USER_FILE(USER_FILE_PATH, in)
    int key1 = 0, key2 = 0, floodgate = 0;
    char buf[1024] = {0};
    bool sign = true;
    while (in >> buf) {
        ++floodgate;
        if (sign) {
            if (std::string account_buf(buf); account == account_buf) { ++key1; }
            sign = false;
        } else {
            if (std::string password_buf(buf); password == password_buf) { ++key2; }
            sign = true;
        }
        if (floodgate == 2 && key1 == 0 && key2 == 1) {
            key1 = key2 = 0;
            floodgate = 0;
        } else if (key1 == 0 && key2 == 0) {
            floodgate = 0;
        } else if (floodgate == 2 && key1 == 1 && key2 == 1) {
            CLS
            std::cout << "��¼�ɹ�" << std::endl;
            SLEEP
            CLS
            innerMenu();
            return;
        } else if (floodgate == 2 && key1 == 1 && key2 == 0) {
            std::cout << "�������" << std::endl;
            SLEEP
            return;
        }
    }
    std::cout << "�˺Ų�����" << std::endl;
    SLEEP
    in.close();
}

void writeFile(const std::string &account, const std::string &password) {
    WRITE_USER_FILE(USER_FILE_PATH, out)
    out << account << ' ' << password << std::endl;
    std::cout << "ע��ɹ�" << std::endl;
    SLEEP
    out.close();
}

void informationDispose(auto func) {
    std::string account;
    std::string password;
    std::cout << "�˺� :";
    std::cin >> account;
    std::cout << "���� :";
    std::cin >> password;
    func(account, password);
}

void module() {
    DIVIDE_LINE
    DIVIDE_LINE_2("[1]  ��¼")
    DIVIDE_LINE_2("[2]  ע��")
    DIVIDE_LINE_2("[3]  ����")
    DIVIDE_LINE_2("[0]  �˳�")
    DIVIDE_LINE
    CHOOSE_BUTTON
}

void menu(const int num, bool &flag) {
    if (flag) {
        DIVIDE_LINE
        std::cout << "||" << std::setfill('=') << std::setw(10) << '=' << std::setw(36) <<
                std::left << " ��ӭʹ�ó��л������ϵͳ " << "||" << std::endl;
        flag = false;
    } else {
        DIVIDE_LINE
        DIVIDE_LINE_1
    }
    if (num != 4) {
        DIVIDE_SINGLE_LINE
        DIVIDE_LINE_3(num)
    }
    module();
}

void signInMenu() {
    OBJ_GENERIC_TITLE("���� ¼��")
    informationDispose(readFile);
}

void signUpMenu() {
    OBJ_GENERIC_TITLE("��ע �ᡶ")
    informationDispose(writeFile);
}

void aboutMenu() {
    OBJ_GENERIC_TITLE("���� �ڡ�")
    std::cout << "��ϵͳ��[ChaHaiJiLan(�躣����)]����" << std::endl;
    std::ifstream about(ABOUT_FILE_PATH, std::ios::in);
    std::string txtFile;
    while(getline(about, txtFile)) {
        std::cout << txtFile << std::endl;
    }
    about.close();
    WAIT
}

void innerMenu() {
    int choose = 4, choice;
    while (true) {
        CLS
        innerPage_(choose);
        CHOOSE_BUTTON
        std::cin >> choice;
        switch (choice) {
            case ADD_GOODS: CLS
                add();
                break;
            case QUERY_GOODS: CLS
                query();
                break;
            case SELL_GOODS: CLS
                sell();
                break;
            case EXIT: CLS
                std::cout << "��������˵�" << std::endl;
                SLEEP
                return;
            case ADD_IN_BULK: CLS
                addPlus();
                break;
            case QUERY_SHELVES: CLS
                queryShelves();
                break;
            case SELL_IN_BULK: CLS
                sellPlus();
                break;
            case END: CLS
                std::cout << "��ӭ�´�ʹ��" << std::endl;
                SLEEP
                exit(0);
            default:
                if (choose == 1) { CHOOSE_ERROR_INNER }
                std::cout << "ģ��  ʩ����" << std::endl;
                SLEEP
                --choose;
                break;
        }
        if (3 >= choice && choice >= 0) {
            choose = 4;
        }
    }
}

void innerPage_(const int num) {
    DIVIDE_LINE
    DIVIDE_LINE_1
    if (num != 4) {
        DIVIDE_SINGLE_LINE
        DIVIDE_LINE_3(num)
    }
    DIVIDE_LINE
    DIVIDE_LINE_2("�����˵���")
    DIVIDE_SINGLE_LINE
    std::cout << FORMAT_MOD_PAGE_("�����Ʒ[1]", "��ѯ��Ʒ[2]", "������Ʒ[3]") << "����[4]||" << std::endl;
    DIVIDE_SINGLE_LINE
    std::cout << FORMAT_MOD_PAGE_("�������[5]", "�鿴����[6]", "��������[7]") << "�˳�[0]||" << std::endl;
    DIVIDE_LINE
    /*
       * cin.clear()
       * ����Ƿ����룺���û����벻����Ԥ��ʱ�������������ַ������������֣�����������״̬��
       * �ָ���״̬���ڴ��������󣬿���ʹ��std::cin.clear()���������״̬���Ա���������û������롣
       */
    std::cin.clear();
    std::cout << std::endl;
    // ����ʣ������룬ֱ���������з�
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * ǰ�����˽���ģ��Ľӿڡ�
 * 1. �����Ʒ
 * 2. ��ѯ��Ʒ
 * 3. ������Ʒ
 * 4. ���������Ʒ
 * 5. �鿴����
 * 6. ����������Ʒ
 * 7. �˳�ϵͳ
 */

void add() {
    int choice;
    OBJ_GENERIC_TITLE("��� ��Ʒ")
    std::cout << " ����Ҫ����Ʒ��ӵ���һ������\n��++�ճ���Ʒ[1]++ʳƷ[2]++����[3]++����[0]++��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case  0:
            break;
        case 1:
            Supermarket::Add(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::Add(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::Add(superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}

void query() {
    int choice;
    OBJ_GENERIC_TITLE("��ѯ ��Ʒ")
    std::cout << " ����Ҫ��ѯ��һ�����ܵ���Ʒ\n��==�ճ���Ʒ[1]==ʳƷ[2]==����[3]==ȫ��[4]==����[0]==��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case 0:
            break;
        case 1:
            Supermarket::Search(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::Search(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::Search(superOBJ.goods_e);
            break;
        case 4:
            Supermarket::showAllGoods(superOBJ.goods_d, superOBJ.goods_f, superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}

void sell() {
    int choice;
    OBJ_GENERIC_TITLE("���� ��Ʒ")
    std::cout << " ����Ҫ������һ�����ܵ���Ʒ\n��==�ճ���Ʒ[1]==ʳƷ[2]==����[3]==����[0]==��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case 0:
            break;
        case 1:
            Supermarket::Sale(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::Sale(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::Sale(superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}

void addPlus() {
    int choice;
    OBJ_GENERIC_TITLE("���� ���")
    std::cout << " ����Ҫ����Ʒ��ӵ���һ������\n��++�ճ���Ʒ[1]++ʳƷ[2]++����[3]++����[0]++��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case  0:
            break;
        case 1:
            Supermarket::addPlus(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::addPlus(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::addPlus(superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}

void queryShelves() {
    int choice;
    OBJ_GENERIC_TITLE("�鿴 ����")
    std::cout << " ����Ҫ��ѯ��һ�����ܵ���Ʒ\n��==�ճ���Ʒ[1]==ʳƷ[2]==����[3]==ȫ��[4]==����[0]==��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case 0:
            break;
        case 1:
            Supermarket::searchPlus(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::searchPlus(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::searchPlus(superOBJ.goods_e);
            break;
        case 4:
            Supermarket::showAllGoods(superOBJ.goods_d, superOBJ.goods_f, superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}

void sellPlus() {
    int choice;
    OBJ_GENERIC_TITLE("���� ����")
    std::cout << " ����Ҫ������һ�����ܵ���Ʒ\n"
                 "��-----�ճ���Ʒ[1]-----ʳƷ[2]-----����[3]-----��\n"
                 "��--ȫ���ճ���Ʒ[4]--ȫ��ʳƷ[5]--ȫ������[6]--��\n"
                 "��-----------------ȫ����Ʒ[7]-----------------��\n"
                 "��-------------------����[0]-------------------��" << std::endl;
    CHOOSE_BUTTON
    std::cin >> choice;
    Supermarket superOBJ{DailyGoods(), Food(), ElectricalAppliance()};
    switch (choice) {
        case 0:
            break;
        case 1:
            Supermarket::salePlus(superOBJ.goods_d);
            break;
        case 2:
            Supermarket::salePlus(superOBJ.goods_f);
            break;
        case 3:
            Supermarket::salePlus(superOBJ.goods_e);
            break;
        case 4:
            Supermarket::saleAllGoods(superOBJ.goods_d);
            break;
        case 5:
            Supermarket::saleAllGoods(superOBJ.goods_f);
            break;
        case 6:
            Supermarket::saleAllGoods(superOBJ.goods_e);
            break;
        case 7:
            Supermarket::saleAllGoods(superOBJ.goods_d);
            Supermarket::saleAllGoods(superOBJ.goods_f);
            Supermarket::saleAllGoods(superOBJ.goods_e);
            break;
        default:
            std::cout << "��Чѡ��" << std::endl;
            SLEEP
            CLS
    }
}
