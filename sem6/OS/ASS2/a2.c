#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct file_details{
char file_name[10];
int  file_size;
int file_start;
int file_end;
}directory[100];

int bit_vector[100];
int memory_size,free_blocks,count=0;

void initialize_bit_vector()
{
 int i;
 printf("Enter total number of memory blocks");
 scanf("%d",&memory_size);

 for(i=0;i<memory_size;i++)
  bit_vector[i]=-1;
  free_blocks=memory_size;
}

void show_memory_blocks()
{
 int i;
 printf("\nBlock Status:\n");
 for(i=0;i<memory_size;i++)
{
  if(bit_vector[i]==-1)
    printf("%d:Free\n",i);
 else if(bit_vector[i]==9)
    printf("%d:End of file\n",i);
  else
    printf("%d:Linked->%d\n",i,bit_vector[i]);
  }
printf("Freeblocks available:%d\n",free_blocks);
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
	int i,filesize,start_pos=-1,end_pos=-1,prev_pos=-1;
	char filename[10];

	printf("Enter file name:\n");
	scanf("%s",filename);

	printf("Enter file size(blocks):)");
	scanf("%d",&filesize);

	if(filesize>free_blocks)
	{
		printf("Not enough memory\n");
		 return;
        }

	int remaining=filesize;

	for(i=0;i<memory_size && remaining>0;i++)
	{
		if(bit_vector[i]==-1)
		{
			if(start_pos==-1)
				start_pos=i;
			else
			   bit_vector[prev_pos]=i;
			prev_pos=i;
			end_pos=i;

			 remaining--;
			 free_blocks--;
		}
	}
	bit_vector[end_pos]=-9;

	add_directory_entry(filename,filesize,start_pos,end_pos);
	printf("File created sucessfully\n");
}
 
void delete_file()
{
	int i,j,temp,pos;
	char filename[10];

	printf("Enter file name to delete\n");
	scanf("%s",filename);

	for(i=0;i<count;i++)
	{
		if(strcmp(directory[i].file_name,filename)==0)
		{
			pos=directory[i].file_start;
			while(pos!=-9)
			{
				temp=bit_vector[pos];
				bit_vector[pos]=-1;
				free_blocks++;
				pos=temp;
			}
			for(j=i;j<count-1;j++)
				directory[j]=directory[j+1];
			count--;
			printf("File deleted successfully\n");
			return;
		}
	}
	printf("File not found\n");
}


void display_directory()
{
	int i;
	printf("\nFile Directory\n");
	printf("Name\tSize\tStart\tEnd\n");

	for(i=0;i<count;i++)
	{

		printf("%s\t%d\t%d\t%d\n",directory[i].file_name,directory[i].file_size,directory[i].file_start,directory[i].file_end);
 }
}
int main()
{
     int choice;
     initialize_bit_vector();

        do{
                printf("\nMenu\n");
                printf("1.Create file\n2.Delete file\n3.Show memory blocks\n4.Display Directory\n5.Exit\n");
                printf("Enter choice\n");
                scanf("%d",&choice);

                switch(choice)
                {
                        case 1:create_file();
                               break;
                        case 2:delete_file();
                               break;
                        case 3:show_memory_blocks();
			       break;
			case 4:display_directory();
			       break;
	        }

             }
	while(choice!=5);
	return 0;
}

