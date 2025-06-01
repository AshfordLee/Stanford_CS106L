#include<iostream>
#include "include/StanfordID.h"
#define MEMBER_WISE

int main()
{
    StanfordID jacob{"Jacod Roberts-Baca","jtrb",12345678};
    StanfordID fabio{"Fabio Ibanez","fabioi",87654321};

    if (jacob < fabio) {
        std::cout << jacob.getName() << " has a lower ID number than " << fabio.getName() << std::endl;
    } else {
        std::cout << fabio.getName() << " has a lower ID number than " << jacob.getName() << std::endl;
    }

    auto result=jacob<fabio;
    return 0;
}