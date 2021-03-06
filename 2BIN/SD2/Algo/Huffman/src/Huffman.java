
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;


public class Huffman {
	
	public static void main(String[] args) throws IOException {
		//String s = "Bonjour! Au revoir!";
		String s = HuffmanReadFile.loadFile(new File("11-0.txt"));
		Map<Character, Integer> freq = computeFreq(s);
		System.out.println(freq);
		
		// Test BuildTree
		Node root = buildTree(freq);
		System.out.println("Nombre de lettre dans la chaine de caract�re � encoder:" + root.freq);
		System.out.println("Fr�quence des lettres dans le sous-arbre de gauche: " + root.left.freq);
		System.out.println("Fr�quence des lettres dans le sous-arbre de droite: " + root.right.freq);
		
		
		Map<Character, String> dictionnaire = buildCode(root);
		System.out.println(dictionnaire);
		
		
		String compress = compress(s, dictionnaire);
		System.out.println(compress);
		
		HuffmanWriteFile.write("fichier_compresse", compress);
		
		
		String textOriginal = expand(root, HuffmanReadFile.read("fichier_compresse"));
		System.out.println(textOriginal);
		
	}
	
	private static class Node  {
		private char ch;
		private int freq;
		private final Node left, right;

		public Node(char ch, int freq, Node left, Node right) {
			this.ch = ch;
			this.freq = freq;
			this.left = left;
			this.right = right;
		}
		
		/**
		 * M�thode qui dit que si le noeud est une feuille ou pas
		 * @return
		 */
		public boolean isLeaf() {
			return left == null && right == null;
		}
	}
	
	// renvoie une map qui a comme cl� les lettres de la chaine de 
	// caract�re donn�e en param�tre et comme valeur la fr�quence de 
	// ces lettres 
	public static Map<Character, Integer> computeFreq(String s) {
		Map<Character, Integer> freq = new HashMap<>();
		
		for (int i = 0; i < s.length(); i++) {
			if(freq.containsKey(s.charAt(i)))
				freq.put(s.charAt(i), freq.get(s.charAt(i)) + 1);
			else
				freq.put(s.charAt(i), 1);
			
		}
		return freq;
	}	
	
	// renvoie l'arbre de Huffman obtenu � partir de la map des fr�quences des lettres 
	public static Node buildTree(Map<Character, Integer> freq) {
		
		// Comparateur sur la frequence des noeuds
		Comparator<Node> myNodeComparator = new Comparator<Node>() {
			public int compare(Node n1, Node n2) {
				if (n1.freq > n2.freq)
					return 1;
				else if(n1.freq == n2.freq)
					return 0;
				else
					return -1;
			}
		};
		
		PriorityQueue<Node> file = new PriorityQueue<>(myNodeComparator);
		
		freq.forEach((k,v) -> {
				file.add(new Node(k,v, null , null ));
			}
		);
		
		while (file.size() > 1) {
			Node fG = file.poll();	// enl�ve les deux nombres les plus petits
			Node fD = file.poll();
			file.add(new Node('\0', fG.freq + fD.freq, fG, fD)); // la valeur du sommet n'a pas d'importance
		}
		return file.poll();
	}
	
	// renvoie une map qui associe chaque lettre � son code (suite de 0 et de 1). 
	// Ce code est obtenu en parcourant l'arbre de Huffman donn� en param�tre
	public static Map<Character, String> buildCode(Node root) {
		Map<Character, String> dictionnaire = new HashMap<>();
		String code = "";
		
		buildCode(dictionnaire, code +"0",root.left); // parcours sous arbre de gauche
		buildCode(dictionnaire, code +"1",root.right); // parcours sous arbre de droite
		
		return dictionnaire;
	}
	
	public static void buildCode(Map<Character, String> dictionnaire, String code, Node current) {
		if(current.isLeaf()) {
			dictionnaire.put(current.ch, code);
			return;
		}
		
		buildCode(dictionnaire, code +"0",current.left); // parcours sous arbre de gauche
		buildCode(dictionnaire, code +"1",current.right); // parcours sous arbre de droite
	}
	
	// encode la chaine de caract�re prise en param�tre en une chaine de 
	// bit (0 et 1) en utilisant la map des codes codeMap
	public static String compress(String s, Map<Character, String> codeMap) {
		StringBuilder resultat = new StringBuilder();
		for (int i = 0; i < s.length(); i++) {
			resultat.append(codeMap.get(s.charAt(i)));
		}
		return resultat.toString();
	}
	
	// Cette m�thode d�code une chaine de 0 et de 1 cod� � l'aide de l'algorithme de Huffman
	// En param�tre, en plus de la chaine � d�coder, est sp�cifi� la racine de l'arbre de 
	// Huffman 
	public static String expand(Node root, String t) {
		int bitPosition = 0;
		StringBuilder resultat = new StringBuilder();
		// boucle tant que le nombre de lettres n'a pas �t� lu; le nombre de lettre est la fr�quence de la racine. 
		for (int i = 0; i < root.freq; i++) {
			Node current = root;
			// tant qu'on est pas sur une feuille
			while(!current.isLeaf()) {
				char bit = t.charAt(bitPosition);
				if (bit == '0') {
					current = current.left;
				} else {
					current = current.right;
				}
				bitPosition++;
			}
			resultat.append(current.ch);
		}
		return resultat.toString();
	}
	
}
