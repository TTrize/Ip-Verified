#include <stdio.h>
#include <stdlib.h>

 #include <string.h>

int validate(int r1,int r2,int r3){
	//function get values from a, b, c, and d, before execute contidional verification for ip validate is exist or unknown values.
	if((r1 == 0 && r2 == 0 && r3 == 0) || (r1 == 255 && r2 == 255 && r3 == 255)){//if IP note have param valids printf("Invalid IP")
		printf("Invalid IP\n");
		return -1;
	}else{//else values is true, split ip for class A, B, C and D
		if(r1 >= 0 && r1 <= 254){
			if(r2 >= 0 && r2 <= 254){
				if(r3 >= 0 && r2 <= 254){
					printf("IP Verified\n");
				}
			}
		}
	}
return 0;
}

int main(){
	//Input the variable for values the conditional, ip and archives
	FILE *fd;
	FILE *fp;
	char *classA = "Class A\n";
	char *classB = "Class B\n";
	char *classC = "Class C\n";
	char *classD = "Class D\n";
	char *classE = "Class E\n"; 
	char ipstr[255];
	char archive[50];
	char *str,*str1,*str2,*str3;
	int a,b,c,d;
	
	//get file name archive and open for read/write (data)
	printf("Insert archive name (example: achive.txt):");
	scanf(" %s", &archive); 
	
	fd = fopen(archive, "r");
	fp = fopen("ipresolver.txt", "w");
	
    //archive exists? yes continue || no? response error				
	if(fd == NULL){
		printf("error");
	}else{	
			while(fgets(ipstr, 255, fd) != NULL){//String verification and ip data for converted string into integer
				str = strtok(ipstr, ".");
				str1 = strtok(NULL,".");
				str2 = strtok(NULL,".");
				str3 = strtok(NULL,".");
				a = atoi(str);b = atoi(str1);c = atoi(str2);d = atoi(str3);
				
				//the data verified ip if it is valided or unknown, divide ip in their classes
					if(a > 255 || b > 255 || c > 255 || d > 255){
						fprintf(fp,"%d.%d.%d.%d  -\tUnknown\n",a,b,c,d);  
					}else{
						if(a >= 0 && a <= 126){ //Class A
							validate(b, c, d);
							fprintf(fp,"%d.%d.%d.%d  -\t%s", a,b,c,d,classA);
						}
						else{
							if(a == 127){				
								validate(b,c,d);
								fprintf(fp,"%d.%d.%d.%d  -\tlocalhost\n",a,b,c,d);
							}
							else{	
								if(a >= 128 && a <= 191){ //Class B
									validate(b, c, d);
									fprintf(fp,"%d.%d.%d.%d  -\t%s", a,b,c,d,classB);
								}	 
								else{
									if((a >= 192 && a <= 223) && (d >= 0 && d <= 254)){	//Class C
										validate(b, c, d);
										fprintf(fp,"%d.%d.%d.%d  -\t%s", a,b,c,d,classC);
										
									}
									else{
										if(a >= 224 && a <= 239){ //Class D
											validate(b, c, d);
											fprintf(fp,"%d.%d.%d.%d  -\t%s", a,b,c,d,classD);
										}else{
											if(a >= 240 && a <=255){//Class E
												validate(b, c, d);
												fprintf(fp,"%d.%d.%d.%d  -\t%s", a,b,c,d,classE);
											}
											else{
												printf("IP invalided");									
									}
								}
							}
						}
					}
			}
		}
	}
}
	//close archive
	fclose(fopen("ipresolver.txt", "a"));
	printf("Archive ipresolver.txt create\n");
	return 0;
}
