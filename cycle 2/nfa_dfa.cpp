#include<bits/stdc++.h>
#include<set>
#include<vector>

using namespace std;
struct node{
	
	int val;
	struct node *link;

}*transitiontab1[100][100];

struct temp_str{

	char str[100];
	struct temp_str *link;

};


struct temp_str *transitiontab2[100][100];
char temp_string[100],uni[100];
char newstates[100][100];
int states,alpha_no,tansitions,visited[100]={0};
int add_state,add_apha,row=2,col=1;
set <int, greater <int> > chk;
static int newi=0,l=0;

void insrt_tab(int in_state,int alpha,int nxt_state){
	
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	struct node *temp2,*temp3,*pre;
	
	temp->val=nxt_state;
	temp->link=NULL;
	
	if(transitiontab1[in_state][alpha]!=NULL){
			temp2=transitiontab1[in_state][alpha];
			while(temp2->link!=NULL){
				temp2=temp2->link;
			}

			temp2->link=temp;

	}
	else
		transitiontab1[in_state][alpha]=temp;
	
}

void print_tab(){

	int i,j;
	struct node *temp;
	for(i=1;i<=states;i++){
			printf("\n\n q%d:{ ",i);
			for(j=1;j<=alpha_no;j++){
				if(transitiontab1[i][j]!=NULL){
						printf("[%d]::{ ",j); 
						temp=transitiontab1[i][j];
						while(temp!=NULL){
							printf("%d, ",temp->val);
							temp=temp->link;
						}
						printf("}");
						printf("\t");
				}
				else
					printf("[%d]::null \t",j);
			}		
		printf("\n");
	}
}

void append_str(int x,struct temp_str *string){
	
	int len;
	
	len=strlen(string->str);
	string->str[len]=x+'0';
	string->str[len+1]='\0';

}

void print_tab2(){

	int i,j;
	struct temp_str *temp;
	
	for(i=1;i<=newi;i++){
		printf("\n %d:",i);
		for(j=1;j<=alpha_no;j++){
				if(transitiontab2[i][j]!=NULL){
					printf("[%d]::{",j);
					temp=transitiontab2[i][j];
					printf("%s} \t",temp->str);
					
				}
				else{
					printf("[%d]::{} \t",j);

				}
		}
	}


}

void convert(char k,int j,int fl=0){

	int i,flag=0,m,s,n; 
	struct node *temp;
	i=k-'0';

	if(transitiontab1[i][j]!=NULL){
		temp=transitiontab1[i][j];

		while(temp!=NULL){
		chk.insert(temp->val);
		temp=temp->link;

		}

	}

}

void union_set(){

	int s;
	vector <int> v;
	set <int, greater <int> > :: iterator itr;

				s=0;
			for (itr = chk.begin(); itr != chk.end(); itr++){
			 	v.push_back(*itr);
			}

			sort(v.begin(),v.end());

			for(int x:v){
				//printf("%d ",x );
				uni[l++]=x+'0';
			}
		chk.clear();
}

int checknew(char str[]){

	int i,flag=0;

	for(i=0;i<newi;i++){
		if(!(strcmp(str,newstates[i]))){
			flag=1;
			break;
		}

	}

	if(flag==0)
		return 1;
	else{
		return 0;
		visited[i]+=1;
	}

}

void visit(char str[]){
	int i;

	for(i=0;i<newi;i++){
		if(!strcmp(newstates[i],str))
			break;
	}
	visited[i]+=1;

}

int isvisited(char str[]){
	int i;

	for(i=0;i<newi;i++){
		if(!strcmp(newstates[i],str))
			break;
	}
	if(visited[i]>0)
		return 1;
	else
		return 0;
}

