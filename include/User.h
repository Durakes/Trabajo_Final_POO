#ifndef __USER_H__
#define __USER_H__
#include <iostream>
#include <cstring>
using namespace std;
class User
{
    protected:
        int Code;
        char Name[100];
        char Username[100];
        char Password[100];
        char Type[100];
    public:
        User(){}
        User(int code,char* name, char* username, char* pass, char* type)
        {
            Code = code;
            strcpy(Name, name);
            strcpy(Username, username);
            strcpy(Password, pass);
            strcpy(Type, type);
        }

        int getCode()    {return Code;}
        void setCode(int code)   {Code = code;}

        char* getName()    {return Name;}
        void setName(char* name)   {strcpy(Name, name);}

        char* getUsername()    {return Username;}
        void setUsername(char* user) {strcpy(Username, user);}

        char* getPassword()    {return Password;}
        void setPassword(char *pass) {strcpy(Password, pass);}

        char* getType()    {return Type;}
        void setType(char* type)   {strcpy(Type, type);}
};

#endif
