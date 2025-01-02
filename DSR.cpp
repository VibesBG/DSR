#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const unsigned short max_players = 100;
const unsigned short max_name_size = 15;
const unsigned short max_country_size = 15;

#define COLUMN_WIDTH_1 15
#define COLUMN_WIDTH_2 18
#define COLUMN_WIDTH_3 15
#define COLUMN_WIDTH_4 15
#define COLUMN_WIDTH_5 15
#define COLUMN_WIDTH_6 12
#define COLUMN_WIDTH_7 14
#define COLUMN_SEPARATORS 8

#define TABLE_WIDTH (COLUMN_WIDTH_1 + COLUMN_WIDTH_2 + COLUMN_WIDTH_3 + COLUMN_WIDTH_4 + COLUMN_WIDTH_5 + COLUMN_WIDTH_6 + COLUMN_WIDTH_7 + COLUMN_SEPARATORS)


struct player
{
	int number_in_tournament;
	int place_in_the_world;
	char first_name[max_name_size];
	char last_name[max_name_size];
	char country[max_country_size];
	int points;
	short trophies;
};

struct match 
{
	int player1_index;
	int player2_index;
	int player1_score;
	int player2_score;
	int winner_index;
};


void menu();
void submenu(player players[], int& player_counter);
void tournament_menu(player players[], int player_counter);
void pause();

void enter_players(player players[], int& player_counter);

void print_players(const player players[], int& player_counter);
void print_table_header();
void print_table_row(const player& p);
void print_table_footer();
void print_players(const player players[], int& player_counter);

void search_trophies(const player players[], int player_counter);
void search_country(const player players[], int player_counter);
void sort_world(player players[], int playerCount);

void save_to_file(const player players[], int player_counter);
void load_from_file(player players[], int& player_counter);

void sort_trophies(player players[], int player_counter);
void search_country_and_name(const player players[], int player_counter);

void create_matches(match matches[], int& match_counter, const player players[], int player_counter);
void add_results(match matches[], int match_counter, player players[]);
void create_elimination_matches(match matches[], int& match_counter, const match previous_round[], int previous_match_count);


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	player players[max_players];
	int player_counter = 0;

	int choice;

	load_from_file(players, player_counter);

	do
	{
		menu();
		cout << endl << "Въведи команда: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			enter_players(players, player_counter);
			break;
		case 2:
			system("cls");
			cout << "Списък на всички състезатели:" << endl;
			print_players(players, player_counter);
			break;
		case 3:
			system("cls");
			search_trophies(players, player_counter);
			break;
		case 4:
			system("cls");
			search_country(players, player_counter);
			break;
		case 5:
			system("cls");
			sort_world(players, player_counter);
			break;
		case 6:
			system("cls");
			save_to_file(players, player_counter);
			break;
		case 7:
			system("cls");
			load_from_file(players, player_counter);
			break;
		case 8:
		{
			system("cls");
			submenu(players, player_counter);
			break;
		}
		case 9:
			system("cls");
			tournament_menu(players, player_counter);
			break;
		case 0:
			system("cls");
			cout << endl << "Изход от програмата." << endl;
			save_to_file(players, player_counter);
			break;
		default:
			cout << endl << "Въведете валидна команда!" << endl;
		}

		if (choice != 0)
		{
			pause();
		}
	} while (choice != 0);

	return 0;
}

void menu()
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "\t\tМЕНЮ\t\t" << endl;
	cout << "1. Добавяне на състезатели в турнира." << endl;
	cout << "2. Извеждане на всички състезатели на екрана." << endl;
	cout << "3. Извеждане на състезатели с най-малко спечелени купи." << endl;
	cout << "4. Извеждане на състезатели от определена държава." << endl;
	cout << "5. Подреждане на състезателите в нарастващ ред на номера в световната ранглиста." << endl;
	cout << "6. Извеждане на масива със състезателите във файл." << endl;
	cout << "7. Въвеждане на масива със състезателите от файл." << endl;
	cout << "8. Подменю." << endl;
	cout << "9. Турнир." << endl;
	cout << "0. Изход." << endl;
}

