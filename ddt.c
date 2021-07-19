#include<stdio.h>

int main()
{
	int x, x_star, x_p;	//x, x*, x'
	int y, y_star, y_p;	//y, y*, y'
	int compare;
	int Sbox[16]={0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};
	int count=0;

	for(x_p=0; x_p<=0xF; x_p++){
		for(compare=0; compare<=0xF; compare++){
			for(x=0; x<=0xF; x++){
				x_star=x^x_p;	//x*=x^x' 
				y=Sbox[x];
				y_star=Sbox[x_star];
				y_p=y^y_star;
				if(compare==y_p) count++;	
			} 
			printf("%d ", count);
			count=0;
		}
		count=0;
		printf("\n");
	} 
	
	return 0;
}
