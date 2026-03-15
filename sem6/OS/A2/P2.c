#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct File_details
{
	char file_name[10];
	int file_size;
	int file_start;
	int file_end;
}directory[100];
int bit_vector[100];
int memory_size;
int count=0,free_blocks;

void initialize_bit_vector()
{
	int i;
	printf("Enter total number of disk blocks:");
	scanf("%d",&memory_size);
	for(i=0;i<memory_size;i++)
		bit_vector[i]=-1;
	free_blocks=memory_size;
}
void show_memory_blocks()
{
        int i;
        printf("\nMemory blocks:");
        for(i=0;i<memory_size;i++)
               printf("Block %d-->%d\n", i,bit_vector[i]);
	printf("Free blocks available:%d\n",free_blocks);
}
void update_bit_vector(int start_pos,int value)
{
		bit_vector[start_pos]=value;
}
void add_directory_entry(char *filename,int filesize,int start_pos,int end_pos)
{
	strcpy(directory[count].file_name,filename);
	directory[count].file_size=filesize;
	directory[count].file_start=start_pos;
	directory[count].file_end=end_pos;
	count++;
}
void create_file()
{
	char filename[10];
	int i,random_no,filesize,start_pos=-1,prev_pos=-1,last_pos=-1;
	printf("Enter file name:");
	scanf("%s",filename);
	printf("Enter file size(in blocks):");
	scanf("%d",&filesize);
	if(filesize>free_blocks)
	{
		printf("ERROR:Not enough memory to create file\n");
		return;
	}
	for(i=0;i<filesize;i++)
	{
		random_no=rand()%memory_size;
		if(bit_vector[random_no]==-1)
		{
			if(start_pos==-1)
				start_pos=random_no;
			else
		             update_bit_vector(prev_pos,random_no);
			prev_pos=random_no;
			last_pos=random_no;
			bit_vector[random_no]=-2;
			free_blocks--;
		}
		else
		{
			i--;
		}
	}
	update_bit_vector(last_pos,-9);
	add_directory_entry(filename,filesize,start_pos,last_pos);
	printf("File '%s'created successfully\n",filename);
	printf("Start Block:%d End Block:%d\n",start_pos,last_pos);
}
void delete_file()
{
	int i,j,start_pos,next_pos,temp;
	char filename[10];
	printf("Enter file name to delete:");
	scanf("%s",filename);
	for(i=0;i<count;i++)
	{
		if(strcmp(directory[i].file_name,filename)==0)
		{
		
			start_pos=directory[i].file_start;
			next_pos=start_pos;
			while(next_pos!=-9)
			{
		        	temp=bit_vector[next_pos];
			        bit_vector[next_pos]=-1;
			        free_blocks++;
			        next_pos=temp;
		        }
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
	printf("File Name\tStart block\tSize\t\tEnd\n");
	for(i=0;i<count;i++)
	{
		printf("%s\t\t%d\t\t%d\t\t%d\n",directory[i].file_name,directory[i].file_start,directory[i].file_size,directory[i].file_end);
	}
}
int main()
{
	int choice;
	initialize_bit_vector();
	do{
		printf("\n---Linked File Allocation Menu\n");
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
