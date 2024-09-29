#ifndef SUPERMARKEauto_H
#define SUPERMARKEauto_H
#include <iostream> // 标准输入输出库
#include <string> // 字符串库
#include <vector>
#include "constSpace.h" // 常量空间
#include "timePure.h" // 时间戳
#include "pageDependencies.h" // 菜单依赖

// 商品类 抽象基类。 抽象类不允许创建对象，只能通过派生类创建对象。
class Goods {
public:
    Goods() = default; // 默认构造函数
    virtual ~Goods() = default; //  （虚）默认析构函数 用于确保当通过基类指针删除派生类对象时，能够正确调用到派生类的析构函数
    Goods &operator=(const Goods &goods_new) = default;

    virtual void showMe() = 0; // 虚函数
    std::vector<std::string> goods_name{}; // 商品名称
    std::vector<std::string> goods_num{}; // 商品数量
    std::vector<std::string> shelf_life{}; // 保质期
    std::vector<std::string> colour{}; // 颜色
    std::vector<std::string> timestamp{}; // 添加时间 时间戳。
};

// 日常用品类
class DailyGoods final : public Goods {
public:
    // DailyGoods公共继承自Goods 且不允许继续向下继承
    DailyGoods() = default; // 默认构造函数
    ~DailyGoods() override = default; // 重写默认析构函数
    void showMe() override; // 虚函数重写用于显示日常用品的【名称】【数量】。
    DailyGoods &operator=(const DailyGoods &);
};

// 食品类
class Food final : public Goods {
public:
    Food() = default; // 默认构造函数:
    ~Food() override = default; // 重写默认析构函数
    void showMe() override; // 虚函数重写用于显示食物的【名称】【数量】以及【保质期】。
    Food &operator=(const Food &);
};

inline void fileWrite(Goods &goods);

inline void fileRead(Goods &goods);

// 电器类
class ElectricalAppliance final : public Goods {
public:
    ElectricalAppliance() = default; // 默认构造函数
    ~ElectricalAppliance() override = default; // 重写默认析构函数
    void showMe() override; // 虚函数重写用于显示家电的【名称】【数量】以及【颜色】。
    ElectricalAppliance &operator=(const ElectricalAppliance &);
};

/**
 * @brief 超市类
 * @details 超市类，用于管理商品，支持添加、销售、查询，并且支持管理商品分区查看
 */
class Supermarket final {
    friend std::ostream &operator<<(std::ostream &Out, auto &goods);

    friend std::istream &operator>>(std::istream &In, auto &goods);

public:
    explicit Supermarket(const DailyGoods &goodDG, const Food &goodF,
                         const ElectricalAppliance &goodEA): goods_d(goodDG)
                                                             , goods_f(goodF), goods_e(goodEA) {
    }

    ~Supermarket() {
        if (!goods_d.goods_name.empty()) { fileWrite(goods_d); }
        if (!goods_f.goods_name.empty()) {
            fileWrite(goods_f);
            return;
        }
        if (!goods_e.goods_name.empty()) {
            fileWrite(goods_e);
        }
    };

    static void Add(auto &goods); // 添加商品
    static void Sale(auto &goods); // 销售商品         `
    static void Search(auto &goods); // 查询商品
    static void showAllGoods(DailyGoods DG, Food F, ElectricalAppliance EA);

    static void addPlus(auto &goods); // 批量添加商品
    static void salePlus(auto &goods); // 批量销售商品         `
    static void searchPlus(auto &goods); // 查询货架商品
    static void saleAllGoods(auto &goods); // 批量销售所有商品

    DailyGoods goods_d{};
    Food goods_f{};
    ElectricalAppliance goods_e{};
};

/*
 * 基于采用了SautoL泛型编程所以无法写成头文件声明源文件实现的形式
 * 故后续为目标类中所有方式的实现。
 *
 *
 * Goods默认函数实现。
 * Goods派生类虚函数方法的实现
 */

//
inline DailyGoods &DailyGoods::operator=(const DailyGoods &goods_new) {
    if (this == &goods_new) {
        return *this;
    }
    delete this;
    this->goods_name.assign(goods_new.goods_name.begin(), goods_new.goods_name.end());
    this->goods_num.assign(goods_new.goods_num.begin(), goods_new.goods_num.end());
    return *this;
};

inline Food &Food::operator=(const Food &goods_new) {
    if (this == &goods_new) {
        return *this;
    }
    delete this;
    this->goods_name.assign(goods_new.goods_name.begin(), goods_new.goods_name.end());
    this->goods_num.assign(goods_new.goods_num.begin(), goods_new.goods_num.end());
    this->shelf_life.assign(goods_new.shelf_life.begin(), goods_new.shelf_life.end());
    return *this;
}

