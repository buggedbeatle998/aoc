#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#define TABLE_SIZE 1024


typedef struct {
    char *key;
    char *friends;
    int8_t friends_len;
    int64_t paths;
} hash_element;


uint16_t jenkins_hash(char *key);
void hash_item_add(hash_element *hash_table, char *key, char *friends, int8_t friends_len);
hash_element *hash_item_get(hash_element *hash_table, char *key);

int64_t find_paths(hash_element *hash_table, char *src, char *dest);


int main(int argc, char **argv) {
    FILE *fptr = fopen(strcat(argv[1], ".txt"), "r");
    uint64_t total = 0;
    hash_element *hash_table = calloc(TABLE_SIZE, sizeof(hash_element));
    char *node = malloc(sizeof(char) * 4);

    while (fscanf(fptr, "%[^:]: ", node) == 1) {
        char *key = malloc(sizeof(char) * 4);
        strcpy(key, node);
        char *friends = malloc(sizeof(char) * 4 * 25);
        int8_t i;
        for (i = 0; fscanf(fptr, "%[^ \n]%*[ ]", friends + i * 4) == 1; ++i); //printf("%d %s\n", i, friends + i * 4);
        fscanf(fptr, "%*[\n]");
        hash_item_add(hash_table, key, friends, i);
        //printf("key: %s is this\n", key);
    }

    total = find_paths(hash_table, "you", "out");

    free(node);
    //for (size_t i = 0; i < TABLE_SIZE; ++i) {
    //    if (hash_table[i].key != NULL) {
    //        free(hash_table[i].key);
    //        //for (size_t n = 0; n < hash_table[i].friends_len; ++n)
    //        //    free(hash_table[i].friends[n]);
    //        free(hash_table[i].friends);
    //    }
    //}
    free(hash_table);
    fclose(fptr);
    printf("%ld\n", total);
    
    return 0;
}


uint16_t jenkins_hash(char *key) {
    uint32_t hash = 0;
    for (size_t i = 0; i < 3; ++i) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return (uint16_t)hash;
}


void hash_item_add(hash_element *hash_table, char *key, char *friends, int8_t friends_len) {
    hash_element *temp = malloc(sizeof(hash_element));
    temp->key = key;
    temp->friends = friends;
    temp->friends_len = friends_len;
    temp->paths = -1;

    uint16_t hash = jenkins_hash(key);
    size_t i = 0;
    while (hash_table[(hash + i) % TABLE_SIZE].key != NULL)
        ++i;
    hash_table[(hash + i) % TABLE_SIZE] = *temp;
    //printf("\t%s\n", hash_table[(hash + i) % TABLE_SIZE].friends);
}


hash_element *hash_item_get(hash_element *hash_table, char *key) {
    uint16_t hash = jenkins_hash(key);
    size_t i = 0;
    while (strcmp(hash_table[(hash + i) % TABLE_SIZE].key, key))
        ++i;
    return hash_table + ((hash + i) % TABLE_SIZE);
}


int64_t find_paths(hash_element *hash_table, char *src, char *dest) {
    //printf("%s\n", src);
    hash_element *element = hash_item_get(hash_table, src);
    if (element->paths == -1) {
        element->paths = 0;
        for (uint64_t i = 0; i < element->friends_len; ++i) {
            if (strcmp(dest, element->friends + i * 4) == 0)
                ++element->paths;
            else
                element->paths += find_paths(hash_table, element->friends + i * 4, dest);
        }
    }
    //printf("%ld\n", element->paths);
    return element->paths;
}
