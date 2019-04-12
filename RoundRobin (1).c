#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
struct process{
  int pId;
  int burstTime;
  int waitingTime;
  int turnAround;
  int arrivalTime;
  int remaining;
  bool flag;
};
struct process *p;
int i,j,n,tq;
float sumwait(struct process *p,int size)
{
  int sum=0;
  for(i=0;i<size;i++)
  {
    sum+=p[i].waitingTime;
  }
  return sum;
}
//sumturn function is use to calculate the sum of turnAround of all process
float sumturn(struct process *p,int size)
{
  int sum=0;
  for(i=0;i<size;i++)
  {
    sum+=p[i].turnAround;
  }
  return sum;
}
void display(struct process *p)
{
  char la[]="Process Id";

  char lc[]="BurstTime";
  char lf[]="ArrivalTime";
  char ld[]="WaitingTime";
  char le[]="Turnaroundtime";
  char lg[]="Remaining";
  printf("\n\n\n%10s %10s %10s %10s %10s %10s\n",la,lc,lf,ld,le,lg);

 for( i=0;i<n;i++)
 {


 printf("%10d %10d %10d %10d %10d %10d\n",(p+i)->pId,(p+i)->burstTime,(p+i)->arrivalTime,(p+i)->waitingTime,(p+i)->turnAround,(p+i)->remaining);

 }
 float avgw=sumwait(p,n);
 printf("\n\n------------Avereage waiting time=%f--------------------",avgw/n);
 float avgt=sumturn(p,n);
 printf("\n\n--------------Average Turnaroundtime=%f---------------------\n",avgt/n);

}
void psorting(struct process *p,int size)
{
  for(i=size-1;i>=0;i--)
  {
    for(j=0;j<i;j++)
    {
      if(p[j].arrivalTime>p[j+1].arrivalTime)
      {
        struct process temp=p[j];
        p[j]=p[j+1];
        p[j+1]=temp;

      }
    }
  }
}
void getInput()
{
  p=(struct process *)calloc(n,sizeof(struct process));
  printf("How many process to Schedule\n");
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    struct process pro;
    printf("Enter the Arrival Time and burst time of Process[%d] ",i+1);

    scanf("%d",&pro.arrivalTime);
    scanf("%d",&pro.burstTime);
    pro.pId=i+1;
    pro.flag=false;
    pro.remaining=pro.burstTime;
    p[i]=pro;
  }
  printf("Enter the Time Quantum\n");
  scanf("%d",&tq);
}
void RoundRobin(struct process *p,int size)
{
 psorting(p,size);
 int remain=size;
 int timer=p[0].arrivalTime;


 while(remain!=0)
 {
   for(i=0;i<size;i++)
   {
     if(p[i].remaining<=tq && p[i].remaining>0)
     {
       timer+=p[i].remaining;
       p[i].remaining=0;
       
       p[i].turnAround=timer-p[i].arrivalTime;
       p[i].waitingTime=p[i].turnAround-p[i].burstTime;
       remain--;


     }
     else if(p[i].remaining>tq)
     {
       timer+=tq;
       p[i].remaining-=tq;
     }
      

  }
 }
display(p);
}
int main()
{
  getInput();
  RoundRobin(p,n);
}
