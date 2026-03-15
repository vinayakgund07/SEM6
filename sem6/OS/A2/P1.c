#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct File_deatails
{
	char file_name[10];
	int file_size;
	int file_start;
}directory[100];
int bit_vector[100];
int memory_size;
int count=0;

void initialize_bit_vector()
{
	int i;
	printf("Enter total number of disk blocks:");
	scanf("%d",&memory_size);
	for(i=0;i<memory_size;i++)
		bit_vector[i]=1;
}
void show_memory_blocks()
{
        int i;
        printf("\nMemory blocks:");
        for(i=0;i<memory_size;i++)
               printf("%d", bit_vector[i]);
	printf("\n");
}
int check_if_freeblock(int block_no)
{
	if(bit_vector[block_no]==1)
		return 1;
	else
		return 0;
}
int check_for_continuous_space(int file_size)
{
	int i,j;
	for(i=0;i<=memory_size-file_size;i++)
	{
		for(j=0;j<file_size;j++)
		{
			if(!check_if_freeblock(i+j))
				break;
		}
		if(j==file_size)
			return i;
	}
	return -1;
}
void update_bit_vector(int start_pos,int file_size)
{
	int i;
	for(i=start_pos;i<start_pos+file_size;i++)
		bit_vector[i]=0;
}
void add_directory_entry(char *fileName,int filesize,int start_pos)
{
	strcpy(directory[count].file_name,fileName);
	directory[count].file_size=filesize;
	directory[count].file_start=start_pos;
	count++;
}
void create_file()
{
	char filename[10];
	int filesize,start_pos;
	printf("Enter file name:");
	scanf("%s",filename);
	printf("Enter file size(in blocks):");
	scanf("%d",&filesize);
	start_pos=check_for_continuous_space(filesize);
	if(start_pos==-1)
	{
		printf("ERROR:Not enough contiguous space available\n");
	}
	else
	{
		update_bit_vector(start_pos,filesize);
		add_directory_entry(filename,filesize,start_pos);
		printf("File created successfully at block %d\n",start_pos);
	}
}
void delete_file()
{
	int i,j,fileSize,fileStart;
	char filename[10];
	printf("Enter file name to delete:");
	scanf("%s",filename);
	for(i=0;i<count;i++)
	{
		if(strcmp(directory[i].file_name,filename)==0)
		{
			fileSize=directory[i].file_size;
			fileStart=directory[i].file_start;
			for(j=fileStart;j<fileStart+fileSize;j++)
				bit_vector[j]=1;
			for(j=i;j<count-1;j++)
				directory[j]=directory[j+1];
	count--;
	printf("File deleted successfully\n");
	return;
		}
	}
	printf("Error:File not found\n");
}
void display_directory()
{
	int i;
	if(count==0)
	{
		printf("Directory is empty\n");
		return;
	}
	printf("File Name\tStart block\tSize\n");
	for(i=0;i<count;i++)
	{
		printf("%s\t\t%d\t\t%d\n",directory[i].file_name,directory[i].file_start,directory[i].file_size);
	}
}
int main()
{
	int choice;
	initialize_bit_vector();
	do{
		printf("\n---Sequential File Allocation Menu\n");
		printf("1.Create file\n2.Delete file\n3.Display Directory\n4.Show Memory Blocks\n5.Exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:create_file();
			       break;
			case 2:delete_file();
			       break;
			case 3:display_directory();
			       break;
			case 4:show_memory_blocks();
			       break;
			case 5:exit(0);
			default:printf("Invalid choice!\n");
		}
	}while(1);
	return 0;
}
