#include "oslabs.h"

struct PTE {
    int is_valid;
    int frame_number;
    int arrival_timestamp;
    int last_access_timestamp;
    int reference_count;
};

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    // Check if page is already in memory
    if (page_table[page_number].is_valid) {
        // Update timestamps and reference count
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count++;
        return page_table[page_number].frame_number;
    }

    // Check for free frames
    if (*frame_cnt > 0) {
        int new_frame = frame_pool[--(*frame_cnt)];
        page_table[page_number].frame_number = new_frame;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        return new_frame;
    }

    // Replace a page using FIFO
    int oldest_index = -1;
    for (int i = 0; i < *table_cnt; i++) {
        if (page_table[i].is_valid && (oldest_index == -1 || page_table[i].arrival_timestamp < page_table[oldest_index].arrival_timestamp)) {
            oldest_index = i;
        }
    }

    // Replace the oldest page
    page_table[oldest_index].is_valid = 0;
    page_table[oldest_index].frame_number = -1;
    page_table[oldest_index].arrival_timestamp = -1;
    page_table[oldest_index].last_access_timestamp = -1;
    page_table[oldest_index].reference_count = -1;

    // Insert the new page
    int new_frame = page_table[oldest_index].frame_number;
    page_table[page_number].frame_number = new_frame;
    page_table[page_number].is_valid = 1;
    page_table[page_number].arrival_timestamp = current_timestamp;
    page_table[page_number].last_access_timestamp = current_timestamp;
    page_table[page_number].reference_count = 1;
    return new_frame;
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int page_faults = 0;
    int current_timestamp = 1;

    for (int i = 0; i < reference_cnt; i++) {
        int page_number = reference_string[i];
        if (!page_table[page_number].is_valid) {
            page_faults++;
            process_page_access_fifo(page_table, &table_cnt, page_number, frame_pool, &frame_cnt, current_timestamp++);
        } else {
            page_table[page_number].last_access_timestamp = current_timestamp++;
            page_table[page_number].reference_count++;
        }
    }
    return page_faults;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    // Check if page is already in memory
    if (page_table[page_number].is_valid) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count++;
        return page_table[page_number].frame_number;
    }

    // Check for free frames
    if (*frame_cnt > 0) {
        int new_frame = frame_pool[--(*frame_cnt)];
        page_table[page_number].frame_number = new_frame;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        return new_frame;
    }

    // Replace a page using LRU
    int lru_index = -1;
    for (int i = 0; i < *table_cnt; i++) {
        if (page_table[i].is_valid && (lru_index == -1 || page_table[i].last_access_timestamp < page_table[lru_index].last_access_timestamp)) {
            lru_index = i;
        }
    }

    // Replace the least recently used page
    page_table[lru_index].is_valid = 0;
    page_table[lru_index].frame_number = -1;
    page_table[lru_index].arrival_timestamp = -1;
    page_table[lru_index].last_access_timestamp = -1;
    page_table[lru_index].reference_count = -1;

    // Insert the new page
    int new_frame = page_table[lru_index].frame_number;
    page_table[page_number].frame_number = new_frame;
    page_table[page_number].is_valid = 1;
    page_table[page_number].arrival_timestamp = current_timestamp;
    page_table[page_number].last_access_timestamp = current_timestamp;
    page_table[page_number].reference_count = 1;
    return new_frame;
}

int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int page_faults = 0;
    int current_timestamp = 1;

    for (int i = 0; i < reference_cnt; i++) {
        int page_number = reference_string[i];
        if (!page_table[page_number].is_valid) {
            page_faults++;
            process_page_access_lru(page_table, &table_cnt, page_number, frame_pool, &frame_cnt, current_timestamp++);
        } else {
            page_table[page_number].last_access_timestamp = current_timestamp++;
            page_table[page_number].reference_count++;
        }
    }
    return page_faults;
}

int process_page_access_lfu(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    // Check if page is already in memory
    if (page_table[page_number].is_valid) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count++;
        return page_table[page_number].frame_number;
    }

    // Check for free frames
    if (*frame_cnt > 0) {
        int new_frame = frame_pool[--(*frame_cnt)];
        page_table[page_number].frame_number = new_frame;
        page_table[page_number].is_valid = 1;
        page_table[page_number].arrival_timestamp = current_timestamp;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        return new_frame;
    }

    // Replace a page using LFU
    int lfu_index = -1;
    for (int i = 0; i < *table_cnt; i++) {
        if (page_table[i].is_valid && (lfu_index == -1 || page_table[i].reference_count < page_table[lfu_index].reference_count || 
            (page_table[i].reference_count == page_table[lfu_index].reference_count && page_table[i].arrival_timestamp < page_table[lfu_index].arrival_timestamp))) {
            lfu_index = i;
        }
    }

    // Replace the least frequently used page
    page_table[lfu_index].is_valid = 0;
    page_table[lfu_index].frame_number = -1;
    page_table[lfu_index].arrival_timestamp = -1;
    page_table[lfu_index].last_access_timestamp = -1;
    page_table[lfu_index].reference_count = -1;

    // Insert the new page
    int new_frame = page_table[lfu_index].frame_number;
    page_table[page_number].frame_number = new_frame;
    page_table[page_number].is_valid = 1;
    page_table[page_number].arrival_timestamp = current_timestamp;
    page_table[page_number].last_access_timestamp = current_timestamp;
    page_table[page_number].reference_count = 1;
    return new_frame;
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int page_faults = 0;
    int current_timestamp = 1;

    for (int i = 0; i < reference_cnt; i++) {
        int page_number = reference_string[i];
        if (!page_table[page_number].is_valid) {
            page_faults++;
            process_page_access_lfu(page_table, &table_cnt, page_number, frame_pool, &frame_cnt, current_timestamp++);
        } else {
            page_table[page_number].last_access_timestamp = current_timestamp++;
            page_table[page_number].reference_count++;
        }
    }
    return page_faults;
}
