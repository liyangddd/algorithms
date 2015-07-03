#include "test.h"
#include "3-6polynomial.h"

Polynomial MakeEmptyPolynomial() {
	Polynomial poly_list = (struct NodePoly *)malloc(sizeof(struct NodePoly));
	if (poly_list == NULL) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	poly_list->coefficient = -1;
	poly_list->exponent = -1;
	poly_list->next = NULL;
	return poly_list;
}

PositionPoly FirstPolynomial(Polynomial lst) {
	return lst->next;
}

PositionPoly AdvancePolynomial(PositionPoly p) {
	return p->next;
}

void InsertPoly(int c, int e, Polynomial lst, PositionPoly p) {
	PositionPoly tmp;
	tmp = (struct NodePoly *)malloc(sizeof(NodePoly));
	if (tmp == NULL) {
		cout << "malloc failed." << endl;
		return;
	}
	tmp->exponent = e;
	tmp->coefficient = c;
	tmp->next = p->next;
	p->next = tmp;
}

void PrintElementsPoly(Polynomial poly) {
	PositionPoly p = poly->next;
	while (p->next != NULL) {
		cout << p->coefficient << "(" << p->exponent << ")" << " + ";
		p = p->next;
	}
	cout << p->coefficient << "(" << p->exponent << ")" << endl;
}

Polynomial PolynomialAdd(Polynomial lstp1, Polynomial lstp2) {  //3.6多项式加法
	PositionPoly p1 = FirstPolynomial(lstp1);
	PositionPoly p2 = FirstPolynomial(lstp2);
	Polynomial result_poly = MakeEmptyPolynomial();
	PositionPoly resultp = result_poly;

	while (p1 != NULL && p2 != NULL) {
		if (p1->exponent > p2->exponent) {
			InsertPoly(p1->coefficient, p1->exponent, result_poly, resultp);
			p1 = AdvancePolynomial(p1);
			resultp = AdvancePolynomial(resultp);
		}
		else if (p1->exponent < p2->exponent) {
			InsertPoly(p2->coefficient, p2->exponent, result_poly, resultp);
			p2 = AdvancePolynomial(p2);
			resultp = AdvancePolynomial(resultp);
		}
		else {
			InsertPoly(p1->coefficient + p2->coefficient, p1->exponent, result_poly, resultp);
			p1 = AdvancePolynomial(p1);
			p2 = AdvancePolynomial(p2);
			resultp = AdvancePolynomial(resultp);
		}
	}
	return result_poly;
}

Polynomial PolynomialMultiply(Polynomial lstp1, Polynomial lstp2) {  //3.7多项式乘法
	PositionPoly p1 = FirstPolynomial(lstp1);
	PositionPoly p2 = FirstPolynomial(lstp2);
	Polynomial result_poly = MakeEmptyPolynomial();

	while (p1 != NULL) {
		p2 = lstp2->next;
		while (p2 != NULL) {
			int c = p2->coefficient * p1->coefficient;
			int e = p2->exponent + p1->exponent; 
			if (result_poly->next == NULL)   //插入多项式的第一个乘积
				InsertPoly(c, e, result_poly, result_poly);
			else {
				PositionPoly resultp = result_poly->next;
				while (resultp != NULL) {
					if (resultp->exponent == e) {
						resultp->coefficient += c;
						break;
					}
					else if ((resultp->exponent < e && resultp->next->exponent > e) || resultp->next == NULL) {
						InsertPoly(c, e, result_poly, resultp);
						break;
					}
					resultp = resultp->next;
				}
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return result_poly;
}

Polynomial PolynomialPow(Polynomial poly, int n) {  //3.8 F(X)是多项式，求F(X)的N次方。
	                                                //这里使用3.7的函数，并借助求某个数的n次方的递归方法（见课本24页）
	if (n == 1)
		return poly;
	if (n % 2 == 0)
		return PolynomialPow(PolynomialMultiply(poly, poly), n / 2);
	else {
		Polynomial p1 = PolynomialPow(PolynomialMultiply(poly, poly), n / 2);
		return PolynomialMultiply(p1, poly);
	}
}
/*
int main() {
	int start_time = GetTickCount();
	Polynomial poly1 = MakeEmptyPolynomial();
	InsertPoly(7, 3, poly1, poly1);
	InsertPoly(3, 2, poly1, poly1->next);
	InsertPoly(6, 1, poly1, poly1->next->next);
	InsertPoly(4, 0, poly1, poly1->next->next->next);
	PrintElementsPoly(poly1);
	Polynomial poly2 = MakeEmptyPolynomial();
	InsertPoly(9, 4, poly2, poly2);
	InsertPoly(2, 3, poly2, poly2->next);
	InsertPoly(122, 2, poly2, poly2->next->next);
	InsertPoly(999, 1, poly2, poly2->next->next->next);
	InsertPoly(2, 0, poly2, poly2->next->next->next->next);
	PrintElementsPoly(poly2);
	Polynomial result_add_poly = PolynomialAdd(poly1, poly2);
	PrintElementsPoly(result_add_poly);

	Polynomial result_mutiply_poly = PolynomialMultiply(poly1, poly2);
	PrintElementsPoly(result_mutiply_poly);

	Polynomial result_pow_poly = PolynomialPow(poly1, 2);
	PrintElementsPoly(result_pow_poly);
	int end_time = GetTickCount();
	cout << "time: "  << end_time - start_time << endl;
	return 0;
}
*/