#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// �ݳB�z�p�G�ۦP�����p 

void biggest(vector<string> &item, vector<size_t> &item_times)
{
	// ��X�̤j�ȩҦb��m 
	size_t biggest_times = 0;		// �̤j���� 
	size_t biggest_pos = 0;			// ��m 
	for(size_t i = 0; i < item_times.size(); ++i)
		if(item_times[i] > biggest_times){
			biggest_times = item_times[i];
			biggest_pos = i;
		}
		
	// �ˬd�O�_���ۦP�̤j��
	bool flag = false;
	vector<string> biggest_same{item[biggest_pos]};
	for(size_t i = 0; i < item.size(); ++i){
		if(item[i] != item[biggest_pos] && item_times[i] == item_times[biggest_pos]){
			flag = true;
			biggest_same.push_back(item[i]);
			cout << "���ۦP�̤j���ƪ�: " << item[i] << " " << item_times[i] << " ��" << endl; 
		}
	}
	if(!flag)
		cout << "\n\n�̦h���O:" << item[biggest_pos] << " " << "�`�@��: " << item_times[biggest_pos] << " ��" << endl; 
	else{
		cout << "\n�̤j�ۦP���Ƥ���@��...\n" << endl;
		cout << biggest_same[rand() % biggest_same.size()] << "���̲׵��G�I" << endl;
	}
}

void print(vector<string> &vec, vector<size_t> &record)
{
	// method 1
	for(size_t i = 0; i < vec.size(); ++i)
		cout << vec[i] << " " << record[i] << " ��" << endl; 
}

int main(void)
{
    ifstream ifs("D:/CPPstudy/menu.txt");
    
    srand(time(NULL));

	string str;
	vector<string> item;
    while(getline(ifs, str))
        item.push_back(str);
    
    // record �O�s�C�Ӧ�m���������� 
    vector<size_t> item_times(item.size(), 0);
    
    int t = 0;
    for(int i = 0; i < 9487123; ++i){
    	t = rand() % item.size(); 
    	++item_times[t];
    	// cout << t << " " << item[t] << endl; // �L�X�C�������G
	}
	
	print(item, item_times);
	biggest(item, item_times);

    return 0;
}
