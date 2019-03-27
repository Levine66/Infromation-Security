//本代码是在已知正调查分布的情况下，生成相应的负调查结果
//再用算法将负调查结果转换为正调查结果从而比较不同算法之间的准确率的实验 
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#define CN 50
int c = 5;   //选项个数 
int low[CN]; //low和up数组不包含在初赛使用范围内 
int up[CN];
int t[CN];  //正调查选人数分布 
int _t[CN];
int r[CN];  //负调查人数分布 
double t_hat[CN];  //以下三个t[]是作为算法准确率的评判标准的，不需要加入在我们的算法 
int t_pie[CN];
double t_pie2[CN];
int rand_seed;

int n = 500;
void init()
{
	c =  5;    //选项数为5 
	n = 500;   //参与者为500 
}
void caseA()  //测试数据A 
{
	t[0]=10; t[1]=25; t[2]=60; t[3]=150; t[4]=200;
	low[0]=0; low[1]=0;   low[2]=50;   low[3]=100; low[4]=250;
	up[0]=100; up[1]=200;  up[2]=300;   up[3]=400; up[4]=500;
}

void caseB() //测试数据B 
{
	low[0]=0; low[1]=0;   low[2]=0;   low[3]=100; low[4]=250;
	up[0]=50; up[1]=100;  up[2]=500;   up[3]=500; up[4]=500;
	while(true)
	{
		int tn = 0;
		int i = 0; 
		for(i=0;i<c-1;i++)
		{
			t[i] = low[i]+rand()%(up[i]-low[i]+1);
			tn+=t[i];
		}
		t[i] = n-tn;
		if((t[i]>=low[i])&&(t[i]<=up[i]))
		{
			break;
		}
	}
}
//void realD()
//{
//	t[0] = 10; t[1];
//	low[0] = 0; up[0] = 100;
//	r[0]...r[c] = ;
//}

void caseU()//uniform distribution 均匀分布 
{
	t[0]=99; t[1]=89; t[2]=103; t[3]=109; t[4]=100;// 99    89   103   109   100
	low[0]=0; low[1]=0;   low[2]=0;   low[3]=100; low[4]=0;
	up[0]=100; up[1]=500;  up[2]=500;   up[3]=500; up[4]=500;
}

void caseN()//normal distribution 正态分布
{
	t[0]=10; t[1]=102; t[2]=290; t[3]=96; t[4]=2;// 10   102   290    96     2
	low[0]=0; low[1]=0;   low[2]=250;   low[3]=0; low[4]=0;
	up[0]=20; up[1]=500;  up[2]=500;   up[3]=500; up[4]=10;
}

void caseE()//exp distribution 根据背景经验的分布
{
	t[0]=317; t[1]=130; t[2]=38; t[3]=10; t[4]=5;// 317   130    38    10     5
	low[0]=250; low[1]=0;   low[2]=0;   low[3]=0; low[4]=0;
	up[0]=500; up[1]=200;  up[2]=100;   up[3]=20; up[4]=10;
}

void caseLN()//log-normal distribution 对数正态分布 
{
	
	t[0]=5; t[1]=269; t[2]=205; t[3]=19; t[4]=2;//5   269   205    19     2
	low[0]=0; low[1]=200;   low[2]=200;   low[3]=0; low[4]=0;
	up[0]=10; up[1]=500;  up[2]=500;   up[3]=50; up[4]=10;
}

void showInfo() //打印正调查矩阵
{
	printf("\n---------------------------->  Positive Survey:  <------------------------\n");
	for(int i=0;i<c;i++) printf("%d ",t[i]);
	printf("\n");
	for(int i=0;i<c;i++) printf("[%d,%d]	",low[i],up[i]);
	printf("\n");
}

void generatePS() //生成正调查人数分布 
{
//	caseA();
//	caseB();
	showInfo();
}


void generateNS()  //生成负调查人数分布 
{
	int i;
	for(i=0;i<c;i++) r[i]=0;
	for(i=0;i<c;i++)
	{
		for(int j=0;j<t[i];j++)
		{
			int temp=rand()%(c-1);
			if(temp>=i)
			{
				r[temp+1]++;
			}
			else r[temp]++;
		}
	}
	
	printf("Negative Survey:\n");
	for(i=0;i<c;i++)
	{
		printf("%d ",r[i]);
	}
	printf("\n");
}

