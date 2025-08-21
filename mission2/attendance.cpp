#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

#define MAX_NUM		(100)
#define MAX_PLAYER	(100)

enum {
	MON = 0,
	TUE = 1,
	WED = 2,
	THU = 3,
	FRI = 4,
	SAT = 5,
	SUN = 6,
	MAX_DAY = 7,
};

int attend_day[MAX_PLAYER][MAX_NUM];
int points[MAX_PLAYER];

string names[MAX_PLAYER];
bool mandatory_training[MAX_PLAYER];


map<string, int> player;

class BASEBALL_PLAYER {
public:
	string name;
	int id;
	int point;
	int attend_day[MAX_DAY];

	void update_attendDay(int day) {
		attend_day[day]++;
	}

	void add_point(int day) {
		point++;

		if (day == WED){
			point += 3;
			mandatory_training = true;
		}
		else if (day == SAT || day == SUN) {
			point += 2;
			mandatory_training = true;
		}
		else{ 
			point++;
		}
	}
private:
	bool mandatory_training = false;
};

BASEBALL_PLAYER bplayer[MAX_PLAYER];

int num_player = 0;

int get_playerID(std::string& name)
{
	//ID 부여
	if (player.count(name) == 0) {
		player.insert({ name, ++num_player });
		names[num_player] = name;
	}
	return player[name];
}

int get_DayIndex(string day) {
	int day_index;

	if (day == "monday") {
		day_index = MON;
	}
	if (day == "tuesday") {
		day_index = TUE;
	}
	if (day == "wednesday") {
		day_index = WED;
	}
	if (day == "thursday") {
		day_index = THU;
	}
	if (day == "friday") {
		day_index = FRI;
	}
	if (day == "saturday") {
		day_index = SAT;
	}
	if (day == "sunday") {
		day_index = SUN;
	}

	return day_index;
}

void update_trainingScore(int player_id, int day_index, int add_point) {

	attend_day[player_id][day_index] += 1;
	points[player_id] += add_point;
	if ((day_index == WED) || (day_index == SAT) || (day_index == SUN)) {
		mandatory_training[player_id] = true;
	}
}

void analize_attendance(string name, string day) {
	
	int player_id = get_playerID(name);
	int add_point = 0;
	int day_index = 0;

	add_point++;

	if (day == "monday") {
		day_index = MON;
	}
	if (day == "tuesday") {
		day_index = TUE;
	}
	if (day == "wednesday") {
		day_index = WED;
		add_point += 2;
	}
	if (day == "thursday") {
		day_index = THU;
	}
	if (day == "friday") {
		day_index = FRI;
	}
	if (day == "saturday") {
		day_index = SAT;
		add_point += 1;
	}
	if (day == "sunday") {
		day_index = SUN;
		add_point += 1;
	}
	//사용자ID별 요일 데이터에 1씩 증가
	update_trainingScore(player_id, day_index, add_point);
}

void caculate_result() {

	for (int player_id = 1; player_id <= num_player; player_id++) {
		if (attend_day[player_id][WED] > 9) {
			points[player_id] += 10;
		}

		if (attend_day[player_id][SAT] + attend_day[player_id][SUN] > 9) {
			points[player_id] += 10;
		}
	}
}

void print_socre()
{
	for (int player_id = 1; player_id <= num_player; player_id++) {

		cout << "NAME : " << names[player_id] << ", ";
		cout << "POINT : " << points[player_id] << ", ";
		cout << "GRADE : ";

		if (points[player_id] >= 50) {
			cout << "GOLD" << "\n";
		}
		else if (points[player_id] >= 30) {
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
		if (points[player_id] < 30 && mandatory_training[player_id] == false) {
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

	print_socre();

	return 0;
}
