#include <vector>
#include "page.cpp"
using namespace std;

bool check_if_in_vec(vector<Page> vec, Page target)
{
    for (int i=0; i<vec.size(); i++)
    {
        if (vec[i].page_num == target.page_num)
            return true;
    }
    return false;
}


// void right_shift(vector<Page> frames_vec_)
// {
//     for(int i=0; i<frames_vec_.size(); i++)
//     {
//         frames_vec_[i].r_register.push_front(0);  // add new reference bit as 0
//         frames_vec_[i].r_register.pop_back(); // abandon the last one of reference bits
//         cout<<frames_vec_[i].page_num<<" ";
//         for(deque<int>::iterator t=frames_vec_[i].r_register.begin(); t!=frames_vec_[i].r_register.end();t++)
//         {
//             cout<<*t;
//         }
//         cout<<"          ";
//     }
// }


// int find_victim_page_idx_ARU(vector<Page> frames_vec_, int bits)
// {
//     vector<int> idx;
//     for(int i=0; i<frames_vec_.size();i++)
//         idx.push_back(0);


//     for(int i=0; i<bits; i++)    
//     {

//         //count how many 0s and 1s on ith bit.
//         int num_0 = 0;
//         int num_1 = 0;
        
//         for(int j=0; j<frames_vec_.size(); j++)
//         {
//             if(idx[j]!=-1)
//             {
//                 if (frames_vec_[j].r_register[i] == 0)
//                     num_0 ++;
//                 else if (frames_vec_[j].r_register[i] == 1)
//                     num_1 ++;
//             }
//         }


//         if(num_0 == 0 || num_1 == 0) // all the same at the ith bit, continue to next bit
//             continue;
//         else
//         {
//             for(int a=0; a<frames_vec_.size(); a++)
//             {
//                 if (frames_vec_[a].r_register[i] == 1)
//                     idx[a] = -1;
//             }
//         }
//     }

//     // find victim page idx by FIFO
//     for(int i=0; i<frames_vec_.size(); i++)
//     {
//         if(idx[i] == 0)
//         {
//             cout<<"!!!!!!!!!!!!!!!!!!!!!!!!"<< i<<endl;
//             return i;
//         }
            
//         else
//             continue;
//     }

//     return -3;
// }