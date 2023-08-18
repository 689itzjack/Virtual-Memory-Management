//
// Created by student on 6/2/22.
//


#ifndef EX5_SIM_MEM_H
#define EX5_SIM_MEM_H

#define MEMORY_SIZE 200
extern char main_memory[MEMORY_SIZE];
#include <string>
using namespace std;
//========================================FUNCTIONS PART==========================================

typedef struct page_descriptor
{
    int V; // valid
    int D; // dirty
    int P; // permission
    int frame; //the number of a frame if in case it is page-mapped
    int swap_index; // where the page is located in the swap file.
} page_descriptor;

class sim_mem {
    int swapfile_fd; //swap file fd                 V
    int program_fd[2]; //executable file fd         V
    int text_size;    //                            v
    int data_size;//                                V
    int bss_size;//                                 V
    int heap_stack_size;    //                      V
    int num_of_pages;//                             V
    int page_size;//                                V
    int num_of_proc;//                              V
    int* id_pages_in_RAM;
    int* places_empty_in_SWAP;
    int* id_processes;
    int* id_processes_in_SWAP;


    page_descriptor **page_table; //pointer to page table
public:
    sim_mem(char exe_file_name1[],char exe_file_name2[], char swap_file_name2[], int text_size,
            int data_size, int bss_size, int heap_stack_size,
            int num_of_pages, int page_size, int num_of_process);

    ~sim_mem();

    char load(int process_id, int address);

    void store(int process_id, int address, char value);

    void print_memory();

    void print_swap();

    void print_page_table();
    //////////////////////////////////////////////SOS FUNCTIONS//////////////////////////////////////
    char* read_page_from_FILE(int fd, int number_of_page);

    int put_in_RAM(char* page_to_load, int num_page, int num_process);

    char address_zone(char addr);

    char* read_page_from_SWAP(int fd_, int num_of_page);

    void sending_to_SWAP();

    void write_to_SWAP(char* page, int fd_, int pagesize, int ind_in_SWAP);


    int seek_free_space_in_SWAP();

    void print_arrRAM();

    void print_arrSWAP();

    void print_idProcesses();

    void print_idProcesses_inSWAP();
    };
#endif //EX5_SIM_MEM_H
