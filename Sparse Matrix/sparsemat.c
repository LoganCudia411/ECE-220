#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
//This program takes a sparse matrix and stores its non-zero entries inside of a linked list. Each node in
//the list is a tuple which holds the row , col, and value of the non-zero cell within the sparse matrix
//This method is efficient for storing larger matrices with high amount of zero entries. This program 
//allocates the memory needed to create the linked list as well as each tuple inside. We get specific information such as the dimension
//(x,y) coordinates and the value that corresponds to that location. Set_tuple does most of the work to organize the linked list so that it is
//sorted while also rejecting 0 value locations, replaceing dubplicate locations with the newest value, and inserting the node in the middle, head or tail. 
//Lastly, this program also does matrix addition to print a list of the summated products between 2 matrices. 




sp_tuples * load_tuples(char* input_file)
{
    FILE *file = NULL; 
    file = fopen(input_file, "r");
    //alocating memory for the tuple struct
    sp_tuples * tup_ptr = (sp_tuples*)malloc(sizeof(sp_tuples)); 
    int rows, cols; 
    fscanf(file, "%d %d\n", &rows, &cols);
    tup_ptr->m = rows; 
    tup_ptr->n = cols; 
    //so far our linked list is empty with 0 non-zero entries
    tup_ptr->nz = 0; 
    tup_ptr->tuples_head = NULL; 

    //transfer the data into our struct now using the set_tuples function 
    int x, y;
    double value; 
    while( fscanf(file, "%d %d %lf\n", &x, &y, &value) != EOF){ //keep going until we reach the end of the file 
        set_tuples(tup_ptr, x, y, value);
    }
    
    fclose(file);
    return tup_ptr;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    //set cur_tup to the head of the linked list to evaluate the first node
    sp_tuples_node * cur_tup = mat_t->tuples_head;
    while(cur_tup!=NULL){ //traverse the linked list until the end
        if(cur_tup->row == row && cur_tup->col ==col){//if current node is lcoated, we return the value 
            return cur_tup->value;
        }
        else{ //otherwise increment to the next node and evaluate
            cur_tup = cur_tup->next;
        }
    }
    //the case for if we didnt find the node
    return 0;
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    
    //conditional for when we add the first node in the empty list
    if(mat_t->tuples_head==NULL && value!=0){
        sp_tuples_node *tup_ptr = malloc(sizeof(sp_tuples_node)); //allocating memory for first node
        tup_ptr->row = row; /* inserting current row, col, and value in to node*/
        tup_ptr->col = col; 
        tup_ptr->value = value; 
        mat_t->nz++; //increment nonzero elememnt counter 
        tup_ptr->next=NULL; //next node is null since we only have 1 item in the lsit 
        mat_t->tuples_head=tup_ptr; // establish our list's head 
        return;
    }


    /*DELETING NODES*/
    //when value ==0 we need to delete 
    if (value==0){
    sp_tuples_node*current=mat_t->tuples_head; 
    sp_tuples_node * prev; 

        //case 1: list is empty (head is NULL)
        if(current==NULL){
        return; 
        }

        while(current!=NULL){
    //case 2A: we find the value at the head node, we need to reassign the head node
    //then we free the node and decrement the nz counter
    if(current->row == row && current->col == col&&prev==NULL){
        mat_t->tuples_head = current->next; //reassign the head to the next item in list 
         //free the previous head node
        free(current); 
        mat_t->nz--; //decrement NZ counter
        return; 
    }
    //case 2B : the node we need to delete is in the middle of the node
    if(current->row == row && current->col == col){
        prev->next = current->next; //before we free the current node we link the previous node and the next node to bride the 
        //gap in between 
        free(current); 
         mat_t->nz--; 
        return; 
    }
    //if we do not satisfy any of the conditions, we traverse the list
    prev = current; 
    current = current->next; 
    }
    }

    /*UPDATING A NODE*/
    if(value!=0){
        sp_tuples_node* cur = mat_t->tuples_head; 
            while(cur!=NULL){ //loop to iterate search for duplicate value for the entire list
                if(cur->row==row&&cur->col==col){ //if we find inputted location in the list, we replace old value
                    cur-> value = value;
                    return; 
                }
                cur=cur->next;
            }
        }

    /*INSERTING A NODE*/
    if(value!=0){
        sp_tuples_node * current = mat_t->tuples_head;
        sp_tuples_node* prev = NULL; 
        sp_tuples_node* insert = malloc(sizeof(sp_tuples_node)); 
        
        insert->row = row; 
        insert->col = col; 
        insert->value = value; 
        insert->next = NULL;
        
        //traverse the list until we reach the position where the node needs to be placed
        while(current!=NULL){
        int insert_idx = (insert->row)*(mat_t->n) + (insert->col);
        int cur_idx = (current->row)*(mat_t->n) + (current->col);
          

            //new insert node is less than head and therefore the new head
            if((cur_idx>insert_idx) && (prev == NULL)){
                insert->next = current; 
                mat_t->tuples_head = insert; 
                mat_t->nz++;
                return;
            }

            //if we are at the tail, we add the node and make it the new tail
            if((current->next ==NULL) && (cur_idx<insert_idx)){
                insert->next = NULL; 
                current->next = insert; 
                mat_t->nz++; 
                return; 
            }
            //if we need to place the insert in the middle of the list
            if((insert_idx>cur_idx) && (insert_idx<((current->next->row)*(mat_t->n) + (current->next->col)))){ 
                insert->next = current->next; 
                current->next = insert; 
                mat_t->nz++;
                return; 
            }
            //if we see an entry already in we replace it with the new value 
            if(cur_idx == insert_idx){
                current->value = insert->value; 
                mat_t->nz++; 
                return; 
            }
            prev = current; 
            current = current->next;
        }
        return;
    }
    }
    

