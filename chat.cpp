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
	setlocale(LC_ALL, "Russian");	// задаём русский текст
	system("chcp 1251");			// настраиваем кодировку консоли

	// статические переменные
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

	

	cout << "Добро пожаловать в чат!" << endl;
	do
	{
		cout << "Вы зарегестрированы ранее?" << endl << "Y - да" << endl << "N - нет" << endl;
		cin >> registrationcheck;
	} while (registrationcheck != "Y" && registrationcheck != "N");





	if (registrationcheck == "Y")
	{
		do
		{
			if (counterTryInter == 10)
			{
				cout << "Введен неправильный логин или пароль 10 раз" << endl << "Возможно вы не рарегистрированы! Войдите в чат повторно и зарегистрируйтесь." << endl;
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
			cout << "Введите логин" << endl;
			cin >> userlogin;
			cout << "Введите пароль" << endl;
			cin >> userpassword;

			while (!access.eof())
			{
				int i = 0;
				access.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
				if (userlogin == UsersArr[i].GetLogin() && userpassword == UsersArr[i].GetPassword())
				{
					cout << "Логин и пароль приняты" << endl << "Вход в чат" << endl;
					accessUser = true;
					break;
				}
				i++;
			}
			if (accessUser == false)
			{
				cout << "Введен неправильный логин или пароль" << endl;
				counterTryInter++;
			}
			access.close();


		} while (accessUser == false);

	}
	else if (registrationcheck == "N")
	{


		// Проверяем, занят ли такой логин

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
			cout << "Для регистрации введите логин" << endl;
			cin >> userlogin;
			while (!access.eof())

			{
				int iarr = 0;
				access.read((char*)&UsersArr[iarr], sizeof(UsersArr[iarr]));

				if (UsersArr[iarr].GetLogin() == userlogin)
				{
					cout << "Такой логин уже существует/занят" << endl;
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
		// Продолжаем регистрацию
		cout << "Для регистрации введите пароль" << endl;
		cin >> userpassword;
		cout << "Также мы просим ввести ваше имя" << endl;
		cin >> username;


		// Записываем данные нового пользователя в файл
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
		cout << "Пользователь зарегестрирован!" << endl;
	}
	
	cout << "Приветсвуем Вас, " << userlogin << ", в нашем чате!" << endl;
	cout << "Напоминаем, что просмотреть возможности чата можно, введя команду '-info'" << endl;

	// Проверяем сообщения для пользователя
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
		cout << "У Вас новые сообщения от пользователей:" << endl;
		cout << massage << endl;
		while (!loginmassage.eof()) // 
		{
			getline(loginmassage, massage);
			cout << massage << endl;
			massage = "";
		}
		loginmassage.close();

		// Делаем файл пустым
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
				cout << "Возможности чата:" << endl
					<< "1. Найти пользователя по логину" << endl
					<< "2. Просмотреть список логинов всех пользователей" << endl
					<< "3. Выйти из меню" << endl
					<< "Для выхода из чата введите '-exit'" << endl;
				cin >> choise;
				if (choise != 1 && choise != 2 && choise != 3)
				{
					cout << "Выбирете пункт меню" << endl;
				}

			} while (choise != 1 && choise != 2 && choise != 3);
			switch (choise)
			{
			case 1:
				// Ищем зарегистрированного пользователя по логину
				do
				{
					cout << "Введите логин пользователя для поиска." << endl
						<< "Или введите '-main' для выхода в общий чат" << endl;
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
								cout << "Личный чат с " << choisestr << " открыт." << endl
									<< "Для выхода '-exit' " << endl
									<< "Для получения информации о пользователе введите '-IU' " << endl;
								usermassage << userlogin << endl;
								do
								{
									// Пишем пользователю в чат (заполняем файл)
									
									massage = "";
									getline(cin, massage);
									if (massage != "-exit" && massage != "" && massage != "-IU")
									{

										usermassage << massage << endl;
										
									}
									if (massage == "-IU")
									{
										cout << "Логин пользователя\t" << UsersArr[i].GetLogin() << endl;
										cout << "Имя пользователя\t" << UsersArr[i].GetName() << endl;
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

			// Отправляем сообщения каждому в общий чат, но оно не будет доставлено
			while (!usermassagesend.eof())
			{
				int i = 0;
				usermassagesend.read((char*)&UsersArr[i], sizeof(UsersArr[i]));
				if (UsersArr[i].GetLogin() != userlogin)
				{
					/*
					* Отправляем всем пользователям из списка Users.
					*/
					if (!usermassagesend.eof())
					{
						cout << "Сообщение пользователю " << UsersArr[i].GetLogin() << " отправлено" << endl;
					}
				}
			}
			usermassagesend.close(); 

		}

	} while (massage != "-exit");
	
}
