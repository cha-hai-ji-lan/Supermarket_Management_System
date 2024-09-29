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
            std::cout << "登录成功" << std::endl;
            SLEEP
            CLS
            innerMenu();
            return;
        } else if (floodgate == 2 && key1 == 1 && key2 == 0) {
            std::cout << "密码错误" << std::endl;
            SLEEP
            return;
        }
    }
    std::cout << "账号不存在" << std::endl;
    SLEEP
    in.close();
}

void writeFile(const std::string &account, const std::string &password) {
    WRITE_USER_FILE(USER_FILE_PATH, out)
    out << account << ' ' << password << std::endl;
    std::cout << "注册成功" << std::endl;
    SLEEP
    out.close();
}

void informationDispose(auto func) {
    std::string account;
    std::string password;
    std::cout << "账号 :";
    std::cin >> account;
    std::cout << "密码 :";
    std::cin >> password;
    func(account, password);
}

void module() {
    DIVIDE_LINE
    DIVIDE_LINE_2("[1]  登录")
    DIVIDE_LINE_2("[2]  注册")
    DIVIDE_LINE_2("[3]  关于")
    DIVIDE_LINE_2("[0]  退出")
    DIVIDE_LINE
    CHOOSE_BUTTON
}

void menu(const int num, bool &flag) {
    if (flag) {
        DIVIDE_LINE
        std::cout << "||" << std::setfill('=') << std::setw(10) << '=' << std::setw(36) <<
                std::left << " 欢迎使用超市货物管理系统 " << "||" << std::endl;
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
    OBJ_GENERIC_TITLE("》登 录《")
    informationDispose(readFile);
}

void signUpMenu() {
    OBJ_GENERIC_TITLE("》注 册《")
    informationDispose(writeFile);
}

void aboutMenu() {
    OBJ_GENERIC_TITLE("》关 于《")
    std::cout << "本系统由[ChaHaiJiLan(茶海霁澜)]开发" << std::endl;
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
                std::cout << "返回主题菜单" << std::endl;
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
                std::cout << "欢迎下次使用" << std::endl;
                SLEEP
                exit(0);
            default:
                if (choose == 1) { CHOOSE_ERROR_INNER }
                std::cout << "模块  施工中" << std::endl;
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
    DIVIDE_LINE_2("》主菜单《")
    DIVIDE_SINGLE_LINE
    std::cout << FORMAT_MOD_PAGE_("添加商品[1]", "查询商品[2]", "出售商品[3]") << "返回[4]||" << std::endl;
    DIVIDE_SINGLE_LINE
    std::cout << FORMAT_MOD_PAGE_("批量添加[5]", "查看货架[6]", "批量出售[7]") << "退出[0]||" << std::endl;
    DIVIDE_LINE
    /*
       * cin.clear()
       * 处理非法输入：当用户输入不符合预期时，例如输入了字符串而不是数字，流会进入错误状态。
       * 恢复流状态：在处理完错误后，可以使用std::cin.clear()来清除错误状态，以便继续接收用户的输入。
       */
    std::cin.clear();
    std::cout << std::endl;
    // 忽略剩余的输入，直到遇到换行符
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * 前端与后端交互模块的接口。
 * 1. 添加商品
 * 2. 查询商品
 * 3. 出售商品
 * 4. 批量添加商品
 * 5. 查看货架
 * 6. 批量出售商品
 * 7. 退出系统
 */

void add() {
    int choice;
    OBJ_GENERIC_TITLE("添加 商品")
    std::cout << " 您需要把商品添加到哪一个货架\n【++日常用品[1]++食品[2]++电器[3]++返回[0]++】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}

void query() {
    int choice;
    OBJ_GENERIC_TITLE("查询 商品")
    std::cout << " 您需要查询哪一个货架的商品\n【==日常用品[1]==食品[2]==电器[3]==全部[4]==返回[0]==】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}

void sell() {
    int choice;
    OBJ_GENERIC_TITLE("出售 商品")
    std::cout << " 您需要出售哪一个货架的商品\n【==日常用品[1]==食品[2]==电器[3]==返回[0]==】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}

void addPlus() {
    int choice;
    OBJ_GENERIC_TITLE("批量 添加")
    std::cout << " 您需要把商品添加到哪一个货架\n【++日常用品[1]++食品[2]++电器[3]++返回[0]++】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}

void queryShelves() {
    int choice;
    OBJ_GENERIC_TITLE("查看 货架")
    std::cout << " 您需要查询哪一个货架的商品\n【==日常用品[1]==食品[2]==电器[3]==全部[4]==返回[0]==】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}

void sellPlus() {
    int choice;
    OBJ_GENERIC_TITLE("批量 出售")
    std::cout << " 您需要出售哪一个货架的商品\n"
                 "【-----日常用品[1]-----食品[2]-----电器[3]-----】\n"
                 "【--全部日常用品[4]--全部食品[5]--全部电器[6]--】\n"
                 "【-----------------全部商品[7]-----------------】\n"
                 "【-------------------返回[0]-------------------】" << std::endl;
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
            std::cout << "无效选项" << std::endl;
            SLEEP
            CLS
    }
}
