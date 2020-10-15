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