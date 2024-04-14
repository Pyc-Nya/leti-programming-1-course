#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 64
struct LNode {
    int id;
    char* word;
    struct LNode* next;
};

struct LHead {
    int last_id;
    int cnt;
    struct LNode* first;
    struct LNode* last;
};

typedef struct LHead head;
typedef struct LNode node;

head* make_head();

node* make_node(char* new_word, int slen);

void add_node(head* my_head, node* new_node);

node* select_id(head* my_head, int n);

void delete_node(head* my_head, node* current_node);

void clear_list(head* my_head);
int main() {
    head* ph = NULL;
    node* p = NULL;
    char my_word[MAXLEN];
    int slen, n;
    ph = make_head();
    puts("--Press \"\\q\" for terminate input--\n");
    while (strncmp(my_word, "\\q", 2) != 0) {
        printf("%s: ", "Please enter your word");
        fgets(my_word, MAXLEN, stdin);
        slen = strlen(my_word);
        my_word[slen - 1] = '\0';
        if (strncmp(my_word, "\\q", 2) != 0) {
            p = make_node(my_word, slen);
            add_node(ph, p);
            printf("%d %s\n", p->id, p->word);
        }
    }
    puts("\n--Input terminated. Your data are:--");
    p = ph->first;
    while (p != NULL) {
        printf("Address: %p, data: %d %s\n", p, p->id, p->word);
        p = p->next;
    }
    printf("Head fields: %d %d %p %p\n", ph->last_id, ph->cnt, ph->first,
           ph->last);
    printf("%s: ", "\nPlease enter your number");
    scanf("%d", &n);
    p = select_id(ph, n);
    if (p != NULL) {
        printf("Address: %p, data: %d %s\n", p, p->id, p->word);
        delete_node(ph, p);
        puts("--Data after deleting selected node --");
        p = ph->first;
        while (p != NULL) {
            printf("Address: %p, data: %d %s\n", p,

                   p->id, p->word);
            p = p->next;
        }
        printf("Head fields: %d %d %p %p\n", ph->last_id, ph->cnt, ph->first,
               ph->last);
    } else
        printf("ERROR! Element not exists!\n");
    clear_list(ph);
    return 0;
}
head* make_head() {
    head* ph = NULL;
    ph = (head*)malloc(sizeof(head));
    if (ph != NULL) {
        ph->last_id = 0;
        ph->cnt = 0;
        ph->first = NULL;
        ph->last = NULL;
    }
    return ph;
}
node* make_node(char* new_word, int slen) {
    node* new_node = NULL;
    char* someword = NULL;
    new_node = (node*)malloc(sizeof(node));
    someword = (char*)malloc((slen + 1) * sizeof(char));
    if (new_node && someword) {
        strcpy(someword, new_word);
        new_node->id = 1;
        new_node->word = someword;
        new_node->next = NULL;
    }
    return new_node;
}
void add_node(head* my_head, node* new_node) {
    node* q = NULL;
    int k;
    if (my_head && new_node) {
        q = my_head->first;
        if (q == NULL) {
            my_head->last_id = 1;
            my_head->cnt = 1;
            my_head->first = new_node;
            my_head->last = new_node;
        } else {
            k = my_head->last_id + 1;
            my_head->cnt++;
            new_node->id = k;
            new_node->next = q;
            my_head->first = new_node;
            my_head->last_id = k;
        }
    }
}
node* select_id(head* my_head, int n) {
    node* q;
    int k;
    q = my_head->first;
    k = my_head->last_id;
    if ((n > 0) && (n <= k)) {
        while (((q->id) != n) && (q != NULL)) q = q->next;
    } else
        q = NULL;
    return q;
}
void delete_node(head* my_head, node* current_node) {
    node *q, *q1;
    q = my_head->first;
    q1 = my_head->last;
    if (current_node == q) {
        my_head->first = current_node->next;
        current_node->next = NULL;
        free(current_node);
    } else {
        while (q != NULL) {
            if (q->next == current_node) {
                if (current_node == q1) my_head->last = q;
                q->next = current_node->next;
                current_node->next = NULL;
                free(current_node);
            } else
                q = q->next;
        }
    }
    my_head->cnt--;
}
void clear_list(head* my_head) {
    node *q, *q1;
    q = my_head->first;
    while (q != NULL) {
        q1 = q->next;
        free(q);
        q = q1;
    }
    free(my_head);
}
