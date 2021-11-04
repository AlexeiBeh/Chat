#include <iostream>
#include <string>
#include <stdlib.h>



using namespace std;

class User
{
private:
	string login;
	string password;
	string name;
	int id;
	
public:
	static int counterID;
	User() = default;
	
	User (string login, string password, string name)
	{
		this->login = login;
		this->password = password;
		this->name = name;
		counterID++;
		id = counterID;
	}

	int Getid()
	{
		return id;
	}
	
	string GetLogin()
	{
		return login;
	}

	string GetPassword()
	{
		return password;
	}
	
	string GetName()
	{
		return name;
	}

};
int User::counterID = 0;

int main()
{
	setlocale(LC_ALL, "");
	string registrationcheck;
	string username;
	string userlogin;
	string userpassword;
	string massage;
	string choisestr;
	int counterTryInter = 0;
	int counterUserArray = 2;
	int choise;
	bool accessUser = false;
	bool loginCheck = false;



	int size = 20;
	User* UsersArr = new User[size];


	UsersArr[0] = User("Admin", "1", "������");
	UsersArr[1] = User("fighter", "2", "������");
	UsersArr[2] = User("travelers", "3", "���������");
	cout << "����� ���������� � ���!" << endl;
	do
	{
		cout << "�� ���������������� �����?" << endl << "Y - ��" << endl << "N - ���" << endl;
		cin >> registrationcheck;
	} while (registrationcheck != "Y" && registrationcheck != "N");


	while (accessUser == false)
	{
		if (registrationcheck == "Y")
		{
			do
			{
				cout << "������� �����" << endl;
				cin >> userlogin;
				cout << "������� ������" << endl;
				cin >> userpassword;
				for (int i = 0; i < size; i++)
				{
					if (accessUser == false)
					{
						if (counterTryInter <= 10)
						{
							if (userlogin == UsersArr[i].GetLogin() && userpassword == UsersArr[i].GetPassword())
							{
								cout << "����� � ������ �������" << endl << "���� � ���" << endl
									<< "����������� ���, " << userlogin << ", � ����� ����!" << endl;

								accessUser = true;
							}
						}
						else
						{
							cout << "������ ������������ ����� ��� ������ 10 ���" << endl << "�������� �� �� ����������������! ������� � ��� �������� � �����������������." << endl;
							return 0;
						}
					}
				}
				if (accessUser == false)
				{
					cout << "������ ������������ ����� ��� ������" << endl;
					counterTryInter++;
				}

			} while (accessUser == false);
		}
		else if (registrationcheck == "N")
		{
			counterUserArray++;
			do
			{
				cout << "��� ����������� ������� �����" << endl;
				cin >> userlogin;
				for (int i = 0; i < counterUserArray; i++)
				{
					if (UsersArr[i].GetLogin() == userlogin)
					{
						cout << "����� ����� ��� ����������/�����" << endl;
						loginCheck = false;
						break;
					}

					if (UsersArr[i].GetLogin() != userlogin)
					{
						loginCheck = true;
					}
				}
			} while (loginCheck == false);

			cout << "��� ����������� ������� ������" << endl;
			cin >> userpassword;
			cout << "����� �� ������ ������ ���� ���" << endl;
			cin >> username;
			UsersArr[counterUserArray] = User(userlogin, userpassword, username);
			registrationcheck = "Y";
			cout << "������������ ���������������!" << endl;
		}
	}
	
	cout << "����������, ��� ����������� ����������� ���� �����, ����� ������� '-info'" << endl;

	do
	{
		loginCheck = false;
		choise = 0;
		massage = "";
		cout << endl;
		getline(cin, massage);
		if (massage == "-info")
		{
			do
			{
				cout << "����������� ����:" << endl
					<< "1. ����� ������������ �� ������" << endl
					<< "2. ����������� ������ ������� ���� �������������" << endl
					<< "3. ����� �� ����" << endl
					<< "��� ������ �� ���� ������� '-exit'" << endl;
				cin >> choise;
				if (choise != 1 && choise != 2 && choise != 3)
				{
					cout << "�������� ����� ����" << endl;
				}
			} while (choise != 1 && choise != 2 && choise != 3);

			switch (choise)
			{
			case 1:
				do
				{
					cout << "������� ����� ������������ ��� ������." << endl
						<< "��� ������� '-main' ��� ������ � ����� ���" << endl;
					cin >> choisestr;
					if (choisestr != "-main")
					{
						for (int i = 0; i <= counterUserArray; i++)
						{
							if (choisestr == UsersArr[i].GetLogin())
							{
								massage = "";
								cout << "������ ��� � " << choisestr << " ������." << endl
									<< "��� ������ '-exit' " << endl
									<< "��� ��������� ���������� � ������������ ������� '-IU' " << endl;
								do
								{
									massage = "";
									getline(cin, massage);
									if (massage != "-exit" && massage != "" && massage != "-IU")
									{
										cout << "��������� ������������ ����������." << endl;
									}
									if (massage == "-IU")
									{
										cout << "ID ������������\t\t" << UsersArr[i].Getid() << endl;
										cout << "����� ������������\t" << UsersArr[i].GetLogin() << endl;
										cout << "��� ������������\t" << UsersArr[i].GetName() << endl;
									}

								} while (massage != "-exit");

							}
							if (choisestr == "-main")
							{
								break;
							}
							else
							{
								loginCheck = false;
							}
						}
					}
					else if (choisestr == "-main")
					{
						break;
					}
				} while (loginCheck == false);
				break;

			case 2:
			{
				for (int i = 0; i <= counterUserArray; i++)
				{
					cout << UsersArr[i].GetLogin() << endl;
				}
			}

			default:
				break;
			}

		}
		else if (massage == "-exit")
		{
			break;
		}
		else if (massage != "")
		{
			for (int i = 0; i <= counterUserArray; i++)
			{
				// ��������� �����, ����� �� ���������� ��������� ����
				if (UsersArr[i].GetLogin() != userlogin)
					cout << "��������� ������������ " << UsersArr[i].GetLogin() << " ����������." << endl;
			}
		}

	} while (massage != "!exit!");


	delete[] UsersArr;
	registrationcheck = "";
	return 0;

}




