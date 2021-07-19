#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int L1, L2, L3, L4;
	int count[16][16][16][16];
	int Sbox_inver[16] = {0xd, 0x0, 0x8, 0x6, 0x2, 0xc, 0x4, 0xb, 0xe, 0x7, 0x1, 0xa, 0x3, 0x9, 0xf, 0x5};
	long long int y, y_star;
	long long int y_tmp, y_star_tmp;
	int y_part[8], y_star_part[8];
	int i;
	int u4_1, u4_3, u4_5, u4_7;
	int v4_1, v4_3, v4_5, v4_7;
	int u4_1_star, u4_3_star, u4_5_star, u4_7_star;
	int v4_1_star, v4_3_star, v4_5_star, v4_7_star;
	int u4_1_p, u4_3_p, u4_5_p, u4_7_p;
	int max=-1;
	int max_L1, max_L2, max_L3, max_L4;
	FILE *fp;
	FILE *fp2;
	int now, previous;
	int flag=0;
	
//	char y_test[8], y_star_test[8];
	long long int line;
	
	//초기화 
	printf("초기화 시작\n");
	for(L1=0; L1<=0xF; L1++){
		for(L2=0; L2<=0xF; L2++){
			for(L3=0; L3<=0xF; L3++){
				for(L4=0; L4<=0xF; L4++){
					count[L1][L2][L3][L4]=0;
				}
			}
		}
	}
	printf("초기화 완료\n");

	fp = fopen("CipherText.txt", "r");	//암호파일 읽기
	fp2 = fopen("result2.txt", "w");	//결과파일 쓰기 
	
	printf("계산 시작\n");
	for(line=0x00000001; line<=0x100000000; line++) {
		now=line/(16*16*16*16*16*16*16);
		
		if(flag==0){
				printf("now read: %X\n", now);
				previous=line/(16*16*16*16*16*16*16);
				flag++;
		}
		
		if(previous!=now)
		{
			printf("now read: %X\n", now);
			previous=now;
		}
		
		if(line%2==1){	//i가 홀수
			fscanf(fp, "%X\n", &y);
		} 
		
		else if(line%2==0){	//i가 짝수 
			
			fscanf(fp, "%X/n", &y_star);
			
			y_tmp=y;
			y_star_tmp=y_star;
			
			for(i=7; i>=0; i--){
				y_part[i]=y_tmp%16;
				y_tmp=y_tmp/16;
							
				y_star_part[i]=y_star_tmp%16;
				y_star_tmp=y_star_tmp/16;
			}
			
			//TEST
//			for(i=0; i<8; i++){
//				printf("%X", y_part[i]);
//			}
//			printf("\n");
//			for(i=0; i<8; i++){
//				printf("%X", y_star_part[i]);
//			}
//			getchar();

			if(y_part[1]==y_star_part[1] && y_part[3]==y_star_part[3] && y_part[5]==y_star_part[5] && y_part[7]==y_star_part[7]){
				for(L1=0; L1<=0xF; L1++){
					for(L2=0; L2<=0xF; L2++){
						for(L3=0; L3<=0xF; L3++){
							for(L4=0; L4<=0xF; L4++){
								v4_1=L1^y_part[0];
								v4_3=L2^y_part[2];
								v4_5=L3^y_part[4];
								v4_7=L4^y_part[6];
								
								//TEST
			//					printf("v4_2: %X\n", v4_2);
			//					printf("v4_4: %X\n", v4_4);	
									
								u4_1=Sbox_inver[v4_1];
								u4_3=Sbox_inver[v4_3];
								u4_5=Sbox_inver[v4_5];
								u4_7=Sbox_inver[v4_7];
								
								//TEST
			//					printf("u4_2: %X\n", u4_2);
			//					printf("u4_4: %X\n", u4_4);	
											
								v4_1_star=L1^y_star_part[0];
								v4_3_star=L2^y_star_part[2];
								v4_5_star=L3^y_star_part[4];
								v4_7_star=L4^y_star_part[6];
								
								//TEST
			//					printf("v4_2_star: %X\n", v4_2_star);
			//					printf("v4_4_star: %X\n", v4_4_star);	
						
								u4_1_star=Sbox_inver[v4_1_star];
								u4_3_star=Sbox_inver[v4_3_star];
								u4_5_star=Sbox_inver[v4_5_star];
								u4_7_star=Sbox_inver[v4_7_star];
								
								//TEST
			//					printf("u4_2_star: %X\n", u4_2_star);
			//					printf("u4_4_star: %X\n", u4_4_star);	
											
								u4_1_p=u4_1^u4_1_star;
								u4_3_p=u4_3^u4_3_star;
								u4_5_p=u4_1^u4_5_star;
								u4_7_p=u4_3^u4_7_star;
								//TEST
			//					printf("u4_2_p: %X\n", u4_2_p);
			//					printf("u4_4_p: %X\n", u4_4_p);	
								
								if(u4_1_p==0x8 && u4_3_p==0x4 && u4_5_p==0x8 && u4_7_p==0x4){
									printf("found!!!\n");
									count[L1][L2][L3][L4]++;
									fprintf(fp2, "------------\n");
									fprintf(fp2, "found, %X, %X, %X, %X\n", L1, L2, L3, L4);
									fprintf(fp2, "------------\n");
								}
							}
						}
					}
				}
			}
		} 
    } 
    printf("계산 완료\n");

//	for(L1=0; L1<=0xF; L1++){
//		for(L2=0; L2<=0xF; L2++){
//			fprintf(fp2, "count[%X][%X]=%d\n", L1, L2, count[L1][L2]);
//		}
//	}
//	
	printf("최댓값 찾기시작\n");
	for(L1=0; L1<=0xF; L1++){
		for(L2=0; L2<=0xF; L2++){
			for(L3=0; L3<=0xF; L3++){
				for(L4=0; L4<=0xF; L4++){
					if(count[L1][L2][L3][L4]>max){
						max=count[L1][L2][L3][L4];
						max_L1=L1;
						max_L2=L2;
						max_L3=L3;
						max_L4=L4;
					}
				}
			}
		}
	}
	fprintf(fp2, "[maxkey] L1: %X, L2: %X, L3: %X, L4: %X\n", max_L1, max_L2, max_L3, max_L4);
	printf("최댓값 찾기 완료\n");
		
	fclose(fp);

	return 0;
}
