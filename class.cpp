/*
�ϥ� class ���c�� whattoeattonight
- ��J
- �L�X
- ���`�B�z (�]�t�榡)
�W�z�w����
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
    // �]�t�n�L�X i, �ҥH�פ���󤣬O i < item.size() - 1
    for(size_t i = 0; i < this->item.size();){
        if(i + 1 < item.size() && this->item[i] == this->item[i+1]){
            this->times[i+1] += this->times[i];
            this->times.erase(this->times.begin() + i);
            this->item.erase(this->item.begin() + i);
        }
        else{
            cout << this->item[i] << " " << this->times[i] << endl;
            ++i;
            // �ѩ� erase �|���������A�ҥH�u�ݦb�D erase �ɻ��W i 
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
    // �Ĥ@����X�̤j��
    // �ĤG����X�P�̤j�ȬۦP����
    item_info same;
    size_t biggest = 0, pos = 0;

    for(size_t i = 0; i < this->times.size(); ++i){
        if(this->times[i] > biggest){
            biggest = this->times[i];
            pos = i;
        }   
    }

    // �T�{�O�_���̤j�Ȥ��u�@��
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
    stringstream ss(proportion); // stringstream �i�ϥ� >> �ާ@

    if(!(ss >> d) || ss >> c)
        return false; // �p�G�����ഫ���Ʀr or �i�H�ഫ�� char, �h���O�Ʀr
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