#include<stdio.h>
#include<stdlib.h>


int bubblesort(int arr[],int n)
{
	int i,j,temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void accept_requests(int requests[],int nreqs)
{
        int i;
        printf("\nEnter the disk requests:\n");
        for(i=0;i<nreqs;i++)
                scanf("%d",&requests[i]);

        bubblesort(requests,nreqs);
}


int sstf(int head,int requests[],int nreqs)
{
	int i,total_movement=0;
	int visited[200]={0};
	int nearest,count=nreqs;
        int left,right,dist;
	int left_dist,right_dist,direction=1;

	printf("Sequence:%d",head);
	while(count-- >0)
	{
		left=-1;
		right=-1;

		for(i=0;i<nreqs;i++)
		{
			if(!visited[i])
			{
				if(requests[i]<=head)
				  left=i;
				if(requests[i]>head)
				{
					right=i;
					break;
				}
			}
		}
		if(left==-1)
			nearest=right;

		else if(right==-1)
			nearest=left;
		else
		{
			left_dist=abs(head-requests[left]);
			right_dist=abs(head-requests[right]);
			if(left_dist<=right_dist)
				nearest=left;
			else
				nearest=right;
		}
		total_movement+=abs(head-requests[nearest]);
	        head=requests[nearest];
		visited[nearest]=1;
		printf("->%d",head);
	}
	printf("\nTotal Head Movement=%d\n",total_movement);
	return total_movement;
}

int main()
{
	int requests[200];
	int nreqs,head;

	printf("Enter Number of disk requests:");
	scanf("%d",&nreqs);

	accept_requests(requests,nreqs);

	printf("Enter initial head position\n");
	scanf("%d",&head);

	sstf(head,requests,nreqs);
	return 0;
}
