#include<stdio.h>
#include<stdlib.h>

void accept_requests(int requests[],int nreqs)
{
	int i;
	printf("Enter the disk request:\n");
	for(i=0;i<nreqs;i++)
	{
		scanf("%d",&requests[i]);
	}
}


int fcfs(int head,int requests[],int nreqs)
{
	int i,total_movement=0;
	printf("Sequence:%d",head);
	for(i=0;i<nreqs;i++)
		{
			total_movement+=abs(head-requests[i]);
			head=requests[i];
			printf("->%d",head);
		}
	printf("\n Total head movement=%d\n",total_movement);
	return total_movement;
}

int main()
{
	int requests[200];
	int nreqs,head;

	printf("Enter the number of disk requests");
	scanf("%d",&nreqs);

	accept_requests(requests,nreqs);

	printf("Enter initial head position");
	scanf("%d",&head);

	fcfs(head,requests,nreqs);

	return 0;
}
