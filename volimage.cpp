#include <iostream> //for cout,
#include <fstream>  //Needed for file stream objects
#include <sstream> //Needed for string stream objects
#include <vector>
#include <string>
#include "volimage_h.h"

using namespace std;

namespace GRLMAT001         //declaring namespace to work in
{        

VolImage::VolImage()        //default constructor 
{       
    width = 0;
    height = 0;
    noSlices = 0;
    sum = 0;
}

VolImage::~VolImage()       //default destructor
{      
    cout << "Cleaning up...\n";
    if (slices.size() == 0){return;}        //if already empty, quit
    
    for (unsigned int i = 0; i < slices.size(); i++)        //iterate through vector to remove pointers
    {
        for (int j = 0; j < height; j++)
        {
            delete[] slices[i][j];
        }
        delete[] slices[i];
    }
    cout << "Memory has been cleared.\n";     //print
}

int VolImage::volImageSize(void)        //calculates num images and bytes req
{     
    int a = (width * height * noSlices);
    int b = noSlices * height * sizeof(char*);
    int tot = a + b;
    cout << "Number of images: " << noSlices << "\n";
    cout << "Number of bytes required: " << tot << "\n";
    return 0;
}

void VolImage::extract(int sliceId, std::string output_prefix)      //extracts a single slice and writes to file
{     
    ofstream outfile;
    int slice = 1;
    cout << "Beginning extraction process...\n";
    outfile.open("output.data",ios::binary);
    outfile << to_string(width) + " " + to_string(height) + " " + to_string(slice);     //print to .data string
    outfile.close();

    outfile.open(output_prefix,ios::binary);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outfile << slices[slice][i][j];     //printing slice to file
        }
        
    }
    outfile.close();
    cout << "file successfully extracted to " + output_prefix + "\n";
}

bool VolImage::readImages(std::string baseName)     //reads the images from file into memory
{
    ifstream data(baseName);
    std::string swidth, sheight, snoSlices;
    cout << "Attemping to read data to file...\n";

    if (getline(data, swidth, ' ') &&
        getline(data, sheight, ' ') &&
        getline(data, snoSlices)) {}        //gets values from .data file

    width = atoi(swidth.c_str());
    height = atoi(sheight.c_str());
    noSlices = atoi(snoSlices.c_str());     //set values to int

    for (int i = 0; i < noSlices; i++)
    {
        std::stringstream ss;
        ss << i;
        std::string sService = ss.str();
        string raw = "brain_mri_raws/MRI" + sService + ".raw";

        ifstream file(raw, ios::in | ios::binary);
        if (file.is_open())
        {
            unsigned char **arrHeight = new unsigned char *[height];

            for (int j = 0; j < height; j++)
            {
                sum = sum + sizeof(slices[i][j]);
                arrHeight[j] = new unsigned char[width];
                for (int k = 0; k < width; k++)
                {
                    arrHeight[j][k] = file.get();             //getting values from file       
                }
            }
            
            slices.push_back(arrHeight);        //pushing into vector
            sum = sum + sizeof(slices[i]);
            file.close();

        }else{
            cout << "unable to open file\n";
            return false;
            }
    }
    cout << "file/s successfully read into memory.\n";
    return true;
}

void VolImage::diffmap(int sliceI,int sliceJ,std::string output_prefix){        //produces a difference map between two slices

    ofstream outfile;
    cout << "Generating diffmap...\n";
    outfile.open(output_prefix,ios::binary);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outfile << (unsigned char)(abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);       //differentiates each point between slice i and j
        }
        
    }
    cout << "diffmap generated in file: " + output_prefix << "\n";
    outfile.close();
}
}
