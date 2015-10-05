#include <stdio.h>
#include <openssl/sha.h>
#include <openssl/md5.h>

int main()
{
  int i;
  char message[] = "56-78934/123456789/31.12.2010/$100";
  printf("Message à hacher: \"%s\" \n", message);
  unsigned char resume_sha1[SHA_DIGEST_LENGTH];
  SHA1(message, sizeof(message) -1, resume_sha1);
  printf("Le résumé SHA1 de cette chaîne est: 0x");
  for(i = 0; i < SHA_DIGEST_LENGTH; i++) printf("%02x", resume_sha1[i]);
  printf("\n");

  unsigned char resume_md5[MD5_DIGEST_LENGTH];
  unsigned char buffer[1024];
  int nb_octets_lus;
  // On ouvre le fichier
  char *nom_du_fichier="butokuden.jpg";
  FILE *fichier = fopen (nom_du_fichier, "rb");
  if (fichier == NULL) {
    printf ("%s can't be opened.\n", nom_du_fichier);
    return 0;
  }
  MD5_CTX contexte;
  MD5_Init (&contexte); // Initialisation de la fonction de hachage
  nb_octets_lus = fread (buffer, 1, 1024, fichier);
  while (nb_octets_lus != 0) {
    MD5_Update (&contexte, buffer, nb_octets_lus);
    // Digestion par morceaux du fichier
    nb_octets_lus = fread (buffer, 1, 1024, fichier);
  }
  fclose (fichier);
  MD5_Final (resume_md5, &contexte);
  printf("Le résumé MD5 du fichier \"butokuden.jpg\" vaut: 0x");
  for(i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", resume_md5[i]);
  printf("\n");
  return 0;
}

/*
$ ./resumes
Message à hacher: "56-78934/123456789/31.12.2010/$100" 
Le résumé SHA1 de cette chaîne est: 0x549ac8a2c2785f22c3e67eeec0a0862757a65cfe
Le résumé MD5 du fichier "butokuden.jpg" vaut: 0xaeef572459c1bec5f94b8d62d5d134b5

*/