void nfa_dfa(){

	int i,j,k,m,test;
	struct node *temp;
	struct temp_str *str_t;
	char temp2[100];

	strcpy(newstates[newi],"1");
	visited[newi]+=1;
	newi++;
			
	for(i=1;i<2;i++){
		for(j=1;j<=alpha_no;j++){
			str_t=(struct temp_str*)malloc(sizeof(struct temp_str));
			if(transitiontab2[i][j]==NULL){
				if(transitiontab1[i][j]!=NULL){
					temp=transitiontab1[i][j];
					while(temp!=NULL){
						append_str(temp->val,str_t);
						temp=temp->link;
					}
					transitiontab2[i][j]=str_t;
					if(checknew(str_t->str)){
						strcpy(newstates[newi],str_t->str);
						visited[newi]+=1;
						newi++;
					}
				}				
			}
			// else
			// 	printf("hey\n" );					
		}
	}


  	for(i=1;i<=newi;i++){
  	 	for(j=1;j<=alpha_no;j++){
  	 		m=1;
  	 		k=0;
  	 		//printf("i:%d j:%d\n",i,j );
  	 		if(transitiontab2[i][j]!=NULL){
  	 			//printf("\ttab2:%s\n\n",transitiontab2[i][j]->str);
  	 			strcpy(temp2,transitiontab2[i][j]->str);
  	 			//printf("==========================>%d\n",isvisited(temp2));
  	 			if(isvisited(temp2) && i>1 || !strcmp(temp2,"1") && i==1)
  	 				continue;
  	 			else
  	 				visit(temp2);

  	 			while(m<=alpha_no){
  	 				//printf("\t\tval1:%c col1:%d\n",temp2[k],m);
  	 			 	convert(temp2[k],m);
  	 			 	k++;
  	 			 	if(temp2[k]=='\0'){
  	 			 		m++;
  	 			 		k=0;
  	 			 		union_set();
  	 			 		//printf("\t\t\tunion:%s\n",uni);
  	 			 		str_t=(struct temp_str*)malloc(sizeof(struct temp_str));
	 	 			 	strcpy(str_t->str,uni);
	 	 			 	if(transitiontab2[row][col]==NULL){
	 	 			 		//printf("\t\t\t\trowt2:%d colt2:%d \n",row,col);
	 	 			 		if(strlen(uni)>0)
	 	 			 			transitiontab2[row][col++]=str_t;
	 	 			 		else
	 	 			 			transitiontab2[row][col++]=NULL;
	
	 	 			 		if(col>alpha_no){
	 	 			 			col=1;
	 	 			 			row++;
	 	 			 		}
	 	 			 		if(checknew(uni) && strlen(uni)>0){
	 	 			 			strcpy(newstates[newi++],uni);
	 	 			 		}
	 	 			 	}
	 	 			 		memset(uni,0,sizeof(uni));
	 	 			 		l=0;
	 	 			 	}
  				 	}
  				 	
  	 			}
  	 			// else
  	 			// 	printf("\tnull\n\n" );
  	 	}
  	 }
  	
	
	print_tab2();

}

int main(){

	int i,j,in_state,alpha,nxt_state;
	
	printf("\n enter no of states \n");
	scanf("%d%*c",&states);
	
	printf("\n enter no of alphabets \n");
	scanf("%d%*c",&alpha_no);
	
	printf("\n enter no of transitions \n");
	scanf("%d%*c",&tansitions);
	
	printf("\n enter transitions with transition alphabet eg: 1 1 3 \n");
	for(i=0;i<tansitions;i++){
		
		scanf("%d %d %d",&in_state,&alpha,&nxt_state);
		insrt_tab(in_state,alpha,nxt_state);	
		
	}
	printf("\nTransition table for NFA\n");
	print_tab();
	printf("\n");
	printf("\nTransition table for DFA\n");
	nfa_dfa();

	printf("\n");
	//printf("%d\n",newi );
	printf("\nDFA States\n");
	for(i=0;i<newi;i++)
		printf("%d => %s\n",i+1,newstates[i] );
	
	//printf("\n%d %d\n",row,newi );
	return 0;		


}
