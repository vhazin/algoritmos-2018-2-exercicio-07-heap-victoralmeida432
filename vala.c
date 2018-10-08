#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aa
{
	char l[76];
	int p;
}a[50004];
int tree[1<<18];

int f(struct aa x,struct aa y)
{
	return (strcmp(x.l,y.l)<0?0:1);
}

void initialise(int node,int l,int r)
{
	if(l==r){
		tree[node]=l;
	return;
	}
	initialise(node<<1,l,(l+r)/2);
	initialise((node<<1)+1,((l+r)/2)+1,r);
	if(a[tree[node<<1]].p >= a[tree[(node<<1)+1]].p)	tree[node]=tree[node<<1];
	else tree[node]=tree[(node<<1)+1];
}

int query(int node,int n_l,int n_r,int q_l,int q_r)
{
	if(n_l>q_r || n_r<q_l)	
	return -1;
	else if(n_l>=q_l && n_r<=q_r)	
	return tree[node];
	int x=query(node<<1,n_l,(n_l+n_r)/2,q_l,q_r);
	int y=query((node<<1)+1,((n_l+n_r)/2)+1,n_r,q_l,q_r);
	if(x==-1)	
	return y;
	else if(y==-1)	
	return x;
	else if(a[x].p>=a[y].p)	
	return x;
	else					
	return y;
}
int n;
void work(int l,int r)
{
	int k;
	if(l>r)	
	return;
	printf("(");
	k=query(1,0,n-1,l,r);
	work(l,k-1);
	printf("%s/%d",a[k].l,a[k].p);
	work(k+1,r);
	printf(")");
}

int main()
{
	int i,j,l;
	char s[100];
	scanf("%d",&n);
	while(n)
	{
		for(i=0;i<n;i++){
			scanf(" %s",s);
			l=strlen(s);
			for(j=0;j<l;j++)
			{
				if(s[j]=='/')	
				break;
				a[i].l[j]=s[j];
			}
			a[i].l[j]=0;
			j++;
			a[i].p=0;
			for(;j<l;j++)
				a[i].p=a[i].p*10+(s[j]-'0');
		}
		qsort(a,n,sizeof(a[0]),(void *)f);
		initialise(1,0,n-1);
		work(0,n-1);
		printf("\n");
		scanf("%d",&n);
	}
	return 0;
}
