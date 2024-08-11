#include <stdio.h>
#include <stdlib.h>
typedef struct Node node_t;

long int data[] = {4, 8, 15, 16, 23, 42};
size_t data_length = sizeof(data) / sizeof(data[0]);

void print_int(node_t *elem);
node_t *add_element(long int value, node_t *next);
void map(node_t *elem, void (*func)(node_t *elem));
long int odd(node_t *elem);
node_t *filter(node_t *head, long int (*f)(node_t *elem));

struct Node
{
    long int value;
    node_t *next;
};

node_t *add_element(long int value, node_t *next)
{
    node_t *elem = (node_t *)malloc(sizeof(node_t));
    if (!elem)
    {
        return NULL;
    }
    elem->value = value;
    elem->next = next;
    return elem;
}
long int odd(node_t *elem)
{
    return elem->value & 1;
}

void map(node_t *head, void (*f)(node_t *elem))
{
    if (!head)
        return;
    f(head);
    map(head->next, f);
}

node_t *filter(node_t *head, long int (*f)(node_t *elem))
{
    node_t *cur = head;
    while (!f(head))
    {
        if (head->next)
        {
            cur = head;
            head = head->next;
            free(cur);
        }
    }

    node_t *new_head = head;

    if (new_head)
    {
        node_t *prev = new_head;
        cur = NULL;
        if (new_head->next == NULL)
            return new_head;

        cur = prev->next;
        while (cur)
        {
            if (!f(cur))
            {
                if (cur->next)
                {
                    prev->next = cur->next;
                    free(cur);
                    cur = prev;
                }
                else
                {
                    free(cur);
                    prev->next = NULL;
                    return new_head;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }

    return new_head;
}

void print_int(node_t *node)
{
    printf("%ld ", node->value);
}

int main()
{
    node_t *head = add_element(data[0], NULL);
    node_t *head_tmp = head;

    for (size_t i = 1; i < data_length; i++)
    {
        node_t *next = add_element(data[i], NULL);
        head_tmp->next = next;
        head_tmp = head_tmp->next;
    }

    map(head, print_int);
    printf("\n");
    node_t *new_head = filter(head, odd);
    map(new_head, print_int);
    printf("\n");
    // freeing the rest

    node_t *tmp = NULL; 
    while (new_head)
    {   tmp=new_head;
        new_head=new_head->next;
        free(tmp);
    }
    

    return 0;
}
