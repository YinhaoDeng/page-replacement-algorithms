/*
created by: Yinhao Deng, Chenyu Mei
ID: a1731310, a1752385
Contact Email: yinhao.deng@student.adelaide.edu.au
               chenyu.mei@student.adelaide.edu.au
-----------------------------------------------------

*/

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#include <iostream>
#include <iomanip>
#include <sstream>


int events_in_trace = 0;
int total_disk_reads = 0;
int total_disk_writes = 0;
int page_fault = 0;

vector<string> action_vec;
vector<int> address_vec;



void read_txt_input(string filename, int page_size)
{
    string rubbish1, rubbish2;

    char action; // read or write
    string x;
    int y;  //hexdecimal address
    
    ifstream in_file {filename};

    int line_number = 0;
    while(!in_file.eof())
    {   
        stringstream ss;
        if(line_number==0)
        {
            cout<<line_number<<endl;
            in_file>>rubbish1>>rubbish2;
            line_number ++;
            continue;
        }else
        {
            in_file >> action >> x;
            ss << hex << x;
            ss >> y;
            cout<<line_number<<" "<<action<<" "<<y/page_size<<endl;

            action_vec.push_back(x);
            address_vec.push_back(y/page_size);
            line_number ++;
        }
    }
    in_file.close();
    events_in_trace = line_number -1;  // assign events in trace
    cout<<"events in trace: "<<events_in_trace<<endl;
    return;
}


void FIFO(int page_frames_num_)
{
    vector<int> frames_vec;
    // initialise frames_vec
    for (int i=0; i<page_frames_num_; i++)
    {
        frames_vec.push_back(-1);
    }



}



int main(int argc, char ** argv)
{
    cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
  
    for (int i = 0; i < argc; ++i) 
        cout << i <<" "<< argv[i] << "\n"; 

    
    int page_size = stoi(argv[2]);
    int page_frames_num = stoi(argv[3]);
    string alg_name = argv[4];
    cout<<page_size<<" "<<page_frames_num<<" "<< alg_name<<endl;

    cout<<"read input:"<<endl;
    read_txt_input(argv[1], page_size);


    // algorithm name:
    if (alg_name == "FIFO")
    {

    }else if(alg_name == "LRU")
    {

    }else if(alg_name == "ARB")
    {
        
    }else if(alg_name == "WSARB-1")
    {
        
    }else if(alg_name == "WSARB-2")
    {
        
    }


    return 0; 
}