inline ElectricalAppliance &ElectricalAppliance::operator=(const ElectricalAppliance &goods_new) {
    if (this == &goods_new) {
        return *this;
    }
    delete this;
    this->goods_name.assign(goods_new.goods_name.begin(), goods_new.goods_name.end());
    this->goods_num.assign(goods_new.goods_num.begin(), goods_new.goods_num.end());
    this->colour.assign(goods_new.colour.begin(), goods_new.colour.end());
    return *this;
}

// 显示日常用品的【名称】【数量】。
inline void DailyGoods::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "日常用品暂无商品信息。" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_TOW_BLOCK_("日常用品") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_1_(goods_name[i], goods_num[i]) << std::endl;
    }
    WAIT
}

// 显示食物的【名称】【数量】以及【保质期】。
inline void Food::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "食品暂无商品信息。" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_THREE_BLOCK_("食品类  ") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_SHELF_LIFE_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_2_(goods_name[i], goods_num[i], shelf_life[i]) << std::endl;
    }
    WAIT
}

// 显示家电的【名称】【数量】以及【颜色】。
inline void ElectricalAppliance::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "电器暂无商品信息。" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_THREE_BLOCK_("家电类  ") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_COLOUR_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_2_(goods_name[i], goods_num[i], colour[i]) << std::endl;
    }
    WAIT
}

// coutSentence函数 显示提示语
inline void coutSentence(const int choose) {
    if (choose == 1 || choose == 4) std::cout << "请输入要查找的商品名称：";
    if (choose == 2 || choose == 5) std::cout << "请输入要添加的商品名称：";
    if (choose == 3 || choose == 6) std::cout << "请输入要出售的商品名称：";
}

inline void goodsClear(Goods &goods) {
    goods.goods_name.clear();
    goods.goods_num.clear();
    goods.shelf_life.clear();
    goods.colour.clear();
    goods.timestamp.clear();
}

// typeSort函数 根据商品类型选择读取文件
std::ifstream typeSort(UNUSE const auto &goods) {
    if (typeid(goods) == typeid(DailyGoods)) {
        READ_DAILY_GOODS(DAILY_GOODS_FILE_PATH, goodD)
        return goodD;
    }
    if (typeid(goods) == typeid(Food)) {
        READ_FOOD(FOOD_FILE_PATH, goodF)
        return goodF;
    }
    if (typeid(goods) == typeid(ElectricalAppliance)) {
        READ_ELECTRICAL_APPLIANCE(ELECTRICAL_APPLIANCE_FILE_PATH, goodE)
        return goodE;
    }
    std::cout << "未知商品类型，无法查询。" << std::endl;
    return nullptr;
}

// typeSortWrite函数 根据商品类型选择写入文件
std::ofstream typeSortWrite(UNUSE auto &goods_W) {
    if (typeid(goods_W) == typeid(DailyGoods)) {
        WRITE_DAILY_GOODS(DAILY_GOODS_FILE_PATH, goodD)
        return goodD;
    }
    if (typeid(goods_W) == typeid(Food)) {
        WRITE_FOOD(FOOD_FILE_PATH, goodF)
        return goodF;
    }
    if (typeid(goods_W) == typeid(ElectricalAppliance)) {
        WRITE_ELECTRICAL_APPLIANCE(ELECTRICAL_APPLIANCE_FILE_PATH, goodE)
        return goodE;
    }
    std::cout << "未知商品类型，无法查询。" << std::endl;
    return nullptr;
}

// searchGood函数 根据商品类型选择查找商品 并打印商品信息
void searchGood(auto &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            std::cout << "商品数量： [" << goods.goods_num[i] << "]" << std::endl;
            if (typeid(goods) == typeid(Food)) {
                std::cout << "保质期： [" << goods.shelf_life[i] << "]" << std::endl;
            } else if (typeid(goods) == typeid(ElectricalAppliance)) {
                std::cout << "颜色：" << goods.colour[i] << std::endl;
            }
            fileWrite(goods);
            WAIT
            return;
        }
    }
    std::cout << "未找到该商品" << std::endl;
    SLEEP
}

// addGood函数 根据商品类型选择添加商品及相关信息，若无目标商品则添加
void addGood(auto &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            int num;
            std::cout << "请输入要添加的商品的数量：";
            std::cin >> num;
            int temp = std::stoi(goods.goods_num[i]);
            temp += num;
            goods.goods_num[i] = std::to_string(temp);
            std::cout << "添加成功" << std::endl;
            fileWrite(goods);
            SLEEP
            return;
        }
    }
    goods.goods_name.push_back(search_name);
    std::string num;
    std::cout << "请输入要添加的商品的数量：";
    std::cin >> num;
    goods.goods_num.push_back(num);
    if (typeid(goods) == typeid(Food)) {
        std::cout << "请输入该商品的保质期：";
        std::cin >> num;
        goods.shelf_life.push_back(num);
    } else if (typeid(goods) == typeid(ElectricalAppliance)) {
        std::cout << "请输入该商品的颜色：";
        std::string colour;
        std::cin >> colour;
        goods.colour.push_back(colour);
    }
    std::cout << "添加成功" << std::endl;
    fileWrite(goods);
    SLEEP
}

