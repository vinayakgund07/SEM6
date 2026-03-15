#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct file_details{
	char file_name[10];
	int file_size;
	int file_start;
}directory[100];

int bit_vector[100], memory_size, count=0;

void initialize_bit_vector(){
	int i;
	printf("Enter total number of memory blocks: ");
	scanf("%d", &memory_size);
	for(i=0;i<memory_size;i++)
		bit_vector[i] = 1;
}

void show_memory_blocks()
{
	int i;
	printf("Memory Block:");
	for(i=0;i<memory_size;i++)
		printf("%d",bit_vector[i]);
	printf("\n");
}

int check_if_freeblock(int block_no)
{
  if(bit_vector[block_no]==1)
    return 1;
  else
    return 0;
}

int check_for_continuos_space(int file_size){
  int i,j;
  for(i=0;i<=memory_size-file_size;i++){
    for(j=i;j<i+file_size;j++){
      if(check_if_freeblock(j)==0)
        break;
    }
    if(j==i+file_size)
      return i;
  }
  return -1;
}

void update_bit_vector(int start_pos,int file_size,int value){
	int i;
	for(i=start_pos;i<start_pos+file_size;i++)
		bit_vector[i]=value;
}

void add_directory_entry(char *fileName,int fileSize,int start_pos)
{
	strcpy(directory[count].file_name,fileName);
	directory[count].file_size=fileSize;
	directory[count].file_start=start_pos ;
        count++;
}

void create_file()
{
	char filename[10];
	int filesize,start_pos;

	printf("Enter filename");
	scanf("%s",filename);

	printf("Enter file size:");
	scanf("%d",&filesize);

	start_pos=check_for_continuos_space(filesize);

	if(start_pos==-1)
		printf("No continuos free space available");
	else
	{ 
		update_bit_vector(start_pos,filesize,0);
		add_directory_entry(filename,filesize,start_pos);
		printf("File allocated successfully");
	}

}


void delete_file()
{
	int i,j,fileSize,fileStart;
	char filename[10];

	printf("Enter filename to delete:");
	scanf("%s",filename);

	for(i=0;i<count;i++)
	{
		if(strcmp(directory[i].file_name,filename)==0)
		{
			fileSize=directory[i].file_size;
			fileStart=directory[i].file_start;
			update_bit_vector(fileStart,fileSize,1);
			for(j=1;j<count-1;j++)
				directory[j]=directory[j+1];
				count--;
				printf("File deleted successfully\n");
				return;
		}
		}
	printf("File not found");
	}

void display_directory()
{
	int i;
	printf("Directory contents/Details\n");
	for(i=0;i<count;i++)
	{
	        printf("\nFile name:%s\n",directory[i].file_name);
	        printf("\nStart Block:%d\n",directory[i].file_start);
                printf("\nSize:%d\n",directory[i].file_size);
}
}



int main()
{
	int choice;
	initialize_bit_vector();

	while(1)
	{
		printf("\n1.Create File\n2.Delete File\n3.Display Directory\n4.Show Memory Blocks\n5.Exit\n");
		printf("Enter your choice\n");
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
			 default:printf("Invalid choice");
		}
	}
}



			    
