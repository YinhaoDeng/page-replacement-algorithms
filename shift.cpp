#include <stdio.h> 
#include <iostream>
#include <iomanip>      // std::setbase
#include <deque>
#include <vector>
using namespace std;



int main() 
{  
    deque<int> d;

    for (int i=0; i<10; i++)
    {
        d.push_back(i);
    }
    

    for(deque<int>::iterator i=d.begin(); i!=d.end();i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;

    // d.push_front(1);
    // d.pop_back();
    cout<<d.back()<<endl;

    for(deque<int>::iterator i=d.begin(); i!=d.end();i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;


    return 0; 
} 