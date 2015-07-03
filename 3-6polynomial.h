#ifndef TEST_POLYNOMIAL_H
#define TEST_POLYNOMIAL_H

struct NodePoly;
typedef struct NodePoly *Ptr2Node;
typedef Ptr2Node Polynomial;
typedef Ptr2Node PositionPoly;
struct NodePoly {
	int coefficient;
	int exponent;
	Polynomial next;
};

Polynomial MakeEmptyPolynomial();
PositionPoly FirstPolynomial(Polynomial lst);
PositionPoly AdvancePolynomial(PositionPoly p);

#endif