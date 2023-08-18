Ytzhak Ariel Armoni

ex5 - OS : Physical and Logical memory .

--Description--
This program is simulator of the operation system memory management , from logical memory to physical memory and use swap if the memory is full .
this program contains char`s and numbers that we use them as a memory address . The program use 2 processes, in other words, two executable files that contain
the data in format of chars (every char means one address) so in the constructor we decide if we want to work with one file or two files (processes)
 
 --Functions--
    char load(int address) - get address and load it to the main memory , this function know how to deal with all 	    the memory cases ( Valid or not, Dirty or not, Permmission 0\1) .

    void store(int address, char value) - get address and char , bring the address to main memory , and then put the char value on the address the user put . 
    if the address is invalid , this method will output error . 

    void print_memory() - print the main memory .

    void print_swap() - print the swap memory .

    void print_page_table() - print the page table .

FUNCTIONS SOS (THESE FUNCTIONS HELP US TO HAVE A MODULAR CODE)------------------------------------------------------

void struct_Page_table_initialization(page_descriptor* page_tab, int page_table_size, int num_pages_txt){
//INITIALIZATION PAGE TABLE 

void initializer_swap(int fd_file, int size_file){//initialize the swap file with zeros

char* sim_mem::read_page_from_FILE(int fd_, int num_of_page){//READ A PAGE FROM THE EXEC FILE (FROM DATA/TEXT ZONE)

char* sim_mem::read_page_from_SWAP(int fd_, int index_swap){//READ A PAGE FROM THE SWAP FILE ACCORD TO THE PAGE INDEX IN THE SWAP

int sim_mem::put_in_RAM(char* page_to_load, int num_page, int num_process){//gets as param the page to be loaded and write it in the RAM, returns the number of the frame

char sim_mem::address_zone(char addr){//CALCULATES THE ADDRESS AREA BELONGS AT THE PROCESS

int sim_mem::seek_free_space_in_SWAP(){//SEEK FREE SPACE IN THE SWAP AND RETURNS THE INDEX

void sim_mem::write_to_SWAP(char* page, int fd_, int pagesize, int ind_in_SWAP){//WRITES A STRING TO THE FILE SWAP

void sim_mem::sending_to_SWAP(){//IF THE MEMORY IS FULL WE OVERWRITE THE DATA

How to compile the ṕrogram:---------------------------------------------------------------- 
when you access to the main program push the hammer button,
if the program shows:>>

g++ main.cpp sim_mem.cpp -o ex5

How to run the program:-------------------------------------------------------------

Press shift+f10 and then will appears an screen so you can start.

and via the terminal: ./ex5 

Output expected :(The input must to do it in the terminal).-------------------------------------

"/home/student/Desktop/marajot afala shana dalet/Ex5/cmake-build-debug/Ex5"

 page table of process: 0 
Valid	 Dirty		 Permission 	 Frame		 Swap index
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]

 page table of process: 1 
Valid	 Dirty		 Permission 	 Frame		 Swap index
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]

 Physical memory
[B]
[B]
[B]
[B]
[B]
[C]
[C]
[C]
[C]
[C]
[X]
[0]
[0]
[0]
[0]
[Q]
[Q]
[Q]
[Q]
[Q]
[Y]
[0]
[0]
[0]
[0]
[R]
[R]
[R]
[R]
[R]
[K]
[K]
[K]
[K]
[K]
[D]
[D]
[D]
[D]
[D]
[U]
[U]
[U]
[U]
[U]
[0]
[0]
[0]
[0]
[0]
[.]
[.]
[.]
[.]
[.]
[W]
[W]
[W]
[W]
[V]
[Z]
[Z]
[Z]
[Z]
[Z]
[0]
[0]
[0]
[0]
[W]
[0]
[W]
[0]
[0]
[0]
[0]
[0]
[0]
[0]
[W]
[G]
[G]
[G]
[G]
[G]
[V]
[V]
[V]
[V]
[V]
[I]
[I]
[I]
[I]
[Y]
[X]
[X]
[X]
[X]
[X]
[-]
[W]
[-]
[-]
[-]
[F]
[F]
[F]
[F]
[W]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]
[ ]

 page table of process: 0 
Valid	 Dirty		 Permission 	 Frame		 Swap index
[0]			[0]			[0]			[-1]			[-1]
[1]			[0]			[0]			[0]			[-1]
[1]			[0]			[0]			[1]			[-1]
[1]			[0]			[0]			[7]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[1]			[1]			[1]			[21]			[-1]
[1]			[0]			[1]			[16]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[18]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[0]			[1]			[6]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[13]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[15]			[-1]
[1]			[1]			[1]			[14]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[2]			[-1]

 page table of process: 1 
Valid	 Dirty		 Permission 	 Frame		 Swap index
[0]			[0]			[0]			[-1]			[-1]
[1]			[0]			[0]			[3]			[-1]
[1]			[0]			[0]			[5]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[0]			[0]			[0]			[-1]			[-1]
[1]			[0]			[1]			[8]			[-1]
[1]			[0]			[1]			[17]			[-1]
[1]			[1]			[1]			[11]			[-1]
[1]			[0]			[1]			[19]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[0]			[1]			[12]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[20]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[0]			[1]			[10]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[0]			[1]			[9]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[1]			[1]			[1]			[4]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
[0]			[0]			[1]			[-1]			[-1]
You cannot overwrite the text area (Seg Fault)
: Success
You cannot overwrite the text area (Seg Fault)
: Success
THE ADDRESS REQUEST IS OUT OF BOUNDS ACCORDING TO THE PROCESS, TRY AN SMALLER ADDRESS
: Success
The memory it wasn't allocated yet,
please allocate memory with store()function
: Success
The memory it wasn't allocated yet,
please allocate memory with store()function
: Success
The memory it wasn't allocated yet,
please allocate memory with store()function
: Success
The memory it wasn't allocated yet,
please allocate memory with store()function
: Success
THE ADDRESS REQUEST IS OUT OF BOUNDS ACCORDING TO THE PROCESS, TRY AN SMALLER ADDRESS
: Success
[0]			[0]			[1]			[-1]			[-1]

 Swap memory
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

Process finished with exit code 0


