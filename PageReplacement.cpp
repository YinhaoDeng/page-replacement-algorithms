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
#include "page.cpp"

// Page page1 = Page();

int events_in_trace = 0;
int total_disk_reads = 0;
int total_disk_writes = 0;
int page_fault = 0;

vector<string> action_vec;
vector<int> address_vec;
vector<Page>pages_vec;


void read_txt_input(string filename, int page_size)
{
   

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
            string rubbish1, rubbish2;
            cout<<line_number<<endl;
            in_file>>rubbish1>>rubbish2;
            line_number ++;
            continue;
        }else
        {
            in_file >> action >> x;
            ss << hex << x;
            ss >> y;
            cout<<"line number:"<<line_number<<" "<<action<<" "<<y/page_size<<endl;
            pages_vec.push_back(Page(y/page_size, false, false, action, 0));
            // page = Page(y/page_size, false, false, action, 0);
            // action_vec.push_back(x);
            // address_vec.push_back(y/page_size);
            line_number ++;
        }
    }
    in_file.close();
    events_in_trace = line_number - 1;  // assign events in trace
    cout<<"events in trace: "<<events_in_trace<<endl;


    for(int i=0; i<pages_vec.size(); i++)
    {
        cout<<pages_vec[i].page_num<<" ";
    }
    return;
}

bool check_if_in_frames(vector<int> vec, int target)
{
    for (int i=0; i<vec.size(); i++)
    {
        if (vec[i] == target)
            return true;
    }
    return false;
}



void FIFO(int page_frames_num_)
{
    vector<int> frames_vec;
    vector<string> status_vec; // miss or hit?


    // time
    int time = 0;
    while(!address_vec.empty())
    {
        if(check_if_in_frames(frames_vec, address_vec.front())) // if page is loaded
        {
            status_vec.push_back("Hit");  // do nothing

        }else //the page is loaded
        {
            status_vec.push_back("Miss");
            page_fault ++;
            total_disk_reads++;

            if(frames_vec.size() < page_frames_num_)  //frames still have space
            {
                frames_vec.push_back(address_vec.front());
                address_vec.erase(address_vec.begin());

            }else // frames have no space
            {
                //find the victim page
                frames_vec.erase(frames_vec.begin());  // remove the victim page
                frames_vec.push_back(address_vec.front());
                address_vec.erase(address_vec.begin());                        
                
                
            }
            
        }


        time ++; 
    }

}



int main(int argc, char ** argv)
{
    cout << "You have entered " << argc 
         << " arguments:" << "\n"; 
  
    for (int i = 0; i < argc; ++i) 
        cout <<"argv["<< i <<"] "<< argv[i] << "\n"; 

    
    int page_size = stoi(argv[2]);
    int page_frames_num = stoi(argv[3]);
    string alg_name = argv[4];
    // cout<<page_size<<" "<<page_frames_num<<" "<< alg_name<<endl;

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