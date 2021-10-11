#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctype.h>

class Student
{
public:
	std::string name;
	int student_id;
	int birth_year;
	std::string department;
	std::string telephone;

	Student(std::string line)
	{ 
		std::vector<std::string> parse;
		std::istringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ',')) parse.push_back(token);

		name = parse[0];
		student_id = std::stoi(parse[1]);
		birth_year = std::stoi(parse[2]);
		department = parse[3];
		telephone = parse[4];
	}

	Student(std::string nm, int stdid, int birth, std::string depart, std::string tel)
	{
		name = nm;
		student_id = stdid;
		birth_year = birth;
		department = depart;
		telephone = tel;

	}

	std::string GetStudent()
	{
		return name + "," +
			std::to_string(student_id) + "," +
			std::to_string(birth_year) + "," +
			department + "," +
			telephone;
	}
};

std::string file;
std::vector<Student> student_info;

void ReadAll()
{
	std::ifstream fin(file);
	if (!fin.is_open())
	{
		std::cout << "Since the file doesn't exist, it creates a new file.\n";
		std::ofstream make_file(file);
		make_file.close();
		return;
	}

	while (!fin.eof())
	{
		std::string line;
		std::getline(fin, line);
		if (line.empty()) break;
		Student s(line);
		student_info.push_back(s);
	}
	fin.close();
}

void WriteAll()
{
	std::ofstream fout(file);
	for (Student student : student_info) fout << student.GetStudent() << std::endl;
	fout.close();
}

void WriteLine(Student student)
{
	student_info.push_back(student);
	std::ofstream fout(file, std::ios::out | std::ios::app);
	fout << student.GetStudent() << std::endl;
	fout.close();
}


bool isDigitOnly(std::string in)
{
	for (int i = 0; i < in.length(); i++)
	{
		if (!isdigit(in[i])) {
			return false;
		}

	}
	return true;

}

bool isCharOnly(std::string in)
{
	for (int i = 0; i < in.length(); i++) // for (�ʱⰪ; �ݺ���� ; ������� ) 
	{
		if (isdigit(in[i])) 
		{
			return false;
		}
	}
	return true;

}


// trim from left 
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}
// trim from right 
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from left & right 
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
	return ltrim(rtrim(s, t), t);
}


void Insertion() // ����

{
	// �̸� �Է�

	std::string name;
	

	for (;;)
	{
		std::cout << "\nEnter student's name : ";
		std::cin.ignore(); // cin�� whitespace�� ����? �ϰ� getline��� �� �ޱ�
		std::getline(std::cin, name);
		trim(name);
		std::cout << name << "\n";


		if (name.empty())
		{

			// ����
			std::cout << "Please enter the name.\n";
			//std::cin.ignore(); // ���͵� ������ �ν��ϱ� ��ؼ� ignore ���� ���.
			continue;
		}


		if (name.length() > 15)
		{
			// ����
			std::cout << "Please enter shorter name. you can enter up to 15 digits.\n";
			continue;
		}
		
		if (!isCharOnly(name))
		{
			// ����
			std::cout << "\nPlease enter correct name.(charactor only)\nyou should enter charactor. your input=" << name << "\n";
			continue;
		}

			break;
		
		// 에러
		std::cout << "\nPlease enter the name.\n\n";
		return;
	}

	// 학번
	int stdid;

	
	//std::cin.ignore();
	
	for (;;)
	{
		std::cout << "Enter student id: ";
		//std::cin.ignore();

		if (!(std::cin >> stdid)) { //0
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nPlease enter correct student id(digit).\nyou should enter 10 digits. your input=" << stdid << "\n";
			// std::cin.ignore();
		}


		if (stdid < 1000000000 || stdid > 9999999999) // 10�ڸ� Ȯ��
		{
			// �ڸ��� ����
			std::cout << "Please enter correct student ID(range). you should enter 10 digits. your input=" << stdid << "\n";
			//std::cin.ignore();
			continue;
		}

		if (stdid < 1918000000 || stdid > 2077000000) // ���� Ȯ��.. ���Ƿ� 1918~2077�� ���
		{
			// �й� ����
			std::cout << "Please enter correct student ID.\n Student IDs can only be entered from 1900 to 2077. your input=" << stdid << "\n";
			//std::cin.ignore();
			continue;
		}

		// �ߺ�üũ
		bool exist = false;

		for (Student student : student_info)
		{
			if (student.student_id == stdid)
			{
				// ����
				std::cout << "\nError : Already inserted\n";
				exist = true;
				break;
			}
		}

		if (exist) continue;
		else break;

	}


	// 생년
	int birth;

	//std::cout << "Enter student's birth year:";
	/*
	if (!(std::cin >> birth))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	*/

	for (;;)
	{
		std::cout << "Enter student's birth year : ";
		//std::cin.ignore();

		if (!(std::cin >> birth))  // ���ڰ� �ƴϸ� 0 �� ��ȯ, ���ڸ� true
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits. your input=" << birth << "\n";
			// std::cin.ignore();
			continue;
		}
		

		if (birth < 1000 || birth > 9999)
		{
			// ����
			std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits. your input=" << birth << "\n";
			std::cin.ignore();
			continue;
		}
		//std::cout << "your input=" << birth << "\n";
		break;

	}


	/**
	if (birth.length() < 4) {
		// 에러
		return;
	}
	birth = birth.substr(0, 4); // 앞의 4자리?
	**/


	// �а�

	std::string depart;
	std::cout << "Enter student's department:";
	// std::cin >> depart;
	std::cin.ignore();
	std::getline(std::cin, depart); // 공백도 받게


	// 전화번호
	std::string tel;


	// 12�ڸ� üũ

	for (;;)
	{
		std::cout << "Enter student's TEL number : ";

		std::cin >> tel;
		trim(tel);

		if (tel.length() > 12 || tel.length() < 10) //�ִ� 12�ڸ�
		{
			// ����
			std::cout << "\nPlease enter correct TEL.(length)\nyou should enter 11 to 12 digits. your input=" << tel << "\n";
			//std::cin.ignore();
			continue;
		}

		if (!isDigitOnly(tel)) 
		{
			// ����
			std::cout << "\nPlease enter correct TEL.(number only)\nyou should enter number. your input=" << tel << "\n";

			continue;
		}

		break;
	}

	// 저장
	Student s(name, stdid, birth, depart, tel);

	WriteLine(s);
	std::cout << "\nsaved successfully!\n\n";

}


