import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Queue;

public class Trees {

	// *******************************************************
	// Un premier exemple: le nombre de feuilles d'un arbre
	// *******************************************************
	public static int nbrLeaves(Tree t) {
		int r;
		if (t.isLeaf()) {
			r = 1;
		} else {
			r = 0;
			for (Tree child : t) {
				r += nbrLeaves(child);
			}
		}
		return r;
	}

	// *******************************************************
	// Un deuxième exemple: aplanir un arbre
	// *******************************************************
	public static Tree[] flattenLeaves(Tree t) {
		int nl = nbrLeaves(t);
		Tree[] r = new Tree[nl];
		flattenLeaves(t, r, 0);
		return r;
	}

	private static int flattenLeaves(Tree t, Tree[] a, int idx) { // récupère toutes les feuilles dans une liste
		int r;
		if (t.isLeaf()) {
			a[idx] = t;
			r = 1;
		} else {
			r = 0;
			for (Tree child : t) {
				r += flattenLeaves(child, a, idx + r);
			}
		}
		return r;
	}

	// *******************************************************
	// Un troisième exemple:
	// tous les algorithmes ne sont pas récursifs
	// *******************************************************
	public static void pathV1(Tree t) {
		System.out.println(t.getValue());
		if (t.getParent() != null) {
			pathV1(t.getParent());
		}
	}

	public static void pathV2(Tree t) {
		while (t != null) {
			System.out.println(t.getValue());
			t = t.getParent();
		}
	}

	// *******************************************************
	// Exercices 1
	// *******************************************************

	// 1.1) Renvoie le nombre de noeuds de l'arbre T
	public static int nbrNode(Tree t) {
		int r = 1;
		
		for(Tree child : t) {
			r += nbrNode(child);
		}
		
		return r;
	}

	// 1.2) Renvoie la plus petite valeur associée à un noeud de l'arbre
	public static int min(Tree t) {
		int minVal = t.getValue();
		
		for (Tree child : t) {
			
			int valChild = min(child);
			// traitement après l'appel sur l'enfant
			if (minVal > valChild) {
				minVal = valChild;
			}
		}
		
		return minVal;
	}

	// 1.3) Renvoie la sommes des valeurs associées aux noeud de l'arbre T
	public static int sum(Tree t) {
		int somme = t.getValue();
		
		for (Tree child : t) {
			somme += sum(child);
		}
		
		return somme;
	}

	// 1.4) Renvoie true si t1 et t2 représente le même arbre et qui renvoie false sinon
	public static boolean equals(Tree t1, Tree t2) {
		
		boolean r = false;
		// les deux sont vide (dans le cas ou on reçoit directement null)
		if (t1 == null && t2 == null) {
			r = true;
		}
		
		// Aucun des 2 n'est vide
		if (t1 != null && t2 != null) {
			if (t1.getValue() == t2.getValue() && t1.getChildren().length == t2.getChildren().length) {
				r = true;
				for (int i = 0; i < t1.getChildren().length;i++) {
					r = r && equals(t1.getChildren()[i], t2.getChildren()[i]) ;
				}
			}
		}
		// l'Un est vide l'autre pas -> false
		return r;
	}

	// 1.5) Renvoie la prodonfeur du noeud n 
	public static int depth(Tree n) {
		return (n.getParent() == null) ? 0 : 1 + depth(n.getParent()); // return 0 ou 1 + l'appel
	}

	// 1.6) Renvoie true si n1 et n2 appartienent tous les deux à un même arbre false dans le 
	// cas contraire
	public static boolean sameOne(Tree n1, Tree n2) {
		
		//Remonte jusqu'au root et ensuite propage  le resultat de la racine à l'appel initial grâce au return
		// Dans un premier temps, on monte les 2 arbres jusqu'au root puis une fois au root on compare (ligne 145).
		// Puis on retourne true ou false; ensuite on propage jusqu'au premier appel grâce au return.
		if (n1.getParent() != null) 
			return sameOne(n1.getParent(), n2);
		if (n2.getParent() != null)
			return sameOne(n1, n2.getParent());
		
		return n1 == n2; //renvoie true si même parent
	}

	// 1.7) DFS
	public static void dfsPrint(Tree t) {
		System.out.println(t.getValue());
		for(Tree child : t)
			dfsPrint(child);
	}

	// 1.8) BFS
	public static void bfsPrint(Tree t) {
		Queue<Tree> noeuds = new ArrayDeque<Tree>(); // file
		noeuds.add(t);
		bfsPrint(noeuds);	
	}
	
	private static void bfsPrint(Queue<Tree> noeuds) {
		if (noeuds.isEmpty()) return;
		
		Tree current = noeuds.poll();
		System.out.println(current.getValue());
		for (Tree child : current)
			noeuds.add(child);
		bfsPrint(noeuds);
		
	}

	// *******************************************************
	// Exercices 2
	// *******************************************************

	// 2.1)
	static void printPathV1(Tree node) {
		if (node.getParent() != null)
			printPathV1(node.getParent());
		System.out.println("["+ node.getValue()+"]");
	}

	// 2.2)
	static void printPathV2(Tree node) {
		Deque<Tree> noeuds = new ArrayDeque<Tree>(); // file
		while (node != null) {
			noeuds.push(node);
			node = node.getParent();
		}
		// affichage
		while (!noeuds.isEmpty()) {
			System.out.println("["+ noeuds.pop().getValue() +"]");
		}
	}

	// 2.3
	static void printPathV3(Tree t, int v) {
		printPathV1(trouverNoeud(t, v));
	}
	
	// Parcours en pronfondeur 
	static Tree trouverNoeud(Tree t, int v) {
		if (t.getValue() == v)
			return t;
		for(Tree child : t) {
			Tree node = trouverNoeud(child, v);
			if (node != null)
				return node;
		}
		return null;
	}

	// *******************************************************
	// Exercices 3
	// *******************************************************

	// 3.1 Transforme un 
	public static int[][] toArray(Tree t) {
		int [][] tab = new int[3][nbrNode(t)];
		// init tab 
		for (int i = 0; i < tab.length; i++) {
			for (int j = 0; j < tab[i].length; j++) {
				tab[i][j] = -1;
			}
		}
		transformation(t , tab, 0);
		return tab;
	}
	
	public static int transformation(Tree t, int[][] tab, int index) {
		// Rajoute un noued 
		tab[0][index] = t.getValue();
		int r = 1;
		// Recupere le parent
		if(t.getParent() != null) {
			for (int i = 0; i < tab[0].length; i++) {
				if (t.getParent().getValue() == tab[0][i]) {
					//FG
					if (tab[1][i] == -1) {
						tab[1][i] = index;
					} else { // FD
						tab[2][i] = index;
					}
				}   
			}
		}
		
		for (int i = 0; i < t.getChildren().length; i++) {
			r += transformation(t.getChildren()[i] , tab, index + r);
		}
		return r;
		
	}

	// 3.2
	public static Tree toTree(int[][] t) {
		return null;
	}

	// *******************************************************
	// Exercices 4
	// *******************************************************

	public static Tree lca(Tree n1, Tree n2) {
		return null;
	}
}