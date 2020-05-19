#include <iostream> //for cout,
#include <string>
#include "volimage_h.h"
using namespace std;
//bool readImages(std::string baseName);


int main(int argc, char *argv[])
{ //main method
    GRLMAT001::VolImage v;      //creating class object
    v.readImages(argv[1]);        //read in from file into vector

    if (argc == 2)
    { 
       v.volImageSize();
    } else if (argc == 5)
    {
        v.volImageSize();
        v.extract(stoi(argv[3]),argv[4]);
        
    } else if (argc == 6)
    {
        v.volImageSize();
        v.diffmap(stoi(argv[3]),stoi(argv[4]),argv[5]);
        
    } else {
        cout << "incorrect input format, please try again.\n";
    }

    return 0;
}