void NStoPS(int t[])  //第一种negative survey向正调查转换，太过简单，不考虑 
{
	for(int i=0;i<c;i++)
	{
		t[i]=n-(c-1)*r[i];
	}
	
	printf("\nNStoPS:\n");
	for(int i=0;i<c;i++)
	{
		printf("%d ",t[i]);
	}
	printf("\n");
}
/*
第二种转换方法，本cpp文件中的形参为空数组t[]，用来存储负数据(全局变量r[])转化后的正数据。
 for(int i=0;i<c;i++)
	{
		t[i]=n-(c-1)*r[i];
		flag[i]=true;
	}
这段代码用于将负数据初步转化为正数据
接下来的循环为去除数据中的错误不可用数据。
在正式的编写中，传入参数只要有负调查的人数分布，在函数内部转化为正调查的数组，并且经过错误数据的去除与数据的填写即可 
*/ 
void NStoPSII(double t[])    //第二种转换方法 
{
	bool flag[CN];
	for(int i=0;i<c;i++)
	{
		t[i]=n-(c-1)*r[i];
		flag[i]=true;
	}
	int tN=n;
	int tc=c;
	while(true)      //对于小于0的分布进行置0处理 
	{	int i;
		for(i=0;i<c;i++)
		{
			if(t[i]<0) break;
		}
		if(i==c) break;
		for(i=0;i<c;i++)
		{
			if(t[i]<0)
			{
				t[i]=0;
				flag[i]=false;
				tN=tN-r[i];
				tc=tc-1;
			}
		}
		for(i=0;i<c;i++)
		{
			if(flag[i]==true)
			{
				t[i]=tN-(tc-1)*r[i];
				t[i]=t[i]*n/tN;
			}
		}
	}
	int p = 0;
	int tn = n;
	for(int i=0;i<c;i++)    //对数据进行误差处理 
	{
		_t[i] = int(t[i]+0.5);
		if(flag[i])
		{
			p = i;
		}
		tn-=_t[i];
	}
	_t[p] += tn;

	printf("\nNStoPS-II:\n");
	for(int i=0;i<c;i++)
	{
		printf("%d ",_t[i]);
	}
	printf("\n");
}

void NStoPS_BK(double t[])  //结合了背景考虑的负调查向正调查转换方法，本次实验不考虑 
{
	bool flag[CN];
	for(int i=0;i<c;i++)
	{
		flag[i]=true;
		t[i]=n-(c-1)*r[i];
	}
	bool act=true;
	double n1=n;
	while(act)
	{
		int s=0;
		act=false;
		double n2=n1;
		for(int i=0;i<c;i++)
		{
			if(flag[i])
			{
				if(low[i]>t[i])
				{
					flag[i]=false;
					n1=n1-low[i];
					n2=n2-t[i];
					t[i]=low[i];
					act=true;
				}
				else if(t[i]>up[i])
				{
					flag[i]=false;
					n1=n1-up[i];
					n2=n2-t[i];
					t[i]=up[i];
					act=true;
				}

			}
		}
		for(int i=0;i<c;i++)
		{
			if(flag[i] &&(n2!=0))
				t[i]=t[i]*n1/n2;
		}
	}
	
	int tn=n;
	int p=0;
	for(int i=0;i<c;i++)
	{
		_t[i] = int(t[i]+0.5);
		if(flag[i])
			p=i;
		tn-=_t[i];
	}
	_t[p] += tn;

	printf("\nNStoPS-BK:\n");
	for(int i=0;i<c;i++)
	{
		printf("%d ",_t[i]);
	}
	printf("\n");
	
}


void iter_U()
{
	int i,j;
	int iterN = 1000;
	double acc = 0;
	double acc1 = 0;
	double acc2 = 0;
	char filename[30]="U.txt";
	FILE * fp = fopen(filename,"w");
	printf("\n\n---------------------->   Uniform Distribution    <----------------------\n\n");
	caseU();
	for(i=0;i<iterN;i++)
	{
	//	showInfo();
		generateNS();
		NStoPS(t_pie);     
		NStoPSII(t_pie2);
		NStoPS_BK(t_hat);
		double temp_acc = 0;    //此类acc变量不需要出现在初赛中，此为误差评判变量 
		double temp_acc1 = 0;
		double temp_acc2 = 0;
		for(j = 0;j<c;j++)
		{
			temp_acc+=(t[j]-t_hat[j])*(t[j]-t_hat[j]);
			temp_acc1+=(t[j]-t_pie[j])*(t[j]-t_pie[j]);
			temp_acc2+=(t[j]-t_pie2[j])*(t[j]-t_pie2[j]);
		}
		acc+=sqrt(temp_acc)/iterN;
		acc1+=sqrt(temp_acc1)/iterN;
		acc2+=sqrt(temp_acc2)/iterN;
	}
	fprintf(fp,"Rand_Seed: %d\n",rand_seed);
	fprintf(fp,"Accuracy: \n");
	fprintf(fp,"NStoPS-BK:%f\n",acc/n);
	fprintf(fp,"NStoPS:%f\n",acc1/n);
	fprintf(fp,"NStoPSII:%f\n",acc2/n);
	fclose(fp);
}


