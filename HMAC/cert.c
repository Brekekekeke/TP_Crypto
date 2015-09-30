#include <stdio.h>
#include <stdlib.h>
//#include <openssl/sha.h>
//#include <openssl/md5.h>
#include <string.h>


typedef int bool;
#define true 1
#define false 0

#define TAILLE_MAX_LIGNE 1000
#define TAILLE_MAX_CORPS 10000
#define TAILLE_MAX_NM 10000

int main(int argc, char *argv[])
{
	bool adv = true; //nom fichier dans l'argument
	bool vb = true; // verbose

	char * nomFichier;
	if (adv==true) {
		/*if (argc != 2) { // 1 nomFichier 2 secret
			printf("Wrong arg number\n");
			return 0;
		}*/
		nomFichier = argv[1];
	} else {nomFichier = "email1.txt";}


	FILE * fichier = fopen (nomFichier, "r");
	if (fichier == NULL) {
		printf("%s can't be opened\n", nomFichier);
		return 0;
	}

// Lire l'entete
	int ch;
	char ligne[TAILLE_MAX_LIGNE];
	while (fgets(ligne, TAILLE_MAX_LIGNE, fichier)) {
		if (vb==true) {printf("%s", ligne);}
		ch = fgetc(fichier);
		if (ch == ((int) '\n')) {
			if (vb==true) {printf("WIN\n\n");}
			break;
		}
	}

// Récupérer le corps	
	char corps[TAILLE_MAX_CORPS];
	while (fgets(ligne, TAILLE_MAX_LIGNE, fichier) != NULL) {
		strcat(corps, ligne);
	}
	if(vb==true) {printf("Corps :\n%s", corps);}

	
	//char myMD5[nbBits] = md5 du corps plus secret (argv[2])
	

	char champSecure[strlen("X-UdC_authentique :") + nbBits] = "X-UdC_authentique :";
	strcat(champSecure, myMd5);
	strcat(champSecure, '\n');

// Création nouveau mail
	// trouver la fin de l'entête
	char newMail[TAILLE_MAX_NM];
	while (fgets(ligne, TAILLE_MAX_LIGNE, fichier)) {
		if (vb==true) {printf("%s", ligne);}
		strcat(newMail, ligne);
		ch = fgetc(fichier);
		if (ch != ((int) '\n')) {
			strcat(newMail, ch) // pb de type? &ch ?
		} else {
			if (vb==true) {printf("WIN\n\n");}
			strcat(newMail, ); // place le résumé
			strcat(newMail, ch) // pb de type? &ch ?
			break;
		}
	}

	// ecrire le nouveau mail
	FILE* fichierSortie = fopen("email1-secure.txt", "w");
	if (fichierSortie != NULL)
	{
		fputs(newMail, fichierSortie);
		fclose(fichierSortie);
	}




	fclose(fichier);
	return 0;
}
