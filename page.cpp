#include <string>
#include <deque>
using namespace std;


class Page
{
public:
    int page_num = -1;
    bool is_in_frame = false;
    char r_or_w; // r w
    deque<int> r_register;
    int c_counter = -1;

    Page() // default constructor
    {
        page_num = -1;
        is_in_frame = false;
        r_or_w = '!';
        c_counter = -1;
    }

    Page(int page_num_, bool is_in_frame_, char r_or_w_, int c_counter_)
    {
        page_num = page_num_;
        is_in_frame = is_in_frame_;
        r_or_w = r_or_w_;
        c_counter = c_counter_;
    }
};