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
	
	// 從中找出最大的 
	for(const auto& item : record)
		if(item.second > biggest_item_times){
			biggest_item_name = item.first;
			biggest_item_times = item.second;
		}	
	// cout << "\n最多的是:" << biggest_item_name << " " << "總共出現: " << biggest_item_times << " 次" << endl;
	
	// check
	bool flag = false;
	vector<string> same{biggest_item_name};
	for(map<string, size_t>::iterator it = record.begin(); it != record.end(); ++it){
		if(it->first != biggest_item_name && it->second == biggest_item_times){
			flag = true;
			same.push_back(it->first);
			cout << "有相同最大次數者: " << it->first << " " << it->second << " 次" << endl;
		}	
	}
	
	// 最大相同次數中選一個為最終結果 
	if(flag){
		cout << "\n最大相同次數中選一個為最終結果 ...\n\n" << endl;	
		cout << same[rand() % same.size()] << " 為最終結果！" << endl;
	}
	else
		cout << "\n最多的是:" << biggest_item_name << " " << "總共出現: " << biggest_item_times << " 次" << endl;
				 
}

void print(map<string, size_t> &record)
{
	// method1
	for(const auto &s : record){
		cout << s.first << " " << s.second << " 次" << endl;
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
    
    // 讀入檔案保存到 item 中 
    string str;
    vector<string> item;
	map<string, size_t> record;
	
    while(getline(ifs, str)){
    	item.push_back(str);
    	record[str];					// initialize map (下標操作可以添加元素至 map 中) 
	}
    
    srand(time(NULL));
    int t = 0;
    for(int i = 0; i < 9487123; ++i){
    	t = rand() % item.size();
    	++record[item[t]];				// 累加對應名稱的次數
    	// cout << t << " " << item[t] << endl;	// 印出每次的結果 
	}
	
	print(record);
	biggest(record);

    return 0;
}
