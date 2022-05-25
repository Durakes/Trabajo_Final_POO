#include <iostream>
using namespace std;
class User
{
    protected:
        string Code;
        string Name;
        string Email;
        int PhoneNumber;
        string Username;
        string Password;
    public:
        User(){}
        User(string code,string name, string email, int number, string username, string pass)
        {
            Code = code;
            Name = name;
            Email = email;
            PhoneNumber = number;
            Username = username;
            Password = pass;
        }

        string getCode()
        {
            return Code;
        }

        string getName()
        {
            return Name;
        }

        string getEmail()
        {
            return Email;
        }

        int getPhoneNumber()
        {
            return PhoneNumber;
        }

        string getUsername()
        {
            return Username;
        }

        string getPassword()
        {
            return Password;
        }
};