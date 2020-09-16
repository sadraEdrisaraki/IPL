import java.util.Arrays;
import java.util.HashMap;
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
	 *  renvoie vrai si tous les entiers contenus dans l'arbre sont strictement positifs
	 *  renvoie faux sinon
	 */
	public boolean strictementPositif() {
		boolean isPos = (this.getValue() > 0);
		
		for (Tree child : this.getChildren()) {
			isPos = isPos && child.strictementPositif();
		}
		
		return isPos; // retourne à la fin, parce que le noeud courrant dois quand même parcourir ses enfants
	}
	
	/*
	 *  A COMPLETER
	 *  renvoie une map dont les clés sont les entiers présents dans l'arbre et les valeurs sont le nombre de fois 
	 *  qu'apparaissent ces entiers dans l'arbre
	 */
	public HashMap<Integer,Integer> toMap(){
		HashMap<Integer, Integer> occurence = new HashMap<Integer, Integer>();
		toMap(occurence, this);
		return occurence;
	}
	
	public void toMap(HashMap<Integer, Integer> map, Tree current){
		if (!map.containsKey(current.getValue())) {
			map.put(current.getValue(), 1);
		} else { // modifie
			map.put(current.getValue(), map.get(current.getValue()) + 1);
		}
		
		for (Tree child : current) {
			toMap(map, child);
		}
	}
	
}
