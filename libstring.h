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

string* create_string();
void perNode_addString(string* t, char str[MAX_STRING_IN_NODE], size_t limit);
void notOptimized_addString(string* t, char *str, size_t len);
char* toStaticString(string* t);
void destroyString(string* t);




/*

void addString(string* str_t, const char* input_str, size_t len) {
    size_t number_of_nodes = len / MAX_STRING_IN_NODE;
    size_t has_remain = len % MAX_STRING_IN_NODE != 0;
    size_t total_nodes = number_of_nodes + has_remain;


   
    
*/