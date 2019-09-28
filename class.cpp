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
    void test_print();
    void print(); // will delete same
    void biggest();
    void random(size_t n);
    inline size_t size()
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

void item_info::test_print()
{
    for (size_t i = 0; i < this->size(); ++i)
        cout << this->item[i] << " " << this->times[i] << endl;
    
}

void item_info::print()
{   
    // 包含要印出 i, 所以終止條件不是 i < item.size() - 1
    for(size_t i = 0; i < this->item.size();){
        if(i + 1 < item.size() && this->item[i] == this->item[i+1]){
            this->times[i+1] += this->times[i];
            this->times.erase(this->times.begin() + i);
            this->item.erase(this->item.begin() + i);
        }
        else{
            cout << this->item[i] << " " << this->times[i] << endl;
            ++i;
            // 由於 erase 會移除元素，所以只需在非 erase 時遞增 i 
        }
    }
}

void item_info::random(size_t n)
{
    srand(time(NULL));
    size_t t = 0;
    for(size_t i = 0; i < n; ++i){
        t = rand() % this->item.size();
        ++this->times[t];
        cout << t << " " << this->item[t] << endl;
    }
}

void item_info::biggest()
{
    // 第一次找出最大值
    // 第二次找出與最大值相同的值
    item_info same;
    size_t biggest = 0, pos = 0;

    for(size_t i = 0; i < this->times.size(); ++i){
        if(this->times[i] > biggest){
            biggest = this->times[i];
            pos = i;
        }   
    }

    // 確認是否有最大值不只一個
    bool flag = false;
    for(size_t i = 0; i < this->times.size(); ++i){
        if(biggest == this->times[i] && i != pos){
            same.item.push_back(this->item[i]);
            same.times.push_back(this->times[i]); 
            flag = true;
        }
    }

    if(!flag)
        cout << "biggest is " << this->item[pos] << " " << this->times[pos] << endl;
    else{
        cout << "more than one maximum, and one final result will be randomly selected from them." << endl;
        size_t i = rand() % same.item.size();
        cout << "the final result is: " << same.item[i] << " " << same.times[i] << endl;
    }
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
    string filepath("C:/Users/create_vars/Documents/cpprepos/whattoeattonight/menu.txt");
    ifstream ifs(filepath);
    item_info list;

    check(filepath);
    list.input(filepath);
    list.test_print();
    list.random(10);
    list.print();
    list.biggest();

    return 0;
}