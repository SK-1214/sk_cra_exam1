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

	void update_attendDay(int day) {
		attend_day[day]++;

		if (day == WED || day == SAT || day == SUN) {
			mandatory_training = true;
		}
	}

	void add_point(int day) {
		if (day == WED){
			point += 3;
		}
		else if (day == SAT || day == SUN) {
			point += 2;
		}
		else{ 
			point++;
		}
	}

	bool IsAttendWedTrainingHard() {
		if (attend_day[WED] > 9) return true;
		else  return false;
	}

	bool IsAttendWeekendTrainingHard() {
		if (attend_day[SAT] + attend_day[SUN] > 9) return true;
		else  return false;
	}
	
	bool IsAttendMandatoryTraining() {
		return mandatory_training;
	}

	void IncreaseAdditionalPoint(int num) {
		point += num;
	}

	int get_point() {
		return point;
	}
private:
	int point;
	int attend_day[MAX_DAY];
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

void generate_PlayerInfo(string name, string day) {
	
	int player_id = get_playerID(name);
	int day_index = get_DayIndex(day);
	BASEBALL_PLAYER* pPlayer = &bplayer[player_id];

	pPlayer->add_point(day_index);
	pPlayer->update_attendDay(day_index);

}

void caculate_AdditionalPoints() {
	BASEBALL_PLAYER* pPlayer;

	for (int player_id = 1; player_id <= num_player; player_id++) {
		pPlayer = &bplayer[player_id];

		if (pPlayer->IsAttendWedTrainingHard() == true || pPlayer->IsAttendWeekendTrainingHard() == true) {
			pPlayer->IncreaseAdditionalPoint(10);
		}
	}
}

void print_PlayerScore()
{
	BASEBALL_PLAYER* pPlayer;
	int points;
	for (int player_id = 1; player_id <= num_player; player_id++) {
		pPlayer = &bplayer[player_id];
		points = pPlayer->get_point();

		cout << "NAME : " << names[player_id] << ", ";
		cout << "POINT : " << points << ", ";
		cout << "GRADE : ";

		if (points >= 50) {
			cout << "GOLD" << "\n";
		}
		else if (points >= 30) {
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
		if (points < 30 && mandatory_training[player_id] == false) {
			std::cout << names[player_id] << "\n";
		}
	}
}


int main() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력

	for (int i = 0; i < 500; i++) {
		string name, day;
		fin >> name >> day;
		generate_PlayerInfo(name, day);
	}

	caculate_AdditionalPoints();

	print_PlayerScore();

	return 0;
}
