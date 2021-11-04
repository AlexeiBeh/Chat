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


}




