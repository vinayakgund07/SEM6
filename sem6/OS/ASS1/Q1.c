#include<stdio.h>
int n,m;
int Allocation[10][10],Max[10][10],Need[10][10];
int Avail[10];

void accept_matrix(int A[10][10])
{
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&A[i][j]);
		}
	}
}

void accept_available()
{        int i;
	for(i=0;i<m;i++){
                        scanf("%d",&Avail[i]);
          }
}

void Find_Need()
{
	int i,j;
	 for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                    Need[i][j]=Max[i][j]-Allocation[i][j];
		}
	 }
}

void Display_Matrix(int A[10][10])
{
	  int i,j;
        for(i=0;i<n;i++){
                for(j=0;j<m;j++){
                        printf("%d\t",A[i][j]);
                }
               printf("\n");
	}
}

void Display_available()
{
	int i;
          for(i=0;i<m;i++){
		  printf("%d\t",Avail[i]);
         }
	  printf("\n");

}

int main()
{
	printf("Enter the number of processes(n):");
	scanf("%d",&n);

	printf("Enter number of resource types(m):");
	scanf("%d",&m);

	printf("Enter Allocation Matrix:");
	accept_matrix(Allocation);

	printf("Enter Max Matrix:");
	accept_matrix(Max);

	printf("Enter available resources:");
	accept_available();

	Find_Need();

	printf("\nAllocation Matrix:\n");
	Display_Matrix(Allocation);

	printf("\nMax Matrix\n");
	Display_Matrix(Max);

	printf("\nAvailable Resources:\n");
	Display_available();

	printf("\nNeed Matrix\n");
	Display_Matrix(Need);

	return 0;
}

