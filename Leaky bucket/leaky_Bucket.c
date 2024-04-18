#include<stdio.h>
void main()
{
    int in,out,bsize,n,bucket=0;
    printf("Enter the bucket size : ");
    scanf("%d",&bsize);
    printf("\nEnter the no.of inputs : ");
    scanf("%d",&n);
    printf("\nEnter Packet outgoing rate : ");
    scanf("%d",&out);

    while(n!=0)
    {
        printf("\nEnter the incoming Packet size : ");
        scanf("%d",&in);
        if(in <= (bsize - bucket))
        {
            bucket += in;
            printf("\nBucket Status : %d out of %d",bucket,bsize);
        }
        else
        {
            printf("\nDropped Packets : %d \n",in-(bsize-bucket));
            bucket = bsize;
            printf("\nBucket Status : %d out of %d",bucket,bsize);
        }
        bucket = bucket - out;
        printf("\nAfter outgoing, Bucket Status : %d out of %d",bucket,bsize);
        n--;
    }
    printf("\n");
}
