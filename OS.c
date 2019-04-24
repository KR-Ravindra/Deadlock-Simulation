/** There are 3 studentprocesses and 1 teaher process. Students are supposed to do their assignments and they need 3 things for that- pen,paper and question paper. The teacher has an infinite supply of all the three things. One student has pen, another has paper and another has question paper. The teacher places two things on a shared table and the student having the third complementary thing makes the assignment and tells the teacher on completion. The teacher then places two things out of three and again the student having the third thing makes the assignment and tells the teacher on completion. This cycle continues. Write a program to synchronise the teacher and the students.
 * Two types of people can enter into a library-students and teachers. After entering the library, the visitor searches for the required books and get them. In ordr to get them issued, he goes to the single CPU which is there to process the issuing of books. Two types of queues are there at the counter-one for students and one for teachers.A student goes and stands at the tail of the queue for students and simliarly the teacher goes and stands at the tail of the queue for teaches (FIFO).If a student is being served and a teacher arrives at the counter, he would be the next person to get service (PRIORITY - non preemtive). If two teachers arrive at the same time, they will stand in their queue to get service (FIFO). Write a program to ensure that the system works in a non-chaotic manner.
 * If a teacher is being served and during the period when he is being served, another teacher comes, then that teacher would get the service next. This process might continue leading to increase in waiting time of students. Ensure in your program that the waiting time of students is minimized.**/


#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>


pthread_mutex_t lockt=PTHREAD_MUTEX_INITIALIZER;
int s0[3];
int s1[3];
int s2[3];

