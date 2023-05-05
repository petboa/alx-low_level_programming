#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: Size of the array
 *
 * Return: Pointer to new sorted hash table, NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    if (ht == NULL)
        return (NULL);

    ht->size = size;
    ht->array = calloc(size, sizeof(shash_node_t *));
    if (ht->array == NULL) {
        free(ht);
        return (NULL);
    }

    ht->shead = NULL;
    ht->stail = NULL;

    return (ht);
}

/**
 * shash_table_set - Inserts a key-value pair into a sorted hash table
 * @ht: Sorted hash table
 * @key: Key to insert
 * @value: Value associated with key
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    unsigned long int idx;
    shash_node_t *node, *temp;

    if (ht == NULL || key == NULL || *key == '\0')
        return (0);

    idx = key_index((const unsigned char *)key, ht->size);
    temp = ht->array[idx];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            free(temp->value);
            temp->value = strdup(value);
            return (1);
        }
        temp = temp->next;
    }

    node = malloc(sizeof(shash_node_t));
    if (node == NULL)
        return (0);

    node->key = strdup(key);
    if (node->key == NULL) {
        free(node);
        return (0);
    }
    node->value = strdup(value);
    if (node->value == NULL) {
        free(node->key);
        free(node);
        return (0);
    }

    node->next = ht->array[idx];
    ht->array[idx] = node;

    if (ht->shead == NULL) {
        node->sprev = NULL;
        node->snext = NULL;
        ht->shead = node;
        ht->stail = node;
    } else {
        temp = ht->shead;
        while (temp != NULL && strcmp(key, temp->key) > 0)
            temp = temp->snext;

        if (temp == NULL) {
            node->sprev = ht->stail;
            node->snext = NULL;
            ht->stail->snext = node;
            ht->stail = node;
        } else if (temp == ht->shead) {
            node->sprev = NULL;
            node->snext = ht->shead;
            ht->shead->sprev = node;
            ht->shead = node;
        } else {
            node->sprev = temp->sprev;
            node->snext = temp;
            temp->sprev->snext = node;
            temp->sprev = node;
        }
    }

    return (1);
}

/**
 * shash_table_get - Retrieves a value associated with a key from a sorted hash table
 * @ht: Sorted hash table
 * @key: Key to retrieve value for
 *
 * Return: Value associated with key, NULL if key not