void submenu(player players[], int& player_counter)
{
	system("cls");
	
	int sub_choice;

	do
	{
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "\t\tПОДМЕНЮ\t\t" << endl;
		cout << "1. Извеждане на спортистите в намаляващ ред на спечелените титли." << endl;
		cout << "2. Търсене и извеждане на състезател по държава и първо име." << endl;
		cout << "0. Връщане към главното меню." << endl;
		cout << endl << "Въведи команда: ";
		cin >> sub_choice;

		switch (sub_choice)
		{
		case 1:
			system("cls");
			sort_trophies(players, player_counter);
			break;
		case 2:
			system("cls");
			search_country_and_name(players, player_counter);
			break;
		case 0:
			system("cls");
			cout << endl << "Връщане към основното меню." << endl;
			break;
		default:
			system("cls");
			cout << endl << "Въведете валидна команда!" << endl;
		}

		if (sub_choice != 0)
		{
			pause();
		}
	} while (sub_choice != 0);
}

void tournament_menu(player players[], int player_counter)
{
	match matches[50];
	match next_round[50];
	int match_counter = 0;
	int next_round_counter = 0;

	int choice;

	do
	{
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "\t\tТурнирно меню\t\t" << endl;
		cout << "1. Съставяне на начални двубои." << endl;
		cout << "2. Въвеждане на резултати за двубоите." << endl;
		cout << "3. Съставяне на елиминационни двубои." << endl;
		cout << "0. Изход от турнира." << endl;
		cout << endl << "Въведете избор: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			create_matches(matches, match_counter, players, player_counter);
			break;
		case 2:
			system("cls");
			add_results(matches, match_counter, players);
			break;
		case 3:
			system("cls");
			create_elimination_matches(next_round, next_round_counter, matches, match_counter);

			match_counter = next_round_counter;
			for (int i = 0; i < match_counter; i++)
			{
				matches[i] = next_round[i];
			}
			break;
		case 0:
			system("cls");
			cout << "Изход от турнира." << endl;
			break;
		default:
			system("cls");
			cout << "Невалиден избор!" << endl;
		}

		if (choice != 0)
		{
			pause();
		}
	} while (choice != 0);
}

void pause() 
{
	cout << endl << "Натиснете Enter, за да продължите...";
	cin.ignore();
	cin.get();
	system("cls");
}

void enter_players(player players[], int& player_counter)
{
	if (player_counter >= max_players)
	{
		cout << endl << "Достигнат е максималният брой състезатели!" << endl;
		return;
	}

	int n;
	cout << endl << "Брой играчи, които желаете да въведете: ";
	cin >> n;

	if (player_counter + n > max_players)
	{
		cout << endl << "Не можете да въведете повече от " << max_players << " състезатели!" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		player p;
		cout << endl << "Играч " << i + 1 << ":" << endl;

		cout << "Номер в турнира: ";
		cin >> p.number_in_tournament;

		cout << "Номер в световната ранглиста: ";
		cin >> p.place_in_the_world;

		cout << "Име: ";
		cin >> p.first_name;

		cout << "Фамилия: ";
		cin >> p.last_name;

		cout << "Държава: ";
		cin >> p.country;

		cout << "Текущи точки: ";
		cin >> p.points;

		cout << "Спечелени купи: ";
		cin >> p.trophies;

		players[player_counter++] = p;
	}
}

void print_players(const player players[], int& player_counter)
{
	if (player_counter == 0)
	{
		cout << endl << "Няма въведени състезатели!" << endl;
		return;
	}

	print_table_header();

	for (int i = 0; i < player_counter; i++)
	{
		print_table_row(players[i]);
	}

	print_table_footer();
}

