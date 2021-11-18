#include <iostream>
#include <string>
#include <stdlib.h>
#include <locale.h>
#include <fstream>

using namespace std;

class User
{
private:
	string login;
	string password;
	string name;


public:
	static int counterID;
	User() = default;

	User(string login, string password, string name)
	{
		this->login = login;
		this->password = password;
		this->name = name;
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


int main()
{
	setlocale(LC_ALL, "Russian");	// ����� ������� �����
	system("chcp 1251");			// ����������� ��������� �������

	// ����������� ����������
	string registrationcheck;
	string username;
	string userlogin;
	string userpassword;
	string massage;
	string choisestr;
	int counterTryInter = 0;
	int choise;
	bool accessUser = false;
	bool loginCheck = false;
	bool choiseswitch = false;

	int size = 1;
	User* UsersArr = new User[size];

	

	cout << "����� ���������� � ���!" << endl;
	do
	{
		cout << "�� ���������������� �����?" << endl << "Y - ��" << endl << "N - ���" << endl;
		cin >> registrationcheck;
	} while (registrationcheck != "Y" && registrationcheck != "N");





	if (registrationcheck == "Y")
	{
		do
		{
			if (counterTryInter == 10)
			{
				cout << "������ ������������ ����� ��� ������ 10 ���" << endl << "�������� �� �� ����������������! ������� � ��� �������� � �����������������." << endl;
				return 0;
			}

			ifstream access;
			try
			{
				access.open("Users.txt");
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
			cout << "������� �����" << endl;
			cin >> userlogin;
			cout << "������� ������" << endl;
			cin >> userpassword;

			while (!access.eof())
			{
				int i = 0;
				access.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
				if (userlogin == UsersArr[i].GetLogin() && userpassword == UsersArr[i].GetPassword())
				{
					cout << "����� � ������ �������" << endl << "���� � ���" << endl;
					accessUser = true;
					break;
				}
				i++;
			}
			if (accessUser == false)
			{
				cout << "������ ������������ ����� ��� ������" << endl;
				counterTryInter++;
			}
			access.close();


		} while (accessUser == false);

	}
	else if (registrationcheck == "N")
	{


		// ���������, ����� �� ����� �����

		ifstream access;
		try
		{
			access.open("Users.txt");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		do
		{
			cout << "��� ����������� ������� �����" << endl;
			cin >> userlogin;
			while (!access.eof())

			{
				int iarr = 0;
				access.read((char*)&UsersArr[iarr], sizeof(UsersArr[iarr]));

				if (UsersArr[iarr].GetLogin() == userlogin)
				{
					cout << "����� ����� ��� ����������/�����" << endl;
					loginCheck = false;
					break;
				}

				else
				{
					loginCheck = true;
				}

			}

		} while (loginCheck == false);
		access.close();
		// ���������� �����������
		cout << "��� ����������� ������� ������" << endl;
		cin >> userpassword;
		cout << "����� �� ������ ������ ���� ���" << endl;
		cin >> username;


		// ���������� ������ ������ ������������ � ����
		ofstream record;

		try
		{
			record.open("Users.txt", ofstream::app);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		User* UsersArr1 = new User[1];
		UsersArr1[0] = User(userlogin, userpassword, username);
		record.write((char*)&UsersArr1[0], sizeof(UsersArr1[0]));
		record.close();
		delete[] UsersArr1;
		cout << "������������ ���������������!" << endl;
	}
	
	cout << "����������� ���, " << userlogin << ", � ����� ����!" << endl;
	cout << "����������, ��� ����������� ����������� ���� �����, ����� ������� '-info'" << endl;

	// ��������� ��������� ��� ������������
	ifstream loginmassage;
	try
	{
		loginmassage.open(userlogin + ".txt");
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	getline(loginmassage, massage);


	if (massage != "")
	{
		cout << "� ��� ����� ��������� �� �������������:" << endl;
		cout << massage << endl;
		while (!loginmassage.eof()) // 
		{
			getline(loginmassage, massage);
			cout << massage << endl;
			massage = "";
		}
		loginmassage.close();

		// ������ ���� ������
		ofstream nullmassage;

		try
		{
			nullmassage.open(userlogin + ".txt");
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		nullmassage << "";
	}
	

	
	do
	{
		loginCheck = false;
		choise = 0;
		massage = "";
		//cout << endl;
		getline(cin, massage);
		if (massage == "-info")
		{
			do
			{
				choise = 0;
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
				// ���� ������������������� ������������ �� ������
				do
				{
					cout << "������� ����� ������������ ��� ������." << endl
						<< "��� ������� '-main' ��� ������ � ����� ���" << endl;
					cin >> choisestr;
					if (choisestr != "-main")
					{
						ifstream usersearch;
						try
						{
							usersearch.open("Users.txt");
						}
						catch (const std::exception& ex)
						{
							cout << ex.what() << endl;
						}

						while (!usersearch.eof())
						{
							int i = 0;
							usersearch.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
							if (choisestr == UsersArr[i].GetLogin())
							{
								usersearch.close();
								
								ofstream usermassage;
								try
								{
									usermassage.open(choisestr + ".txt", ofstream::app);
								}
								catch (const std::exception& ex)
								{
									cout << ex.what() << endl;
								}
								cout << "������ ��� � " << choisestr << " ������." << endl
									<< "��� ������ '-exit' " << endl
									<< "��� ��������� ���������� � ������������ ������� '-IU' " << endl;
								usermassage << userlogin << endl;
								do
								{
									// ����� ������������ � ��� (��������� ����)
									
									massage = "";
									getline(cin, massage);
									if (massage != "-exit" && massage != "" && massage != "-IU")
									{

										usermassage << massage << endl;
										
									}
									if (massage == "-IU")
									{
										cout << "����� ������������\t" << UsersArr[i].GetLogin() << endl;
										cout << "��� ������������\t" << UsersArr[i].GetName() << endl;
									}
									
								} while (massage != "-exit");
								usermassage << endl;
								usermassage.close();

							}
							if (massage == "-exit")
							{
								break;
							}
							if (choisestr == "-exit")
							{
								break;
							}
							else
							{
								loginCheck = false;
															
							}
							
						}
						usersearch.close();

					}
					else if (choisestr == "-main")
					{
						massage = "";
						break;
					}
					
				} while (loginCheck == false);
				break;

				case 2:
				{
					ifstream userinfo;
					try
					{
						userinfo.open("Users.txt");
					}
					catch (const std::exception& ex)
					{
						cout << ex.what() << endl;
					}
					
					while (!userinfo.eof())
					{
						int i = 0;
						userinfo.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
						if (!userinfo.eof())
						{
							cout << UsersArr[i].GetLogin() << endl;
						}
					}
					userinfo.close();
				}

				default:
					break;
				
				
			}

		}
		
		else if (massage == "-exit")
		{
			//delete[] UsersArr;	
			return 0;
		}

		else if (massage != "")
		{
			ifstream usermassagesend;
			try
			{
				usermassagesend.open("Users.txt");
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}

			// ���������� ��������� ������� � ����� ���, �� ��� �� ����� ����������
			while (!usermassagesend.eof())
			{
				int i = 0;
				usermassagesend.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
				if (UsersArr[i].GetLogin() != userlogin)
				{
					/*
					* ���������� ���� ������������� �� ������ Users.
					*/
					if (!usermassagesend.eof())
					{
						cout << "��������� ������������ " << UsersArr[i].GetLogin() << " ����������" << endl;
					}
				}
			}
			usermassagesend.close(); 

		}

	} while (massage != "-exit");
	
}
