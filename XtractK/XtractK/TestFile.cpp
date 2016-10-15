#include <iostream>

/*
	Commentaire complet
 */

int main(void)
{
	// test a faire sur les constantes numeriques
	int a = 17; // entier
	double dbl1 = .132; // double
	double dbl2 = 0.145; // double
	float f = 0.666f; // float
	int hexa = 0xCC; // hexa
	int hexa2 = 0XCC; // hexa
	int octal1 = 7; // octale
	int octal2 = 0; // octale
	int binaire = 0b10; // binaire
	int binaire2 = 0b11; //binaire
	int zero = 0; //entier

	// test a faire sur les constantes textuelle
	std::cout << "Ceci est une chaine de charactere, mais le prochain est un char : " << 'a' << std::endl;
	
	return EXIT_SUCCESS;
}