void print_table_header()
{
	cout << endl << setw(TABLE_WIDTH) << setfill('-') << "" << setfill(' ') << endl;
	cout << "|"
		<< setw(COLUMN_WIDTH_1) << left << "Номер в турнира" << "|"
		<< setw(COLUMN_WIDTH_2) << "Световна ранглиста" << "|"
		<< setw(COLUMN_WIDTH_3) << "Име" << "|"
		<< setw(COLUMN_WIDTH_4) << "Фамилия" << "|"
		<< setw(COLUMN_WIDTH_5) << "Държава" << "|"
		<< setw(COLUMN_WIDTH_6) << "Текущи точки" << "|"
		<< setw(COLUMN_WIDTH_7) << "Спечелени купи" << "|";
	cout << endl << setw(TABLE_WIDTH) << setfill('-') << "" << setfill(' ') << endl;
}

void print_table_row(const player& p)
{
	cout << "|"
		<< setw(COLUMN_WIDTH_1) << left << p.number_in_tournament << "|"
		<< setw(COLUMN_WIDTH_2) <<p.place_in_the_world << "|"
		<< setw(COLUMN_WIDTH_3) << p.first_name << "|"
		<< setw(COLUMN_WIDTH_4) << p.last_name << "|"
		<< setw(COLUMN_WIDTH_5) << p.country << "|"
		<< setw(COLUMN_WIDTH_6) << p.points << "|"
		<< setw(COLUMN_WIDTH_7) << p.trophies << "|"
		<< endl;
}

void print_table_footer()
{
	cout << setw(TABLE_WIDTH) << setfill('-') << "" << setfill(' ') << endl;
}

void search_trophies(const player players[], int player_counter)
{
	bool found = false;

	int min_trophies = players[0].trophies;
	for (int i = 1; i < player_counter; ++i)
	{
		if (players[i].trophies < min_trophies)
		{
			min_trophies = players[i].trophies;
			found = true;
		}
	}

	cout << endl << "Състезатели с най-малко спечелени купи:" << endl;

	print_table_header();

	for (int i = 0; i < player_counter; ++i)
	{
		if (players[i].trophies == min_trophies)
		{
			print_table_row(players [i]);
		}
	}

	if (!found) cout << "Няма намерени състезатели!" << endl;

	print_table_footer();
}

void search_country(const player players[], int player_counter)
{
	bool found = false;

	string country;
	cout << endl << "Въведете държава: ";
	cin >> country;

	system("cls");

	cout << endl << "Състезатели от " << country << ":" << endl;

	print_table_header();

	for (int i = 0; i < player_counter; ++i)
	{
		if (players[i].country == country)
		{
			print_table_row(players[i]);
			found = true;
		}
	}

	if (!found) cout << "Няма намерени състезатели!" << endl;

	print_table_footer();
}

void sort_world(player players[], int playerCount)
{
	cout << endl << "Състезателите са подредени по номер в световната ранглиста!" << endl;

	for (int i = 0; i < playerCount - 1; i++)
	{
		for (int j = i + 1; j < playerCount; j++)
		{
			if (players[i].place_in_the_world > players[j].place_in_the_world)
			{
				player temp = players[i];
				players[i] = players[j];
				players[j] = temp;
			}
		}
	}
}

void save_to_file(const player players[], int player_counter)
{
	ofstream file("players.bin", ios::out, ios::binary);
	if (!file)
	{
		cout << endl << "Възникна грешка при отварянето на файла!" << endl;
		return;
	}

	for (int i = 0; i < player_counter; ++i)
	{
		const player& p = players[i];
		file << p.number_in_tournament << " " << p.place_in_the_world << " "
			<< p.first_name << " " << p.last_name << " " << p.country << " "
			<< p.points << " " << p.trophies << endl;
	}

	file.close();
	cout << endl << "Състезателите са запазени!" << endl;
}

void load_from_file(player players[], int& player_counter)
{
	ifstream file("players.bin", ios::in, ios::binary);
	if (!file)
	{
		cout << endl << "Възникна грешка при зареждането на файла!" << endl;
		return;
	}

	player_counter = 0;
	while (file >> players[player_counter].number_in_tournament
		>> players[player_counter].place_in_the_world
		>> players[player_counter].first_name
		>> players[player_counter].last_name
		>> players[player_counter].country
		>> players[player_counter].points
		>> players[player_counter].trophies)
	{
		++player_counter;
		if (player_counter >= max_players) break;
	}

	file.close();
	cout << endl << "Състезателите са заредени от файла!" << endl;
}

