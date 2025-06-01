#include<string>
#include<iostream>
// #define MEMBER_WISE
class StanfordID{
    private:
        std::string name;
        std::string sunet;
        int idNumber;
    
    public:
        StanfordID(std::string name,std::string sunet,int idNumber);
        StanfordID();
        std::string  getName() const;
        std::string getSunet() const;
        int getIdNumber() const;

    #ifdef MEMBER_WISE
        bool operator<(const StanfordID& other) const;

    #endif
        bool operator==(const StanfordID& other) const;
        bool operator!=(const StanfordID& other) const;
        friend bool operator<(const StanfordID& lhs,const StanfordID& rhs);
};