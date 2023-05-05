int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    unsigned long int index;
    hash_node_t *new_node, *tmp;

    if (!ht || !key || !*key || !value)
        return 0;

    index = key_index((const unsigned char *)key, ht->size);
    tmp = ht->array[index];

    while (tmp)
    {
        if (strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            return 1;
        }
        tmp = tmp->next;
    }

    new_node = malloc(sizeof(hash_node_t));
    if (!new_node)
        return 0;

    new_node->key = strdup(key);
    if (!new_node->key)
    {
        free(new_node);
        return 0;
    }
    new_node->value = strdup(value);
    if (!new_node->value)
    {
        free(new_node->key);
        free(new_node);
        return 0;
    }

    new_node->next = ht->array[index];
    ht->array[index] = new_node;
    return 1;
}
