public class Tree {

	int value;

	Tree parent;

	Tree[] children;

	// *******************************************************
	// CONSTRUCTEURS
	// *******************************************************
	public Tree(int v, Tree[] chd) {
		value = v;
		children = chd;

		int i = 0;
		while (i != chd.length) {
			chd[i].parent = this;
			i++;
		}
	}

	public Tree(int v) {
		this(v, new Tree[0]);
	}

	public int nbNoeudEgalA(int x) {
		//� compl�ter
		return 0;
	}

	public void imprimerNoeudAvecProfondeur() {
		imprimerNoeud(0);
	}
	
	public void imprimerNoeud(int position) {
		System.out.println(this.value + " :" + position);
		for (Tree child : children) {
			child.imprimerNoeud(position + 1);
		}
	}

	public static void main(String[] args) {
		Tree l1 = new Tree(5);
		Tree l2 = new Tree(4);
		Tree l3 = new Tree(2);
		Tree l4 = new Tree(3);
		Tree l5 = new Tree(7);
		Tree t3 = new Tree(5, new Tree[] { l3 });
		Tree t1 = new Tree(3, new Tree[] { l2, t3 });
		Tree t2 = new Tree(3, new Tree[] { l4, l5 });
		Tree root = new Tree(1, new Tree[] { l1, t1, t2 });
		System.out.println(root.nbNoeudEgalA(5));
		root.imprimerNoeudAvecProfondeur();
	}
}
