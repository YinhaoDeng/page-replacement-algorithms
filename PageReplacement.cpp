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
deque<Page> WS_dq;

int bits;
int interval;
int WS_size;




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
            pages_vec.push_back(Page(y/page_size, false, action, 0));
            line_number ++;
        }
    }
    in_file.close(); // close input.txt file
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


int find_victim_idx_based_on_r_register(vector<Page> frames_vec_, int bits)
{
    vector<int> idx;
    for(int i=0; i<frames_vec_.size();i++)
        idx.push_back(0);


    for(int i=0; i<bits; i++)    
    {

        //count how many 0s and 1s on ith bit.
        int num_0 = 0;
        int num_1 = 0;
        
        for(int j=0; j<frames_vec_.size(); j++)
        {
            if(idx[j]!=-1)
            {
                if (frames_vec_[j].r_register[i] == 0)
                    num_0 ++;
                else if (frames_vec_[j].r_register[i] == 1)
                    num_1 ++;
            }
        }


        if(num_0 == 0 || num_1 == 0) // all the same at the ith bit, continue to next bit
            continue;
        else
        {
            for(int a=0; a<frames_vec_.size(); a++)
            {
                if (frames_vec_[a].r_register[i] == 1)
                    idx[a] = -1;
            }
        }
    }

    // find victim page idx by FIFO
    for(int i=0; i<frames_vec_.size(); i++)
    {
        if(idx[i] == 0)
            return i;
        else
            continue;
    }
}

void FIFO()


void right_shift(vector<Page> frames_vec)
{
    
}


void ARB(int page_frames_num_, Page current_page)
{
    if((events_in_trace-1) % interval == 0)
    {   
        cout<<"right shift";
        for(int i=0; i<frames_vec.size(); i++)
        {
            frames_vec[i].r_register.push_front(0);  // add new reference bit as 0
            frames_vec[i].r_register.pop_back(); // abandon the last one of reference bits
        }
    }


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
                frames_vec[i].r_register[0]=1;
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
            cout<<" page  "<<current_page.page_num;

            //find the victim page
            int victim_idx = find_victim_idx_based_on_r_register(frames_vec, bits);

            bool f = false;
            if (frames_vec[victim_idx].r_or_w == 'W')
            {
                total_disk_writes++;
                f = true;
            }

            cout<<"  REPLACE: page   "<<frames_vec[victim_idx].page_num<<"        ";
            frames_vec.erase(frames_vec.begin()+victim_idx);  // remove the victim page
            
            if(f == true)
                cout<<"(DIRTY)          "; 

            frames_vec.push_back(current_page);
        }
    }
}



void WSARB_1(int page_frames_num_, Page current_page)
{
    if((events_in_trace-1) % interval == 0)
    {   
        cout<<"right shift";
        for(int i=0; i<frames_vec.size(); i++)
        {
            frames_vec[i].r_register.push_front(0);  // add new reference bit as 0
            frames_vec[i].r_register.pop_back(); // abandon the last one of reference bits
        }
    }


    //update current working set
    if(WS_dq.size() < WS_size) // if Working set has room
        WS_dq.push_back(current_page);
    else // working set is full
    {
        WS_dq.front().c_counter --;
        WS_dq.pop_front();// clean the deque tail
        WS_dq.push_back(current_page);// add current page to WS front
    }
    

    if(check_if_in_vec(frames_vec, current_page)) // if page is in frames
    {
        cout<<"     Hit:      ";
        cout<<"page  "<<current_page.page_num<<"                                        ";
       
        for (int i=0; i<frames_vec.size(); i++)
        {
            if(frames_vec[i].page_num == current_page.page_num)
            {
                frames_vec[i].c_counter ++;
                if (current_page.r_or_w == 'W' && frames_vec[i].r_or_w == 'R')
                    frames_vec[i].r_or_w = 'W';
                frames_vec[i].r_register[0] = 1;  // update r_register
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
            current_page.c_counter++;
            frames_vec.push_back(current_page);  //add the page to the frames last
            cout<<" page  "<<current_page.page_num;
            cout<<"                       ";
            
        }
        else // frames have no space
        {
            cout<<" page  "<<current_page.page_num;

            // find min c_counter
            int min_c_counter = 1000;
            for (int i=0; i< frames_vec.size(); i++)
            {
                if(frames_vec[i].c_counter<min_c_counter)
                    min_c_counter = frames_vec[i].c_counter;
            }
            // I got the minimun c_counter value
            

            vector<Page> min_c_vec; // look for all the pages which have the same c_counter value as the min c_counter value
            for(int i=0; i<frames_vec.size(); i++) // find the page with min c_counter
            {
                if(frames_vec[i].c_counter == min_c_counter)
                    min_c_vec.push_back(frames_vec[i]);
            }

            cout<<" -----> min_c_vec: {";
            for (int i=0; i<min_c_vec.size(); i++)
            {
                cout<<min_c_vec[i].page_num<<"["<<min_c_vec[i].c_counter<<"]  ";
            }
            cout<<"}"<<endl;

            //look for the victim page
            int victim_idx = -1;
            if(min_c_vec.size()==1)
            {
                for(int i=0; i<frames_vec.size(); i++)
                {
                    if(frames_vec[i].page_num = min_c_vec[0].page_num)
                        victim_idx = i;
                        break;
                }
            }
            else if(min_c_vec.size()>1) // if there are more than one page with min c_counter, then we compare their r_registers
            {
                victim_idx = find_victim_idx_based_on_r_register(min_c_vec, bits); // FIFO included
            }

            cout<<"victim page idx: ["<<victim_idx<<"]"<<endl;
            bool f = false;
            if (frames_vec[victim_idx].r_or_w == 'W')
            {
                total_disk_writes++;
                f = true;
            }

            cout<<"  REPLACE: page   "<<frames_vec[victim_idx].page_num<<"        ";
            frames_vec[victim_idx].c_counter = 0;
            frames_vec.erase(frames_vec.begin()+victim_idx);  // remove the victim page
            
            if(f == true)
                cout<<"(DIRTY)          "; 

            current_page.c_counter ++; //Miss, and frames are full.
            frames_vec.push_back(current_page);
        }
    }
}
    


void WSARB_2(int page_frames_num_, Page current_page)
{

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
        cout<<"-----------------------------------------------------------------------------"<<endl;
        cout<<"Time:   "<<i+1;
        events_in_trace ++;

             // algorithm name:
        if (algorithm_name == "FIFO")
            FIFO(page_frame_num, pages_vec[i]);
        else if(algorithm_name == "LRU")
            LRU(page_frame_num, pages_vec[i]);
        else if(algorithm_name == "ARB")
            ARB(page_frame_num, pages_vec[i]);
        else if(algorithm_name == "WSARB-1")
            WSARB_1(page_frame_num, pages_vec[i]);
        else if(algorithm_name == "WSARB-2")
            WSARB_2(page_frame_num, pages_vec[i]);
        else{
            cout<<"wrong algorithm name!"<<endl;
            return;
        }


        cout<<"frames after excution: ";
        for(int i=0; i<frames_vec.size(); i++)
        {
            cout<<frames_vec[i].page_num<<" ["<<frames_vec[i].c_counter<<"] (";
            for(deque<int>::iterator t=frames_vec[i].r_register.begin(); t!=frames_vec[i].r_register.end(); t++)
                cout<<*t;
            cout<<") ";
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
   
    
    if(argc>5)
    {
        bits = stoi(argv[5]);
        interval = stoi(argv[6]);
    }
    if(argc>7)
        WS_size = stoi(argv[7]);


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