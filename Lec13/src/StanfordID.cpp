#define MEMBER_WISE
#include "../include/StanfordID.h"
StanfordID::StanfordID(){
    name="John Appleseed";
    sunet="jappleseed";
    idNumber=00000001;
}

StanfordID::StanfordID(std::string name,std::string sunet,int idNumber)
{
    this->name=name;
    this->sunet=sunet;

    if(idNumber>=0)
    {
        this->idNumber=idNumber;
    }

    else{
        this->idNumber=0;
    }
}

std::string StanfordID::getName() const
{
    return this->name;
}

std::string StanfordID::getSunet() const{
    return this->sunet;
}

int StanfordID::getIdNumber() const
{
    return this->idNumber;
}

#ifdef MEMBER_WISE
bool StanfordID::operator<(const StanfordID& other) const{
    return this->idNumber<other.idNumber;
}
#endif

bool StanfordID::operator==(const StanfordID& other) const{
    return this->idNumber==other.idNumber;
}

bool StanfordID::operator!=(const StanfordID& other) const{
    return this->idNumber!=other.idNumber;
}

#ifdef MEMBER_WISE

bool operator<(const StanfordID& lhs,const StanfordID& rhs)
{
    return lhs.getIdNumber()<rhs.getIdNumber();
}
#endif