void SearchName()
{
	int num = 0;
	std::string name;

	std::cout << "Please input your name.\n";
	std::cin.ignore();
	std::getline(std::cin, name);

	for (Student student : student_info) 
	{
		if (student.name == name) 
		{
			num++;
			std::cout << student.name + "," << std::endl;
			std::cout << std::to_string(student.student_id) + "," << std::endl; 
			std::cout << std::to_string(student.birth_year) + "," << std::endl; 
			std::cout << student.department + "," << std::endl;
			std::cout << student.telephone + '\n' << std::endl;
		}
	}

	std::cout << "Total " << num << " student was found.\n";
}

void SearchId() 
{
	int num = 0;
	std::string id ;
	long long id_changed = 0; // 10자리 수를 받기 위하여 long long을 사용.

	std::cout << "Please input your student ID. (10 numbers)\n";
	std::cin >> id;

	// Digit check
	if (!isDigitOnly(id)) 
	{
		std::cout << "Please input correct ID.\nYou should enter number. \n";
		SearchId();
	}
	else 
	{
		id_changed = stoll(id); // String to long long

		// Range check
		if (id_changed < 1000000000 || id_changed >= 10000000000)
		{
			std::cout << "You input wrong ID.\n";
			SearchId();
		}
		// 기존 방식에서는 input wrong ID 인 상태에서도 Total ~ student was found 가 출력되었기 때문에, else문 안에 넣어서 처리하였음.
		else
		{
			for (Student student : student_info)
			{
				if (static_cast<long long>(student.student_id) == id_changed) // vector안의 값을 long long으로 형변환
				{
					num++;
					std::cout << student.name + "," << std::endl;
					std::cout << std::to_string(student.student_id) + "," << std::endl;
					std::cout << std::to_string(student.birth_year) + "," << std::endl;
					std::cout << student.department + "," << std::endl;
					std::cout << student.telephone + '\n' << std::endl;
				}
			}

			std::cout << "Total " << num << " student was found.\n";
		}
	}	
}

