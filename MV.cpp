#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map> 
#include <ctime>
using namespace std;

void biggest(map<string, size_t> &record)
{
	string biggest_item_name;
	size_t biggest_item_times = 0;
	
	// �q����X�̤j�� 
	for(const auto& item : record)
		if(item.second > biggest_item_times){
			biggest_item_name = item.first;
			biggest_item_times = item.second;
		}	
	// cout << "\n�̦h���O:" << biggest_item_name << " " << "�`�@�X�{: " << biggest_item_times << " ��" << endl;
	
	// check
	bool flag = false;
	vector<string> same{biggest_item_name};
	for(map<string, size_t>::iterator it = record.begin(); it != record.end(); ++it){
		if(it->first != biggest_item_name && it->second == biggest_item_times){
			flag = true;
			same.push_back(it->first);
			cout << "���ۦP�̤j���ƪ�: " << it->first << " " << it->second << " ��" << endl;
		}	
	}
	
	// �̤j�ۦP���Ƥ���@�Ӭ��̲׵��G 
	if(flag){
		cout << "\n�̤j�ۦP���Ƥ���@�Ӭ��̲׵��G ...\n\n" << endl;	
		cout << same[rand() % same.size()] << " ���̲׵��G�I" << endl;
	}
	else
		cout << "\n�̦h���O:" << biggest_item_name << " " << "�`�@�X�{: " << biggest_item_times << " ��" << endl;
				 
}

void print(map<string, size_t> &record)
{
	// method1
	for(const auto &s : record){
		cout << s.first << " " << s.second << " ��" << endl;
	}
	cout << endl;
	
	// method2
	/*
	for(map<string, size_t>::iterator it = record.begin(); it != record.end(); ++it)
		cout << it->first << " " << it->second << endl;
	*/
}

int main(void)
{
	// vector<map<string, size_t>> vee{{{"kevin", 5}, {"jason", 4}}};
    ifstream ifs("menu.txt");
    
    // Ū�J�ɮ׫O�s�� item �� 
    string str;
    vector<string> item;
	map<string, size_t> record;
	
    while(getline(ifs, str)){
    	item.push_back(str);
    	record[str];					// initialize map (�U�оާ@�i�H�K�[������ map ��) 
	}
    
    srand(time(NULL));
    int t = 0;
    for(int i = 0; i < 9487123; ++i){
    	t = rand() % item.size();
    	++record[item[t]];				// �֥[�����W�٪�����
    	// cout << t << " " << item[t] << endl;	// �L�X�C�������G 
	}
	
	print(record);
	biggest(record);

    return 0;
}
