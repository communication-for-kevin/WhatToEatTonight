#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// 惠矪瞶狦薄猵 

void biggest(vector<string> &item, vector<size_t> &item_times)
{
	// т程┮竚 
	size_t biggest_times = 0;		// 程Ω计 
	size_t biggest_pos = 0;			// 竚 
	for(size_t i = 0; i < item_times.size(); ++i)
		if(item_times[i] > biggest_times){
			biggest_times = item_times[i];
			biggest_pos = i;
		}
		
	// 浪琩琌Τ程
	bool flag = false;
	vector<string> biggest_same{item[biggest_pos]};
	for(size_t i = 0; i < item.size(); ++i){
		if(item[i] != item[biggest_pos] && item_times[i] == item_times[biggest_pos]){
			flag = true;
			biggest_same.push_back(item[i]);
			cout << "Τ程Ω计: " << item[i] << " " << item_times[i] << " Ω" << endl; 
		}
	}
	if(!flag)
		cout << "\n\n程琌:" << item[biggest_pos] << " " << "羆Τ: " << item_times[biggest_pos] << " " << endl; 
	else{
		cout << "\n程Ω计い匡...\n" << endl;
		cout << biggest_same[rand() % biggest_same.size()] << "程沧挡狦" << endl;
	}
}

void print(vector<string> &vec, vector<size_t> &record)
{
	// method 1
	for(size_t i = 0; i < vec.size(); ++i)
		cout << vec[i] << " " << record[i] << " Ω" << endl; 
}

int main(void)
{
    ifstream ifs("D:/CPPstudy/menu.txt");
    
    srand(time(NULL));

	string str;
	vector<string> item;
    while(getline(ifs, str))
        item.push_back(str);
    
    // record 玂–竚じΩ计 
    vector<size_t> item_times(item.size(), 0);
    
    int t = 0;
    for(int i = 0; i < 9487123; ++i){
    	t = rand() % item.size(); 
    	++item_times[t];
    	// cout << t << " " << item[t] << endl; // –Ω挡狦
	}
	
	print(item, item_times);
	biggest(item, item_times);

    return 0;
}
