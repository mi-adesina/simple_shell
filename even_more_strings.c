#include "shell.h"

/**
 * dup_characters - Duplicate characters from a source string within
 *             a specified range.
 * @pathstr: The source string to duplicate characters from.
 * @start_idx: The starting index (inclusive) for character duplication.
 * @end_idx: The ending index (exclusive) for character duplication.
 *
 * Return: pointer to new buffer
 */
char *dup_characters(char *pathstr, int start_idx, int end_idx)
{
    static char duplicated_buffer[1024];
    int source_idx = start_idx, duplicated_idx = 0;

    while (source_idx < end_idx)
    {
        if (pathstr[source_idx] != ':')
        {
            duplicated_buffer[duplicated_idx++] = pathstr[source_idx];
        }
        source_idx++;
    }
    duplicated_buffer[duplicated_idx] = '\0';
    return duplicated_buffer;
}