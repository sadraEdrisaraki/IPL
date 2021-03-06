import java.util.Arrays;
import java.util.Iterator;

public class Tree implements Iterable<Tree> {

	private int value;

	private Tree parent;

	private Tree[] children;

	// *******************************************************
	// CONSTRUCTEURS
	// *******************************************************
	public Tree(int v, Tree[] chd) {
		value = v;
		children = chd;

		for (Tree child : chd) {
			child.parent = this;
		}
	}

	public Tree(int v) {
		this(v, new Tree[0]);
	}

	// *******************************************************
	// GETTERS
	// *******************************************************
	public int getValue() {
		return value;
	}

	public Tree getParent() {
		return parent;
	}

	public Tree[] getChildren() {
		return children;
	}

	// *******************************************************
	// ITERATEUR
	// *******************************************************
	public Iterator<Tree> iterator() {
		return Arrays.asList(children).iterator();
	}

	public int nbrChildren() {
		return children.length;
	}

	public boolean isLeaf() {
		return children.length == 0;
	}

	// *******************************************************
	// QUESTIONS
	// *******************************************************

	//v�rifier que chaque noeud interne a au moins un fils qui lui est �gal
	public boolean auMoins1EnfantDeMemeValeur(){
		boolean same = false;
		for (Tree child : this.getChildren()) {
			same = same || (this.getValue() == child.getValue());
		}
		
		for(Tree child : this.getChildren()) {
			same = same || child.auMoins1EnfantDeMemeValeur();
		}
		
		return same;
	}

	//Cette m�thode imprime � la sortie standard tous les noeuds 
	//suivis du maximum de la valeur du noeud et de celle de ses anc�tres.
	public void afficherNoeudsAvecMaximumAncetres() {
		if (this.getParent() != null) {
			System.out.println(this.getValue() + " :" + Integer.max(this.getParent().getValue(), this.getValue()));
		} else {
			System.out.println(this.getValue() + " :" + this.getValue());
		}
		
		for (Tree child : this.getChildren()) {
			child.afficherNoeudsAvecMaximumAncetres();
		}
	}

	public static void main(String[] args){
	    Tree l5 = new Tree(1);
	    Tree l6 = new Tree(6);
	    Tree l7 = new Tree(2);
	    Tree l8 = new Tree(5);
	    
	    Tree t2 = new Tree(7, new Tree[]{l5, l6});
	    Tree l3 = new Tree(12);
	    Tree t4 = new Tree(6, new Tree[]{l7, l8});
	    
	    Tree t1 = new Tree(6, new Tree[]{t2, l3, t4});
	    System.out.println(t1.auMoins1EnfantDeMemeValeur());
	    t1.afficherNoeudsAvecMaximumAncetres();
	}
}
