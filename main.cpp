#include <iostream>
#include "sim_mem.h"

int main() {


////////////////////////////////////////////////TESTER FOR ONE PROCESS////////////////////////////////
    char val1;
    char val2;
    char val5,val3,val4,val6,val7,val8,val9,val10,val11,val12,val13,val14,val15,val16,val17,val18,val19;
  /* sim_mem mem_sm((char*)"exec_file", (char*)"", (char*)"swap_file" ,25, 50, 25,25, 25, 5,1);

    val1 = mem_sm.load (1, 7);
    mem_sm.store(1,1,'Y');//SSSSSSSSSSS
    val2 = mem_sm.load (1, 12);
    mem_sm.store(1, 12,'X');//SSSSSSSSSS
    val3 = mem_sm.load (1, 25);
    val4 = mem_sm.load (1, 5);
    val5 = mem_sm.load (1, 17);
    val6 = mem_sm.load (1, 3);
    val7 = mem_sm.load (1, 15);
    val8 = mem_sm.load (1, 10);
    val9 = mem_sm.load (1, 13);
    mem_sm.store(1,1,'W');
    mem_sm.store(1,9,'W');
    mem_sm.store(1,19,'W');
    mem_sm.store(1,15,'W');
    val10 = mem_sm.load (1, 26);//put in the ram 0000, return 0 (BSS)
    val11 = mem_sm.load (1, 37);//MUST TO BE ERROR !!!BECAUSE THE PAGE IS NOT IN THE RAM(ZONE HEAP-STACK)
    mem_sm.store(1,38,'E');//PUT IN THE RAM 00E0
    mem_sm.print_memory();
    mem_sm.print_page_table();
    val11 = mem_sm.load (1, 37);//THIS TIME NOT RET ERROR, return 0
    mem_sm.store(1,2,'E');//MUST TO BE ERROR (TEXT ZONE NOT ALLOWED TO WRITE)!!!
    mem_sm.print_memory();
    mem_sm.print_page_table();
    mem_sm.store(1,5,'E');//MUST TO BE ERROR (TEXT ZONE NOT ALLOWED TO WRITE) !!!
    val12 = mem_sm.load (1, 5);//THIS TIME NOT RET ERROR, return B
    mem_sm.print_memory();
    mem_sm.print_page_table();
    mem_sm.store(1,14,'E');//MUST TO BE ERROR (TEXT ZONE NOT ALLOWED TO WRITE) !!!
    mem_sm.store(1,26,'E');//MUST TO BE ERROR (TEXT ZONE NOT ALLOWED TO WRITE)!!!
    mem_sm.print_memory();
    mem_sm.print_page_table();
    mem_sm.store(1,20,'P');//PUT FFFF IN RAM AND RETURN PFFF
    mem_sm.store(1,30,'P');//PUT 0000 IN RAM AND RETURN 00P0
    mem_sm.print_memory();
    mem_sm.print_page_table();
    mem_sm.store(1,10,'Q');//PUT 0000 IN RAM AND RETURN 00P0
    mem_sm.print_memory();
    mem_sm.print_page_table();
    mem_sm.print_swap();


*/



     //*************************************************************************************************88

    //////////////////////////////////////////////TESTER FOR 2 PROCESSES////////////////////////////////
    sim_mem mem_sm2((char*)"exec_file", (char*)"exec_file2",(char*)"swap_file"
                   ,25, 50, 25,25, 25, 5,2);

    mem_sm2.print_page_table();
    //////////////////////////////////////////////////////PROCESS 0 //////////////////////////
    val1 = mem_sm2.load (1, 7);
    mem_sm2.store(1,1,'Y');//SSSSSSSSSSS
    val2 = mem_sm2.load (1, 12);
    mem_sm2.store(1, 120,'X');//SSSSSSSSSS
    ////////////////////////////////////////////////PROCESS 1//////////////////////////////////////////
    val3 = mem_sm2.load (2, 7);
    mem_sm2.store(2,100,'Y');//SSSSSSSSSSS
    val4 = mem_sm2.load (2, 12);
    mem_sm2.store(2, 12,'X');//SSSSSSSSSS
    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    //mem_sm.print_memory();
    //mem_sm.print_page_table();
    //////////////////////////////////////////////////////PROCESS 0 //////////////////////////
    val5 = mem_sm2.load (2, 125);
    val6 = mem_sm2.load (1, 53);
    val7 = mem_sm2.load (1, 17);
    //////////////////////////////////////////////////////PROCESS 1 //////////////////////////
    //.print_memory();
    //mem_sm.print_page_table();
    val8 = mem_sm2.load (2, 25);
    val9 = mem_sm2.load (2, 85);
    val10 = mem_sm2.load (2, 74);
    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    //mem_sm.print_memory();
    //mem_sm.print_page_table();
    //////////////////////////////////////////////////////PROCESS 0 //////////////////////////
    mem_sm2.store(2, 39,'O');
    val12 = mem_sm2.load (1, 122);
    //////////////////////////////////////////////////////PROCESS 1 //////////////////////////
    val13 = mem_sm2.load (2, 53);
    mem_sm2.store(1,99,'W');
    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    //mem_sm.print_memory();
    //mem_sm.print_page_table();
    //////////////////////////////////////////////////////PROCESS 0 //////////////////////////
    val16 = mem_sm2.load (1, 100);
    val17 = mem_sm2.load (1, 113);
    //////////////////////////////////////////////////////PROCESS 1 //////////////////////////
    val18 = mem_sm2.load (2, 110);
    val19 = mem_sm2.load (2, 113);
    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    //mem_sm.print_memory();
    //mem_sm.print_page_table();
    //////////////////////////////////////////////////////PROCESS 0 //////////////////////////
    mem_sm2.store(1,111,'W');
    mem_sm2.store(1,109,'W');
    mem_sm2.load(1,32);
    mem_sm2.load(2,32);
    mem_sm2.load(1,40);
    mem_sm2.load(2,40);

    //////////////////////////////////////////////////////PROCESS 1 //////////////////////////
    mem_sm2.store(2,61,'W');//HASTAAAAAAAAAAAAAAAAAAA AQUI LLEGUE/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    mem_sm2.store(2,125,'Z');
    mem_sm2.store(1,44,'Y');
    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    //mem_sm.print_memory();
    //mem_sm.print_page_table();
    ///////////////////////////////////////
    mem_sm2.store(2,39,'V');
    mem_sm2.store(1,29,'W');


    //////////////////////////////////////////PRINTING/////////////////////////////////////////////////
    mem_sm2.print_memory();
    mem_sm2.print_page_table();
    mem_sm2.print_swap();
    ///////////////////////////////////////




    return 0;

}
