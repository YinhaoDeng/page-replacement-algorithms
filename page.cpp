#include <string>
#include <deque>
using namespace std;


class Page
{
public:
    int page_num = -1;
    bool is_in_frame = false;
    bool is_dirty = false;
    char r_or_w; // r w
    deque<int> r_register;
    int c_counter;

    Page() // default constructor
    {
        page_num = -1;
        is_in_frame = false;
        is_dirty = false;
        r_or_w = '!';
        c_counter = -1;
    }

    Page(int page_num_, bool is_in_frame_, bool is_dirty_, char r_or_w_, int c_counter_)
    {
        page_num = page_num_;
        is_in_frame = is_in_frame_;
        is_dirty = is_dirty_;
        r_or_w = r_or_w_;
        c_counter = c_counter_;
    }
};