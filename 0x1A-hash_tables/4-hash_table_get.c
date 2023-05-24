#include "hash_tables.h"

/**
 * ht_get - retrieves a value associated with a key in a hash table.
 * @ht: the hash table to search in
 * @key: the key to search for
 *
 * Return: the value associated with the key if found, NULL if not found
 */
char *ht_get(const hash_table_t *ht, const char *key)
{
    hash_node_t *current_node;
    unsigned long int index;

    if (ht == NULL)
        return (NULL);

    index = key_index((const unsigned char *)key, ht->size);
    current_node = ht->array[index];

    while (current_node != NULL)
    {
        if (strcmp(current_node->key, key) == 0)
            return (current_node->value);

        current_node = current_node->next;
    }

    return (NULL);
}