void sort_trophies(player players[], int player_counter)
{
	for (int i = 0; i < player_counter - 1; i++)
	{
		for (int j = i + 1; j < player_counter; j++)
		{
			if ((players[i].trophies < players[j].trophies) || (players[i].trophies == players[j].trophies && players[i].place_in_the_world > players[j].place_in_the_world))
			{
				player temp = players[i];
				players[i] = players[j];
				players[j] = temp;
			}
		}
	}

	cout << endl << "Състезатели, подредени по титли:" << endl;

	print_table_header();

	for (int i = 0; i < player_counter; i++)
	{
		print_table_row(players[i]);
	}

	print_table_footer();
}

void search_country_and_name(const player players[], int player_counter)
{
	string country, name;
	cout << endl << "Въведете държава: ";
	cin >> country;
	cout << "Въведете първо име: ";
	cin >> name;

	system("cls");

	cout << "Състезатели с име (" << name << ") от държава (" << country << "):" << endl;

	bool found = false;

	print_table_header();

	for (int i = 0; i < player_counter; i++)
	{
		if (players[i].country == country && players[i].first_name == name)
		{
			print_table_row(players[i]);
			found = true;
		}
	}

	if (!found) cout << "Няма намерени състезатели!" << endl;

	print_table_footer();
}

void create_matches(match matches[], int& match_counter, const player players[], int player_counter)
{
	match_counter = 0;

	if (player_counter % 2 != 0)
	{
		cout << "Необходим е четен брой играчи за съставяне на двубои!" << endl;
		return;
	}

	for (int i = 0; i < player_counter; i += 2)
	{
		matches[match_counter].player1_index = i;
		matches[match_counter].player2_index = i + 1;
		matches[match_counter].player1_score = 0;
		matches[match_counter].player2_score = 0;
		matches[match_counter].winner_index = -1;
		match_counter++;
	}

	cout << "Съставени са двубои за турнира!" << endl;
}

void add_results(match matches[], int match_counter, player players[]) 
{
	for (int i = 0; i < match_counter; i++) 
	{
		match& m = matches[i];

		cout << "Двубой " << i + 1 << ": "
			<< players[m.player1_index].first_name << " vs "
			<< players[m.player2_index].first_name << endl;

		cout << "Въведете резултат за " << players[m.player1_index].first_name << ": ";
		cin >> m.player1_score;
		cout << "Въведете резултат за " << players[m.player2_index].first_name << ": ";
		cin >> m.player2_score;

		if (m.player1_score > m.player2_score) 
		{
			m.winner_index = m.player1_index;
		}
		else if (m.player2_score > m.player1_score) 
		{
			m.winner_index = m.player2_index;
		}
		else 
		{
			cout << "Резултатът е равен, повторете въвеждането!" << endl;
			i--;
			continue;
		}

		cout << "Победител: " << players[m.winner_index].first_name << endl;
	}
}

void create_elimination_matches(match matches[], int& match_counter, const match previous_round[], int previous_match_count) 
{
	match_counter = 0;

	for (int i = 0; i < previous_match_count; i += 2) 
	{
		if (previous_round[i].winner_index == -1 || previous_round[i + 1].winner_index == -1) 
		{
			cout << "Не всички двубои от предишния кръг са приключени!" << endl;
			return;
		}

		matches[match_counter].player1_index = previous_round[i].winner_index;
		matches[match_counter].player2_index = previous_round[i + 1].winner_index;
		matches[match_counter].player1_score = 0;
		matches[match_counter].player2_score = 0;
		matches[match_counter].winner_index = -1;
		match_counter++;
	}

	cout << "Съставени са елиминационни двубои!" << endl;
}