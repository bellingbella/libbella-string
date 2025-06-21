#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <libstring.h> 
/*
libstring.h:
        #define MAX_STRING_IN_NODE 4
        typedef struct {
            void* start_node;
            void* last_node;

            //properties
            size_t properties_length;
            size_t properties_notOptimized_length;
            int properties_nodeNum;
        } string; //this shi is root


        typedef struct 
        {
            char s[MAX_STRING_IN_NODE];
            void* root_node;
            void* next_node;
            void* prev_node;
            size_t number_of_lastNull; 
        } strnode;

\e

*/

string* create_string() {
    string *first_node = (string*)malloc(sizeof(string));
    if (first_node == NULL) {
        return NULL;
    }

    memset(first_node, 0, sizeof(string)); //first node is always null
    return first_node; 
}

void perNode_addString(string* t, char str[MAX_STRING_IN_NODE], size_t limit) {
    if (limit > MAX_STRING_IN_NODE) return;

    strnode* ptr = (strnode*)malloc(sizeof(strnode));
    if (ptr == NULL) return;
    
    memset(ptr, 0, sizeof(strnode));
    ptr->root_node = t;

    

    for (int i = 0;i < limit;i++) {
        ptr->s[i] = str[i];
    }

    if (t->last_node == NULL) { //if ts have not been initialized yet 
        t->last_node = ptr; 
        t->start_node = ptr;
    } 
    else {
        strnode* prev_node;
        prev_node = t->last_node;
        t->last_node = ptr;

        prev_node->next_node = ptr;
        ptr->prev_node = prev_node;
    }

    size_t nused = MAX_STRING_IN_NODE - limit;
    ptr->number_of_lastNull= nused;
    t->properties_length += limit;
    t->properties_nodeNum++;

}



void notOptimized_addString(string* t, char *str, size_t len) {
    //this function is not optmized yet.
    size_t number_of_nodes = len / MAX_STRING_IN_NODE;
    size_t has_remain = len % MAX_STRING_IN_NODE != 0;
    size_t total_nodes = number_of_nodes + has_remain;

    for (int i = 0;i < total_nodes;i++) {
        size_t limit = 0;
        if (i == (total_nodes - 1)) {
            limit = len - i * MAX_STRING_IN_NODE;

        }
        else {
            limit = MAX_STRING_IN_NODE;
        }

        perNode_addString(t, str + i * MAX_STRING_IN_NODE, limit);
    }
}

char* toStaticString(string* t) {
    char* static_ptr = (char*)malloc(sizeof(char)*(t->properties_length) + 1);
    if (static_ptr == NULL) {
        return NULL; 
    }

    strnode *current_node;
    current_node = t->start_node;

    size_t str_count = 0;
    for (int i = 0;i < t->properties_nodeNum;i++) {
        for (int j = 0;j < ( MAX_STRING_IN_NODE -  current_node->number_of_lastNull) ;j++) {
            static_ptr[str_count] = current_node->s[j];
            str_count++;
        }
        current_node = current_node->next_node;
    }
    static_ptr[str_count] = '\0';
    return  static_ptr;
}

void destroyString(string* t) {
    strnode *current_node;
    current_node = t->start_node;


    for (int i = 0;i < t->properties_nodeNum;i++) {
        void* next_ptr;
        next_ptr = current_node->next_node;
        free(current_node);
        current_node = next_ptr;
    }
    free(t);
}