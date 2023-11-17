#include "shell_functions.h"

/**
 * custom_input_buf - Reads input from the user,
 * handling signals and building a command buffer.
 * @info: Pointer to the info_t structure containing program information.
 * @buffer: Pointer to the buffer to store user input.
 * @length: Pointer to the length variable indicating the size of the buffer.
 * Return: Number of bytes read on success, or 0 on failure.
 */
ssize_t custom_input_buf(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytes_read = 0;
    size_t temp_length = 0;

    if (!*length)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, custom_sigintHandler);
        bytes_read = custom_getline(info, buffer, &temp_length);

        if (bytes_read > 0)
	{
            if ((*buffer)[bytes_read - 1] == '\n')
	    {
                (*buffer)[bytes_read - 1] = '\0';
                bytes_read--;
            }

            info->linecount_flag = 1;
            custom_remove_comments(*buffer);
            custom_build_history_list(info, *buffer, info->histcount++);
            *length = bytes_read;
            info->cmd_buf = buffer;
        }
    }

    return (bytes_read);
}
/**
 * custom_get_input - Gets a line of input
 * from the user, handling command chaining.
 * @info: Pointer to the info_t structure containing program information.
 * Return: Number of bytes read on success, or -1 on failure.
 */
ssize_t custom_get_input(info_t *info)
{
    static char *buffer;
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buffer_ptr = &(info->arg);
    char *current_position;

    custom_putchar(BUF_FLUSH);
    bytes_read = custom_input_buf(info, &buffer, &length);

    if (bytes_read == -1)
    {
        return -1;
    }

    if (length)
    {
        j = i;
        current_position = buffer + i;

        custom_check_chain(info, buffer, &j, i, length);

        while (j < length)
	{
            if (custom_is_chain(info, buffer, &j))
	    {
                break;
            }
            j++;
        }
        i = j + 1;

        if (i >= length)
	{
            i = length = 0;
            info->cmd_buf_type = CMD_NORM;
        }
        *buffer_ptr = current_position;
        return custom_strlen(current_position);
    }

    *buffer_ptr = buffer;
    return (bytes_read);
}
/**
 * custom_read_buf - Reads a buffer from the specified file descriptor.
 * @info: Pointer to the info_t structure containing program information.
 * @buffer: Buffer to store the read data.
 * @size: Pointer to the size variable indicating the size of the buffer.
 * Return: Number of bytes read on success, or 0 on failure.
 */
ssize_t custom_read_buf(info_t *info, char *buffer, size_t *size)
{
    ssize_t bytes_read = 0;

    if (*size)
    {
        return 0;
    }
    bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);

    if (bytes_read >= 0)
    {
        *size = bytes_read;
    }
    return (bytes_read);
}
/**
 * custom_getline - Reads a line of input from the specified file descriptor.
 * @info: Pointer to the info_t structure containing program information.
 * @ptr: Pointer to the buffer to store the read data.
 * @length: Pointer to the length variable indicating the size of the buffer.
 * Return: Number of bytes read on success, or -1 on failure.
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0, total_bytes = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
    {
        total_bytes = *length;
    }
    if (i == len)
    {
        i = len = 0;
    }

    bytes_read = custom_read_buf(info, buffer, &len);
    if (bytes_read == -1 || (bytes_read == 0 && len == 0))
    {
        return -1;
    }
    c = custom_strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : len;

    new_p = realloc(p, total_bytes ? total_bytes + k : k + 1);

    if (!new_p)
    {
        return (p ? free(p), -1 : -1);
    }
    if (total_bytes)
    {
        custom_strncat(new_p, buffer + i, k - i);
    }
    else
    {
        custom_strncpy(new_p, buffer + i, k - i + 1);
    }
    total_bytes += k - i;
    i = k;
    p = new_p;
    if (length)
    {
        *length = total_bytes;
    }
    *ptr = p;
    return (total_bytes);
}
/**
 * custom_sigintHandler - Handles the SIGINT signal,
 * printing a message and flushing the buffer.
 * @sig_num: Signal number.
 * Return: void
 */
void custom_sigintHandler(__attribute__((unused)) int sig_num)
{
    custom_puts("\n");
    custom_puts("$ ");
    custom_putchar(BUF_FLUSH);
}