void exit1()
{
	printf("\n\n\n\t Thank you. Submitted to: Ms.Cherry Khosla (LFTS). Submitted by: Kathi Raja Ravindra (11702961), K17PG-A26. \n");
	sleep(2);
	exit(0);
}	
int assign(int x,int y)											//Function which prevents students from having same resources
{
	int i=1;
	if(y==0)
	{
		if(s1[x]==1 || s2[x]==1)
		{
			printf("\nTwo students can't have same resource.");
			exit1();
		}
	}
	if(y==1)
	{
		if(s0[x]==1 || s2[x]==1)
		{
			printf("\nTwo students can't have same resource.");
			exit1();
		}
	}
	if(y==2)
	{
		if(s0[x]==1 || s1[x]==1)
		{
			printf("\nTwo students can't have same resource.");
			exit1();
		}
	}
	return i;
}
void *student0()												//Function that takes input for student 1
{
	printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 1st student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		s0[0]=assign(0,0);
	}
	else
		{ if(a==2)
			{
				s0[1]=assign(1,0);
			}
		else
			{ if(a==3)
				{
					s0[2]=assign(2,0);
				}
			else
				{
			printf(" A student isn't configured to contain this.\n");
		}}
	}
	pthread_mutex_unlock(&lockt);
}
void *student1()												//Function that takes input for student 2
{
	//printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 2nd student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		s1[0]=assign(0,1);
	}
	else{ if(a==2)
	{
		s1[1]=assign(1,1);
	}
	else{ if(a==3)
	{
		s1[2]=assign(2,1);
	}
	else
	{
		printf(" A student isn't configured to contain this.\n");
	}}}
	pthread_mutex_unlock(&lockt);
}
void *student2()													//Function that takes input for student 3
{
	//printf("\nPress 1 for pen, 2 for paper and 3 for question paper\n");
	printf("Enter the item present with 3rd student: ");
	int a;
	pthread_mutex_lock(&lockt);	
	scanf("%d",&a);
	if(a==1)
	{
		s2[0]=assign(0,2);
	}
	else{ if(a==2)
		{
			s2[1]=assign(1,2);
		}
		else{ if(a==3)
			{
				s2[2]=assign(2,2);
			}
		    else
			{
			printf("A student isn't configured to contain this.\n");
			}
		  }
	}
	pthread_mutex_unlock(&lockt);
}
int checking(int a,int b)											//Function that determines the items with student
{   	int c=0;
	if (a==1 && b==2 || a==2 && b==1)
		{ 										
			c=3;
		}
	else{ if (a==1 && b==3 || a==3 && b==1)
		{
			c=2;
		}
		else{ if (a==2 && b==3 || a==3 && b==2)
			{
				c=1;
			}
			else
			{
				printf("\nPlease check your input; Your input might be wrong or You have entered the same resources twice which will yield no result\n");
				exit1();
			}
		   }
	}
	return c;
}
void checking1(int c)												//Function that completes a student process accordingly
{
if(s0[c-1]==1)
		{		
		 	printf("******1st Student has the last item, he completes the task and reports to teacher******\n\n");
			sleep(1.5);
		}
		else{ if(s1[c-1]==1)
		{
			printf("******2nd Student has the last item, he completes the task and reports to teacher******\n");
			sleep(1.5);
		}
		else{ if(s2[c-1]==1)
		{
			printf("******3rd Student has the last item, he completes the task and reports to teacher******\n");
			sleep(1.5);
		}
		else { printf("\nStudent having the coreesponding last item has either completed his task\n");}}}return;
}
void *table()												//Function that determine the exam hall,teacher and students
{
	int i,a,b,c,d,e,f;
		pthread_mutex_lock(&lockt);		
		a=1,b=2;
		printf("\n______Teacher places Pen and Paper on the shared table______\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
		pthread_mutex_lock(&lockt);		
		a=2,b=3;
		printf("\n______Teacher places Question Paper and Paper on the shared table______\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
		pthread_mutex_lock(&lockt);		
		a=1,b=3;
		printf("\n______Teacher places Pen and Question Paper on the shared table______\n");
		sleep(2);
		c=checking(a,b);
		checking1(c);
		pthread_mutex_unlock(&lockt);
}

void main()															//MAIN
{
	int a;pthread_t Std0;
	pthread_t Std1;
	pthread_t Std2;
	pthread_t Tea1;
	printf("***********************#  OS SIMULATION #***************************\n");
	system("clear");	
printf("The following simulation involves TWO scenes.\nSCENE 1:At Exam Hall \nSCENE 2:At Library\nSCENE 3:There is an optimised solution implemented for the SCENE 2 which is practically ideal..... \n  Please proceed accordingly by choosing one :-   ");
	scanf("%d",&a);
switch(a)
{
	case 1:
		printf("\nScene Illustration: \nThere are 3 studentprocesses and 1 teaher process. Students are supposed to do their assignments and they need 3 things for that- pen,paper and question paper. The teacher has an infinite supply of all the three things. One student has pen, another has paper and another has question paper. The teacher places two things on a shared table and the student having the third complementary thing makes the assignment and tells the teacher on completion. The teacher then places two things out of three and again the student having the third thing makes the assignment and tells the teacher on completion. This cycle continues.\n\n");
		pthread_create(&Std0,NULL,student0,NULL);
		pthread_join(Std0,NULL);
		pthread_create(&Std1,NULL,student1,NULL);
		pthread_join(Std1,NULL);	
		pthread_create(&Std2,NULL,student2,NULL);
		pthread_join(Std2,NULL);
		pthread_create(&Tea1,NULL,table,NULL);
		pthread_join(Tea1,NULL);
		printf("\n\nScene 1 at Exam Hall is complete\n");
		int a;
		printf("\nHit 0 to enter other scene, else any to exit :  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
	case 2:
		{printf("\nScene Illustration: \nTwo types of people can enter into a library-students and teachers. After entering the library, the visitor searches for the required books and get them. In ordr to get them issued, he goes to the single CPU which is there to process the issuing of books. Two types of queues are there at the counter-one for students and one for teachers.A student goes and stands at the tail of the queue for students and simliarly the teacher goes and stands at the tail of the queue for teaches (FIFO).If a student is being served and a teacher arrives at the counter, he would be the next person to get service (PRIORITY - non preemtive). If two teachers arrive at the same time, they will stand in their queue to get service (FIFO).\n\n");
		int p[30],pr[30],bt[30],temp,max,wt[30],ta[30],sum=0,i,j,n;
		int c=0,d=0;
		wt[0]=0;
		printf("Enter the number of persons=");
		scanf("%d",&n);
		printf("Enter the value 0 for teacher and 1 for student\n");
		for(i=0;i<n;i++)
		{													//Assign
			p[i]=i+1;
			bt[i]=1;
			printf("Who arrived %d? =",i+1);
			scanf("%d",&pr[i]);
		}
		for(i=0;i<n;i++)
		{													//Priority Queue sorting done here
		   	max=i;
			for(j=i+1;j<n;j++)
			{
				if(pr[j] <pr[max])
				max=j;
			}
			temp=pr[max];
			pr[max]=pr[i];
			pr[i]=temp;
			temp=bt[max];
			bt[max]=bt[i];
			bt[i]=temp;
			temp=p[max];
			p[max]=p[i];
			p[i]=temp;
		}

		for(i=0;i<n;i++)
		{     													//Calculate
			wt[i+1]=bt[i]+wt[i];
			ta[i]=bt[i]+wt[i];
			sum+=ta[i];
		}
		for(i=0;i<n;i++)
		{													//Output
			printf("\nWaiting time for %d person is =%d",p[i],wt[i]);
			//printf("\t turn around time for %d person=%d",p[i],ta[i]);
		}
		//printf("\n\naverage turn around=%d",sum/n);
		printf("\n\nScene 2 at Library is complete\n");
		int a;
		printf("\nHit 0 to enter other scene, else any to exit :  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
		}
	case 3:
		{printf("\nScene Illustration:\nIf two teachers arrive at the same time, they will stand in their queue to get service (FIFO).\n If a teacher is being served and during the period when he is being served, another teacher comes, then that teacher would get the service next. This process might continue leading to increase in waiting time of students and the program times to minimise this.\n\n");
		int p[30],pr[30],bt[30],temp,max,wt[30],ta[30],sum=0,i,j,n;
		int c=0,d=0;
		wt[0]=0;
		printf("Enter the number of persons=");
		scanf("%d",&n);
		printf("Enter the value 0 for teacher and 1 for student\n");
		for(i=0;i<n;i++)
		{
			p[i]=i+1;
			bt[i]=1;
			printf("\t Who arrived %d? =",i+1);
			scanf("%d",&pr[i]);
			if(pr[i]==0)
			{												//Assign with ageing conditions
				c=c+1;
				//printf("%d",c);
			}
			if(pr[i]==0 && d==1)
			{
				//printf("inside");
				pr[i]=pr[i]+1;//printf("\t%d",pr[i]);
				d=0;
			}
			if(c==3)
			{
				c=0;
				d=1;
				continue;
			}
		}
		for(i=0;i<n;i++)
		{													//Priority Queue sorting done here
	   		max=i;
			for(j=i+1;j<n;j++)
			{
				if(pr[j] <pr[max])
				max=j;
			}
			temp=pr[max];
			pr[max]=pr[i];
			pr[i]=temp;
			temp=bt[max];
			bt[max]=bt[i];
			bt[i]=temp;
			temp=p[max];
			p[max]=p[i];
			p[i]=temp;
		}

		for(i=0;i<n;i++)
		{     															//Calculate
			wt[i+1]=bt[i]+wt[i];
			ta[i]=bt[i]+wt[i];
			sum+=ta[i];
		}
		for(i=0;i<n;i++)
		{															//Output
			printf("\nWaiting time for person %d is =%d",p[i],wt[i]);
			//printf("\t turn around time for p[%d]=%d",p[i],ta[i]);
		}
		//printf("\n\naverage turn around=%d",sum/n);
		printf("\n\nScene 3 at Library is complete\n");		
		int a;
		printf("\nHit 0 to enter other scene, else any:  ");
		scanf("%d",&a);
		if (a==0)
		{
			main();
		}
		else {exit1();}
		break;
	}

default:
	printf("Scene doesn't match any of the listed, Have a Good Day!");exit1();
}
}