//writes the data in the sparse matrix to a new text file
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    //file open to write into our output file
    FILE * file = NULL; 
    file = fopen(file_name, "w");
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
    sp_tuples_node *cur_node = mat_t->tuples_head;
    //write data until we reach tail node
    while(cur_node != NULL){
        fprintf(file, "%d %d %lf\n", cur_node->row, cur_node->col, cur_node->value);
        cur_node = cur_node->next;
    }
    fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //case for if A + B is impossible
    if(matB->m!=matA->m || matB->n!=matA->n){
        return NULL; 
    }
    sp_tuples *sum_mat= malloc(sizeof(sp_tuples)); //allocating memory for the sum matrix
    sum_mat->m = matA->m;
    sum_mat->n = matA->n;
    sum_mat->nz = 0;
    sum_mat->tuples_head =NULL;
    
    //head node for both A and B 
    sp_tuples_node * nodeA = matA->tuples_head;
    sp_tuples_node * nodeB = matB->tuples_head;

    //set up sum matrix with A's values
    while(nodeA !=NULL){
        set_tuples(sum_mat, nodeA->row, nodeA->col, nodeA->value);
        nodeA = nodeA->next;
    }

    //now adding A with B and storing it in sum_mat
    while(nodeB != NULL){
        double cvalue= gv_tuples(sum_mat, nodeB->row, nodeB->col);
        set_tuples(sum_mat, nodeB->row, nodeB->col, nodeB->value+cvalue);
        nodeB = nodeB->next; 
    }

	return sum_mat;
}



/*sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return 0;

}*/
	
void destroy_tuples(sp_tuples * mat_t){
    //Step 1. free the individual nodes 
    //Step 2. free the actual matix
    sp_tuples_node * node = mat_t->tuples_head;
    while(node!=NULL){
        sp_tuples_node*temp = node->next; 
        free(node);
        node = temp;
    }
    free(mat_t);
    return;
} 






