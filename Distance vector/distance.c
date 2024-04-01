#include<stdio.h>
struct node
{
	unsigned dist[20];
	unsigned from[20];
}rt[10];
int main()
{
	int n,i,j,dm[10][10],k,count;
	printf("enter the no of nodes : ");
	scanf("%d",&n);
	printf("enter the cost matrix\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&dm[i][j]);
			dm[i][i]=0;
			rt[i].dist[j]=dm[i][j];
			rt[i].from[j]=j;
		}
	}
	do
	{
		count=0;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				for(k=0;k<n;k++)
				{
					if(rt[i].dist[j]>dm[i][k]+rt[k].dist[j])
					{
						rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
						rt[i].from[j]=k;
						count++;
					}
				}
			}
		}
	}while(count!=0);
	for(i=0;i<n;i++)  
	{
		printf("\ntable for router %d  \n",i+1);
		for(j=0;j<n;j++)   
		{
			printf("\t\nnode %d Distance %d next hop %d",j+1,rt[i].dist[j],rt[i].from[j]+1); 
		}	
		printf("\n\n");  
	}
}