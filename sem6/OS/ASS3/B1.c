#include<stdio.h>
#include<stdlib.h>
#define MAX_CYL 200
void sort(int arr[],int n)
{
        int i,j,temp;
        for(i=0;i<n-1;i++)
                for(j=i+1;j<n;j++)
                        if(arr[i]>arr[j])
                        {
                                temp=arr[i];
                                arr[i]=arr[j];
                                arr[j]=temp;
                        }
}

void accept_requests(int requests[],int nreqs)
{
        int i;
        for(i=0;i<nreqs;i++)
                scanf("%d",&requests[i]);
        sort(requests,nreqs);
}

int scan(int head,int direction,int requests[],int nreqs)
{
	int i,total_movement=0;
	printf("sequence:%d",head);
	if(direction==1)
	{
		for(i=0;i<nreqs;i++)
			if(requests[i]>=head)
			{
				total_movement+=abs(head-requests[i]);
				head=requests[i];
				printf("->%d",head);
			}
		total_movement+=abs(head-(MAX_CYL-1));
		head=MAX_CYL-1;
		for(i=nreqs-1;i>=0;i--)
			if(requests[i]<head)
			{
				total_movement+=abs(head-requests[i]);
				head=requests[i];
				printf("->%d",head);
			}
	}
	printf("total head movement=%d\n",total_movement);
	return total_movement;
}

int main()
{
        int requests[200];
        int nreqs,head,direction;
        printf("enter number of requests:");
        scanf("%d",&nreqs);

        printf("enter disk requests:\n");
        accept_requests(requests,nreqs);

        printf("enter initial head position:");
        scanf("%d",&head);
        printf("enter direction(1 for right):");
	scanf("%d",&direction);
        scan(head,direction,requests,nreqs);
        return 0;
}

