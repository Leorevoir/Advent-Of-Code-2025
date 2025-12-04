#include "macros.h"

#include <stdio.h>
#include <sys/stat.h>

static char *get_file_content(const char *filename)
{
    struct stat st;
    FILE *stream = fopen(filename, "r");
    char *buffer = NULL;

    if (stream == NULL || stat(filename, &st) != 0)
    {
        return NULL;
    }
    const size_t size = (size_t)st.st_size;

    buffer = malloc(size + 1);
    if (!buffer || fread(buffer, 1, size, stream) != size)
    {
        return NULL;
    }
    fclose(stream);
    return buffer;
}

int main(const int argc, const char **argv)
{
    if (argc != 2)
    {
        return ERROR;
    }
    defer_free char *buffer = get_file_content(argv[1]);

    puts(buffer ? buffer : "ERROR reading file");

    return SUCCESS;
}
