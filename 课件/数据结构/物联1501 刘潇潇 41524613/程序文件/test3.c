#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct node
{
	char data;
	struct node *next;

}Qnode,*Qlink;

typedef struct
{
	Qlink front,rear;
}linkqueue;

void Createqueue(linkqueue *q);		//创建空队列
int Emptyqueue(linkqueue *q);
void Enqueue(linkqueue *q,char e);
char Dequeue(linkqueue *q); 

void main(){
	char x,data,judge;
	linkqueue q;
	Createqueue(&q);
	printf("请输入字符：\n输入的字符为’0’时，执行出队操作并将出队元素打印到屏幕上；\n当输入的字符为’@’时，队列中剩余所有元素依次出队并打印到屏幕上；\n当输入其他字符时，字符入队\n");
	
	while(1){
	
		fflush(stdin);
		x=getche();				
		if(x=='0'){
			if(Emptyqueue(&q))
				printf("\n队列已空\n");
			else{
				data=Dequeue(&q);
				printf("\n出队一个元素%c\n",data);
			}
		}
		else if(x=='@'){
			if(Emptyqueue(&q))
				printf("\n队列已空\n");
			else{
				printf("\n出队所有元素:");
				while(!Emptyqueue(&q)){
					data=Dequeue(&q);
					printf("%c",data);
				}
			}
			printf("\n停止按N,按其余任意键继续\n");
			fflush(stdin);
			judge=getch();
			if(judge=='N'||judge=='n')
				break;
			else 
			{
				printf("请继续输入：");
				continue;
			}

		}else
				Enqueue(&q,x);
	}


}

void Createqueue(linkqueue *q){
	q->front=(Qlink)malloc(sizeof(Qnode));
	q->front->next=NULL;
	q->rear=q->front;
}

int Emptyqueue(linkqueue *q){
	if(q->front==q->rear)	return(1);
	else	return(0);
}

void Enqueue(linkqueue *q,char e){
	Qlink p;
	p=(Qlink)malloc(sizeof(Qnode));
	p->data=e;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}

char Dequeue(linkqueue *q){

	Qlink p;
	if(Emptyqueue(q))	return(0);
	else
	{
		p=q->front;
		q->front=p->next;
		free(p);
		return(q->front->data);

	}
}