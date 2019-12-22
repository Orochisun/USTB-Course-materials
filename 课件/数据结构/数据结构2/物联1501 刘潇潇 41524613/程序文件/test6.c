#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>		
# include <windows.h>
# include <time.h>
//采用平衡二叉排序树
typedef struct Bnode{

	int tag;
	int BF;
	char word[30];
	struct Bnode *Lchild,*Rchild;

}Btnode,*BTptr;

typedef struct Bnode1{

	int tag;
	char word[30];
	
}Btnode1,*BTptr1;

typedef struct snode{

	BTptr node;
	struct snode *next;

}slinknode,*slink;

typedef struct node{
	int tag;
	char word[30];
	struct node *next;
}linknode,*link;

//主要操作
void read(BTptr *bt);
void Input(BTptr *bt);
void Output(BTptr Bt);
void extra(BTptr *bt);
void write(BTptr bt);

//二叉树操作
void BSTinsert(BTptr *T,BTptr *s);		//二叉排序树结点插入(平衡二叉排序树)
BTptr LL(BTptr a);
BTptr RR(BTptr a);
BTptr LR(BTptr a);
BTptr RL(BTptr a);
void Inorder(BTptr T);					//二叉树中序遍历输出前十个
void oneorder(BTptr T);					//二叉树中序遍历输出特定单词次数

//栈的操作

int Emptystack(slink s);         //检测zhan空
BTptr Pop(slink *top);			//出栈 
void Push(slink *top,BTptr e);		//进栈
BTptr Gettop(slink s);			//取栈顶元素

//全局变量
FILE *fps=NULL;					//文件结果写入、读出
int a=0;
char judge='Y';
long op,ed,s;
void main(){

	BTptr Bt;
	
	while(judge!='N'&&judge!='n'){
		Bt=NULL;
		if(judge=='Y')	
			
		read(&Bt);
		
		else	{
			
		Input(&Bt);
		//ed=clock();s=ed-op;
		//printf("%ldms\n",s);
			
		}
	
		Output(Bt);

		
	}
}

void read(BTptr *bt){

	char c[300]={0},a;
	int j=0;	
	BTptr1 q;
	q=(BTptr1)malloc(sizeof(Btnode1));
	fps=fopen("F:\\数据结构与算法\\第六题结果.txt","r");
	printf("查询上次统计结果:\n");
	fread(q, sizeof(Btnode1),1,fps);
	while(!feof(fps)){

		BTptr Bt;
		Bt=(BTptr)malloc(sizeof(Btnode));
		Bt->BF=0;
		Bt->tag=q->tag;
		strcpy(Bt->word,q->word);
		Bt->Lchild=Bt->Rchild=NULL;
		BSTinsert(bt,&Bt);				//构造平衡二叉排序树

		fread(q, sizeof(Btnode1),1,fps);
	}

	fclose(fps);	
	
}

void Input(BTptr *bt){
	char test[30]; 
	int num=0;
	int i,j=0;
	int a=1;
	FILE *fp=NULL;
	char fname[1000];
	printf("请输入统计的文件个数：");
	fflush(stdin);
	scanf("%d",&num);
	while(num<1){
		printf("请输入合适的文件数:");
		fflush(stdin);
		scanf("%d",&num);
	}

	for(i=0;i<num;i++){
		printf("请输入要打开的文件名：");
		scanf("%s",fname);
		//op=clock();
		if((fp=fopen(fname,"r"))!=NULL){

			while(a!=EOF)
			{
				
				//单词字符定义为大小写字母、数字和下划线，其他字符均看作单词分隔符；
				j=0;
				a=(test[j]=fgetc(fp));
				while(test[j]=='_'||(test[j]>='A'&&test[j]<='Z')||(test[j]>='a'&&test[j]<='z')||(test[j]>='0'&&test[j]<='9'))
				{
					j++;
					a=(test[j]=fgetc(fp));
				}
				test[j]='\0';

				if(test[0]!='\0')
				{
					BTptr p;
					p=(BTptr)malloc(sizeof(Btnode));
					p->tag=1;strcpy(p->word,test);
					p->BF=0;p->Lchild=p->Rchild=NULL;
					BSTinsert(bt,&p);				//构造平衡二叉排序树
				}

			}
			fclose(fp);
		}else
		{
			printf("找不到这个文件，请输入下一个文件：\n");

		}
	}

}

