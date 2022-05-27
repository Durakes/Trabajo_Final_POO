#include <iostream>
using namespace std;
class User
{
    protected:
        int Code;
        string Name;
        string Username;
        string Password;
        string Type;
    public:
        User(){}
        User(int code,string name, string username, string pass, string type)
        {
            Code = code;
            Name = name;
            Username = username;
            Password = pass;
            Type = type;
        }

        int getCode()    {return Code;}
        void setCode(int code)   {Code = code;}

        string getName()    {return Name;}
        void setName(string name)   {Name = name;}

        string getUsername()    {return Username;}
        void setUsername(string user) {Username = user;}

        string getPassword()    {return Password;}
        void setPassword(string pass) {Password = pass;}

        string getType()    {return Type;}
        void setType(string type)   {Type = type;}
};
