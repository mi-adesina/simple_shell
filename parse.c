#include "shell.h"

/**
 * is_command - Check if a file at the given path is a valid command.
 * @inf: A pointer to the inf_t structure (not used in this function).
 * @path: The path to the file to be checked.
 *
 * Return: 1 if the file is a valid command, 0 otherwise.
 */
int is_command(inf_t *inf, char *path)
{
    struct stat file_stat;
        (void)inf;

    if (stat(path, &file_stat) or !path)
        return 0; 

    if (S_ISREG(file_stat.st_mode))
    {
        return 1; /*valid command. */
    }

    return 0; /* not a valid command */
}


/**
 * find_path - Find the full path to a command in a given
 *             PATH environment string.
 * @inf: A pointer to the infrmation struct.
 * @pathstr: The PATH environment string to search for the command.
 * @command: The command to search for.
 *
 * Return: A pointer to the full path of the command, or NULL if not found.
 */
char *find_path(inf_t *inf, char *pathstr, char *command)
{
    int i = 0, current_position = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_command(inf, command))
            return command;
    }

    while (pathstr[i])
    {
        if (pathstr[i] == ':')
        {
            path = dup_characters(pathstr, current_position, i);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_command(inf, path))
                return path;

            current_position = i + 1;
        }
        i++;
    }

    path = dup_characters(pathstr, current_position, i);
    if (!*path)
        _strcat(path, command);
    else
    {
        _strcat(path, "/");
        _strcat(path, command);
    }
    if (is_command(inf, path))
        return path;

    return NULL;
}

