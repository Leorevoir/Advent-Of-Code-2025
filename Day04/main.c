#include "macros.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static const i32 DR[] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const i32 DC[] = {-1, 0, 1, -1, 1, -1, 0, 1};

typedef struct
{
    char **grid;
    i32 rows;
    i32 cols;
} Map;

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
        fclose(stream);
        free(buffer);
        return NULL;
    }
    buffer[size] = '\0';
    fclose(stream);
    return buffer;
}

static void free_map(Map *map)
{
    if (!map || !map->grid)
    {
        return;
    }
    for (i32 i = 0; i < map->rows; ++i)
    {
        free(map->grid[i]);
    }
    free(map->grid);

    map->grid = NULL;
    map->rows = 0;
    map->cols = 0;
}

static void string_to_map(Map *map, const char *str)
{
    defer_ptr char *temp = strdup(str);
    char *line = strtok(temp, "\n");

    while (line)
    {
        if (map->cols == 0)
        {
            map->cols = (i32)strlen(line);
        }
        ++map->rows;
        line = strtok(NULL, "\n");
    }

    map->grid = malloc(sizeof(char *) * (size_t)map->rows);
    if (!map->grid)
    {
        return;
    }

    defer_ptr char *content = strdup(str);

    line = strtok(content, "\n");
    for (i32 i = 0; i < map->rows && line; ++i)
    {
        map->grid[i] = strdup(line);
        line = strtok(NULL, "\n");
    }
}

static inline u32 count_adjacent_rolls(const Map *map, const i32 row, const i32 col)
{
    u32 count = 0;

    for (u32 i = 0; i < 8; ++i)
    {
        const i32 nr = row + DR[i];
        const i32 nc = col + DC[i];

        if (nr >= 0 && nr < map->rows && nc >= 0 && nc < map->cols && map->grid[nr][nc] == '@')
        {
            ++count;
        }
    }
    return count;
}

static u32 count_accessible_rolls(const Map *map)
{
    u32 count = 0;
    for (i32 r = 0; r < map->rows; ++r)
    {
        for (i32 c = 0; c < map->cols; ++c)
        {
            if (map->grid[r][c] == '@' && count_adjacent_rolls(map, r, c) < 4)
            {
                ++count;
            }
        }
    }
    return count;
}

static u32 remove_accessible_rolls(Map *map)
{
    u32 removed = 0;
    for (i32 r = 0; r < map->rows; ++r)
    {
        for (i32 c = 0; c < map->cols; ++c)
        {
            if (map->grid[r][c] == '@' && count_adjacent_rolls(map, r, c) < 4)
            {
                map->grid[r][c] = '.';
                ++removed;
            }
        }
    }
    return removed;
}

static void forklift(const char *buffer)
{
    Map map = {0};
    u32 total_removed = 0;
    u32 removed;

    string_to_map(&map, buffer);

    const u32 accessible = count_accessible_rolls(&map);

    do
    {
        removed = remove_accessible_rolls(&map);
        total_removed += removed;
    } while (removed > 0);

    free_map(&map);
    printf("%u\n", accessible);
    printf("%u\n", total_removed);
}

i32 main(const i32 argc, const char **argv)
{
    if (argc != 2)
    {
        return ERROR;
    }

    defer_ptr char *buffer = get_file_content(argv[1]);

    if (!buffer)
    {
        return ERROR;
    }

    forklift(buffer);
    return SUCCESS;
}
