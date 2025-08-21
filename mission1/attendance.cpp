#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define MAX_NUM		(100)

using namespace std;

struct Node {
	string w;
	string wk;
};

map<string, int> player;
int num_player = 0;

//dat[사용자ID][요일]
int dat[MAX_NUM][MAX_NUM];
int points[MAX_NUM];
int grade[MAX_NUM];
string names[MAX_NUM];

int wed[MAX_NUM];
int weekend[MAX_NUM];

int get_playerID(std::string& name)
{
	//ID 부여
	if (player.count(name) == 0) {
		player.insert({ name, ++num_player });
		names[num_player] = name;
	}
	return player[name];
}

void analize_attendance(string name, string day) {
	
	int player_id = get_playerID(name);
	int add_point = 0;
	int day_index = 0;

	add_point++;

	if (day == "monday") {
		day_index = 0;
	}
	if (day == "tuesday") {
		day_index = 1;
	}
	if (day == "wednesday") {
		day_index = 2;
		add_point += 2;
		wed[player_id] += 1;
	}
	if (day == "thursday") {
		day_index = 3;
	}
	if (day == "friday") {
		day_index = 4;
	}
	if (day == "saturday") {
		day_index = 5;
		add_point += 1;
		weekend[player_id] += 1;
	}
	if (day == "sunday") {
		day_index = 6;
		add_point += 1;
		weekend[player_id] += 1;
	}

	//사용자ID별 요일 데이터에 1씩 증가
	dat[player_id][day_index] += 1;
	points[player_id] += add_point;
}

void caculate_result() {

	for (int player_id = 1; player_id <= num_player; player_id++) {
		if (dat[player_id][2] > 9) {
			points[player_id] += 10;
		}

		if (dat[player_id][5] + dat[player_id][6] > 9) {
			points[player_id] += 10;
		}

		if (points[player_id] >= 50) {
			grade[player_id] = 1;
		}
		else if (points[player_id] >= 30) {
			grade[player_id] = 2;
		}
		else {
			grade[player_id] = 0;
		}

		cout << "NAME : " << names[player_id] << ", ";
		cout << "POINT : " << points[player_id] << ", ";
		cout << "GRADE : ";

		if (grade[player_id] == 1) {
			cout << "GOLD" << "\n";
		}
		else if (grade[player_id] == 2) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
		}
	}

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int player_id = 1; player_id <= num_player; player_id++) {

		if (grade[player_id] != 1 && grade[player_id] != 2 && wed[player_id] == 0 && weekend[player_id] == 0) {
			std::cout << names[player_id] << "\n";
		}
	}
}

int main() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

	for (int i = 0; i < 500; i++) {
		string name, day;
		fin >> name >> day;
		analize_attendance(name, day);
	}

	caculate_result();
}