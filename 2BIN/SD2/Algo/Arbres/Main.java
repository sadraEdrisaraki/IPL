public class Main {
  public static void main(String[] args){
    Tree l1 = new Tree(1);
    Tree l3 = new Tree(3);
    Tree l5 = new Tree(5);
    Tree l7 = new Tree(7);
    //Tree l8 = new Tree(8);
    
    Tree t2 = new Tree(2, new Tree[]{l1, l3});
    Tree t6 = new Tree(6, new Tree[]{l7});
    
    Tree t4 = new Tree(4, new Tree[]{t2, l5, t6});
    
    // Arbre binaire
    Tree lb1 = new Tree(1);
    Tree lb2 = new Tree(2 , new Tree[]{lb1});
    
    Tree lb7 = new Tree(7);
    Tree lb3 = new Tree(3);
    Tree lb6 = new Tree(6, new Tree[]{lb3, lb7});
    Tree t44 = new Tree(4, new Tree[]{lb2, lb6});

    System.out.println(Trees.nbrLeaves(t4));
    
    
    Tree[] ls = Trees.flattenLeaves(t4);
    System.out.println("Les " + ls.length + " feuilles");
    int i = 0;
    while(i != ls.length) {
      System.out.println(ls[i].getValue());
      i++;
    }

    System.out.println("Path V1");    
    Trees.pathV1(l7);

    System.out.println("Path V2");    
    Trees.pathV2(l7);
    
    System.out.println("Nombre de noeuds de l'arbre");
    System.out.println(Trees.nbrNode(t4));
    
    System.out.println("Valeur minimal de l'arbre");
    System.out.println(Trees.min(t4));
    
    System.out.println("Somme des noeuds de l'arbre");
    System.out.println(Trees.sum(t4));
    
    System.out.println("comparaison des deux arbres");
    System.out.println(Trees.equals(t4, t4));
    
    System.out.println("Pronfondeur du noeud");
    System.out.println(Trees.depth(l1));
    
    System.out.println("appartiennent tous les deux à un même arbre");
    System.out.println(Trees.sameOne(t2, l5));
    
    System.out.println("DFS");
    Trees.dfsPrint(t4);
    
    System.out.println("BFS");
    Trees.bfsPrint(t4);
    
    System.out.println("Exo 2.1");
    Trees.printPathV1(l5);
    
    System.out.println("Exo 2.2");
    Trees.printPathV2(l5);
    
    System.out.println("Exo 2.3");
    Trees.printPathV3(t4, 5);
    
    System.out.println("Exo 3.1");
    int tab[][] = Trees.toArray(t44);
    for (int l = 0; l < tab.length; l++) {
		for (int j = 0; j < tab[l].length; j++) {
			System.out.print(tab[l][j] +" ");
		}
		System.out.println("");
	}
  }
}
