/* 
* Abhinav Singh
* January 23, 2017
*/

/*=========================== ANIMAL GUESSING GAME ==================================
* This game will guess the animal you're thinking of based off a series of questions
* The program will implement a decision tree in order to do the guessing. The program
* will read from a database, if the database isn't there, it will create one. 

* If the program guess right it will end with a simple message. If the program is 
* wrong the user will be prompted for the correct animal and a way to distinguish 
* their animal in the form of a y/n question. That information will then be added to 
* the database for the next time, essentially allowing the game to get "smarter"
* the more it is played. 
*====================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Element
{
   char * data;
   struct Element* left;
   struct Element* right;
};
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
struct Element * new_tree(struct Element *head);
/*
* Creates a new database and places the first animal inside the database
*/
struct Element * extend_tree(struct Element * head);
/*
* The function will traverse through the tree and write the information to the database
* file with a preorder traversal.
*/
void print_to_database(struct Element * headNode,FILE * fpr);
/*
* Using a preorder traversal the function will go through the database file and 
* build the decision tree from the avaiable nodes.
*/
struct Element * preorder_build(struct Element * headN, FILE * fptr,int count);
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
int check_the_tree(int nodeCount);
/*
* Function to read a line up to the newline character given a file pointed
*/
char * readline(FILE *fp);
/*
* Function to return the total amount of nodes in the tree
*/
int get_node_count(FILE * inFile);

int main(void)
{

   struct Element * head;
   struct Element * tempNode;
   FILE * inFile;
   int counter = 0;

   head = build_tree();
   inFile = fopen("qa.db","r");
   counter = get_node_count(inFile);
   check_the_tree(counter);
   fclose(inFile);
   tempNode = extend_tree(head);
   get_file(tempNode);
   free_the_tree(head);

   return 0;
}
struct Element * build_tree()
{
   FILE *fp;
   struct Element *head;

   head = NULL;
   fp= fopen("qa.db","r");
   if(!fp)
   {
      head = malloc(sizeof(struct Element));
      head = new_tree(head);
      free_the_tree(head);
      exit(0);
   }
   else
   {
      head = preorder_build(head,fp,0);
   }

   fclose(fp);
   return head;

}
struct Element * extend_tree(struct Element * head)
{
   char * answer;
   char * temp_animal;
   char * temp_question;

   struct Element *current;
   struct Element *temp;

   temp = head;
   current = head;

   while((current->left)!= NULL && (current->right)!= NULL)
   {
      do
      {
         printf("%s\n",current->data);
         answer = readline(stdin);
      }while(answer == NULL);
      if(answer[0] == 'y' || answer[0] == 'Y')
      {
         current = current->left;
         temp = current;
      }
      else
      {
         current = current->right;
         temp = current;
      }
      free(answer);
   }
   printf("Is it %s\n", temp->data);
   answer = readline(stdin);
   if(answer[0] == 'y' || answer[0] == 'Y')
   {
      printf("\n");
      printf("My, am I clever.   :)\n");
      printf("Thanks for playing.\n");
      free(answer);
   }
   else
   {
      free(answer);
      do
      {
         printf("How disappointing\n");
         printf("What is it (with article)?\n");
         temp_animal = readline(stdin);
      }while(temp_animal == NULL);
      do
         {
         printf("What is a yes/no question that will distinguish %s from %s\n", temp_animal, temp->data);
         printf("?  ");
         temp_question = readline(stdin);
         }while(temp_question == NULL);

      do
      {
         printf("What is the answer to the question for %s?\n",temp_animal);
         answer = readline(stdin);
      }while(answer == NULL);
      
      printf("\n");
      printf("I'll get it next time, I'm sure.\n");
      printf("Thanks for playing.\n");

      if(answer[0] == 'y' || answer[0] == 'Y')
      {
         free(answer);
         current->left = malloc(sizeof(struct Element));
         current = current->left;
         current->data = malloc(sizeof(char)*(strlen(temp_animal)+1));
         temp->left = current;

         strcpy(current->data, temp_animal);
         current->left = NULL;
         current->right = NULL;
         free(temp_animal);

         current = temp;
         current->right = malloc(sizeof(struct Element));
         current = current->right;
         current->data = malloc(sizeof(char)*(strlen(temp->data)+1));
         temp->right = current;
   
         strcpy(current->data, temp->data);
         current->left = NULL;
         current->right = NULL;

         temp->data = realloc(temp->data,sizeof(char)*(strlen(temp_question)+1));
         strcpy(temp->data, temp_question);
         free(temp_question);
      }
      else
      {
         free(answer);
         current->right = malloc(sizeof(struct Element));
         current = current->right;
         current->data = malloc(sizeof(char)*(strlen(temp_animal)+1));
         temp->right = current;
         
         strcpy(current->data, temp_animal);
         current->left = NULL;
         current->right = NULL;
         free(temp_animal);

         current = temp;
         current->left = malloc(sizeof(struct Element));
         current = current->left;
         current->data = malloc(sizeof(char)*(strlen(temp->data)+1));
         temp->left = current;
         
         strcpy(current->data, temp->data);
         current->left = NULL;
         current->right = NULL;


         temp->data = realloc(temp->data,sizeof(char)*(strlen(temp_question)+1));
         strcpy(temp->data, temp_question);
         free(temp_question);
      }
   }
   return head;
}

void get_file(struct Element * headNode)
{
   FILE * fpr = fopen("qa.db","w");
   print_to_database(headNode,fpr);
   fclose(fpr);
   return; 
}
void print_to_database(struct Element * headNode,FILE * fpr)
{
   if(headNode == NULL)
   {
      fprintf(fpr,"\n");
      return;
   }
   if(headNode->data == NULL)
   {
      fprintf(fpr, "\n");
      return;
   }
   fprintf(fpr,"%s\n",headNode->data);
   print_to_database(headNode->left,fpr);
   print_to_database(headNode->right,fpr);
}
struct Element * new_tree(struct Element *head)
{
   FILE * fp;
   printf("Unable to read qa.db.   Starting fresh.\n\n");
   fp = fopen("qa.db","w");
   printf("What is it (with article) ?\n");
   head->data = readline(stdin);
   fprintf(fp,"%s\n",head->data);
   fclose(fp);
   return head;
}
struct Element * preorder_build(struct Element * headN, FILE * fptr, int count)
{


   char * temp_info;
   temp_info = readline(fptr);
   if(feof(fptr)|| temp_info == NULL)
   {
      free(temp_info);
      return NULL;
   }
   headN = malloc(sizeof(struct Element));
   headN->data = malloc(sizeof(char)*(strlen(temp_info)+1));
   strcpy(headN->data,temp_info);
   
   free(temp_info);
   headN->left = preorder_build(headN->left,fptr,++count);
   headN->right = preorder_build(headN->right,fptr,++count); 
   return headN;
}
int check_the_tree(int count)
{
   if(count % 2 == 0)
   {
      printf("Database file may have been corrupted. Exiting now...\n");
      exit(1);
   }
   return 0;
}
int get_node_count(FILE * inFile)
{
   char * temp;
   int count = 0;
   while(!feof(inFile))
   {  
      temp = readline(inFile);
      if(temp != NULL) count++;
      free(temp);
   }
   return count;
}
void free_the_tree(struct Element * head)
{
   if(head == NULL) return;
   free_the_tree(head->left);
   free_the_tree(head->right);
   free(head->data);
   free(head);
   
}