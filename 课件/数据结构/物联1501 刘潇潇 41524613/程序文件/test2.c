#include"stdio.h"
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct node{
	union u{
		char data;
		float data1;
	}un;
	struct node *next;
}snode,*slink;

char OPC[7]={'+','-','*','/','(',')','#'};

int Emptystack(slink s);         //检测zhan空
char Pop(slink *top);			//出栈 
float Pop1(slink *top);
void Push(slink *top,char e);		//jinzhan
void Push1(slink *top,float e);	
void Clearstack(slink *top);		//置空zhan
char Gettop(slink s);			//取栈顶元素
float Gettop1(slink s);	
int In(char s,char *OPC);
int Precede(char x,char y);      //比较优先级
int mid_post(char *post,char *mid);   //中后序转化
float postcount(char post[]);				//后缀表达式求值

void main(){
	char judge='y',k;
	char mid[1000],post[1000]; //创建数组存储中缀和后缀表达式
	int p,i,len;
	float q;

	while(1){

		if(judge=='Y'||judge=='y'){
			p=0;q=0;len=0;

			memset(mid, 0, 1000);
			memset(post, 0, 1000);

			while(p==0){
				printf("按W从键盘输入表达式，按F从文件读入表达式\n");

				do{
					fflush(stdin);
					k=getch();

					if(k=='W'||k=='w')
					{

						printf("请输入表达式：(回车结束)\n");


						fflush(stdin);
						i=0;
						do{

							mid[i]=getchar();
							i++;
						}while(mid[i-1]!='\n');
						mid[i-1]='#';
						//mid[i]='\0';


						//puts(mid);


					}
					else if(k=='F'||k=='f')
					{
						FILE *pfile=NULL;

						char fname[1000];
						printf("请输入要打开的文件名：");
						scanf("%s",fname);
						//F:\\数据结构与算法\\计算中缀表达式.txt
						if((pfile=fopen(fname,"r"))!=NULL){	
							fseek(pfile,0,SEEK_END);

							len=ftell(pfile);
							rewind(pfile);
							fread(mid,1,len,pfile);
							mid[len]='#';

						}else
						{k=0;
						printf("找不到这个文件，请重新选择W or F\n");}
					}else
					{
						k=0;
						printf("没有这个选项，请重新选择W or F\n");

					}
				}while(k==0);
				p=mid_post(post,mid);
			}


			q=postcount(post);
			if(q!=-1){
							printf("后缀表达式为\n");
			puts(post);
			printf("原表达式结果为%.2f\n继续按Y，停止按N\n",q);}
			else
				printf("表达式格式有误，请重新输入！(继续按Y，停止按N)\n");

		}
		fflush(stdin);
		judge=getch();
		if(judge=='Y'||judge=='y'){}            //大小写都可以，方便用户输入选择
		else if(judge=='N'||judge=='n'){
			break;
		}
		else{
			printf("没有这个选项，请重新选择继续（Y），停止（N）\n");

		}
	}
}

int Emptystack(slink s){

	if(s==NULL) return(1);
	else return(0);

}

int In(char s,char *OPC)
{
	int i;
	for(i=0;i<7;i++){

		if(s==OPC[i])
			return(1);

	}
	return(0);


}

char Pop(slink *top){
	char e;
	slink p;
	if(Emptystack(*top)) return(-1);
	else{
		e=(*top)->un.data;
		p=*top;*top=(*top)->next;
		free(p);return(e);
	}
}

float Pop1(slink *top){
	float e;
	slink p;
	if(Emptystack(*top)) return(-1);
	else{
		e=(*top)->un.data1;
		p=*top;*top=(*top)->next;
		free(p);return(e);
	}
}


void Push(slink *top,char e){
	slink p;
	p=(slink)malloc(sizeof(snode));
	p->un.data=e;
	p->next=*top;*top=p;


}

void Push1(slink *top,float e){
	slink p;
	p=(slink)malloc(sizeof(snode));
	p->un.data1=e;
	p->next=*top;*top=p;


}

void Clearstack(slink *top){
	slink p;
	while(*top!=NULL){
		p=(*top)->next;
		Pop(top);
		(*top)=p;
	}
}

char Gettop(slink s){
	if(s!=NULL) return(s->un.data);
	return(0);

}

