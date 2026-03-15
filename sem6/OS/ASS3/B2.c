#include <stdio.h>
#include <stdlib.h>


#define MAX 200


void accept_requests(int req[], int n) {
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);
}


void sort(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[i]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
}


int cscan(int head, int direction, int req[], int n) {
    sort(req, n);


    int total = 0;
    int index = 0;


    while (index < n && req[index] < head)
        index++;


    printf("\nC-SCAN Sequence: %d", head);


    if (direction == 1) {
        for (int i = index; i < n; i++) {
            total += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }


        total += abs(199 - head);
        head = 199;
        printf(" -> %d", head);
 

        total += 199;
        head = 0;
        printf(" -> %d", head);


        for (int i = 0; i < index; i++) {
            total += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    else {
        for (int i = index - 1; i >= 0; i--) {
            total += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }


        total += abs(head - 0);
        head = 0;
        printf(" -> %d", head);


        total += 199;
        head = 199;
        printf(" -> %d", head);


        for (int i = index; i < n; i++) {
            total += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }
    }


    printf("\nTotal Head Movement = %d\n", total);
    return total;
}


int main() {
    int req[200], n, head, direction;


    printf("Enter number of requests: ");
    scanf("%d", &n);


    accept_requests(req, n);


    printf("Enter initial head position: ");
    scanf("%d", &head);


    printf("Enter direction (1=Right, -1=Left): ");
    scanf("%d", &direction);


    cscan(head, direction, req, n);
    return 0;
}

