#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"

Node *List_Load_From_File(char *filename){
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL){
        return NULL;
    }
    long data;
    Node* newnode;
    Node* tail = NULL;
    Node* head = NULL;
    while(fread(&data, sizeof(long), 1, fp)){
        newnode = (Node *)malloc(sizeof(Node));
        if(newnode == NULL){
            fclose(fp);
            return NULL;
        }
        newnode->next = NULL;
        newnode->value = data;
        if(head != NULL){
            tail->next = newnode;
            newnode->next = NULL;
        }
        else{
            head = newnode;
            newnode->next = NULL;
        }
        tail = newnode;
    }
    fclose(fp);

    return head;
}

int List_Save_To_File(char *filename, Node *list){
    FILE *fp;
    if((fp = fopen(filename, "wb")) == NULL){
        return EXIT_FAILURE;
    }
    Node *current = list;
    int count = 0;
    while(current != NULL){
        fwrite(current, sizeof(long), 1, fp);
        current = current->next;
        count++;
    }
    fclose(fp);

    return count;
}

static Node *Bubble_Sort(Node *start, long *comparison_count, int gap, int last_swap){
    Node *currentNodeA = start; 
    Node *currentNodeB = start;
    Node *previousNodeA = NULL;
    Node *previousNodeB = NULL;
    
    int gapCount = gap;
    while (gapCount--)
    {
        previousNodeB = currentNodeB;
        currentNodeB = currentNodeB->next;
    }

    int isSorted = 0;
    while (!isSorted)
    {
        isSorted = 1;
        int lastElementIndex = last_swap - 1;
        for (int i=gap; i<=lastElementIndex; i++)
        {
            int hasSwapped = 0;
            *comparison_count += 1;
            if (currentNodeA->value > currentNodeB->value)
            {
                if (previousNodeA != NULL)
                    previousNodeA->next = currentNodeB;
                else 
                    start = currentNodeB;
                if (previousNodeB != NULL)
                    previousNodeB->next = currentNodeA;
                else  
                    start = currentNodeA; 

                Node* tempNode = currentNodeB->next;
                currentNodeB->next = currentNodeA->next;
                currentNodeA->next = tempNode;
                last_swap = i;
                hasSwapped = 1;
            }

            if (hasSwapped)
            {
                previousNodeA = currentNodeB;
                Node *tempNode = currentNodeA;
                currentNodeA = currentNodeB->next;
                previousNodeB = tempNode;
                currentNodeB = tempNode->next;
            }
            else
            {
                previousNodeA = currentNodeA;
                currentNodeA = currentNodeA->next;
                previousNodeB = currentNodeB;
                currentNodeB = currentNodeB->next;
            }
        }
    }

    return start;
}


Node *List_Shellsort(Node *list, long *n_comp){
    long *seq;
    int seq_size;
    Node *temp;
    temp = list;
    int count = 0;
    while(temp != NULL){
        temp = temp->next;
        count++;
    }
    seq = Generate_2p3q_Seq(count, &seq_size);
        Node *head = list;

    for (int x=seq_size-1; x>=0; x--)
    {
        int last_swap = count;
        int k = (int)seq[x];
        head = Bubble_Sort(head, n_comp, k, last_swap);
    }

    free(seq);

    return head;
}
