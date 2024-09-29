#ifndef SUPERMARKEauto_H
#define SUPERMARKEauto_H
#include <iostream> // ��׼���������
#include <string> // �ַ�����
#include <vector>
#include "constSpace.h" // �����ռ�
#include "timePure.h" // ʱ���
#include "pageDependencies.h" // �˵�����

// ��Ʒ�� ������ࡣ �����಻����������ֻ��ͨ�������ഴ������
class Goods {
public:
    Goods() = default; // Ĭ�Ϲ��캯��
    virtual ~Goods() = default; //  ���飩Ĭ���������� ����ȷ����ͨ������ָ��ɾ�����������ʱ���ܹ���ȷ���õ����������������
    Goods &operator=(const Goods &goods_new) = default;

    virtual void showMe() = 0; // �麯��
    std::vector<std::string> goods_name{}; // ��Ʒ����
    std::vector<std::string> goods_num{}; // ��Ʒ����
    std::vector<std::string> shelf_life{}; // ������
    std::vector<std::string> colour{}; // ��ɫ
    std::vector<std::string> timestamp{}; // ���ʱ�� ʱ�����
};

// �ճ���Ʒ��
class DailyGoods final : public Goods {
public:
    // DailyGoods�����̳���Goods �Ҳ�����������¼̳�
    DailyGoods() = default; // Ĭ�Ϲ��캯��
    ~DailyGoods() override = default; // ��дĬ����������
    void showMe() override; // �麯����д������ʾ�ճ���Ʒ�ġ����ơ�����������
    DailyGoods &operator=(const DailyGoods &);
};

// ʳƷ��
class Food final : public Goods {
public:
    Food() = default; // Ĭ�Ϲ��캯��:
    ~Food() override = default; // ��дĬ����������
    void showMe() override; // �麯����д������ʾʳ��ġ����ơ����������Լ��������ڡ���
    Food &operator=(const Food &);
};

inline void fileWrite(Goods &goods);

inline void fileRead(Goods &goods);

// ������
class ElectricalAppliance final : public Goods {
public:
    ElectricalAppliance() = default; // Ĭ�Ϲ��캯��
    ~ElectricalAppliance() override = default; // ��дĬ����������
    void showMe() override; // �麯����д������ʾ�ҵ�ġ����ơ����������Լ�����ɫ����
    ElectricalAppliance &operator=(const ElectricalAppliance &);
};

