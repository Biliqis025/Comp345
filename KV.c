#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Build a key store program 


//toimplemet a Key, value store

 typedef struct KV { 
    int key;
    char* value;
    struct KV* next;
} KV;

KV*head = NULL;

// Insert key values and pairs 
//./kv p,10,remzi
// ./kv p,20,andrea p,40,someotherperson

void put (int key, char* value) {

    KV* current = head;


    while (current != NULL) {
        if (current->key == key) {
            free(current->value);  //  to free the old value
            current->value = malloc(strlen(value) + 1);
            if (!current->value) {
                printf("malloc for value fail\n");
                return;
            }
            strcpy(current->value, value);
            printf("Updated: Key = %d, Value = %s\n", key, value);
            return;
        }
        current = current->next;
    }

    KV* n =malloc(sizeof( KV));
    if (!n) {
        printf("malloc failed\n");
        return ;
    } 
// add a condition 
    // modifying put fuction into the linked list ,existing keys and non existing keys 
    // allocates new memory ffor KV annd everytime put() is called a new key value is stored in memory 
     n->key = key;

     n->value = malloc(strlen(value) + 1);  
     ///condition
     if (!n->value){
        printf("malloc for value failed\n");
        free(n);  // free the allocated node before return 
        return;
        
     }
    strcpy(n->value, value);
    n-> next = NULL;
    n-> next = head;   //next is to null for now 
    head = n;
    printf("Stored: Key = %d, Value = %s\n",key, value);
}

//Implemet the get function
char* get(int key){
    KV*current =head;  // starts from head and loops through the linked list 
    while( current != NULL) {
        if ( current -> key == key){
            return current -> value;
        }
        current = current -> next;
    }
    return NULL;  // returns null if key is not found when it reacheds the end 
}

// to parse multiple command 
void delete_key(int key);
void parse_command(char *input) {
    char *cmd;

    while ((cmd = strsep(&input, " ")) != NULL) {  
        if (*cmd == '\0') continue; 

        char *command = strsep(&cmd, ",");
        if (strcmp(command, "p") == 0) {  
            char *key_str = strsep(&cmd, ",");
            char *value = strsep(&cmd, ",");

            if (key_str == NULL || value == NULL) {
                printf("Invalid put command\n");
                continue;
            }

            int key = atoi(key_str);
            put(key, value);
        } 
        else if (strcmp(command, "a") == 0) {
            char *key_str = strsep(&cmd, ",");

            if (key_str == NULL) {
                printf("Invalid get command\n");
                continue;
            }

            int key = atoi(key_str);
            char *value = get(key);

            if (value != NULL) {
                printf("Found: %s\n", value);
            } else {
                printf("Key not found\n");
            }
        } 
        else if (strcmp(command, "b") == 0) {
            char *key_str = strsep(&cmd, ",");
            if (key_str == NULL) {
                printf("Invalid delete command\n");
                continue;
            }
            int key = atoi(key_str);
            delete_key(key);
        } 
        else {
            printf("Unknown command: %s\n", command);
        }
    }
}

// to free memory 
void Free_memory(){
    KV *current = head ;
    while (current != NULL) {
        KV* temp = current;
        current = current->next;
        free(temp->value); 
        free(temp);         
    }
}

 // Implement command to delete using d,key

   void delete_key (int key) {
    if (head == NULL) {  // 
        printf("List is empty. No key to delete.\n");
        return;
    }
    KV* current = head;
    KV* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                head = current->next; 
            } else {
                prev->next = current->next;  
            }

            free(current->value);
            free(current);
            printf("Deleted key: %d\n", key);
            return;
        }
         prev = current;
        current = current->next;
    }

    printf("Key not found\n");
}
   
   int main() {
    char input[100];

    printf("hello,kvs !\n");

    while(1) {
        printf("prompt> ");
        if (fgets(input,sizeof(input),stdin) == NULL){
            break;
        }
        input[strcspn(input,"\n")] = '\0';
        parse_command(input);
            }
            Free_memory();
            return 0;
}
   
   
    //using a while loop 



//int main(){
   //printf("Hello, KV store!\n");
    //return 0;s


    // to parse on simgle command 
/*void parse_command(char*input) {
    char*command = strsep(&input, "," );
    
if(strcmp(command,"p")==0){    // strcmp to check if the command is p
    char *key_str =strsep(&input,",");
    char *value = strsep(&input,",");

    if(key_str == NULL || value == NULL){      // just incase 
        printf("Invalid put command\n");
        return;
    }

    int key =atoi(key_str);
    put(key,value);


} else if (strcmp(command,"g") == 0) {
    char *key_str =strsep(&input,",");

    if (key_str == NULL) {
        printf("Invalid get command \n");
        return;
    }
    int key = atoi(key_str);
    char* value = get(key);

    if (value != NULL) {
            printf("Found: %s\n", value);
        } else {
            printf("Key not found\n");
        }
    } 
    else if (strcmp(command, "d") == 0) {  // "delete" command
        char* key_str = strsep(&input, ",");
        if (key_str == NULL) {
            printf("Invalid delete command\n");
            return;
        }
        int key = atoi(key_str);
        delete_key(key);
    } 
    else {
        printf("Unknown command: %s\n", command);
    }

 } 
 */  