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


	UsersArr[0] = User("Admin", "1", "Андрей");
	UsersArr[1] = User("fighter", "2", "Сергей");
	UsersArr[2] = User("travelers", "3", "Александр");
	cout << "Добро пожаловать в чат!" << endl;
	do
	{
		cout << "Вы зарегестрированы ранее?" << endl << "Y - да" << endl << "N - нет" << endl;
		cin >> registrationcheck;
	} while (registrationcheck != "Y" && registrationcheck != "N");


	while (accessUser == false)
	{
		if (registrationcheck == "Y")
		{
			do
			{
				cout << "Введите логин" << endl;
				cin >> userlogin;
				cout << "Введите пароль" << endl;
				cin >> userpassword;
				for (int i = 0; i < size; i++)
				{
					if (accessUser == false)
					{
						if (counterTryInter <= 10)
						{
							if (userlogin == UsersArr[i].GetLogin() && userpassword == UsersArr[i].GetPassword())
							{
								cout << "Логин и пароль приняты" << endl << "Вход в чат" << endl
									<< "Приветсвуем Вас, " << userlogin << ", в нашем чате!" << endl;

								accessUser = true;
							}
						}
						else
						{
							cout << "Введен неправильный логин или пароль 10 раз" << endl << "Возможно вы не рарегистрированы! Войдите в чат повторно и зарегистрируйтесь." << endl;
							return 0;
						}
					}
				}
				if (accessUser == false)
				{
					cout << "Введен неправильный логин или пароль" << endl;
					counterTryInter++;
				}

			} while (accessUser == false);
		}
		else if (registrationcheck == "N")
		{
			counterUserArray++;
			do
			{
				cout << "Для регистрации введите логин" << endl;
				cin >> userlogin;
				for (int i = 0; i < counterUserArray; i++)
				{
					if (UsersArr[i].GetLogin() == userlogin)
					{
						cout << "Такой логин уже существует/занят" << endl;
						loginCheck = false;
						break;
					}

					if (UsersArr[i].GetLogin() != userlogin)
					{
						loginCheck = true;
					}
				}
			} while (loginCheck == false);

			cout << "Для регистрации введите пароль" << endl;
			cin >> userpassword;
			cout << "Также мы просим ввести ваше имя" << endl;
			cin >> username;
			UsersArr[counterUserArray] = User(userlogin, userpassword, username);
			registrationcheck = "Y";
			cout << "Пользователь зарегестрирован!" << endl;
		}
	}

}




