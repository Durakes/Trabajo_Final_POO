#include <iostream>
using namespace std;
class User
{
    protected:
        string Code;
        string Name;
        string Email;
        string PhoneNumber;
        string Username;
        string Password;
        //string Type; //enum c# --- c++
    public:
        User(){}
        User(string code,string name, string email, string number, string username, string pass)
        {
            Code = code;
            Name = name;
            Email = email;
            PhoneNumber = number;
            Username = username;
            Password = pass;
            //Type = "user";
        }

        string getCode()    {return Code;}
        void setCode(string code)   {Code = code;}

        string getName()    {return Name;}
        void setName(string name)   {Name = name;}

        string getEmail()   {return Email;}
        void setEmail(string email) {Email = email;}

        string getPhoneNumber()    {return PhoneNumber;}
        void setPhoneNumber(int number) {PhoneNumber = number;}

        string getUsername()    {return Username;}
        void setUsername(string user) {Username = user;}

        string getPassword()    {return Password;}
        void setPassword(string pass) {Password = pass;}
};