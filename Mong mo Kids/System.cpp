#include "Header.h"

//User Interface support Function//
void clearScreen()
{
	system("CLS");
}

void warnScreen()
{
	cout << "Your choice isn't correct !! Please choose again" << endl;
}

int choiceScreen(int Number)
{
	string Choice;					
	cout << "Enter your choice (0 -> " << Number << ") :" ; cin >> Choice;
	return checkChoice(Choice, Number);
}
//*******************************//

//Nhung ham ho tro cho viec code ^^//

int checkChoice(string Choice, int Number)
{
	int length = Choice.length();
	int numberCheck = 0;
	for (int i = 0 ; i < length; i++)
		if ((Choice[i] >= '0') && (Choice[i] <= '9'))
			numberCheck += int(Choice[i]) - 48;
		else 
			return -1;		
	if (numberCheck <= Number)						
		return numberCheck;
	return -1;
}

void ignoreLine(ifstream &fi, int number) // Hao. Bo qua number dong khi doc du lieu trong file
{
	for (int i = 0; i < number; i++)
		fi.ignore(255, '\n');
}

void deleteSpace(string &str) // Hao. Xoa khoang trang du thua o khuc cuoi
{
	string s = "";
	int size = str.length() - 1;
	while (str[size] == ' ')
		size--;
	for (int i = size; i >= 0; i--)
		s = str[i] + s;
	str = s;
}

bool check(ifstream &fi, string Username, string Password, accountData &Data, int number) // Hao . Chuc nang: Lay du lieu va Kiem tra tung tai khoan
{
	int n;
	fi >> n;
	fi.ignore(255, '\n');
	accountData dataCheck;
	for (int i = 0; i < n; i++)
	{
		getline(fi, dataCheck.ID); deleteSpace(dataCheck.ID);									
		getline(fi, dataCheck.Password); deleteSpace(dataCheck.Password);						
		getline(fi, dataCheck.Name); deleteSpace(dataCheck.Name);
		fi >> dataCheck.Gender;
		ignoreLine(fi, number);
		if ((dataCheck.ID == Username) && (dataCheck.Password == Password))
		{
			Data = dataCheck;
			return true;
		}
	}
	return false;
}

int checkPassword(string Username, string Password, accountData &Data) // Hao .Chuc nang : Kiem tra tai khoan .
{
	string nameFolder = "fileUser/";
	string nameFile = "";
	ifstream fi;
	bool kt;
	
	nameFile = nameFolder + "Staff.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 2);
	if (kt)
		return 1;
	fi.close();
	
	nameFile = nameFolder + "Lecturer.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 3);
	if (kt)
		return 2;
	fi.close();
	
	nameFile = nameFolder + "Student.txt";
	fi.open(nameFile.c_str());
	kt = check(fi, Username, Password, Data, 5);
	if (kt)
		return 3;
	fi.close();
	
	return -1;
}

void takeDataUser(ifstream &fi, userData * &Data, int &size, int type) // Hao : LAy du lieu trong file fi dua vao Data 
{
	fi >> size;
	fi.ignore();
	Data = new userData[size * 2];
	for (int i = 0 ; i < size * 2; i++)
		Data[i].Type = type;
	for (int i = 0; i < size; i++)
	{
		getline(fi, Data[i].ID);
		getline(fi, Data[i].Password);
		getline(fi, Data[i].Name);
		fi >> Data[i].Gender;
		fi.ignore();		
		if (3 == Data[i].Type)
		{								
			getline(fi, Data[i].Degree);
			fi.ignore();
		}
		else if (2 == Data[i].Type)
		{
			getline(fi,Data[i].DoB);			
			getline(fi, Data[i].className);			
			fi >> Data[i].Status;
			fi.ignore();
			fi.ignore();
		}
		else
			fi.ignore();
	}
}

void insertDataUser(ofstream &fo, userData * &Data, int size) // HAo : Dua du lieu cua mang Data vao file fo
{
	fo << size << endl;
	for (int i = 0; i < size; i++)
	{
		fo << Data[i].ID << endl;			
		fo << Data[i].Password << endl;
		fo << Data[i].Name << endl;
		fo << Data[i].Gender << endl;
		if (Data[i].Type == 2)
		{
			fo << Data[i].DoB << endl;
			fo << Data[i].className << endl;
			fo << Data[i].Status << endl;
		}
		else if (3 == Data[i].Type)
			fo << Data[i].Degree << endl;
		fo << endl;
	}
}

//*********************************************************//

