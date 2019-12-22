#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct Anode{
	int tail,head;
	struct Anode *hlink,*tlink;
}arcnode;

typedef struct Vnode
{
	char data;
	arcnode *fin,*fout;
}vexnode;

typedef struct node{
	int k;
	struct node *next;
}slinknode,*slink;


int createorlist(vexnode G[]);					//建立十字链表
void Creatid(vexnode G[],int n,int id[]);		//求十字链表各顶点入读
int locatevex(vexnode* G,char u,int n);				//求顶点的序号
void Topsort(vexnode G[],int n);
int Emptystack(slink s);         //检测zhan空
int Pop(slink *top);			//出栈 
void Push(slink *top,int e);		//jinzhan
int Gettop(slink s);			//取栈顶元素

void main(){

	char judge;
	int n;
	judge='Y';

	while(judge=='Y'||judge=='y'){

		vexnode G[100];
		n=createorlist(G);
		Topsort(G,n);
		printf("继续按Y，停止按N\n");
		judge=getch();
		while(judge!='Y'&&judge!='y'&&judge!='N'&judge!='n'){
			printf("没有这个选项！重新选择 Y or N\n");
			judge=getch();
		}
	}


}
int createorlist(vexnode G[])
{

	int i,j,n,K,l;
	arcnode *p;
	char ch,u,v,k;
	k=0;
	u=0;
	K=i=n=j=0;

	printf("按W从键盘输入表达式，按F从文件读入表达式\n");
	while(k==0){
		fflush(stdin);
		k=getch();

		if(k=='W'||k=='w')
		{
			printf("输入顶点，以#结束\n");
			ch=getche();
			while(ch!='#')
			{
				for(l=0;l<i;l++){
					if(G[l].data==ch)
						break;
				}
				if(l==i){
					G[i].data=ch;
					G[i].fin=G[i].fout=NULL;
					i++;
				}else
					printf("输入顶点重复，请重新输入：");
				ch=getche();
			}
			n=i;
			printf("输入弧的头尾节点,空格隔开两个弧，以#结束\n");
			fflush(stdin);
			while(1)
			{
				K++;
				printf("\ntail%d=",K);
				u=getche();
				if(u=='#')
					break;
				i=locatevex(G,u,n);			//	求顶点u、v的序号

				while(i==-1){

					printf("不存在这个顶点，重新输入顶点\t");
					printf("tail%d=",K);
					u=getche();
					i=locatevex(G,u,n);
				}
				printf(" head%d=",K);
				v=getche();
				j=locatevex(G,v,n);	
				while(j==-1){

					printf("不存在这个顶点，重新输入顶点\t");
					printf("head%d=",K);
					v=getche();
					j=locatevex(G,v,n);	
				}
				p=(arcnode*)malloc(sizeof(arcnode));			//申请弧节点
				p->tail=i;
				p->head=j;
				p->hlink=G[i].fin;
				G[j].fin=p;
				p->tlink=G[i].fout;
				G[i].fout=p;
				//scanf("%c %c",&u,&v);							//输入下一条弧


				//printf("%c",u);
			}
		}else if(k=='F'||k=='f')

		{
			int m=0;

			//char c[100];

			//E:\刘潇潇\学习和比赛资料\学习资料\数据结构\第五题.txt
			FILE *fp=NULL;
			FILE *fpp=NULL;
			char fname[1000];
			j=0;
			printf("请输入顶点文件名：");
			scanf("%s",fname);
			if((fp=fopen(fname,"r"))!=NULL){
				while((G[i].data=fgetc(fp))!=EOF)
				{
					//n++;
					//fscanf(fp,"%c",&G[i].data);
					printf("%c",G[i].data);
					//G[i].data=ch;
					G[i].fin=G[i].fout=NULL;
					i++;
				}
				n=i;
				fclose(fp);
			}else
			{printf("找不到顶点文件，重新选择 W or  F\n");
			k=0;
			}

			printf("\n请输入弧线文件名：");
			scanf("%s",fname);
			if((fpp=fopen(fname,"r"))!=NULL){
				while(1)
				{
					if(m!=0)
						printf("tail%d=%c head%d=%c\n",m,u,m,v);
					m++;
					u=fgetc(fpp);
					v=fgetc(fpp);
					if(u==EOF||v==EOF)
						break;
					i=locatevex(G,u,n);
					j=locatevex(G,v,n);
					//fscanf(fp,"%c",G[i].data);				
					p=(arcnode*)malloc(sizeof(arcnode));			//申请弧节点
					p->tail=i;
					p->head=j;
					p->hlink=G[i].fin;
					G[j].fin=p;
					p->tlink=G[i].fout;
					G[i].fout=p;			
				}
				fclose(fpp);
			}else
			{printf("找不到弧线文件，重新选择 W or  F\n");
			k=0;
			}
		}else
		{
			printf("没有这个选项，重新选择 W or  F\n");
			k=0;
		}
	}

	return (n);

}

void Creatid(vexnode G[],int n,int id[])
{
	int count,i;
	arcnode *p;
	for(i=0;i<n;i++)
	{
		count=0;
		p=G[i].fin;
		while(p)
		{
			count++;
			p=p->hlink;
		}
		id[i]=count;			
	}
}

void Topsort(vexnode G[],int n)			//对网G进行拓扑排序
{
	int i,j,k,count,id[100];
	//slink s;
	arcnode *p;
	Creatid(G,n,id);		//建立G的入度表id
	Clearstack(s); //s=NULL;
	for(i=0;i<n;i++)
		if(id[i]==0)
			Push(s,i);//Push(&s,i);
	count=0;				//输出顶点计数
	while(!Emptystack(s))
	{
		j=Pop(s);//j=Pop(&s);
		//printf("%c ",G[j].data);
		output(j,G[j].data);
		count++;
		p=G[j].fout;
		while(p)
		{
			k=p->head;
			id[k]--;
			if(id[k]==0)
				Push(&s,k);
			p=p->tlink;
		}
	}

	if(count==n){

		printf("\n网中没有环，拓扑排序为：\n");
		s=NULL;
		for(i=0;i<n;i++)
			if(id[i]==0)
				Push(&s,i);
		count=0;				//输出顶点计数
		while(!Emptystack(s))
		{
			j=Pop(&s);
			printf("%c ",G[j].data);
			count++;
			p=G[j].fout;
			while(p)
			{
				k=p->head;
				id[k]--;
				if(id[k]==0)
					Push(&s,k);
				p=p->tlink;
			}
		}

	}
	else
		printf("\n网中有环\n");

}

int locatevex(vexnode* G,char u,int n)
{
	int i=0;

	while(i<=n){
		if(u==G[i].data)
		{	break;}
		i++;	
	}
	if(i>n)	return(-1);
	return i;
}

int Emptystack(slink s)         //检测zhan空
{
	if(s==NULL) return(1);
	else return (0);

}

int Pop(slink *top)			//出栈 
{
	slink p;
	if(Emptystack(*top))  return (-1);
	p=(slink)malloc(sizeof(slinknode));
	p=*top;
	(*top)=(*top)->next;
	return(p->k);

}
void Push(slink *top,int e)		//jinzhan
{
	slink p;
	p=(slink)malloc(sizeof(slinknode));
	p->k=e;
	p->next=(*top);
	(*top)=p;

}
int Gettop(slink s)			//取栈顶元素
{
	if(Emptystack(s))  return (-1);
	else	return(s->k);

}