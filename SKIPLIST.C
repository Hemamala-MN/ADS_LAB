
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define SKIPLIST_MAX_LEVEL 6
struct snode {
    int key;
    int value;
    struct snode **forward;
};
struct skiplist {
    int level;
    int size;
    struct snode *header;
};

struct skiplist  *skiplist_init(struct skiplist *list) {
    int i;
    struct snode *header = (struct snode *) malloc(sizeof(struct snode));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (struct snode **) malloc(sizeof(struct snode*) * (SKIPLIST_MAX_LEVEL + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++)
    {
        header->forward[i] = list->header;
    }


    list->level = 1;
    list->size = 0;

    return list;
}

static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}

int skiplist_insert(struct skiplist *list, int key, int value) {
    struct snode *update[SKIPLIST_MAX_LEVEL + 1];
    struct snode *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--)
    {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];

    if (key == x->key)
    {
        x->value = value;
        return 0;
    }
    else
    {
        level = rand_level();
        if (level > list->level)
        {
            for (i = list->level + 1; i <= level; i++)
            {
                update[i] = list->header;
            }
            list->level = level;
        }

        x = (struct snode *) malloc(sizeof(struct snode));
        x->key = key;
        x->value = value;
        x->forward = (struct snode **) malloc(sizeof(struct snode*) * (level + 1));
        for (i = 1; i <= level; i++)
        {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}

struct snode *skiplist_search(struct skiplist *list, int key) {
    struct snode *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--)
    {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
    return NULL;
}

static void skiplist_node_free(struct snode *x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}

int skiplist_delete(struct skiplist *list, int key) {
    int i;
    struct snode *update[SKIPLIST_MAX_LEVEL + 1];
    struct snode *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[1] = x->forward[i];
        }
        skiplist_node_free(x);

        while (list->level > 1 && list->header->forward[list->level]
                == list->header)
            list->level--;
        return 0;
    }
    return 1;
}

static void skiplist_dump(struct skiplist *list) {
    struct snode *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}

int main() {
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 }, i;
    struct skiplist list;
    skiplist_init(&list);
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_dump(&list);

    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };

    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        struct snode *x = skiplist_search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not fuound\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    skiplist_delete(&list, 3);
    skiplist_delete(&list, 9);
    skiplist_dump(&list);

    return 0;
}
