#include<string>

class StudentID
{
    protected:
        std::string name;
        std::string sunet;
        int idNumber;

    public:
        StudentID(std::string name,std::string sunet,int idNumber);
        StudentID();
        ~StudentID();

        std::string get_name();
        std::string get_sunet();
        int get_idNumber();

        void setName(std::string name);
        void setSunet(std::string sunet);
        void setIdNumber(int idNumber);
};