void extra(BTptr *bt){

	printf("追加统计\n");
	Input(bt);
	Output(*bt);

}

void write(BTptr bt){

	BTptr p;
	BTptr1 q;
	slink s;
	
	s=NULL;
	p=bt;
	q=(BTptr1)malloc(sizeof(Btnode1));

	fps=fopen("F:\\数据结构与算法\\第六题结果.txt","w");//1.以w模式打开文件a.txt，即写模式打开，会清除文件的所有内容

		while(1){
		while(p){
			Push(&s,p);
			p=p->Lchild;
		}
		if(Emptystack(s))
		{
			//printf("找不到这个单词\n");
			break;
		}
		p=Pop(&s);
		q->tag=p->tag;
		strcpy(q->word,p->word);
		fwrite(q, sizeof(Btnode1),1,fps);
		p=p->Rchild;	
	}
	fclose(fps);//2.关闭文件，成了
}

void Output(BTptr Bt){
	BTptr p;
	p=Bt;
	printf("1 输出出现次数最多的前10个单词及其出现次数\n2 查找某单词出现次数\n3 追加统计\n4 重新初始化\n5 结束查找\n");
	while(1){
		fflush(stdin);
		scanf("%d",&a);
		while(a!=1&&a!=2&&a!=3&&a!=4&&a!=5){
			printf("没有这个选项，重新键入1~4：\n");
			fflush(stdin);
			scanf("%d",&a);
		}
		switch (a)
		{
		case 1 :Inorder(p);break;
		case 2 :oneorder(p);break;
		case 3 :extra(&p);break;
		}
		if(a==4){
			fps=fopen("F:\\数据结构与算法\\第六题结果.txt","w");//1.以w模式打开文件a.txt，即写模式打开，会清除文件的所有内容
			fclose(fps);//2.关闭文件，成了
			judge='c';
			break;
		}
		if(a==5){

			write(Bt);
			judge='N';
			break;
		}

	}

}

//二叉树部分



//输出前十个
void Inorder(BTptr T){
	BTptr p;
	slink s;
	link ten,head,r;
	int i;
	s=NULL;
	//fps=fopen("F:\\数据结构与算法\\第六题结果.txt","r+");
	head=(link)malloc(sizeof(linknode));
	ten=(link)malloc(sizeof(linknode));
	ten->tag=0;
	ten->word[0]='\0';
	ten->next=NULL;
	head->next=ten;
	p=T;

	while(1){
		while(p){
			Push(&s,p);
			p=p->Lchild;
		}
		if(Emptystack(s))
			break;
		p=Pop(&s);
		//大的在前面，依次插入记录，取前十个。
		r=head;
		for(i=0;i<9;i++){

			if(p->tag>=(r->next)->tag)
			{
				link q;
				q=(link)malloc(sizeof(linknode));
				q->tag=p->tag;
				strcpy(q->word,p->word);
				q->next=r->next;
				r->next=q;
				break;
			}else
				r=r->next;

		}

		p=p->Rchild;	
	}
	//输出部分、写入文件
	r=head->next;
	if(r->tag==0)
		printf("这是一个空文档\n");
	else{
			printf("所有文件中单词出现前十的依次为：\n");	
	for(i=1;i<11;i++){
		printf("%d\t出现次数：%d\t单词%s\n",i,r->tag,r->word);
		r=r->next;
		if(r->tag==0)	break;
		if(r==NULL) break;
	}
	}
		

}

//查找特定单词次数
void oneorder(BTptr T){

	BTptr p;
	slink s;
	char a[30];
	int i;
	s=NULL;
	p=T;
	//fps=fopen("F:\\数据结构与算法\\第六题结果.txt","r+");
	printf("请输入需要查找的单词：\n");
	fflush(stdin);
	gets(a);
	while(1){
		while(p){
			Push(&s,p);
			p=p->Lchild;
		}
		if(Emptystack(s))
		{
			printf("找不到这个单词\n");
			break;
		}
		p=Pop(&s);
		if((strcmp(p->word,a))==0)
		{
			printf("单词 %s 出现次数为 %d\n",a,p->tag);
			break;
		}
		p=p->Rchild;	
	}	
		
}

