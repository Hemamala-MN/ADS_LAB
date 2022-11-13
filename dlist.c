#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>
struct node *head=NULL;
struct node
{
    int data;
    struct node* npx;
    
};
struct node* XOR (struct node* a,struct node*b)
{
    return (struct node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}
void insert(struct node** head,int data)
{
    struct node* newnode= (struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->npx = *head;
    if(*head!=NULL)
    {
        struct node* next = XOR((*head)->npx, NULL);
        (*head)->npx = XOR(newnode,(*head)->npx);
    }
    
    *head= newnode;
        
}
void printList (struct node *head) {
    struct node *curr = head;
    struct node *prev = NULL;
    struct node *next;
 
    printf("Following are the nodes of Linked List: \n");
 
    while (curr != NULL) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
}
int main() 
{
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);
    printList(head);
    return 0;
}
