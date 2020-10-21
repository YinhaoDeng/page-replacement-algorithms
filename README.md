# page-replacement-algorithms

Language: C++

COMP SCI 3004/7064 Operating Systems Assignment2, the University of Adelaide

## Introduction
The aim of this assignment is to improve your learning experience in the page replacement
algorithms. Following our discussion of paging in lectures, this practical will allow you to explore
how real applications respond to a variety of page replacement schemes. Since modifying a real
operating system to use different page replacement algorithms can be quite a technical exercise,
your task will be to implement a program that simulates the behaviour of a memory system
using a variety of paging schemes.

## Algorithems implemented in this repository
1. **FIFO**:  Replace the page that has been resident in memory longest.
2. **LRU**: Replace the page that has been resident in memory oldest.
3. **ARB**:  Use multiple reference bits to approximate LRU. Your implementation should use
an a-bit shift register and the given regular interval b. See textbook section 9.4.5.1.
    - If two page’s ARB are equal, you should use FIFO (longest) to replace the frame.
4. **WSARB-1**: Combine the ARB page replacement algorithm with the working set model
that keeps track of the page reference frequencies over a given window size (page references)
for each process (see textbook section 9.6.2). It works as follows:
    - Associate each page with a reference bits as the shift register (R) to track the reference
pattern over the recent time intervals (for a given time interval length), and an integer
counter (C) of 8 bits to record the reference frequency of pages (in the memory frames)
in the current working set window. R and C are initialized to 0.
    - Page replacement is done by first selecting the victim page of the smallest reference
frequency (the smallest value of C), and then selecting the page that has the smallest
reference pattern value in the ARB shift register (the smallest value of R) if there are
multiple pages with the smallest reference frequency.
5. **WSARB-2**: Same as WSARB-1 in combining ARB with the working set model, but selecting a victim for page replacement is done in the reverse order:
    - First select the page having the smallest reference patten value in R, and then that
of the smallest reference frequency

Note that for WSARB-1 and WSARB-2, same as ARB, if there are multiple pages with the
same smallest values of R and C, victim will be chosen according to FIFO among them.


Full version of assignment description please see 'Assignment Description.pdf'.
