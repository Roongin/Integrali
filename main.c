/** \file main.c
	\brief Numeric integration of a polynomial
	\author Paolo Gastaldo

	first version of this software; all the functions are in this file
*/

/*! \mainpage
 *
 * \section intro_sec Introduction
 *
 * This is a software in C language for calculating numerical integration by adopting different techniques
 *
 * \section install_sec Installation
 *
 *
 *
 * etc...
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "mathf.h"
#include "Io.h"


 /*! \brief the main function

	 here we define the polynomial, set the integration range and set the number of equally spaced intervals in which the range should be divided
	 the points delimiting the intervals are defined and then the integration is finalized

 */
int main(void) {

	/* setting all the parameters */
	double xmin = 0.0; 						/* the integration range */
	double xmax = 0.0;
	int intervals = 0; 					/* number of equally spaced intervals */
	poly_s polinomio;
	FILE* fPtr = OpenFile("prova.txt");
	if (fPtr == NULL)
		return -1;

	int check = ReadConfigFile(fPtr, &polinomio, &xmin, &xmax, &intervals);		//starting reading config file

	if (check == -1)
	{
		printf("\n\nERROR _ UNABLE TO READ FILE\n\n");
		return -1;
	}

	if (CloseFile(fPtr) == -1)
	{
		printf("ERROR CLOSING FILE");
		return -1;
	}

	double integ1, integ2;

	int i;
	double in = xmin;
	double gap = (xmax - xmin) / (double)intervals;
	double* fvalues = NULL;

	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues = (double*)malloc(sizeof(double) * (intervals + 1));
	if (fvalues == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i = 0; i <= intervals; i++) {
		fvalues[i] = Polynomial(polinomio, in);
		in += gap;
	}

	integ1 = 0.;
	integ2 = 0.;

	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues, intervals + 1, gap, &integ1, &integ2);
	printf("\nRectangular rule - The integral between %.2f and %.2f is in the interval: [%.3f,%.3f]\n", xmin, xmax, integ1, integ2);

	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues, intervals + 1, gap);
	printf("\nTrapezoidal rule - The integral between %.2f and %.2f is : %.3f\n", xmin, xmax, integ1);


	/* deallocation */
	if (fvalues != NULL)
		free(fvalues);

	if (polinomio.coeffs != NULL)
		free(polinomio.coeffs);

	return 0;
}