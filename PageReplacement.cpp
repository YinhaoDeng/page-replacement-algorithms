/*
created by: Yinhao Deng, Chenyu Mei
ID: a1731310, a1752385
Contact Email: yinhao.deng@student.adelaide.edu.au
               chenyu.mei@student.adelaide.edu.au
-----------------------------------------------------

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#include <iostream>
#include <iomanip>
#include <sstream>

// #include "page.cpp"
#include "helper.cpp"

// Global variables
int events_in_trace = 0;
int total_disk_reads = 0;
int total_disk_writes = 0;
int page_fault = 0;


vector<Page> pages_vec;
vector<Page> frames_vec;


int bits = 0;
int interval = 0;


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
            cout<<"line number:"<<line_number<<endl;
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
            line_number ++;
        }
    }
    in_file.close(); // close input.txt file

    // events_in_trace = line_number - 1;  // assign events in trace???????????????????????????????
    // cout<<"events in trace: "<<events_in_trace<<endl; //??????????????????????????????????????????

    // print what is in pages_vec
    // for(int i=0; i<pages_vec.size(); i++)
    // {
    //     cout<<pages_vec[i].page_num<<" ";
    // }
    return;
}



void FIFO(int page_frames_num_, Page current_page) //有几个内存块
{
    if(check_if_in_vec(frames_vec, current_page)) // if page is loaded
    {
        cout<<"     Hit:      ";
        cout<<"page  "<<current_page.page_num<<"                                        ";
        

        for (int i=0; i<frames_vec.size(); i++)
        {
            if(frames_vec[i].page_num == current_page.page_num)
            {
                // if(current_page.r_or_w == 'R' && frames_vec[i].r_or_w == 'W')
                //     frames_vec[i].r_or_w = 'R';
                if (current_page.r_or_w == 'W' && frames_vec[i].r_or_w == 'R')
                    frames_vec[i].r_or_w = 'W';
            }
        }
    }else
    {
        cout<<"    Miss:       ";

        page_fault ++;
        total_disk_reads++;

        if(frames_vec.size() < page_frames_num_)  //page frames is not full
        {
            // cout<<"frames_vec size:"<<frames_vec.size()<<" < page_frames_num:  "<<page_frames_num_;
            frames_vec.push_back(current_page);  //add the page to the frames last
            cout<<" page  "<<current_page.page_num;
            cout<<"                       ";
            
        }else // frames have no space
        {
            // frames_vec[0].is_dirty == true; // set victim is_dirty = true
            cout<<" page  "<<current_page.page_num;

            bool f = false;
            // if (frames_vec[0].is_dirty == true)
            if (frames_vec[0].r_or_w == 'W')
            {
                // cout<<"  (DIRTY)  ";
                total_disk_writes++;
                f = true;
            }
            cout<<"  REPLACE: page   "<<frames_vec[0].page_num<<"                        ";
            frames_vec.erase(frames_vec.begin());  // remove the victim page (first page)
            
            if(f == true)
                cout<<"(DIRTY)          ";
            frames_vec.push_back(current_page);
        }
    }
}


void LRU(int page_frames_num_, Page current_page)
{
    if(check_if_in_vec(frames_vec, current_page)) // if page is loaded
    {
        cout<<"     Hit:      ";
        cout<<"page  "<<current_page.page_num<<"                                        ";
        

        for (int i=0; i<frames_vec.size(); i++)
        {
            if(frames_vec[i].page_num == current_page.page_num)
            {
                if (current_page.r_or_w == 'W' && frames_vec[i].r_or_w == 'R')
                    frames_vec[i].r_or_w = 'W';
            }
        }

        bool if_swap = false;
        for(int i=0; i<frames_vec.size(); i++)
        {
            if(if_swap)
                swap(frames_vec[i], frames_vec[i-1]);

            if(frames_vec[i].page_num == current_page.page_num)
                if_swap = true;
        }
    }else
    {
        cout<<"    Miss:       ";

        page_fault ++;
        total_disk_reads++;

        if(frames_vec.size() < page_frames_num_)  //page frames is not full
        {
            // cout<<"frames_vec size:"<<frames_vec.size()<<" < page_frames_num:  "<<page_frames_num_;
            frames_vec.push_back(current_page);  //add the page to the frames last
            cout<<" page  "<<current_page.page_num;
            cout<<"                       ";
            
        }else // frames have no space
        {
            // frames_vec[0].is_dirty == true; // set victim is_dirty = true
            cout<<" page  "<<current_page.page_num;

            bool f = false;
            // if (frames_vec[0].is_dirty == true)
            if (frames_vec[0].r_or_w == 'W')
            {
                // cout<<"  (DIRTY)  ";
                total_disk_writes++;
                f = true;
            }
            cout<<"  REPLACE: page   "<<frames_vec[0].page_num<<"                        ";
            frames_vec.erase(frames_vec.begin());  // remove the victim page (first page)
            
            if(f == true)
                cout<<"(DIRTY)          ";
            frames_vec.push_back(current_page);
        }
    
    }
}


void ARB(int page_frames_num_, Page current_page)
{
    if(events_in_trace % interval == 0)
        right_shift(frames_vec);
    

    if(check_if_in_vec(frames_vec, current_page)) // if page is loaded
    {
        cout<<"     Hit:      ";
        cout<<"page  "<<current_page.page_num<<"                                        ";
        
        current_page.r_register[0] = 1;

        for (int i=0; i<frames_vec.size(); i++)
        {
            if(frames_vec[i].page_num == current_page.page_num)
            {
         
                if (current_page.r_or_w == 'W' && frames_vec[i].r_or_w == 'R')
                    frames_vec[i].r_or_w = 'W';
            }
        }
    }else
    {
        cout<<"    Miss:       ";

        current_page.r_register[0] = 1;

        page_fault ++;
        total_disk_reads++;
        

        if(frames_vec.size() < page_frames_num_)  //page frames is not full
        {
            // cout<<"frames_vec size:"<<frames_vec.size()<<" < page_frames_num:  "<<page_frames_num_;
            frames_vec.push_back(current_page);  //add the page to the frames last
            cout<<" page  "<<current_page.page_num;
            cout<<"                       ";
            
        }
        else // frames have no space
        {
            // frames_vec[0].is_dirty == true; // set victim is_dirty = true
            cout<<" page  "<<current_page.page_num;

            // bool f = false;
            // // if (frames_vec[0].is_dirty == true)
            // if (frames_vec[0].r_or_w == 'W')
            // {
            //     // cout<<"  (DIRTY)  ";
            //     total_disk_writes++;
            //     f = true;
            // }
            // cout<<"  REPLACE: page   "<<frames_vec[0].page_num<<"                        ";
            // frames_vec.erase(frames_vec.begin());  // remove the victim page (first page)
            
            // if(f == true)
            //     cout<<"(DIRTY)          ";
            // frames_vec.push_back(current_page);
        }
    }
    
}

void run(string algorithm_name, int page_frame_num)
{ 

    // initialise r_register for ARU  algorithm
    if(bits>1)
    {
        for(int j=0; j<pages_vec.size(); j++)
        {
            deque<int> temp_deque;
            for(int i=0; i<bits; i++)
                temp_deque.push_back(0);
            pages_vec[j].r_register = temp_deque;
        }
    }


    for(int i=0; i<pages_vec.size(); i++) // this for loop is like a timer
    {
        cout<<"Time:   "<<i+1;
        events_in_trace ++;

             // algorithm name:
        if (algorithm_name == "FIFO")
        {
            FIFO(page_frame_num, pages_vec[i]);
        }else if(algorithm_name == "LRU")
        {
            LRU(page_frame_num, pages_vec[i]);
        }else if(algorithm_name == "ARB")
        {
            
            ARB(page_frame_num, pages_vec[i]);
        }else if(algorithm_name == "WSARB-1")
        {
            
        }else if(algorithm_name == "WSARB-2")
        {
            
        }else{
            cout<<"wrong algorithm name!"<<endl;
            return;
        }


        cout<<"frames after excution: ";
        for(int i=0; i<frames_vec.size(); i++)
        {
            cout<<frames_vec[i].page_num<<" ";
        }
        cout<<endl;
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
    // int bits,interval;

    if(argc>5)
    {
        bits = stoi(argv[5]);
        interval = stoi(argv[6]);
    }
    
    cout<<bits<<" "<<interval<<endl;


    cout<<"\nread input:"<<endl;
    read_txt_input(argv[1], page_size);  // read the input.txt and store pages into pages_vec
    run(alg_name, page_frames_num);

    cout<<endl;
    cout<<"events in trace:    "<<events_in_trace<<endl;
    cout<<"total disk reads:   "<<total_disk_reads<<endl;
    cout<<"total disk writes:   "<<total_disk_writes<<endl;
    cout<<"page faults:         "<<page_fault<<endl;
    return 0; 
}