// saleGood函数 出售商品 减少商品数量
inline void saleGood(Goods &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            int num;
            std::cout << "请输入要出售的商品的数量：";
            std::cin >> num;
            int temp = std::stoi(goods.goods_num[i]);
            if (num > temp) {
                std::cout << "货物库存不足" << std::endl;
                std::cout << search_name << "库存剩余" << goods.goods_num[i] << std::endl;
                WAIT
                return;
            }
            temp -= num;
            goods.goods_num[i] = std::to_string(temp);
            std::cout << "已出货" << std::endl;
            if (temp == 0) {
                goods.goods_name[i] = "0";
                std::cout << search_name << "库存已全部售罄" << std::endl;
            } else {
                std::cout << search_name << "库存剩余" << goods.goods_num[i] << std::endl;
            }
            SLEEP
            SLEEP
            return;
        }
    }
    std::cout << "未找到该商品" << std::endl;
    SLEEP
}

inline void chooseMoudle(const int choose, Goods &goods, const std::string &search_good_name) {
    if (choose == 1 || choose == 4) {
        searchGood(goods, search_good_name);
    } else if (choose == 2 || choose == 5) {
        addGood(goods, search_good_name);
    } else { saleGood(goods, search_good_name); }
}

// moduleCarryOut函数 根据商品类型读取文件 选择执行查找、添加、出售商品
inline void moduleCarryOut(Goods &goods, const int choose) {
    bool flag = false;
    do {
        CLS
        DIVIDE_LINE
        coutSentence(choose);
        fileRead(goods);
        std::string search_good_name;
        std::cin >> search_good_name;
        chooseMoudle(choose, goods, search_good_name);
        if (choose == 5 || choose == 6) {
            flag = true;
            DIVIDE_LINE
            std::cout << "是否继续？(是【1】/否【0】)" << std::endl;
            DIVIDE_LINE
            CHOOSE_BUTTON
            int temp;
            std::cin >> temp;
            if (temp == 0) { break; }
        }
    } while (flag);
}

inline void fileRead(Goods &goods) {
    goodsClear(goods);
    int index = 1;
    READER(reader)
    std::ifstream goodD = typeSort(goods);
    if (typeid(goods) == typeid(DailyGoods)) {
        while (goodD >> reader) {
            const std::string temp_name(reader);
            if (index == 1) {
                goods.goods_name.push_back(temp_name);
                ++index;
            } else if (index == 2) {
                goods.goods_num.push_back(temp_name);
                ++index;
            } else if (index == 3) {
                goods.timestamp.push_back(temp_name);
                index = 1;
            }
        }
    } else if (typeid(goods) == typeid(Food)) {
        while (goodD >> reader) {
            const std::string temp_name(reader);
            if (index == 1) {
                goods.goods_name.push_back(temp_name);
                ++index;
            } else if (index == 2) {
                goods.goods_num.push_back(temp_name);
                ++index;
            } else if (index == 3) {
                goods.shelf_life.push_back(temp_name);
                ++index;
            } else if (index == 4) {
                goods.timestamp.push_back(temp_name);
                index = 1;
            }
        }
    } else if (typeid(goods) == typeid(ElectricalAppliance)) {
        while (goodD >> reader) {
            const std::string temp_name(reader);
            if (index == 1) {
                goods.goods_name.push_back(temp_name);
                ++index;
            } else if (index == 2) {
                goods.goods_num.push_back(temp_name);
                ++index;
            } else if (index == 3) {
                goods.colour.push_back(temp_name);
                ++index;
            } else if (index == 4) {
                goods.timestamp.push_back(temp_name);
                index = 1;
            }
        }
    }
    FILE_CLOSE(goodD)
}

// fileWrite函数 根据商品类型选择写入文件
inline void fileWrite(Goods &goods) {
    const std::string temp = timestamp()[0] + "-" + timestamp()[1] + "-" + timestamp()[2];
    std::ofstream write = typeSortWrite(goods);
    if (typeid(goods) == typeid(DailyGoods)) {
        for (int i = 0; i < goods.goods_name.size(); ++i) {
            write << goods.goods_name[i] << " " << goods.goods_num[i] << " "
                    << temp << std::endl;
        }
    } else if (typeid(goods) == typeid(Food)) {
        for (int i = 0; i < goods.goods_name.size(); ++i) {
            write << goods.goods_name[i] << " "
                    << goods.goods_num[i] << " "
                    << goods.shelf_life[i] << " " << temp << std::endl;
        }
    } else if (typeid(goods) == typeid(ElectricalAppliance)) {
        for (int i = 0; i < goods.goods_name.size(); ++i) {
            write << goods.goods_name[i] << " "
                    << goods.goods_num[i] << " "
                    << goods.colour[i] << " " << temp << std::endl;
        }
    }
    FILE_CLOSE(write)
}

