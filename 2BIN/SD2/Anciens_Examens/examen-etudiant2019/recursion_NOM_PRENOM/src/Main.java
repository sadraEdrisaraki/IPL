public class Main {
  public static void main(String[] args){
	Tree l9= new Tree(9);
	Tree l2 =new Tree(-2);
    Tree l1 = new Tree(1);
    Tree l3 = new Tree(3);
    Tree l5 = new Tree(5, new Tree[] {l9,l2});
    Tree l4 = new Tree(4);
    
    Tree t4 = new Tree(4, new Tree[]{l1, l3});
    Tree t3 = new Tree(3, new Tree[]{l4});
    
    Tree r4 = new Tree(4, new Tree[]{t4, l5, t3});
    
    System.out.println(r4.strictementPositif());
    System.out.println("---------------");
    System.out.println(r4.toMap());

  }
}