void SearchYear() 
{
	int num = 0;
	std::string year;
	int year_changed = 0;

	std::cout << "Please input your admission year. (4 numbers)\n";
	std::cin >> year;

	// Digit check
	if (!isDigitOnly(year))
	{
		std::cout << "Please input correct year.\nYou should enter number. \n";
		SearchYear();
	}
	else 
	{
		year_changed = stoi(year); // String to int

		// Range check
		if (year_changed < 1000 || year_changed >= 10000)
		{
			std::cout << "You input wrong year.\n";
			SearchYear();
		}
		// 기존 방식에서는 input wrong ID 인 상태에서도 Total ~ student was found 가 출력되었기 때문에, else문 안에 넣어서 처리하였음.
		else {
			for (Student student : student_info)
			{
				if (student.student_id / 1000000 == year_changed)
				{
					num++;
					std::cout << student.name + "," << std::endl;
					std::cout << std::to_string(student.student_id) + "," << std::endl;
					std::cout << std::to_string(student.birth_year) + "," << std::endl;
					std::cout << student.department + "," << std::endl;
					std::cout << student.telephone + '\n' << std::endl;
				}
			}

			std::cout << "Total " << num << " student was found.\n";
		}
	}
}

void SearchDepartment()
{
	int num = 0;
	std::string department;

	std::cout << "Please input your department.\n";
	std::cin.ignore();
	std::getline(std::cin, department);

	for (Student student : student_info) 
	{
		if (student.department == department) 
		{
			num++;
			std::cout << student.name + "," << std::endl;
			std::cout << std::to_string(student.student_id) + "," << std::endl;
			std::cout << std::to_string(student.birth_year) + "," << std::endl;
			std::cout << student.department + "," << std::endl;
			std::cout << student.telephone + '\n' << std::endl;
		}		
	}

	std::cout << "Total " << num << " student was found.\n";

}

void SearchAll() 
{
	int num = 0;

	for (Student student : student_info) 
	{		
		num++;
		std::cout << student.name + "," << std::endl;
		std::cout << std::to_string(student.student_id) + "," << std::endl;
		std::cout << std::to_string(student.birth_year) + "," << std::endl;
		std::cout << student.department + "," << std::endl;
		std::cout << student.telephone + '\n' << std::endl;
	}

	std::cout << "Total " << num << " student was found.\n";

}

void Search()
{
	while (true)
	{
		int num = 0;
		std::cout << "- Search -\n1. Search by name\n2. Search by student ID\n3. Search by admission year\n4. Search by department name\n5. List All\n6. Exit\n";
		std::cin >> num;

		if (num == 1) SearchName();
		else if (num == 2) SearchId();
		else if (num == 3) SearchYear();
		else if (num == 4) SearchDepartment();
		else if (num == 5) SearchAll();
		else if (num == 6);
		else std::cout << "Please enter the correct number.\n";

		if (num >= 1 && num <= 6) break;
	}
}

bool CompareName(Student a, Student b)
{
	return a.name < b.name;
}
bool CompareId(Student a, Student b)
{
	return a.student_id < b.student_id;
}
bool CompareYear(Student a, Student b)
{
	return a.birth_year < b.birth_year;
}
bool CompareDepart(Student a, Student b)
{
	return a.department < b.department;
}

void Sorting()
{
	int sortnum = 0;

	while (sortnum > 4 || sortnum < 1)
	{
		std::cout << "- Sorting Option\n1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission year\n4. Sort by Department namet\n";
		std::cin >> sortnum;
		if (sortnum == 1) std::sort(student_info.begin(), student_info.end(), CompareName);
		else if (sortnum == 2) std::sort(student_info.begin(), student_info.end(), CompareId);
		else if (sortnum == 3) std::sort(student_info.begin(), student_info.end(), CompareYear);
		else if (sortnum == 4) std::sort(student_info.begin(), student_info.end(), CompareDepart);
		else std::cout << "invalid order";
	}
	std::cout << "Go back to the main menu, after selecting the sorting option..\n";
	WriteAll();
}

int main(int argc, char** argv) // run.exe stu.txt jjhg ==> argc=3,  run.exe => argc=1
{
	if (argc < 2) file = "file1.txt";
	else file = argv[1];

	ReadAll();

	while (true)
	{
		int num = 0;
		std::cout << "1. Insertion\n2. Search\n3. Sorting Option\n4. Exit\n";
		std::cin >> num;

		if (num == 1) Insertion();
		else if (num == 2) Search();
		else if (num == 3) Sorting();
		else if (num == 4) break;
		else std::cout << "Please enter the correct number.\n";
	}
	std::cout << "Program terminated\n";
	return 0;
}

