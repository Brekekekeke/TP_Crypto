import java.io.*;
import java.security.*;

public class Resume {
    public static void main(String[] args) {
	byte[] buffer, resume;
	MessageDigest fonction_de_hachage;
	// Calcul de l'empreinte SHA1 d'une chaîne de caractères
	try {
	    String message="56-78934/123456789/31.12.2010/$100";
	    System.out.println("Message à hacher: \"" + message +"\"");
	    // On récupère les octets de la chaîne dans un buffer
	    buffer = message.getBytes();
	    // On charge la fonction de hachage SHA1 (à partir d'un provider)
	    fonction_de_hachage = MessageDigest.getInstance("SHA1");
	    // On calcule le résumé
	    resume = fonction_de_hachage.digest(buffer);
	    // On affiche le résumé en hexadécimal
	    System.out.println("Le résumé SHA1 de cette chaîne est: 0x"
                               + toHex(resume));
	} catch (Exception e) { e.printStackTrace(); }
	// Calcul du résumé MD5 d'un fichier
	try {
	    // On ouvre le fichier
	    File fichier = new File("butokuden.jpg");
	    FileInputStream fis = new FileInputStream(fichier);
	    fonction_de_hachage = MessageDigest.getInstance("MD5");
	    buffer = new byte[8192];
	    int nbOctetsLus = fis.read(buffer);
	    while (nbOctetsLus != -1) {
		fonction_de_hachage.update(buffer, 0, nbOctetsLus);
		nbOctetsLus = fis.read(buffer);
	    }
	    fis.close();
	    resume = fonction_de_hachage.digest();
	    System.out.println("Le résumé MD5 du fichier \"butokuden.jpg\" vaut: 0x"
			       + toHex(resume));
	} catch (Exception e) { e.printStackTrace(); }
    }

    public static String toHex(byte[] donnees) {
	return javax.xml.bind.DatatypeConverter.printHexBinary(donnees);
    }
    /* Ou bien, si on tient à avoir des minuscules comme caractères hexadécimaux:
      public static String toHex(byte[] donnees) {
	StringBuffer buf = new StringBuffer();
        for(byte b: donnees)
          buf.append(String.format("%02x", b));	
	return buf.toString();
    }
    */
}

/* Sur mon MacBookPro
$ make
javac *.java 
$ java Resume
Message à hacher: "56-78934/123456789/31.12.2010/$100"
Le résumé SHA1 de cette chaîne est: 0x549AC8A2C2785F22C3E67EEEC0A0862757A65CFE
Le résumé MD5 du fichier "butokuden.jpg" vaut: 0xAEEF572459C1BEC5F94B8D62D5D134B5

*/

