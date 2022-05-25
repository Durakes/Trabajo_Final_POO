#include "User.h"
class Artist: public User
{
    private:
        string Description;
        string Twitter;
        string Instagram;
        string Youtube;
    public:
        Artist(){}
        
        Artist(string code, string name, string email, int number, string username, string pass, string description, string twt, string inst, string ytube)
        {
            Code = code;
            Name = name;
            Email = email;
            PhoneNumber = number;
            Username = username;
            Password = pass;
            Description = description;
            Twitter = twt;
            Instagram = inst;
            Youtube = ytube;
        }

        string getDescription()
        {
            return Description;
        }

        string getTwitter()
        {
            return Twitter;
        }

        string getInstagram()
        {
            return Instagram;
        }

        string getYoutube()
        {
            return Youtube;
        }
};