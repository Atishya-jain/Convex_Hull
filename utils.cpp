#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include "utils.h"
using namespace std;

void get_input(string filename, vector<pair<float,pair<float,float>>> &inp)
{
    vector<string> lines;
    string line;
    ifstream myfile(filename.c_str());
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open input file";
        exit(0);
    }

    int num_points = atoi(lines[0].c_str());
    if (num_points + 1 != lines.size())
    {
        cout << "Please check the format of input file";
        exit(0);
    }

    for (int i = 1; i <= num_points; ++i)
    {
        float elements[3];
        splitString(lines[i], " ", elements, 3);
        inp.push_back(make_pair(elements[0], make_pair(elements[1], elements[2])));
    }
}

void splitString(string message, string delimiter, float result[], int n) {
    int i = 0, pos = 0, length = 0, temp;
    temp = message.find ( delimiter.c_str ( ), pos );
    while ( temp != -1 )
    {
        length = temp - pos;
        result[i] = atof((message.substr ( pos, length )).c_str());
        pos = temp + delimiter.size ( );
        temp = message.find ( delimiter.c_str ( ), pos );
        i++;
    }
    result[i] = atof((message.substr ( pos )).c_str());
    i++;
    if ( i != n )
    {
        cout << "The input file is not correct.";
        exit ( 0 );
    }
}

void get_output(string filename, vector<pair<float, pair<float,float>>> &out)
{
    ofstream ofile(filename);
    ofile << out.size() << "\n";
    for (int i = 0; i < out.size(); i++)
    {
        ofile << out[i].first << " " << out[i].second.first << " " << out[i].second.second;
        ofile << "\n";
    }
    ofile.close();
}