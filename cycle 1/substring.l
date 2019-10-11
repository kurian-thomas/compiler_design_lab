%{
	int count = 0;
%}

%%
aba {count += 1;}
\n {return count;};
. {};
%%
int yywrap() {}
int main() {
	yylex();
	printf("Count is: %d", count);
	return 0;
}