void iter_N()
{
	int i,j;
	int iterN = 1000;
	double acc = 0;
	double acc1 = 0;
	double acc2 = 0;
	char filename[30]="N.txt";
	FILE * fp = fopen(filename,"w");
	printf("\n\n---------------------->   Normal Distribution    <----------------------\n\n");
	caseN();
	for(i=0;i<iterN;i++)
	{
		//showInfo();
		generateNS();
		NStoPS(t_pie);
		NStoPSII(t_pie2);
		NStoPS_BK(t_hat);
		double temp_acc = 0; //此类acc变量不需要出现在初赛中，此为误差评判变量 
		double temp_acc1 = 0;
		double temp_acc2 = 0;
		for(j = 0;j<c;j++)
		{
			temp_acc+=(t[j]-t_hat[j])*(t[j]-t_hat[j]);
			temp_acc1+=(t[j]-t_pie[j])*(t[j]-t_pie[j]);
			temp_acc2+=(t[j]-t_pie2[j])*(t[j]-t_pie2[j]);
		}
		acc+=sqrt(temp_acc)/iterN;
		acc1+=sqrt(temp_acc1)/iterN;
		acc2+=sqrt(temp_acc2)/iterN;
	}
	fprintf(fp,"Rand_Seed: %d\n",rand_seed);
	fprintf(fp,"Accuracy: \n");
	fprintf(fp,"NStoPS-BK:%f\n",acc/n);
	fprintf(fp,"NStoPS:%f\n",acc1/n);
	fprintf(fp,"NStoPSII:%f\n",acc2/n);
	fclose(fp);
}


void iter_E()
{
	int i,j;
	int iterN = 1000;
	double acc = 0;
	double acc1 = 0;
	double acc2 = 0;
	char filename[30]="E.txt";
	FILE * fp = fopen(filename,"w");
	printf("\n\n---------------------->   Exp Distribution    <----------------------\n\n");
	caseE();
	for(i=0;i<iterN;i++)
	{
	//	showInfo();
		generateNS();
		NStoPS(t_pie);
		NStoPSII(t_pie2);
		NStoPS_BK(t_hat);
		double temp_acc = 0;   //此类acc变量不需要出现在初赛中，此为误差评判变量 
		double temp_acc1 = 0;
		double temp_acc2 = 0;
		for(j = 0;j<c;j++)
		{
			temp_acc+=(t[j]-t_hat[j])*(t[j]-t_hat[j]);
			temp_acc1+=(t[j]-t_pie[j])*(t[j]-t_pie[j]);
			temp_acc2+=(t[j]-t_pie2[j])*(t[j]-t_pie2[j]);
		}
		acc+=sqrt(temp_acc)/iterN;
		acc1+=sqrt(temp_acc1)/iterN;
		acc2+=sqrt(temp_acc2)/iterN;
	}
	fprintf(fp,"Rand_Seed: %d\n",rand_seed);
	fprintf(fp,"Accuracy: \n");
	fprintf(fp,"NStoPS-BK:%f\n",acc/n);
	fprintf(fp,"NStoPS:%f\n",acc1/n);
	fprintf(fp,"NStoPSII:%f\n",acc2/n);
	fclose(fp);
}


void iter_logN()
{
	int i,j;
	int iterN = 1000;
	double acc = 0;
	double acc1 = 0;
	double acc2 = 0;
	char filename[30]="logN.txt";
	FILE * fp = fopen(filename,"w");
	printf("\n\n---------------------->   log_Normal Distribution    <----------------------\n\n");
	caseLN();
	for(i=0;i<iterN;i++)
	{
//		showInfo();
		generateNS();
		NStoPS(t_pie);
		NStoPSII(t_pie2);
		NStoPS_BK(t_hat);
		double temp_acc = 0;  //此类acc变量不需要出现在初赛中，此为误差评判变量 
		double temp_acc1 = 0;
		double temp_acc2 = 0;
		for(j = 0;j<c;j++)
		{
			temp_acc+=(t[j]-t_hat[j])*(t[j]-t_hat[j]);
			temp_acc1+=(t[j]-t_pie[j])*(t[j]-t_pie[j]);
			temp_acc2+=(t[j]-t_pie2[j])*(t[j]-t_pie2[j]);
		}
		acc+=sqrt(temp_acc)/iterN;
		acc1+=sqrt(temp_acc1)/iterN;
		acc2+=sqrt(temp_acc2)/iterN;
	}
	fprintf(fp,"Rand_Seed: %d\n",rand_seed);
	fprintf(fp,"Accuracy: \n");
	fprintf(fp,"NStoPS-BK:%f\n",acc/n);
	fprintf(fp,"NStoPS:%f\n",acc1/n);
	fprintf(fp,"NStoPSII:%f\n",acc2/n);
	fclose(fp);
}

void test()
{
	NStoPS_BK(t_hat);
}

int main()
{
//	freopen("out.txt","w",stdout);
	rand_seed=(int)time(0);
	srand((unsigned)rand_seed);
	init();
	iter_U();
	iter_N();
	iter_E();
	iter_logN();
	return 0;
}
