#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <algorithm>

typedef std::pair<std::string, int> PAIR;

bool cmp_value(const PAIR& lhs, const PAIR& rhs){
		return lhs.second > rhs.second;
	}

int main(int argc, char* argv[]){
	if (argc < 2){
		std::cerr << "Usage: " << argv[0] << " topic-X.txt, where X = 0, 1, 2, 3, 4"<<std::endl;
		return 1;
	}
	std::map<int, int> data;
	std::map<std::string, int> vocab_map;
	std::map<int, int>::iterator it;
	std::string line;
	double min_sup = 0.01;
	int transcation = 0;
	int j = 0;
	std::string name;
	if ((argv[1][6] - '0') == 0) name = "data/topic-0.txt";
	else if ((argv[1][6] - '0') == 1) name = "data/topic-1.txt";
	else if ((argv[1][6] - '0') == 2) name = "data/topic-2.txt";
	else if ((argv[1][6] - '0') == 3) name = "data/topic-3.txt";
	else if ((argv[1][6] - '0') == 4) name = "data/topic-4.txt";;
	std::ifstream myfile(name);
	if (myfile.is_open()){
		while (getline(myfile,line)){
			transcation++;
			for (size_t i =0; i<line.length();i++){
				if (isspace(line[i])){
				int value = stoi(line.substr(j,i-j));
				if (data.count(value) > 0)
					data.at(value)++;
				else data.insert(std::pair<int, int>(value,1));
				j = i+1;
				}
			}
			j = 0;
		}
	}
	myfile.close();

	int absolute_sup = min_sup * transcation;
	it = data.begin();
	while (it !=data.end())
	{
		if (it->second < absolute_sup){
			it = data.erase(it);
	}
		else{
			++it;
		}
	}

	std::ifstream myfile2("data/vocab.txt");
	if (myfile2.is_open()){
		while (getline(myfile2,line)){
			int value = 0;
			std::string vocab = "";
			for (size_t i =0; i<line.length();i++){
				if (line[i] == 9){
				value = stoi(line.substr(0,i));
				vocab = line.substr(i+1,line.length()-i);
				}
			}
			if (data.count(value) > 0)
				vocab_map.insert(std::pair<std::string, int>(vocab, data[value]));
		}
	}
	myfile2.close();

	std::ofstream write;
	std::string file;
	if ((argv[1][6] - '0') == 0) file = "pattern-0.txt";
	else if ((argv[1][6] - '0') == 1) file = "pattern-1.txt";
	else if ((argv[1][6] - '0') == 2) file = "pattern-2.txt";
	else if ((argv[1][6] - '0') == 3) file = "pattern-3.txt";
	else if ((argv[1][6] - '0') == 4) file = "pattern-4.txt";
	write.open(file);
	std::vector<std::pair<std::string, int>> v(vocab_map.begin(), vocab_map.end());
	std::sort(v.begin(), v.end(), cmp_value);
	for (size_t i =0; i != v.size();i++)
	write<<v[i].second<<"\t"<< v[i].first<<"\n";

	write.close();
	return 0;
}