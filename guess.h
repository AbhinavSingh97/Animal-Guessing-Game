int main(void);
/*
* Function builds decision tree by creating the head node and either invoking
* preorder_build if a database file exists or invoking new_tree if a database
* file does not exist. 
*/
struct Element * build_tree();
/*
* Extend_tree simply traverses the tree accordingly to user input
* and then proceeds to questions weather or not the program made a correct guess.
* If guess is correct the functionwill exit with a winning message. If the guess was 
* incorrect the function will prompt for user input as to the correct answer and add
* it to the tree
*/
struct Element * extend_tree(struct Element * head);
/*
* Creates a new database and places the first animal inside the database
*/
struct Element * new_tree(struct Element *head);
/*
* The function will traverse through the tree and write the information to the database
* file with a preorder traversal.
*/
void print_to_database(struct Element * headNode,FILE * fpr);
/*
* Using a preorder traversal the function will go through the database file and 
* build the decision tree from the avaiable nodes.
*/
struct Element * preorder_build(struct Element * headN, FILE * fptr, int count);
/*
* This function gets the file to be passed when writing to the database
*/
void get_file(struct Element * headNode);
/*
* Will free all the nodes and their corresponding data after the program has finished
*/
void free_the_tree(struct Element * head);
/*
* Program checks the tree to see if the file has not become corrupted, for example a 
* line being deleted.
*/
int check_the_tree(struct Element * root, int nodeCount);
/*
* Function to read a line up to the newline character given a file pointed
*/
char * readline(FILE *fp);
/*
* Function to return the total amount of nodes in the tree
*/
int get_node_count(FILE * inFile);
