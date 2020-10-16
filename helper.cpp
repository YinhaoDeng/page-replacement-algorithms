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


void right_shift(vector<Page> pages_vec_)
{
    for(int i=0; i<pages_vec_.size(); i++)
    {
        pages_vec_[i].r_register.push_front(0);  // add new reference bit as 0
        pages_vec_[i].r_register.pop_back(); // abandon the last one of reference bits
    }
}


// int find_min_ref_idx_ARU(vector<Page> frames_vec_)
// {
//     for()
// }