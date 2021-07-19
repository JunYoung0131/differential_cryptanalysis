#include<stdio.h>

int main()
{
	FILE *fp;
	long long int x, x_star;
	int now, previous;
	int flag=0;
		
	fp = fopen("PlainText.txt", "w");
	
	printf("작성 시작\n");
	for(x=0x00000000; x<=0xFFFFFFFF; x++){
		now=x/(16*16*16*16*16*16*16);
		
		if(flag==0){
			printf("now write: %X\n", now);
			previous=x/(16*16*16*16*16*16*16);
			flag++;
		}
		
		if(previous!=now)
		{
			printf("now write: %X\n", now);
			previous=now;
		}
	
		x_star=x^0x60006000;
		
		fprintf(fp, "%X\n", x);
		fprintf(fp, "%X\n", x_star);
	}
	printf("작성 완료\n");	
	
	fclose(fp);
	
	return 0;
}
