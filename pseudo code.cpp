#include <iostream>
#include <vector>

using namespace std;


class Page
{
public:
	int pageNum;
	bool inFrame;
	bool dirty;

	string r_register;
	int c_counter;

	Page();
	~Page(){}
};


static int EventTrace = 0;
static int diskRead = 0;
static int diskWrite = 0;
static int pageFault = 0;
static int current_time = 0;


function void FIFO (page_Frame, pageNum)
{
	if pageNum is in Frame: do nothing;
	else:
		pageFault++
		diskRead++
		if page_Frame is not full: add the page into last
		else 
			if the first page is Dirty: diskWrite++;
			remove the first page, then add the page into last
}

function void LRU (page_Frame, pageNum)
{
	if pageNum is in Frame:
		move this page into the last
	else:
		pageFault++
		diskRead++
		if page_Frame is not full: add the page into last
		else
			if the first page is Dirty: diskWrite++;
			remove the first page, then add the page into last
}

function void ARB (page_Frame, pageNum)
{
	if (curent_time % interval == 0)
		all page in pageFrame r_register >>> 1

	if pageNum is in Frame:
		page.r_register[0] = 1
	else
		page.r_register[0] = 1
		if page_Frame is not full: add the page into last
		else
			victim = the smallest r_register in the Queue.
			if victim is dirty:  diskWrite++
			remove the victime. then add the page into last
}


function void WARGB1 (page_Frame, pageNum)
{
	if (cuurent_time % interval == 0)
		all page in pageFrame r_register >>> 1

	calculate eache page in Frame counter in the window size;

	if pageNum is in Frame:
		page.r_register[0] = 1
	else
		page.r_register[0] = 1
		if page_Frame is not full: add the page into last
		else
			victim = the smallest counter, then the smallest r_register
			if victim is dirty:  diskWrite++
			remove the victime. then add the page into last
}


function void WARGB2 (page_Frame, pageNum)
{
	if (cuurent_time % interval == 0)
		all page in pageFrame r_register >>> 1

	calculate eache page in Frame counter in the window size;

	if pageNum is in Frame:
		page.r_register[0] = 1
	else
		page.r_register[0] = 1
		if page_Frame is not full: 
			add the page into last
		else
			victim = the smallest r_register then the smallest counter
			if victim is dirty:  diskWrite++
			remove the victime. then add the page into last
}


toDecimal ()
{
	string input
	int number = 0
	for digit the right to the left:
		if '0' <= input[i] <= '9' 
			number += pow(input[i] - '0', i)
		if 'a' <= input[i] <= 'f' 
			number += pow(input[i] - 'a'+10, i)

}






function runTheSystem ()
{
	orders: order1, order2, order3, order4 ....


	// 一个Queue 用于寻找victim
	// static vector <Page> page_Frame = new vector <Page> (3); use full number to check if the frame is full
	// Page [] page_Frame = new Page [120];

	// R 0041f7a0
	// W 31348900
 

	for order in orders:
		EventTrace++

		if is reading: 
			FIFO|LRU(page_Frame, pageNum)

		if is writing:
			FIFO|LRU(page_Frame, pageNum)
			page.isDirty = true;
}


 int main(int argc, char const *argv[])
 {
 	/* code */
 	return 0;
 }