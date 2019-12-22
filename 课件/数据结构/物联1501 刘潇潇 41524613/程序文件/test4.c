#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Bnode
{
	char res[30];
	struct Bnode *Lchild,*Rchild;

}Btnode,*BTptr;

typedef struct node
{
	BTptr zhan;

	struct node *next;

}linknode,*link;

int j;

BTptr CreateLBtree();			//创建二叉树
void Tinsert(BTptr* BT,char* P);		//采用非递归遍历模式
int Emptystack(link s);         //检测zhan空
BTptr Pop(link *top);			//出栈 
void Push(link *top,BTptr e);		//jinzhan
BTptr Gettop(link s);			//取栈顶元素
void Inorder(BTptr T);								//中序遍历

main(){
	BTptr BT;	
	char k='Y';
	while(k=='y'||k=='Y'){
		BT=CreateLBtree();
		printf("按字典顺序排序输出：\n");
		Inorder(BT);
		printf("\n按Y继续，其他键退出\n");
		fflush(stdin);
		k=_getch();
	}
}

BTptr CreateLBtree(){
	char k,c[50][30],a,d[30];
	int i=0;
	BTptr bt;
	j=0;
	k=0;
	bt=(BTptr)malloc(sizeof(Btnode));	
	bt->Lchild=bt->Rchild=NULL;
	printf("按W从键盘输入，F从文件读入\n");
	while(k==0){
	fflush(stdin);
	k=getch();
	if(k=='W'||k=='w')
	{
		printf("请输入：（空格隔开，按回车结束,无效的字符自动忽略）\n");

		i=0;
		a=0;
		fflush(stdin);

		while(1){			
			i=0;
			a=0;
			while(a!=' '&&a!='\n')
			{
				c[j][i]=getchar();
				a=c[j][i];
				if((a>='A'&&a<='Z')||(a>='a'&&a<='z'))
					i++;
			}
			c[j][i]='\0';		
			if(j==0){
				strcpy(bt->res,c[0]);
				j++;
			}else{
				Tinsert(&bt,c[j]);
			}
			if(a=='\n')
				break;
		}
	}
	else if(k=='F'||k=='f')
	{

		FILE *fp=NULL;
		char fname[1000];
		printf("请输入要打开的文件名：");
		scanf_s("%s",fname);
		//F:\\数据结构与算法\\第四题.txt
		if((fp=fopen(fname,"r"))!=NULL){
		while(!feof(fp))
		{
			fscanf(fp,"%s",c[j]);
			printf("%s ",c[j]);

			if(j==0){
				strcpy(bt->res,c[0]);
				j++;
			}else{
				Tinsert(&bt,c[j]);
			}

		}
		fclose(fp);
		}else
		{printf("找不到这个文件，重新选择 W or  F\n");
		k=0;
		}
	}else
	{
		printf("没有这个选项，重新选择 W or  F\n");
		k=0;
	}
	}
	return(bt);
}



void Tinsert(BTptr *BT,char* P){			//插入节点
	BTptr p,q,R,w;
	link s;
	s=NULL;
	w=NULL;
	p=*BT;
	while(1){
		while(*BT){
			Push(&s,*BT);
			*BT=(*BT)->Lchild;
		}	
		if(Emptystack(s))
			break;
		(*BT)=Pop(&s);
		if(strcmp((P),((*BT)->res))<0)
		{
			R=(BTptr)malloc(sizeof(Btnode));
			strcpy(R->res,P);
			R->Lchild=R->Rchild=NULL;
			q=(*BT)->Lchild;
			(*BT)->Lchild=R;
			R->Lchild=q;
			j++;
			(*BT)=p;
			Push(&s,R);
			break;
		}					//插到p的左子
		else if(strcmp((P),((*BT)->res))==0)
		{
			R=(BTptr)malloc(sizeof(Btnode));
			strcpy(R->res,P);
			R->Lchild=R->Rchild=NULL;
			(*BT)=p;
			Push(&s,R);
			break;
		}
		w=(*BT);
		(*BT)=(*BT)->Rchild;

	}			
	if(Emptystack(s))
	{	
		R=(BTptr)malloc(sizeof(Btnode));
		strcpy(R->res,P);
		R->Lchild=R->Rchild=NULL;
		w->Rchild=R;	
		j++;
		(*BT)=p;
	}

}

void Inorder(BTptr T){
	BTptr p;
	link s;
	s=NULL;
	p=T;
	while(1){
		while(p){
			Push(&s,p);
			p=p->Lchild;
		}

		if(Emptystack(s))
			break;
		p=Pop(&s);
		printf("%s ",p->res);
		p=p->Rchild;	
	}
}


int Emptystack(link s){

	if(s==NULL) return(1);
	else return(0);

}


BTptr Pop(link *top){
	link q=NULL;
	if(Emptystack(*top)) return(0);
	else{
		q=*top;
		*top=(*top)->next;
		return(q->zhan);       //返回栈中的树节点
	}
}




void Push(link *top,BTptr e){
	link p;
	p=(link)malloc(sizeof(linknode));
	p->zhan=e;
	p->next=*top;
	*top=p;
}


BTptr Gettop(link s){
	if(s!=NULL) return(s->zhan);
	return(0);

}
