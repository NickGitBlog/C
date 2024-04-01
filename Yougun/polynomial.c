#include <stdio.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b) )
#define MAX_DEGREE 101

typedef struct {
	int degree;	// 차수
	float coef[MAX_DEGREE]; // 계수
} polynomial;

polynomial poly_add (polynomial A, polynomial B) {
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b= B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {	// A의 차수가 B의 차수 보다 클떄
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}


void printpoly(polynomial p) {
	for (int i = p.degree; i > 0; i--) 
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
	
}


int main() {
	polynomial a = { 5 , {1,2,3,4,5,6} };
	polynomial b = { 4 , {1,2,3,4,5} };
	polynomial c ;
	c = poly_add( a,  b);
	printpoly (a);
	printpoly(b);
	printf("==================================================\n");
	printpoly(c);


	return 0;
}

