//
// Created by student on 6/2/22.
//

#include "sim_mem.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

char main_memory[MEMORY_SIZE];
int space_freeRAM=0;
bool fullRAM= false;
/////////////////////////////////////////////////FUNCTIONS SOS/////////////////////////////////////////////
//ALL THESE FUNCTIONS (FUNCTIONS SOS) ARE USED TO HELP US IN THE DEBUGGING
void sim_mem::print_arrSWAP(){//////////////////////////////////////////////////SOS TEMP

    int sizeSWAP = (this->data_size+this->bss_size+this->heap_stack_size)/this->page_size;
    if(this->num_of_proc ==2)
        sizeSWAP*=2;
    for(int i=0;i < sizeSWAP; i++){
        cout<<places_empty_in_SWAP[i]<<", ";
    }
    cout<<endl;
}
void sim_mem::print_arrRAM(){//////////////////////////////////////////////////SOS TEMP
    int sizearr = MEMORY_SIZE/this->page_size;
    cout<<"ARRAY ID_PAGES_IN_RAM ";
    for(int i=0;i < sizearr; i++){
        cout<<id_pages_in_RAM[i]<<", ";
    }
    cout<<endl;
}
void sim_mem::print_idProcesses(){//////////////////////////////////////////////////SOS TEMP
    int sizearr = MEMORY_SIZE/this->page_size;
    cout<<"ARRAY ID_PROCESSES ";
    for(int i=0;i < sizearr; i++){
        cout<<id_processes[i]<<", ";
    }
    cout<<endl;
}
void sim_mem::print_idProcesses_inSWAP(){//////////////////////////////////////////////////SOS TEMP
    int sizeSWAP = (this->data_size+this->bss_size+this->heap_stack_size)/this->page_size;
    if(this->num_of_proc ==2)
        sizeSWAP*=2;
    cout<<"ARRAY ID_PROCESSES_IN_SWAP ";
    for(int i=0;i < sizeSWAP; i++){
        cout<<id_processes_in_SWAP[i]<<", ";
    }
    cout<<endl;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void struct_Page_table_initialization(page_descriptor* page_tab, int page_table_size, int num_pages_txt){
//INITIALIZATION PAGE TABLE
    int zone_txt = 0;
    for (int i=0; i < page_table_size; i++){
        page_tab[i].D = 0;//dirty yes=1, no=0
        if(zone_txt < num_pages_txt)
            page_tab[i].P = 0;
        else page_tab[i].P = 1;//permission read=0, read/write=1
        page_tab[i].V = 0;//valid yes=1, no=0
        page_tab[i].frame = -1;
        page_tab[i].swap_index = -1;
        zone_txt++;
    }
}

void initializer_swap(int fd_file, int size_file){//initialize the swap file with zeros
    char buff_temp[size_file];
    memset(buff_temp,'0',size_file);
    if(write(fd_file,buff_temp,(size_file)) == -1){
        perror("The writing to the file swap failed, try again\n ");
    }
}

char* sim_mem::read_page_from_FILE(int fd_, int num_of_page){//READ A PAGE FROM THE EXEC FILE (FROM DATA/TEXT ZONE)
    char* page_to_return = new char[this->page_size];
    char readen[1];
    int position_in_file = num_of_page * this->page_size;
    lseek(fd_,position_in_file,SEEK_SET);
    for(int i=0; i < this->page_size; i++){
        read(fd_, readen , 1);
        page_to_return[i]=readen[0];
    }
    return page_to_return;
}

char* sim_mem::read_page_from_SWAP(int fd_, int index_swap){//READ A PAGE FROM THE SWAP FILE ACCORD TO THE PAGE INDEX IN THE SWAP
    char* page_to_return = new char[this->page_size];
    char readen[1];
    char writing[1];
    writing[0]='0';
    int position_in_file = index_swap * this->page_size;
    lseek(fd_,position_in_file,SEEK_SET);
    for(int i=0; i < this->page_size; i++){
        read(fd_, readen , 1);
        page_to_return[i]=readen[0];
    }
    lseek(fd_,position_in_file,SEEK_SET);
    for(int i=0; i < this->page_size; i++){
        write(fd_, writing , 1);
    }
    //print_arrSWAP();//===============================================================================================
    this->places_empty_in_SWAP[index_swap] = 0;
    this->id_processes_in_SWAP[index_swap] = 0;
    //print_arrSWAP();//===============================================================================================

    return page_to_return;
}

int sim_mem::put_in_RAM(char* page_to_load, int num_page, int num_process){//gets as param the page to be loaded and write it in the RAM, returns the number of the frame
    //allocated in the RAM
    int index=space_freeRAM * this->page_size;
    int limit = index + this->page_size;
    int ind_page = 0;
    if(space_freeRAM < this->num_of_pages){
        for(index; index < limit; index++,ind_page++){
            main_memory[index]=page_to_load[ind_page];
        }
        //print_arrRAM();//==============================================================
        //print_idProcesses();//==============================================================

        this->id_pages_in_RAM[space_freeRAM] = num_page;
        this->id_processes[space_freeRAM]=num_process;
        //print_arrRAM();//==============================================================
        //print_idProcesses();//==============================================================

        space_freeRAM++;
    }
    if(space_freeRAM == MEMORY_SIZE/this->page_size){
        fullRAM = true;
        int lastPage=space_freeRAM;
        space_freeRAM=0;
        return lastPage;
    }
    return space_freeRAM;
}

char sim_mem::address_zone(char addr){//CALCULATES THE ADDRESS AREA BELONGS AT THE PROCESS
    int text = this->text_size-1;
    int data = this->text_size+this->data_size-1;
    int bss = this->data_size+this->text_size+this->bss_size-1;
    int heap_stack = this->data_size+this->text_size+this->bss_size+this->heap_stack_size-1;
    if(addr <= text)
        return 't';
    else if(addr > text && addr <= data)
        return 'd';
    else if(addr > data && addr <= bss)
        return 'b';
    else if(addr > bss && addr <= heap_stack)
        return 'h';
    else return 'e';
}

int sim_mem::seek_free_space_in_SWAP(){//SEEK FREE SPACE IN THE SWAP AND RETURNS THE INDEX
    int num_pages_in_SWAP = (this->data_size+this->bss_size+this->heap_stack_size)/this->page_size;
    for(int i = 0; i < num_pages_in_SWAP; i++){
        if(this->places_empty_in_SWAP[i] == 0)
            return i;
    }
    return -1;
}

void sim_mem::write_to_SWAP(char* page, int fd_, int pagesize, int ind_in_SWAP){//WRITES A STRING TO THE FILE SWAP

    int position_in_file = ind_in_SWAP * pagesize;
    lseek(fd_,position_in_file,SEEK_SET);
    write(fd_,page, pagesize);
}

void sim_mem::sending_to_SWAP(){//IF THE MEMORY IS FULL WE OVERWRITE THE DATA
    char send_page[this->page_size];//in this arr will save the page to write in the SWAP
    int index = space_freeRAM * this->page_size;//index from the page actually at the RAM
    page_descriptor curr_page;
    //print_arrRAM();//================================================================================
    int curr_page_inRAM = this->id_pages_in_RAM[space_freeRAM];//num of page allocated actually at the RAM
    int id_curr_process = this->id_processes[space_freeRAM];
    page_descriptor* curr_proc_page_table = this->page_table[id_curr_process-1];
    curr_page = curr_proc_page_table[curr_page_inRAM];

    if(curr_page.D == 1 && curr_page.P == 1){
        int index_in_swap = seek_free_space_in_SWAP();//SEEKING A FREE SPACE IN THE SWAP
        int i=0;
        for(i; i < this->page_size; index++,i++){
            send_page[i]=main_memory[index];//COPING DATA FROM THE RAM TO THE PAGE FOR THE SWAP
        }
        write_to_SWAP(send_page,this->swapfile_fd,this->page_size, index_in_swap);
        //AFTER TO WRITE TO THE SWAP WE DELETE THE PAGE FROM THE RAM PLACING THE INDEX SWAP IN THE PAGE
        curr_page.V = 0;
        curr_page.frame = -1;
        curr_page.swap_index = index_in_swap;
        //print_arrSWAP();//===============================================================================================
        //print_idProcesses_inSWAP();//==========================================
        this->places_empty_in_SWAP[index_in_swap] = 1;//the page into the SWAP is full
        this->id_processes_in_SWAP[index_in_swap] = id_curr_process;//saving the id of the current process of SWAP
        //print_arrSWAP();//===============================================================================================
        //print_idProcesses_inSWAP();//==========================================
        curr_proc_page_table[curr_page_inRAM] = curr_page;
        this->page_table[id_curr_process-1] = curr_proc_page_table;
        return ;
    }
    else{
        curr_page.V = 0;
        curr_page.frame = -1;
        curr_proc_page_table[curr_page_inRAM] = curr_page;
        this->page_table[id_curr_process-1] = curr_proc_page_table;
        return ;
    }
}

///////////////////////////////////////////////FINISH FUNCTIONS SOS/////////////////////////////////////////////////

sim_mem::sim_mem(char exe_file_name1[],char exe_file_name2[], char swap_file_name2[], int text_size,
                 int data_size, int bss_size, int heap_stack_size,
                 int num_of_pages, int page_size, int num_of_process){//CONSTRUCTOR
    int fd_exe_1;
    int fd_exe_2;
    int num_pages_text;
    int num_pages_bss;
    int num_pages_data;
    int num_pages_heap_stack;

    fd_exe_1=open(exe_file_name1,O_RDWR,0);//FD FROM THE FIRST FILE EXECUTABLE
    if(fd_exe_1 == -1){
        perror("The system call open() failed in the first executable file, try again.\n");
        exit(1);
    }
    if(strcmp(exe_file_name2,"") != 0){
        fd_exe_2=open(exe_file_name2,O_RDWR,0);//FD FROM THE SECOND FILE EXECUTABLE
        if(fd_exe_2 == -1){
            perror("The system call open() failed in the second executable file, try again.\n");
            exit(1);
        }
        this->program_fd[1] = fd_exe_2;
    }
    this->program_fd[0] = fd_exe_1;
    swapfile_fd=open(swap_file_name2,O_RDWR|O_CREAT,S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if(swapfile_fd == -1){
        perror("The system call open() failed in the swap file, try again.\n");
        exit(1);
    }
    this->text_size=text_size;
    this->data_size=data_size;
    this->bss_size=bss_size;
    this->heap_stack_size=heap_stack_size;
    this->num_of_pages=num_of_pages;
    this->page_size=page_size;
    this->num_of_proc=num_of_process;
    this->id_pages_in_RAM = new int[MEMORY_SIZE/this->page_size];
    this->id_processes = new int[MEMORY_SIZE/this->page_size];
    num_pages_text=text_size/page_size;
    num_pages_data=data_size/page_size;
    num_pages_bss=bss_size/page_size;
    num_pages_heap_stack=heap_stack_size/page_size;
    page_table = new page_descriptor *[num_of_process];

    for(int i=0 ; i < num_of_process ; i++ ){// STARTING PAGE TABLE OF EVERY PROCESS
        page_table[i] = new page_descriptor [num_of_pages];
        struct_Page_table_initialization(page_table[i],num_of_pages,num_pages_text);
    }
    memset(main_memory,0,MEMORY_SIZE);//starting memory RAM in 0
    int size_swap_file = data_size+bss_size+heap_stack_size;// SIZE ADRESES PROCESS WITHOUT SIZE TEXT
    if(num_of_process == 2 ){
        size_swap_file = size_swap_file*2;
    }
    initializer_swap(swapfile_fd, size_swap_file);
    int num_pages_in_SWAP = size_swap_file/this->page_size;

    this->places_empty_in_SWAP = new int[num_pages_in_SWAP];
    this->id_processes_in_SWAP = new int[num_pages_in_SWAP];
}

sim_mem::~sim_mem(){

    close(this->program_fd[0]);
    if(this->num_of_proc == 2)
        close(this->program_fd[1]);
    close(this->swapfile_fd);

    for(int i=0 ; i < this->num_of_proc; i++ ){// STARTING PAGE TABLE OF EVERY PROCESS
        delete [] page_table[i];
    }
    delete [] page_table;
    delete [] id_pages_in_RAM;
    delete [] id_processes;
    delete [] places_empty_in_SWAP;
    delete [] id_processes_in_SWAP;
}

char sim_mem:: load(int process_id, int address){//LOAD A PAGE TO THE MEMORY

    char* page_readed;
    char zone_at;
    page_descriptor* curr_process_page_table=this->page_table[process_id-1];//page table of the current Process
    if(curr_process_page_table == NULL){//if the process doesn't exist
        fprintf(stderr,"the process id doesnt exist yet \n");
        return '\0';
    }
    int number_of_page = address/this->page_size;//NUMBER OF PAGE ACCORDING TO THE ADDRESS
    if(number_of_page >= this->num_of_pages){
        perror("THE ADDRESS REQUEST IS OUT OF BOUNDS ACCORDING TO THE PROCESS, TRY AN SMALLER ADDRESS\n");
        return '\0';
    }
    int remainder = address%this->page_size;//RESIDUAL ACCORDING TO THE ADDRESS

    /*cout<<"NUMBER PAGE: "<<number_of_page<<" TABLE: ";//==========================================================
    cout <<"valid:"<< curr_process_page_table[number_of_page].V<<" dirty:"<<curr_process_page_table[number_of_page].D<<" permission:"
         <<curr_process_page_table[number_of_page].P<<" frame:"<<curr_process_page_table[number_of_page].frame
         <<" idx swap:"<<curr_process_page_table[number_of_page].swap_index<<endl;//===============================================
         */
    page_descriptor curr_page = curr_process_page_table[number_of_page];//CURRENT PAGE IN TH PAGE TABLE

    if(curr_page.V == 0){//MEANS THE PAGE IS NOT IN THE MEMORY RAM

        if(curr_page.P == 0){//PAGE WITHOUT PERMISSIONS
            page_readed= read_page_from_FILE(this->program_fd[process_id-1], number_of_page);
            //cout<<page_readed<<endl;//==========================================
            if(fullRAM == false){
                curr_page.frame=put_in_RAM(page_readed,number_of_page,process_id)-1;
                curr_page.V=1;
            }
            else{
                sending_to_SWAP();
                curr_page.frame=put_in_RAM(page_readed,number_of_page,process_id)-1;
                curr_page.V=1;
            }
            curr_process_page_table[number_of_page]=curr_page;
            this->page_table[process_id-1]=curr_process_page_table;
            char val_ret=page_readed[remainder];
            delete [] page_readed;
            return val_ret;
        }
        else{//we have permissions read/write, in the page.  P=1

            if(curr_page.D == 0){//THE PAGE IS NOT DIRTY
                zone_at = address_zone(address);
                if(zone_at == 'h'){//IF THE ADDRESS BELONG TO THE STACK-HEAP SECTOR
                    perror("The memory it wasn't allocated yet,\nplease allocate memory with store()function\n");
                    return '\0';
                }
                else if(zone_at == 'b'){//IF THE ADDRESS BELONG TO THE BSS SECTOR
                    char* wrt_bss=(char*)"00000";
                    if(fullRAM == false){//if we have space in the RAM
                        curr_page.frame=put_in_RAM(wrt_bss,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    else{//otherwise
                        sending_to_SWAP();
                        curr_page.frame=put_in_RAM(wrt_bss,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    curr_process_page_table[number_of_page]=curr_page;
                    this->page_table[process_id-1]=curr_process_page_table;
                    char val_ret=wrt_bss[remainder];
                    return val_ret;
                }
                else if(zone_at == 'd'){//IF THE ADDRESS BELONG TO THE DATA SECTOR
                    page_readed= read_page_from_FILE(this->program_fd[process_id-1], number_of_page);
                    //cout<<page_readed<<endl;//==========================================
                    if(fullRAM == false){
                        curr_page.frame=put_in_RAM(page_readed, number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    else{
                        sending_to_SWAP();
                        curr_page.frame=put_in_RAM(page_readed,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    curr_process_page_table[number_of_page]=curr_page;
                    this->page_table[process_id-1]=curr_process_page_table;
                    char val_ret=page_readed[remainder];
                    delete [] page_readed;
                    return val_ret;
                }
            }
            else{//THE PAGE IS DIRTY D=1 AND WE HAVE PERMISSIONS P=1 AND THE PAGE IS NOT IN THE RAM V=0
                page_readed= read_page_from_SWAP(this->swapfile_fd,curr_page.swap_index);
                //cout<<page_readed<<endl;//==========================================
                sending_to_SWAP();
                curr_page.frame = put_in_RAM(page_readed,number_of_page,process_id)-1;
                curr_page.V = 1;
                curr_page.D = 0;
                curr_page.swap_index = -1;
                curr_process_page_table[number_of_page]=curr_page;
                this->page_table[process_id-1]=curr_process_page_table;
                char char_to_ret=page_readed[remainder];
                delete [] page_readed;
                return char_to_ret;
            }
        }
    }
    else{//THE PAGE IS VALID (IN THE RAM) V=1
        int at_RAM=(this->page_size*curr_page.frame)+remainder;
        return main_memory[at_RAM];
    }
    return 0;
}

void sim_mem:: store(int process_id, int address, char value){//STORE THE VALUE IN THE GIVEN ADDRESS
    char* page_readed;
    char zone_at;
    int at_RAM;
    page_descriptor* curr_process_page_table=this->page_table[process_id-1];//page table of the current Process
    if(curr_process_page_table == NULL){//if the process doesn't exist
        fprintf(stderr,"the process id doesnt exist yet \n");
        return;
    }
    int number_of_page = address/this->page_size;//NUMBER OF PAGE ACCORDING TO THE ADDRESS
    if(number_of_page >= this->num_of_pages){
        perror("THE ADDRESS REQUEST IS OUT OF BOUNDS ACCORDING TO THE PROCESS, TRY AN SMALLER ADDRESS\n");
        return;
    }
    int remainder = address%this->page_size;//RESIDUAL ACCORDING TO THE ADDRESS

    /*cout<<"NUMBER PAGE: "<<number_of_page<<" TABLE: ";//==========================================================
    cout <<"valid:"<< curr_process_page_table[number_of_page].V<<" dirty:"<<curr_process_page_table[number_of_page].D<<" permission:"
         <<curr_process_page_table[number_of_page].P<<" frame:"<<curr_process_page_table[number_of_page].frame
         <<" idx swap:"<<curr_process_page_table[number_of_page].swap_index<<endl;//===============================================
         */
    page_descriptor curr_page = curr_process_page_table[number_of_page];//CURRENT PAGE IN THE PAGE TABLE

    if(curr_page.V == 0){//MEANS THE PAGE IS NOT IN THE MEMORY RAM

        if(curr_page.P == 0){//PAGE WITHOUT PERMISSIONS, PAGE NOT VALID(NOT IN RAM) V=0
            perror("You cannot overwrite the text area (Seg Fault)\n");
            return;
        }
        else{//we have permissions read-write in the page P=1 but the page not valid V=0

            if(curr_page.D == 0){//THE PAGE IS NOT DIRTY D=0, WE HAVE ACCESS P=1, PAGE NOT IN RAM V=0
                zone_at = address_zone(address);//GET WHAT KIND OF ADDRESS WE GOT (ADDRESS ZONE H_S,BSS,DATA)

                if(zone_at == 'h' || zone_at == 'b'){//IF THE ADDRESS BELONG TO THE STACK-HEAP SECTOR OR TO THE BSS SECTOR
                    //IN THIS CASE WE LOAD A PAGE FULL OF ZEROS TO THE RAM AN AFTER WE WRITE ON IT
                    char *wrt_bss=(char*)"00000";
                    if(fullRAM == false){//THE RAM IS NOT FULL,SO WE PUT IN THE DATA INTO IT
                        curr_page.frame=put_in_RAM(wrt_bss,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    else{//THE RAM FULL,WE SAVE THE DATA BEFORE IN THE SWAP AND WRITE THE NEW ONE AT THE RAM
                        sending_to_SWAP();
                        curr_page.frame=put_in_RAM(wrt_bss,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    at_RAM=(this->page_size*curr_page.frame)+remainder;//ADDRESS IN RAM(PHYSICAL ADDRESS)
                    main_memory[at_RAM] = value;//writing the new char in the RAM
                    curr_page.D = 1;//UPDATING PAGE TO BE DIRTY D=1
                    curr_process_page_table[number_of_page]=curr_page;//UPDATING THE NEW PAGE TABLE
                    this->page_table[process_id-1]=curr_process_page_table;//updating all the page table
                    return;
                }
                if(zone_at == 'd'){//IF THE ADDRESS BELONG TO THE DATA SECTOR,NO DIRTY D=0,YES PERMISSION P=1
                    //PAGE NOT VALID V=O
                    page_readed= read_page_from_FILE(this->program_fd[process_id-1], number_of_page);
                    //cout<<page_readed<<endl;//==========================================
                    if(fullRAM == false){
                        curr_page.frame=put_in_RAM(page_readed, number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    else{
                        sending_to_SWAP();
                        curr_page.frame=put_in_RAM(page_readed,number_of_page,process_id)-1;
                        curr_page.V=1;
                    }
                    at_RAM=(this->page_size*curr_page.frame)+remainder;
                    main_memory[at_RAM] = value;//writing the new char in the RAM
                    curr_page.D = 1;
                    curr_process_page_table[number_of_page]=curr_page;
                    this->page_table[process_id-1]=curr_process_page_table;
                    delete [] page_readed;
                    return ;
                }
            }
            else{//THE PAGE IS DIRTY D=1, PERMISSION P=1, PAGE NOT VALID (NOT IN RAM) V=0
                page_readed= read_page_from_SWAP(this->swapfile_fd,curr_page.swap_index);
                sending_to_SWAP();
                curr_page.frame=put_in_RAM(page_readed,number_of_page,process_id)-1;
                curr_page.V=1;
                curr_page.swap_index = -1;
                at_RAM=(this->page_size*curr_page.frame)+remainder;
                main_memory[at_RAM]=value;
                curr_process_page_table[number_of_page]=curr_page;
                this->page_table[process_id-1]=curr_process_page_table;
                delete [] page_readed;
                return;
            }
        }
    }
    else{//THE PAGE IS VALID V=1, SO WE WRITE DIRECTLY TO THE RAM
        if(curr_page.P == 0){//THE PAGE IS VALID V=1 BUT WITHOUT PERMISSIONS P=0
            perror("You cannot overwrite the text area (Seg Fault)\n");
            return;
        }
        at_RAM=(this->page_size*curr_page.frame)+remainder;
        main_memory[at_RAM]=value;
        curr_page.D = 1;
        curr_process_page_table[number_of_page]=curr_page;
        this->page_table[process_id-1]=curr_process_page_table;
        return;
    }
}

void sim_mem:: print_memory(){

    int i;
    printf("\n Physical memory\n");
    for(i = 0; i < MEMORY_SIZE; i++) {
        printf("[%c]\n", main_memory[i]);
    }
}

void sim_mem:: print_swap(){//PRINTS THE FILE SWAP
    char* str =(char*) malloc(this->page_size *sizeof(char));
    int i;
    printf("\n Swap memory\n");
    lseek(swapfile_fd, 0, SEEK_SET); // go to the start of the file
    while(read(swapfile_fd, str, this->page_size) == this->page_size) {
        for(i = 0; i < page_size; i++) {
            printf("%d - [%c]\t", i, str[i]);
        }
        printf("\n");
    }
    delete [] str;
}

void sim_mem:: print_page_table(){//PRINTS THE PAGE TABLE FROM THE PROCESSES
    int i;
    for (int j = 0; j < num_of_proc; j++) {
        printf("\n page table of process: %d \n", j);
        printf("Valid\t Dirty\t\t Permission \t Frame\t\t Swap index\n");
        for(i = 0; i < num_of_pages; i++) {
            printf("[%d]\t\t\t[%d]\t\t\t[%d]\t\t\t[%d]\t\t\t[%d]\n",
                   page_table[j][i].V,
                   page_table[j][i].D,
                   page_table[j][i].P,
                   page_table[j][i].frame ,
                   page_table[j][i].swap_index);
        }
    }
}


