// -*- coding: utf-8 -*-

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // pour EXIT_SUCCESS
#include <time.h>
#include "gmp.h"
// LG_MAX est la longueur maximale du texte clair (en nombre de caractères ASCII)
#ifndef LG_MAX
#define LG_MAX 10
#endif
typedef unsigned char uchar;



void fabrique(mpz_t clef_publique_n, mpz_t clef_publique_e, mpz_t clef_privee){
  mpz_set_str(clef_publique_n, "196520034100071057065009920573", 10);
  // trouver deux nombres premiers distincts de 1024 bits
  gmp_randstate_t rstate;
  gmp_randinit_default (rstate);
  // P
  mpz_t tempP;
  mpz_urandomb (tempP, rstate, 1024);
  while (mpz_even_p (tempP) != 0) { // vérification parité
	  mpz_urandomb (tempP, rstate, 1024);
  }
  while (mpz_probab_prime_p(tempP, 25) != 2) { // vérification primalité
	mpz_urandomb (tempP, rstate, 1024);
	while (mpz_even_p (tempP) != 0) { // vérification parité
	  mpz_urandomb (tempP, rstate, 1024);
	}
  }
  // Q
  mpz_t tempQ;
  mpz_urandomb (tempQ, rstate, 1024);
  while (mpz_even_p (tempQ) != 0) { // vérification parité
	  mpz_urandomb (tempQ, rstate, 1024);
  }
  while (mpz_probab_prime_p(tempQ, 25) != 2) { // vérification primalité
	mpz_urandomb (tempQ, rstate, 1024);
	while (mpz_even_p (tempQ) != 0) { // vérification parité
	  mpz_urandomb (tempQ, rstate, 1024);
	}
  }
  // Multiplication P * Q
  
  
  mpz_set_str(clef_publique_n, tempP, 10);

  mpz_set_str(clef_publique_e, "7", 10);
  mpz_set_str(clef_privee, "56148581171448620129544540223", 10);
  
  
} // À modifier lors de l'exercice 1

void os2ip (mpz_t x, const uchar *X){
  // Encodez ici le message donné X en un entier long r (le code message)
  mpz_set_str(x, "71933831046500", 10); // À modifier lors de l'exercice 2
} // C'est le codage de la chaîne "Alfred".

uchar* i2osp (mpz_t x){
  uchar *X = malloc(LG_MAX * sizeof(char));
  //sprintf(X, "Alfred"); // À modifier lors de l'exercice 3
  return X;
} // Décodez ici le code message r et retournez le texte correspondant.

int main(){
  srand(time(NULL));
  const uchar message[LG_MAX] = "Alfred"; // C'est le message ASCII à chiffrer
  uchar *message_dechiffre;
  /* Déclaration et initialisation des variables GMP */
  mpz_t code_message, code_message_chiffre, clef_publique_e, clef_publique_n, clef_privee;
  mpz_init(code_message);            // Le message clair, codé
  mpz_init(code_message_chiffre);    // Le message chiffré, codé
  mpz_init(clef_publique_n);         // Le module de la clef publique
  mpz_init(clef_publique_e);         // L'exposant de la clef publique
  mpz_init(clef_privee);             // L'exposant de la clef privée

  fabrique (clef_publique_n, clef_publique_e, clef_privee); // <------------- Exercice 1  
  
  /* Affichage des clefs utilisées à l'aide de la fonction gmp_printf() */
  gmp_printf("Clef publique (n) : %Zd\n", clef_publique_n);
  gmp_printf("Clef publique (e) : %Zd\n", clef_publique_e);
  gmp_printf("Clef privee (d)   : %Zd\n", clef_privee);

  //printf("Message de %d caractères : \"%s\"", strlen(message), message);
  os2ip (code_message, message);     // Codage <----------------------------- Exercice 2
  gmp_printf(" -> %Zd\n", code_message);
  
  /* On effectue à présent le chiffrement RSA du code message */
  mpz_powm(code_message_chiffre, code_message, clef_publique_e, clef_publique_n);
  gmp_printf("Message chiffré : %Zd\n", code_message_chiffre);  

  /* On déchiffre ensuite avec la clef privée */
  mpz_powm(code_message, code_message_chiffre, clef_privee, clef_publique_n);
  gmp_printf("Message déchiffré : %Zd", code_message);

  /* Normalement, le code message n'a pas changé si les clefs sont correctes */
  message_dechiffre = i2osp(code_message); // Décodage <--------------------- Exercice 3
  gmp_printf(" -> \"%s\"\n", message_dechiffre);

  /* Libération de la mémoire utilisée */
  mpz_clear(code_message);
  mpz_clear(code_message_chiffre);
  mpz_clear(clef_publique_n);
  mpz_clear(clef_publique_e);
  mpz_clear(clef_privee);
  exit(EXIT_SUCCESS);
}  

/* 
> make
gcc -o rsa -I/usr/local/include -I/usr/include rsa.c -L/usr/local/lib -L/usr/lib -lgmp
> ./rsa
Clef publique (n) : 196520034100071057065009920573
Clef publique (e) : 7
Clef privee (d)   : 56148581171448620129544540223
Message de 6 caractères : Alfred -> 71933831046500
Message chiffré : 45055523945410630249803126960
Message déchiffré : 71933831046500 -> Alfred
>
*/
