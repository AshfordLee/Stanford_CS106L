
#include<string>
class StudentID{
    protected:
        std::string name;
        std::string sunet;
        int idNumber;

    public:
        StudentID(std::string name,std::string sunet,int idNumber);
        StudentID();
        ~StudentID();

        std::string getName();
        std::string getSunet();
        int getIdNumber();

        void setName(std::string name);
        void setSunet(std::string sunet);
        void setIdNumber(int idNumber);
};