float Gettop1(slink s){
	if(s!=NULL) return(s->un.data1);
	return(0);

}

int Precede(char x,char y){
	switch(x)
	{	
	case'#':x=-1;break;
	case'(': x=0;break;
	case'+': 
	case'-': x=1;break;
	case'*': 
	case'/': x=2;break;
	}

	switch(y)
	{
	case'+': 
	case'-': y=1;break;
	case'*': 
	case'/': y=2;break;
	case')': y=3;break;

	}
	if(x>y) return(1);
	else return(0);

}

int mid_post(char *post,char *mid){

	int i=0,j=0;
	char x,y;
	if(mid[0]=='#')
	{
		printf("输入为空,请重新输入\n");
		return 0;
	}else{
		slink S=NULL;
		Push(&S,'#');
		do{

			y=mid[i+1];          //用来表达式是否格式正确

			x=mid[i];

			if(In(x,OPC))
			{
				i++;
				switch(x){
				case'#':{
					while(!Emptystack(S))
						post[j++]=Pop(&S);
					//printf("\n%c",post[j]);
						}break;
				case')':
					{	if(y=='(')
					{
						printf("输入表达式非法,请重新输入\n");
						return(0);
					}
					while(Gettop(S)!='(')
						post[j++]=Pop(&S);
					Pop(&S);
					}break;
				case'+':
					if(y=='-'||y=='+'||y=='*'||y=='/'||y==')'){
						printf("输入表达式非法,请重新输入\n");
						return(0);
					}
				case'-':
					if(y=='-'||y=='+'||y=='*'||y=='/'||y==')'){
						printf("输入表达式非法,请重新输入\n");
						return(0);
					}
				case'*':
					if(y=='-'||y=='+'||y=='*'||y=='/'||y==')'){
						printf("输入表达式非法,请重新输入\n");
						return(0);
					}
				case'/':
					if(y=='-'||y=='+'||y=='*'||y=='/'||y==')'){
						printf("输入表达式非法,请重新输入\n");
						return(0);
					}
				
				case'(':
					{
						if(y=='-'||y=='+'||y=='*'||y=='/'||y==')'){
							printf("输入表达式非法,请重新输入\n");
							return(0);
						}
						while(Precede(Gettop(S),x))
							post[j++]=Pop(&S);
						Push(&S,x);
					}

				}

			}else if(mid[i]!=' '){

				while(mid[i]>='0'&&mid[i]<='9'||mid[i]=='.'){

					post[j++]=mid[i];
					i++;

				}
				post[j++]=' ';//存入一个空格
				//printf("%d",j);

			}else
				i++;
		}while(mid[i-1]!='#');

	}return(1);
}

float postcount(char post[]){
	int i=0,j,step;
	float z,a,b,sum1,sum2,sum;
	slink s=NULL;
	while(post[i]!='#'){

		if(In(post[i],OPC))
		{
			switch(post[i])
			{
			case'+':b=Pop1(&s);a=Pop1(&s);z=a+b;Push1(&s,z);break;
			case'-':b=Pop1(&s);a=Pop1(&s);z=a-b;Push1(&s,z);break;
			case'*':b=Pop1(&s);a=Pop1(&s);z=a*b;Push1(&s,z);break;
			case'/':b=Pop1(&s);a=Pop1(&s);z=a/b;Push1(&s,z);break;
			}
			i++;
			if(a==-1)
			{				
				return(-1);
			}
		
		}

		else{
			step=0;
			sum1=sum2=sum=0;
			if(post[i]!=' '){
				while(post[i]>='0'&&post[i]<='9'&&post[i]!='.'&&post[i]!=' ')
				{
					sum1=10*sum1+post[i]-'0';
					//printf("%f	",sum1);
					i++;
				}
				if(post[i]=='.'){
					i++;
					while(post[i]>='0'&&post[i]<='9'&&post[i]!=' '){
						sum2=10*sum2+post[i]-'0';
						i++;
						step++;				
					}
					for(j=0;j<step;j++){
						sum2=sum2/10;		
					}
				}

				sum=sum1+sum2;
				//printf("%f	",sum);
				Push1(&s,sum);			 //操作数直接进栈
			}else if(post[i]==' ')
				i++;


		}	
	}
	return(Gettop1(s));  //返回结果
}