//栈部分

int Emptystack(slink s){

	if(s==NULL) return(1);
	else return(0);

}


BTptr Pop(slink *top){
	slink q=NULL;
	if(Emptystack(*top)) return(0);
	else{
		q=*top;
		*top=(*top)->next;
		return(q->node);       //返回栈中的树节点
	}
}




void Push(slink *top,BTptr e){
	slink p;
	p=(slink)malloc(sizeof(slinknode));
	p->node=e;
	p->next=*top;
	*top=p;
}


BTptr Gettop(slink s){
	if(s!=NULL) return(s->node);
	return(0);
}


//平衡二叉树节点插入
//T、s分别是根节点和待插入的节点指针；p为主要活动指针，sa指向可能不平衡的子树，q、f分别指向p、sa的父节点
void BSTinsert(BTptr *T,BTptr *s)
{
	BTptr p=NULL,q=NULL,sa=NULL,f=NULL;
	int d;
	if(*T==NULL){ *T=*s;return;}			//空树时，s作为根节点
	
	sa=p=*T;
	while(p!=NULL){
	
		d=strcmp((*s)->word,p->word);
		if(d==0)	{(p->tag)++;	return;}	//记录存在
		//记下离s最近的BF！=0的节点sa与其父f
		if(p->BF!=0)	{sa=p;f=q; }
		q=p;						//记下当前p为q
		if(d<0) p=p->Lchild;		//走向合适的子树
		else p=p->Rchild;

	}

	if(d<0) q->Lchild=*s;
	else	q->Rchild=*s;
	if(strcmp((*s)->word,sa->word)<0)
	{
		p=sa->Lchild;
		q=p;
		sa->BF+=1;
	}
	else
	{
		p=sa->Rchild;
		q=p;
		sa->BF-=1;
	}
	while(p!=*s)
		if(strcmp((*s)->word,p->word)<0)			//可能有错
		{
			p->BF=1;
			p=p->Lchild;
		}else
		{
			p->BF=-1;
			p=p->Rchild;
		}
		switch(sa->BF)
		{
		case 2:
			switch(q->BF)
			{
			case 1:p=LL(sa);break;
			case -1:p=LR(sa);break;

			}
			//用返回的新节点取代原sa
			if(f==NULL)	*T=p;
			else if(f->Lchild==sa)	f->Lchild=p;
			else f->Rchild=p;
			break;
		case -2:
			switch(q->BF)
			{
			case -1:p=RR(sa);break;
			case 1:p=RL(sa);break;

			}
			if(f==NULL) *T=p;
			else if(f->Lchild==sa)	f->Lchild=p;
			else f->Rchild=p;
			break;
		}
	
		
}

BTptr LL(BTptr a)
{
	BTptr b=a->Lchild;
	a->Lchild=b->Rchild;
	b->Rchild=a;
	b->BF=a->BF=0;
	return(b);
}
BTptr RR(BTptr a)
{
	BTptr b=a->Rchild;
	a->Rchild=b->Lchild;
	b->Lchild=a;
	b->BF=a->BF=0;
	return(b);
}
BTptr LR(BTptr a)
{
	BTptr b=a->Lchild,c=b->Rchild;
	a->Lchild=c->Rchild;
	b->Rchild=c->Lchild;
	c->Lchild=b;
	c->Rchild=a;
	switch(c->BF)
	{
	case 1:a->BF=-1;b->BF=0;break;
	case -1:a->BF=0;b->BF=-1;break;
	case 0:a->BF=b->BF=0;break;
	}
	c->BF=0;
	return(c);
}
BTptr RL(BTptr a)
{
	BTptr b=a->Rchild,c=b->Lchild;
	a->Rchild=c->Lchild;
	b->Lchild=c->Rchild;
	c->Lchild=a;
	c->Rchild=b;
	switch(c->BF)
	{
	case 1:a->BF=0;b->BF=-1;break;
	case -1:a->BF=-1;b->BF=0;break;
	case 0:a->BF=b->BF=0;break;
	
	}
	c->BF=0;return(c);
}