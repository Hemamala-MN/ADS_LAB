
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
struct Node* head=NULL;
struct Node
{
    int data;
    struct Node* npx;
};

struct Node* XOR(struct Node* a, struct Node* b)
{
    return (struct Node*)((uintptr_t)(a)^ (uintptr_t)(b));
}
void insert(struct Node** head,int data)
{
    struct Node* newnode= (struct Node*)malloc(sizeof(struct Node));
    newnode->data=data;
    newnode->npx = *head;
    if(*head!=NULL)
    {
        struct Node* next = XOR((*head)->npx, NULL);
        (*head)->npx = XOR(newnode,(*head)->npx);
    }

    *head= newnode;

}

void printList(struct Node** head)
{

    struct Node* curr = *head;


    struct Node* prev = NULL;


    struct Node* next;


    while (curr != NULL) {


        printf("%d ", curr->data);


        next = XOR(prev, curr->npx);


        prev = curr;


        curr = next;
    }
}
struct Node* delEnd(struct Node** head)
{

    if (*head == NULL)
        printf("List is empty");
    else {


        struct Node* curr = *head;


        struct Node* prev = NULL;


        struct Node* next;


        while (XOR(curr->npx, prev) != NULL) {


            next = XOR(prev, curr->npx);


            prev = curr;


            curr = next;
        }

        if (prev != NULL)
            prev->npx = XOR(XOR(prev->npx, curr), NULL);


        else
            *head = NULL;


        free(curr);
    }


    return *head;
}
int main()
{
    int n,item;
    printf("Enter the number of elements\n");
    scanf("%d",&n);
    printf("Elements to insert\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&item);
        insert(&head,item);
    }
    printf("Before deletion\n");
    printList(&head);
    delEnd(&head);
    printf("\n after deletion\n");
    printList(&head);

}
