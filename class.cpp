/*
使用 class 重構的 whattoeattonight
- 輸入
- 印出
- 異常處理 (包含格式)
上述已完成
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
using namespace std;

class item_info{
public:
    item_info() = default;
    item_info(initializer_list<string>& name, initializer_list<size_t>& i) : item(name), times(i) {}
    void input(string &filepath);
    void print();
    size_t size()
    {
        if(this->item.size() != this->times.size())
            throw runtime_error("item size not equal times size");
        else
            return this->item.size();
    }
private:
    vector<string> item;
    vector<size_t> times;
};

void item_info::input(string& filepath)
{
    ifstream ifstemp(filepath);
    string name, proportion;
    
    // list item name 
    while(ifstemp >> name >> proportion)
        for (size_t i = 0; i < static_cast<size_t>(stoi(proportion)); ++i)
            this->item.push_back(name);

    // list item times
    for (size_t i = 0; i < this->item.size(); ++i)
        this->times.push_back(0);

    ifstemp.close();
}

void item_info::print()
{
    for (size_t i = 0; i < this->size(); ++i)
        cout << this->item[i] << " " << this->times[i] << endl;
    
}

bool isnum(string& proportion)
{
    double d;
    char c;
    stringstream ss(proportion); // stringstream 可使用 >> 操作

    if(!(ss >> d) || ss >> c)
        return false; // 如果不能轉換成數字 or 可以轉換為 char, 則不是數字
    return true;
}

void check(string& filepath)
{
    ifstream ifs(filepath);
    if(!ifs){
        throw runtime_error("can not find file!");
    }

    size_t times = 0;
    string str, proportion;
    while(ifs >> str >> proportion){
        if(!isnum(proportion))
            throw runtime_error("no input corrcet proportion!");
        if(stoi(proportion) < 1)
            throw runtime_error("proportion must be greater then or equal to one.");
        ++times;
    }
    if(times < 2)
        throw runtime_error("At least two items are required in the file");

    ifs.close();
}

int main(void)
{
    string filepath("menu2.txt");
    ifstream ifs(filepath);
    item_info list;

    check(filepath);
    list.input(filepath);
    list.print();

    return 0;
}