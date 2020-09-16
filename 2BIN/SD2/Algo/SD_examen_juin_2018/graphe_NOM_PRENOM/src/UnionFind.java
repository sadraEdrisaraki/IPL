// Cette classe représente une partition de l'interval [0..n[.
public class UnionFind {

  private int[][] t;
  
  private int crd;
  
  // Hypothèse: n >= 0 
  // Instancie la partition initiale de l'interval [0..n[,
  // cad la relation identitée(cf slide 4).
  public UnionFind(int n) {
    t = new int[n][2];
    crd = n;
    
    int i = 0;
    while(i != n) {
      t[i][0] = i;
      t[i][1] = 1;
      i++;
    }
  }
  
  // Hypothèse: e appartient à  l'interval [0..n[.  
  // Renvoie le représentant de la partie de e (cf slide 10).
  private int root(int e) {
    while(t[e][0] != e) {
      e = t[e][0];
    }
    return e;
  }

  // Hypothèse: e appartient à  l'interval [0..n[.  
  // 1) Compresse la partie de e, et 
  // 2) renvoie le représentant de la partie de e (cf slide 12).  
  public int find(int e) {
    int r = root(e);
    int cpt = 0;
    while (e != r) {
      int tmp = t[e][0];
      cpt += t[e][1];
      t[tmp][1] = t[tmp][1] - cpt;
      t[e][0] = r;
      e = tmp;
    }
    t[r][1] += cpt;
    return r;
  }

  // Hypothèse: e appartient à  l'interval [0..n[.  
  // 1) Compresse la partie de e, et 
  // 2) renvoie la taille de la partie de e (cf slide 13).    
  public int cardinal(int e) {
    int r = find(e);
    return t[r][1];
  }
  
  // Renvoie le nbr de parties de la partition représentée par this.
  public int cardinal() {
    return crd;
  }

  // Hypothèse: e1 et e2 appartiennent à  l'interval [0..n[.  
  // 1) Compresse les parties de e1 et e2, et 
  // 2) renvoie la valeur "true" ssi 
  //    e1 et e2 appartiennent Ã  la mÃªme partie (cf slide 14).  
  public boolean equals(int e1, int e2) {
    int r1 = find(e1);
    int r2 = find(e2);
    return r1 == r2;
  }
  
  // Hypothèse: e1 et e2 appartiennent Ã  l'interval [0..n[.  
  // 1) Compresse les parties de e1 et e2, et 
  // 2) fusionne les parties de e1 et e2 (cf slide 15).  
  public void union(int e1, int e2) {
    int r1 = find(e1);
    int r2 = find(e2);
    if (r1 != r2 && t[r1][1] < t[r2][1]) {
      t[r1][0] = r2;
      t[r2][1] = t[r2][1] + t[r1][1];
      crd--;
    } else if (r1 != r2){
      t[r2][0] = r1;
      t[r1][1] = t[r1][1] + t[r2][1];
      crd--;    
    }
  }
}