// -*- coding: utf-8 -*-

import java.math.BigInteger;
    
public class RSA {
  private static BigInteger code_message, code_message_chiffre;
  private static BigInteger clef_publique_e;
  private static BigInteger clef_publique_n;
  private static BigInteger clef_privee;
  private static int LG_MAX=10;
    
  static void fabrique() {
    clef_publique_n =  new BigInteger("196520034100071057065009920573", 10);
    clef_publique_e = new BigInteger("7", 10);
    clef_privee = new BigInteger("56148581171448620129544540223", 10);
  }
 
  static void os2ip(String message) {
    code_message = new BigInteger("71933831046500",10);
  }

  static String i2osp (BigInteger code_message) {
    return("Alfred");
  }
  
  public static void main(String[] args) {
    String message = "Alfred";
    os2ip(message);
    fabrique();
    System.out.println("Clef publique (n) : " + clef_publique_n);
    System.out.println("Clef publique (e) : " + clef_publique_e);
    System.out.println("Clef privée (d)   : " + clef_privee);
    System.out.print("Message de "+message.length()+" caractères : \"" + message +"\"");
    System.out.println(" -> " + code_message);
    /* Chiffrement */
    code_message_chiffre = code_message.modPow(clef_publique_e, clef_publique_n);
    System.out.println("Message codé chiffré : " + code_message_chiffre);
    /* Déchiffrement */
    code_message = code_message_chiffre.modPow(clef_privee, clef_publique_n);
    System.out.print("Message codé déchiffré : " + code_message);
    /* Retour à la chaîne de caractères (Exo 2) */
    String message_dechiffre = i2osp (code_message);
    System.out.println(" -> \"" + message_dechiffre +"\"");
  }
}

/*
> javac RSA.java
> java RSA
Clef publique (n) : 196520034100071057065009920573
Clef publique (e) : 7
Clef privée (d)   : 56148581171448620129544540223
Message de 6 caractères : "Alfred" -> 71933831046500
Message codé chiffré : 45055523945410630249803126960
Message codé déchiffré : 71933831046500 -> "Alfred"
>
*/
