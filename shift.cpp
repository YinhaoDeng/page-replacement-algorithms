#include <stdio.h> 
#include <iostream>
#include <iomanip>      // std::setbase
#include <deque>
using namespace std;



int main() 
{  
    deque<int> d;

    for (int i=0; i<3; i++)
    {
        d.push_back(0);
    }

    d[0] = 1;

    for(deque<int>::iterator i=d.begin(); i!=d.end();i++)
    {
        cout<<*i<<" ";
    }
    return 0; 
} 