#include<stdio.h>
#define LARGE (2100000000)
struct node
{
	int d[8][8];
};
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}
int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
void read(FILE*fp,struct node*a)
{
	char c;
	int f1;
	int f2;
	for(f1=0;f1<8;f1++)
		for(f2=0;f2<8;f2++)
		{
			do
				c=fgetc(fp);
			while((c!='0')&&(c!='1')&&(c!=' '));
			if(c==' ')
				a->d[f1][f2]=-1;
			else
				a->d[f1][f2]=c-'0';
		}
	return;
}
int check(struct node*a,struct node*b,int x,int y,int d)
{
	int ret;
	int f1;
	int f2;
	if((x<0)||(x>=8)||(y<0)||(y>=8)||(a->d[x][y]!=-1))
		return 0;
	ret=0;
	*b=*a;
	b->d[x][y]=d;
	if((x>=2)&&(b->d[x-1][y]==(d^1)))
		for(f1=2;(x-f1>=0)&&(b->d[x-f1][y]!=-1);f1++)
			if(b->d[x-f1][y]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x-f2][y]=d;
				break;
			}
	if((x<6)&&(b->d[x+1][y]==(d^1)))
		for(f1=2;(x+f1<8)&&(b->d[x+f1][y]!=-1);f1++)
			if(b->d[x+f1][y]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x+f2][y]=d;
				break;
			}
	if((y>=2)&&(b->d[x][y-1]==(d^1)))
		for(f1=2;(y-f1>=0)&&(b->d[x][y-f1]!=-1);f1++)
			if(b->d[x][y-f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x][y-f2]=d;
				break;
			}
	if((y<6)&&(b->d[x][y+1]==(d^1)))
		for(f1=2;(y+f1<8)&&(b->d[x][y+f1]!=-1);f1++)
			if(b->d[x][y+f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x][y+f2]=d;
				break;
			}
	if((x>=2)&&(y>=2)&&(b->d[x-1][y-1]==(d^1)))
		for(f1=2;(x-f1>=0)&&(y-f1>=0)&&(b->d[x-f1][y-f1]!=-1);f1++)
			if(b->d[x-f1][y-f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x-f2][y-f2]=d;
				break;
			}
	if((x>=2)&&(y<6)&&(b->d[x-1][y+1]==(d^1)))
		for(f1=2;(x-f1>=0)&&(y+f1<8)&&(b->d[x-f1][y+f1]!=-1);f1++)
			if(b->d[x-f1][y+f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x-f2][y+f2]=d;
				break;
			}
	if((x<6)&&(y>=2)&&(b->d[x+1][y-1]==(d^1)))
		for(f1=2;(x+f1<8)&&(y-f1>=0)&&(b->d[x+f1][y-f1]!=-1);f1++)
			if(b->d[x+f1][y-f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x+f2][y-f2]=d;
				break;
			}
	if((x<6)&&(y<6)&&(b->d[x+1][y+1]==(d^1)))
		for(f1=2;(x+f1<8)&&(y+f1<8)&&(b->d[x+f1][y+f1]!=-1);f1++)
			if(b->d[x+f1][y+f1]==d)
			{
				ret=1;
				for(f2=1;f2<f1;f2++)
					b->d[x+f2][y+f2]=d;
				break;
			}
	return ret;
}
int maxmin(struct node*a,int d,int f)
{
	struct node b;
	int flag;
	int ret;
	int f1;
	int f2;
	flag=0;
	if(d==0)
		ret=-LARGE;
	else
		ret=LARGE;
	for(f1=0;f1<8;f1++)
		for(f2=0;f2<8;f2++)
			if((a->d[f1][f2]==-1)&&check(a,&b,f1,f2,d))
			{
				flag=1;
				if(d==0)
					ret=max(ret,maxmin(&b,d^1,0));
				else
					ret=min(ret,maxmin(&b,d^1,0));
			}
	if(flag)
		return ret;
	if(!f)
		return maxmin(a,d^1,1);
	ret=0;
	for(f1=0;f1<8;f1++)
		for(f2=0;f2<8;f2++)
		{
			if(a->d[f1][f2]==0)
				ret++;
			if(a->d[f1][f2]==1)
				ret--;
		}
	return ret;
}
int main()
{
	struct node a;
	int d;
	scanf("%d",&d);
	read(stdin,&a);
	printf("%d\n",maxmin(&a,d,0));
}