// Search函数 根据商品类型选择查找商品
void Supermarket::Search(auto &goods) {
    moduleCarryOut(goods, 1);
}

// Add函数 根据商品类型选择添加商品
void Supermarket::Add(auto &goods) {
    moduleCarryOut(goods, 2);
}

// Sale函数 根据商品类型选择出售商品
void Supermarket::Sale(auto &goods) {
    moduleCarryOut(goods, 3);
}

void Supermarket::searchPlus(auto &goods) {
    CLS
    goods.showMe();
}

void Supermarket::addPlus(auto &goods) {
    moduleCarryOut(goods, 5);
}

void Supermarket::salePlus(auto &goods) {
    moduleCarryOut(goods, 6);
}

void Supermarket::saleAllGoods(auto &goods) {
    fileRead(goods);
    goodsClear(goods);
    std::cout << "存货已清空。 " << std::endl;
    typeSortWrite(goods).clear();
    SLEEP
}

inline void Supermarket::showAllGoods(DailyGoods DG, Food F, ElectricalAppliance EA) {
    CLS
    if (DG.goods_name.empty()) { fileRead(DG); }
    if (F.goods_name.empty()) { fileRead(F); }
    if (EA.goods_name.empty()) { fileRead(EA); }
    if (DG.goods_name.empty() && F.goods_name.empty() && EA.goods_name.empty()) {
        std::cout << "暂无商品信息。" << std::endl;
        SLEEP
        return;
    }
    std::cout << std::setw(112) << std::setfill('=') << "=" << "\n"
            << LIST_HEAD_TOW_BLOCK_("日常用品")
            << LIST_HEAD_THREE_BLOCK_("食品类  ")
            << LIST_HEAD_THREE_BLOCK_("家电类  ")
            << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_);
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_SHELF_LIFE_);
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_COLOUR_) << std::endl;
    int i = 0, key1 = 0, key2 = 0, key3 = 0;
    while (true) {
        if (key1 == 1 || DG.goods_name.empty()) {
            std::cout << FORMAT_MOD_1_("空", "空");
            key1 = 1;
        } else {
            std::cout << FORMAT_MOD_1_(DG.goods_name[i], DG.goods_num[i]);
            if (DG.goods_name[i] == DG.goods_name.back()) { key1 = 1; }
        }
        if (key2 == 1 || F.goods_name.empty()) {
            std::cout << FORMAT_MOD_2_("空", "空", "空");
            key2 = 1;
        } else {
            std::cout << FORMAT_MOD_2_(F.goods_name[i], F.goods_num[i], F.shelf_life[i]);
            if (F.goods_name[i] == F.goods_name.back()) { key2 = 1; }
        }
        if (key3 == 1 || EA.goods_name.empty()) {
            std::cout << FORMAT_MOD_2_("空", "空", "空") << std::endl;
            key3 = 1;
        } else {
            std::cout << FORMAT_MOD_2_(EA.goods_name[i], EA.goods_num[i], EA.colour[i]) << std::endl;
            if (EA.goods_name[i] == EA.goods_name.back()) { key3 = 1; }
        }
        ++i;
        if (key1 == 1 && key2 == 1 && key3 == 1) {
            std::cout << std::setw(112) << std::setfill('=') << "=" << std::endl;
            break;
        }
    }
    WAIT
}

/**
 * 重载左移运算符, 输出商品信息
 * @param Out
 * @param goods
 * @return Out
 * @attention 此处如果使用了模板会造成与内置左移运算符调用的冲突。
 */
inline std::ostream &operator<<(std::ostream &Out, DailyGoods &goods) {
    goods.showMe();
    return Out;
};

inline std::ostream &operator<<(std::ostream &Out, Food &goods) {
    goods.showMe();
    return Out;
}

inline std::ostream &operator<<(std::ostream &Out, ElectricalAppliance &goods) {
    goods.showMe();
    return Out;
}

/**
 * @brief 重载右移运算符, 添加商品
 * @param cin
 * @param goods
 * @return cin
 * @attention 此处可以使用模板的原因是 此处的右移运算符写入对象是一个明确的对象 这个对象虽然有3种可能，但都被限定在supermarket此类中。
 * @attention 因此 此处可以用泛型模板来进行编程。
 */
template<typename T>
std::istream &operator>>(std::istream &cin, const T &goods) {
    Supermarket::Add(goods);
    return cin;
}
#endif //SUPERMARKEauto_H
