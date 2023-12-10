#include "oslabs.h"

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp)
{
    int frame = -1;
    int rPage = -1;

    // Update page table and return the fame number if page is already in memory
    if (page_table[page_number].is_valid)
    {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count++;
        return page_table[page_number].frame_number;
    }

    // If page is not in memory, return an available frame
    if ((*frame_cnt) > 0)
    {
        frame = frame_pool[(*frame_cnt) - 1];
        (*frame_cnt)--;
        page_table[page_number].frame_number = frame;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        return page_table[page_number].frame_number;
    }

    // Identify first page that arrives in memory
    for (int i = 0; i < *table_cnt; i++)
    {
        if (page_table[i].is_valid)
        {
            if (rPage < 0)
            {
                rPage = i;
            }
            else
            {
                if (page_table[i].arrival_timestamp < page_table[rPage].arrival_timestamp)
                {
                    rPage = i;
                }
            }
        }
    }

    // Replace with new page
    frame = page_table[rPage].frame_number;
    page_table[rPage].is_valid = 0;
    page_table[rPage].frame_number = 0;
    page_table[rPage].arrival_timestamp = 0;
    page_table[rPage].last_access_timestamp = 0;
    page_table[rPage].reference_count = 0;

    page_table[page_number].is_valid = 1;
    page_table[page_number].frame_number = frame;
    page_table[page_number].arrival_timestamp = current_timestamp;
    page_table[page_number].last_access_timestamp = current_timestamp;
    page_table[page_number].reference_count = 1;

    return frame;
};
int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt)
{
    return 0;
};
int process_page_access_lru(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp)
{
    return 0;
};
int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt)
{
    return 0;
};
int process_page_access_lfu(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp)
{
    return 0;
};