/**
 * @brief ������
 * @details �����࣬���ڹ�����Ʒ��֧����ӡ����ۡ���ѯ������֧�ֹ�����Ʒ�����鿴
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

    static void Add(auto &goods); // �����Ʒ
    static void Sale(auto &goods); // ������Ʒ         `
    static void Search(auto &goods); // ��ѯ��Ʒ
    static void showAllGoods(DailyGoods DG, Food F, ElectricalAppliance EA);

    static void addPlus(auto &goods); // ���������Ʒ
    static void salePlus(auto &goods); // ����������Ʒ         `
    static void searchPlus(auto &goods); // ��ѯ������Ʒ
    static void saleAllGoods(auto &goods); // ��������������Ʒ

    DailyGoods goods_d{};
    Food goods_f{};
    ElectricalAppliance goods_e{};
};

/*
 * ���ڲ�����SautoL���ͱ�������޷�д��ͷ�ļ�����Դ�ļ�ʵ�ֵ���ʽ
 * �ʺ���ΪĿ���������з�ʽ��ʵ�֡�
 *
 *
 * GoodsĬ�Ϻ���ʵ�֡�
 * Goods�������麯��������ʵ��
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

// ��ʾ�ճ���Ʒ�ġ����ơ�����������
inline void DailyGoods::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "�ճ���Ʒ������Ʒ��Ϣ��" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_TOW_BLOCK_("�ճ���Ʒ") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_1_(goods_name[i], goods_num[i]) << std::endl;
    }
    WAIT
}

// ��ʾʳ��ġ����ơ����������Լ��������ڡ���
inline void Food::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "ʳƷ������Ʒ��Ϣ��" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_THREE_BLOCK_("ʳƷ��  ") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_SHELF_LIFE_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_2_(goods_name[i], goods_num[i], shelf_life[i]) << std::endl;
    }
    WAIT
}

// ��ʾ�ҵ�ġ����ơ����������Լ�����ɫ����
inline void ElectricalAppliance::showMe() {
    fileRead(*this);
    if (goods_name.empty()) {
        std::cout << "����������Ʒ��Ϣ��" << std::endl;
        SLEEP
        return;
    }
    std::cout << LIST_HEAD_THREE_BLOCK_("�ҵ���  ") << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_COLOUR_) << std::endl;
    for (int i = 0; i < goods_name.size(); ++i) {
        std::cout << FORMAT_MOD_2_(goods_name[i], goods_num[i], colour[i]) << std::endl;
    }
    WAIT
}

// coutSentence���� ��ʾ��ʾ��
inline void coutSentence(const int choose) {
    if (choose == 1 || choose == 4) std::cout << "������Ҫ���ҵ���Ʒ���ƣ�";
    if (choose == 2 || choose == 5) std::cout << "������Ҫ��ӵ���Ʒ���ƣ�";
    if (choose == 3 || choose == 6) std::cout << "������Ҫ���۵���Ʒ���ƣ�";
}

inline void goodsClear(Goods &goods) {
    goods.goods_name.clear();
    goods.goods_num.clear();
    goods.shelf_life.clear();
    goods.colour.clear();
    goods.timestamp.clear();
}

// typeSort���� ������Ʒ����ѡ���ȡ�ļ�
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
    std::cout << "δ֪��Ʒ���ͣ��޷���ѯ��" << std::endl;
    return nullptr;
}

// typeSortWrite���� ������Ʒ����ѡ��д���ļ�
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
    std::cout << "δ֪��Ʒ���ͣ��޷���ѯ��" << std::endl;
    return nullptr;
}

// searchGood���� ������Ʒ����ѡ�������Ʒ ����ӡ��Ʒ��Ϣ
void searchGood(auto &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            std::cout << "��Ʒ������ [" << goods.goods_num[i] << "]" << std::endl;
            if (typeid(goods) == typeid(Food)) {
                std::cout << "�����ڣ� [" << goods.shelf_life[i] << "]" << std::endl;
            } else if (typeid(goods) == typeid(ElectricalAppliance)) {
                std::cout << "��ɫ��" << goods.colour[i] << std::endl;
            }
            fileWrite(goods);
            WAIT
            return;
        }
    }
    std::cout << "δ�ҵ�����Ʒ" << std::endl;
    SLEEP
}

// addGood���� ������Ʒ����ѡ�������Ʒ�������Ϣ������Ŀ����Ʒ�����
void addGood(auto &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            int num;
            std::cout << "������Ҫ��ӵ���Ʒ��������";
            std::cin >> num;
            int temp = std::stoi(goods.goods_num[i]);
            temp += num;
            goods.goods_num[i] = std::to_string(temp);
            std::cout << "��ӳɹ�" << std::endl;
            fileWrite(goods);
            SLEEP
            return;
        }
    }
    goods.goods_name.push_back(search_name);
    std::string num;
    std::cout << "������Ҫ��ӵ���Ʒ��������";
    std::cin >> num;
    goods.goods_num.push_back(num);
    if (typeid(goods) == typeid(Food)) {
        std::cout << "���������Ʒ�ı����ڣ�";
        std::cin >> num;
        goods.shelf_life.push_back(num);
    } else if (typeid(goods) == typeid(ElectricalAppliance)) {
        std::cout << "���������Ʒ����ɫ��";
        std::string colour;
        std::cin >> colour;
        goods.colour.push_back(colour);
    }
    std::cout << "��ӳɹ�" << std::endl;
    fileWrite(goods);
    SLEEP
}

// saleGood���� ������Ʒ ������Ʒ����
inline void saleGood(Goods &goods, const std::string &search_name) {
    for (int i = 0; i < goods.goods_name.size(); ++i) {
        if (goods.goods_name[i] == search_name) {
            int num;
            std::cout << "������Ҫ���۵���Ʒ��������";
            std::cin >> num;
            int temp = std::stoi(goods.goods_num[i]);
            if (num > temp) {
                std::cout << "�����治��" << std::endl;
                std::cout << search_name << "���ʣ��" << goods.goods_num[i] << std::endl;
                WAIT
                return;
            }
            temp -= num;
            goods.goods_num[i] = std::to_string(temp);
            std::cout << "�ѳ���" << std::endl;
            if (temp == 0) {
                goods.goods_name[i] = "0";
                std::cout << search_name << "�����ȫ������" << std::endl;
            } else {
                std::cout << search_name << "���ʣ��" << goods.goods_num[i] << std::endl;
            }
            SLEEP
            SLEEP
            return;
        }
    }
    std::cout << "δ�ҵ�����Ʒ" << std::endl;
    SLEEP
}

inline void chooseMoudle(const int choose, Goods &goods, const std::string &search_good_name) {
    if (choose == 1 || choose == 4) {
        searchGood(goods, search_good_name);
    } else if (choose == 2 || choose == 5) {
        addGood(goods, search_good_name);
    } else { saleGood(goods, search_good_name); }
}

// moduleCarryOut���� ������Ʒ���Ͷ�ȡ�ļ� ѡ��ִ�в��ҡ���ӡ�������Ʒ
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
            std::cout << "�Ƿ������(�ǡ�1��/��0��)" << std::endl;
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

// fileWrite���� ������Ʒ����ѡ��д���ļ�
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

// Search���� ������Ʒ����ѡ�������Ʒ
void Supermarket::Search(auto &goods) {
    moduleCarryOut(goods, 1);
}

// Add���� ������Ʒ����ѡ�������Ʒ
void Supermarket::Add(auto &goods) {
    moduleCarryOut(goods, 2);
}

// Sale���� ������Ʒ����ѡ�������Ʒ
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
    std::cout << "�������ա� " << std::endl;
    typeSortWrite(goods).clear();
    SLEEP
}

inline void Supermarket::showAllGoods(DailyGoods DG, Food F, ElectricalAppliance EA) {
    CLS
    if (DG.goods_name.empty()) { fileRead(DG); }
    if (F.goods_name.empty()) { fileRead(F); }
    if (EA.goods_name.empty()) { fileRead(EA); }
    if (DG.goods_name.empty() && F.goods_name.empty() && EA.goods_name.empty()) {
        std::cout << "������Ʒ��Ϣ��" << std::endl;
        SLEEP
        return;
    }
    std::cout << std::setw(112) << std::setfill('=') << "=" << "\n"
            << LIST_HEAD_TOW_BLOCK_("�ճ���Ʒ")
            << LIST_HEAD_THREE_BLOCK_("ʳƷ��  ")
            << LIST_HEAD_THREE_BLOCK_("�ҵ���  ")
            << std::endl;
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_);
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_SHELF_LIFE_);
    std::cout << OBJ_STD_HEAD_(HEAD_NAME_) << OBJ_STD_HEAD_(HEAD_NUM_) << OBJ_STD_HEAD_(HEAD_COLOUR_) << std::endl;
    int i = 0, key1 = 0, key2 = 0, key3 = 0;
    while (true) {
        if (key1 == 1 || DG.goods_name.empty()) {
            std::cout << FORMAT_MOD_1_("��", "��");
            key1 = 1;
        } else {
            std::cout << FORMAT_MOD_1_(DG.goods_name[i], DG.goods_num[i]);
            if (DG.goods_name[i] == DG.goods_name.back()) { key1 = 1; }
        }
        if (key2 == 1 || F.goods_name.empty()) {
            std::cout << FORMAT_MOD_2_("��", "��", "��");
            key2 = 1;
        } else {
            std::cout << FORMAT_MOD_2_(F.goods_name[i], F.goods_num[i], F.shelf_life[i]);
            if (F.goods_name[i] == F.goods_name.back()) { key2 = 1; }
        }
        if (key3 == 1 || EA.goods_name.empty()) {
            std::cout << FORMAT_MOD_2_("��", "��", "��") << std::endl;
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
 * �������������, �����Ʒ��Ϣ
 * @param Out
 * @param goods
 * @return Out
 * @attention �˴����ʹ����ģ������������������������õĳ�ͻ��
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
 * @brief �������������, �����Ʒ
 * @param cin
 * @param goods
 * @return cin
 * @attention �˴�����ʹ��ģ���ԭ���� �˴������������д�������һ����ȷ�Ķ��� ���������Ȼ��3�ֿ��ܣ��������޶���supermarket�����С�
 * @attention ��� �˴������÷���ģ�������б�̡�
 */
template<typename T>
std::istream &operator>>(std::istream &cin, const T &goods) {
    Supermarket::Add(goods);
    return cin;
}
#endif //SUPERMARKEauto_H
