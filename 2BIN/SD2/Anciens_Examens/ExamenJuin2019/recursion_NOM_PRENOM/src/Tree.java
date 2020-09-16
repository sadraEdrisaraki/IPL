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
	
	/*
	 *  A COMPLETER
	 *  renvoie vrai si l'entier x est contenu dans l'arbre
	 *  renvoie faux sinon
	 */
	public boolean contains(int x) {
		
		boolean contenu = (this.getValue() == x);
		
		for(Tree child : this.getChildren()) {
			contenu = contenu || child.contains(x);  // le or permet que si un fils à renvoyé true, c'est vrai car vrai ou faux c'est = à vrai 
		}
		
		return contenu;
	}
}
