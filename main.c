#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

void printrez(double rez){
	printf("Rezult: %lf\n", rez);
	printf("\nEnter any character to continue...");
	scanf("%*s");
}

void getoperand(double *op_1, double *op_2){
	printf("Enter first operand: ");
	scanf("%lf", op_1);
	printf("Enter second operand: ");
	scanf("%lf", op_2);
	scanf("%*[^\n]");
}

int main()
{
	char option = 0;
	int error;
	double op_1, op_2, rez;
	//описываем для динамической библиотеки
	void *dlfd;
	double (*sum)(double, double);
	double (*sub)(double, double);
	double (*mul)(double, double);
	double (*div)(double, double, int*);
	//Вытаскиваем функции
	dlfd = dlopen("libcalc.so", RTLD_NOW);
	sum = dlsym(dlfd, "sum");
	sub = dlsym(dlfd, "sub");
	mul = dlsym(dlfd, "mul");
	div = dlsym(dlfd, "div");
	//меню
	while(option != 5){
		write(1,"\E[H\E[2J",7);
		printf("Main Menu\n\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\n\nYour selection: ");
		scanf("%1s", &option);
		scanf("%*[^\n]");//пропускаем остаток в потоке ввода
		switch(option){
			case '1': 
				getoperand(&op_1, &op_2);
				printrez(sum(op_1,op_2));
			break;
			case '2': 
				getoperand(&op_1, &op_2);
				printrez(sub(op_1,op_2));
			break;
			case '3': 
				getoperand(&op_1, &op_2);
				printrez(mul(op_1,op_2));
			break;
			case '4': 
				getoperand(&op_1, &op_2);
				rez = div(op_1,op_2, &error);
				if(error != -1)
					printrez(rez);
				else{
					printf("ERROR: division by zero\nEnter any character to continue...");
					scanf("%*s");
				}
			break;
			case '5': return 0;
			break;
		}
	}
	dlclose(dlfd);
	return 0;
}