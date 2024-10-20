#include "oslabs.h"
#include <stdlib.h>
#include <stdio.h>

// Helper functions
void update_page_entry(struct PTE *entry, int frame_number, int current_timestamp) {
    entry->is_valid = 1;
    entry->frame_number = frame_number;
    entry->arrival_timestamp = current_timestamp;
    entry->last_access_timestamp = current_timestamp;
    entry->reference_count = 1;
}

void evict_page(struct PTE *entry) {
    entry->is_valid = 0;
    entry->arrival_timestamp = 0;
    entry->last_access_timestamp = 0;
    entry->reference_count = 0;
}

int find_page_to_evict(struct PTE page_table[TABLEMAX], int table_cnt, const char *strategy) {
    int eavi = -1;
    if (strategy == "FIFO") {
        for (int i = 0; i < table_cnt; i++) {
            if (page_table[i].is_valid && (eavi == -1 || page_table[i].arrival_timestamp < page_table[eavi].arrival_timestamp)) {
                eavi = i;
            }
        }
    } else if (strategy == "LRU") {
        for (int i = 0; i < table_cnt; i++) {
            if (page_table[i].is_valid && (eavi == -1 || page_table[i].last_access_timestamp < page_table[eavi].last_access_timestamp)) {
                eavi = i;
            }
        }
    } else if (strategy == "LFU") {
        for (int i = 0; i < table_cnt; i++) {
            if (page_table[i].is_valid && (eavi == -1 || page_table[i].reference_count < page_table[eavi].reference_count || 
                (page_table[i].reference_count == page_table[eavi].reference_count && page_table[i].arrival_timestamp < page_table[eavi].arrival_timestamp))) {
                eavi = i;
            }
        }
    }
    return eavi;
}

int process_page_access(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp, const char *strategy) {
    if (page_table[page_number].is_valid) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count++;
        return page_table[page_number].frame_number;
    }

    if (*frame_cnt > 0) {
        int next_frame = frame_pool[--(*frame_cnt)];
        update_page_entry(&page_table[page_number], next_frame, current_timestamp);
        return page_table[page_number].frame_number;
    }

    int eavi = find_page_to_evict(page_table, *table_cnt, strategy);
    evict_page(&page_table[eavi]);
    update_page_entry(&page_table[page_number], page_table[eavi].frame_number, current_timestamp);
    return page_table[page_number].frame_number;
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int faults = 0;
    int timestamp = 0;
    for (int i = 0; i < reference_cnt; i++) {
        int j = reference_string[i]; 
        if (!page_table[j].is_valid) {
            faults++;
            process_page_access(page_table, &table_cnt, j, frame_pool, &frame_cnt, timestamp, "FIFO");
        } else {
            page_table[j].last_access_timestamp = timestamp; 
        }
        timestamp++;
    }
    return faults;
}

int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int faults = 0;
    int timestamp = 0;
    for (int i = 0; i < reference_cnt; i++) {
        int j = reference_string[i]; 
        if (!page_table[j].is_valid) {
            faults++;
            process_page_access(page_table, &table_cnt, j, frame_pool, &frame_cnt, timestamp, "LRU");
        } else {
            page_table[j].last_access_timestamp = timestamp; 
        }
        timestamp++;
    }
    return faults;
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt, int reference_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int faults = 0;
    int timestamp = 0;
    for (int i = 0; i < reference_cnt; i++) {
        int j = reference_string[i]; 
        if (!page_table[j].is_valid) {
            faults++;
            process_page_access(page_table, &table_cnt, j, frame_pool, &frame_cnt, timestamp, "LFU");
        } else {
            page_table[j].last_access_timestamp = timestamp; 
        }
        timestamp++;
    }
    return faults;
}


