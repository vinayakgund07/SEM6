#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_BLOCKS 100

typedef struct
{
    char *filename;
    int file_size;
    int index_block;
} file_detail;

typedef struct
{
    int allocated;
    int index[MAX_BLOCKS];
} block;

block bit_vector[MAX_BLOCKS];
file_detail *dir[MAX_FILES];

int memory_size = 0;
int free_memory = 0;

/* Initialize disk */
void initialize_bit_vector()
{
    int i;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &memory_size);

    for (i = 0; i < memory_size; i++)
        bit_vector[i].allocated = 0;

    for (i = 0; i < MAX_FILES; i++)
        dir[i] = NULL;

    free_memory = memory_size;
}

/* Show memory blocks */
void show_memory_blocks()
{
    int i;
    printf("\nBlock status:\n");
    for (i = 0; i < memory_size; i++)
        printf("Block %d : %d\n", i, bit_vector[i].allocated);
}

/* Add file to directory */
void update_directory(file_detail *file)
{
    int i;
    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i] == NULL)
        {
            dir[i] = file;
            return;
        }
    }
}

/* Search file */
int get_file(char *filename)
{
    int i;
    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i] != NULL && strcmp(dir[i]->filename, filename) == 0)
            return i;
    }
    return -1;
}

/* Create file with RANDOM block allocation */
void create_file()
{
    char filename[256];
    file_detail *file;
    int blocks_allocated, i, id, k;

    printf("Enter file name: ");
    scanf("%s", filename);

    k = get_file(filename);
    if (k != -1)
    {
        printf("File already exists!\n");
        return;
    }

    printf("Enter file size (in blocks): ");
    scanf("%d", &blocks_allocated);

    if (blocks_allocated + 1 > free_memory)
    {
        printf("ERROR: Not enough memory\n");
        return;
    }

    file = (file_detail *)malloc(sizeof(file_detail));
    file->filename = (char *)malloc(strlen(filename) + 1);
    strcpy(file->filename, filename);
    file->file_size = blocks_allocated;

    /* Allocate index block randomly */
    do
    {
        id = rand() % memory_size;
    } while (bit_vector[id].allocated);

    file->index_block = id;
    bit_vector[id].allocated = 1;
    free_memory--;

    /* Allocate data blocks randomly */
    for (i = 0; i < blocks_allocated; i++)
    {
        do
        {
            id = rand() % memory_size;
        } while (bit_vector[id].allocated);

        bit_vector[file->index_block].index[i] = id;
        bit_vector[id].allocated = 1;
        free_memory--;
    }

    update_directory(file);

    printf("File '%s' created successfully\n", filename);
    printf("Index Block: %d\n", file->index_block);
}

/* Delete file */
void delete_file()
{
    int i, idx, id;
    char filename[256];
    file_detail *file;

    printf("Enter file name to delete: ");
    scanf("%s", filename);

    idx = get_file(filename);
    if (idx == -1)
    {
        printf("File not found!\n");
        return;
    }

    file = dir[idx];

    for (i = 0; i < file->file_size; i++)
    {
        id = bit_vector[file->index_block].index[i];
        bit_vector[id].allocated = 0;
        free_memory++;
    }

    bit_vector[file->index_block].allocated = 0;
    free_memory++;

    free(file->filename);
    free(file);
    dir[idx] = NULL;

    printf("File deleted successfully!\n");
}

/* Display directory */
void display_directory()
{
    int i, j;
    file_detail *file;

    printf("\nFile Name\tSize\tIndex Block\tData Blocks\n");
    for (i = 0; i < MAX_FILES; i++)
    {
        if (dir[i] == NULL)
            continue;

        file = dir[i];
        printf("%s\t\t%d\t\t%d\t\t",
               file->filename, file->file_size, file->index_block);

        for (j = 0; j < file->file_size; j++)
            printf("%d ", bit_vector[file->index_block].index[j]);

        printf("\n");
    }
}

/* Main */
int main()
{
    int choice;

    srand(time(NULL));   // seed random number generator
    initialize_bit_vector();

    do
    {
        printf("\n--- Indexed File Allocation Menu ---\n");
        printf("1. Create file\n");
        printf("2. Delete file\n");
        printf("3. Display Directory\n");
        printf("4. Show Memory Blocks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_file();
            break;
        case 2:
            delete_file();
            break;
        case 3:
            display_directory();
            break;
        case 4:
            show_memory_blocks();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    } while (1);

    return 0;
}

