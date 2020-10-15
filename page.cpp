#include <string>
using namespace std;


class Page
{
public:
    int page_num = -1;
    bool is_in_frame = false;
    bool is_dirty = false;
    char r_register; // r w
    int c_counter;

    Page() // default constructor
    {
        page_num = -1;
        is_in_frame = false;
        is_dirty = false;
        r_register = '!';
        c_counter = -1;
    }

    Page(int page_num_, bool is_in_frame_, bool is_dirty_, char r_register_, int c_counter_)
    {
        page_num = page_num_;
        is_in_frame = is_in_frame_;
        is_dirty = is_dirty_;
        r_register = r_register_;
        c_counter = c_counter_;
    }
};