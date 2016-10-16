#include <iostream>

/*
	Commentaire complet
 */

int main(void)
{
	// test a faire sur les constantes numeriques
	int a = 17; // entier
	int b = -19;
	double dblUn = .132; // double
	double dblDeux = 0.145; // double
	float f = 0.666f; // float
	int hexa = 0xCC; // hexa
	int hexaDeux = 0XCC; // hexa
	int octal = 7; // octale
	int octalDeux = 0; // octale
	int binaire = 0b10; // binaire
	int binaireDeux = 0b11; //binaire
	int zero = 0; //entier

	// test a faire sur les constantes textuelle
	std::cout << "Ceci est une chaine de charactere, mais le prochain est un char : " << 'a' << std::endl;
	
	return EXIT_SUCCESS;
}