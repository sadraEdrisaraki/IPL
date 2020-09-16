package ex1;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class Ordonnancement {
	
	public static final int NIVEAU_PRIORITE_MAX=5;
	
	private Map<Integer, LinkedList<Tache>> dico; // on utiluse linkedlist comme ça on peut enlever le premier en O(1)

	public Ordonnancement() {
		dico = new HashMap<>();
		// ajout déjà une liste pour chaque priorité
		for (int i = 1; i <= 5; i++) {	// O(1)
			dico.put(i, new LinkedList<Tache>());
		}
	}
	
	public void ajouterTache (String descriptif, int priorite){
		Tache tache = new Tache(descriptif, priorite);
		(dico.get(priorite)).add(tache);
	}
	
	//renvoie la tache prioritaire
	//renvoie null si plus de tache presente
	public Tache attribuerTache(){
		// boucle tant qu'il n'y a pas de tâche dans la priorité courante
		for (int i = 5; i >= 1; i--) { // O(1)
			LinkedList<Tache> taches = dico.get(i);
			if (!taches.isEmpty()) { // renvoie la premier tâche de la priorité la plus haute
				return taches.removeFirst();
			}
		}
		return null;
	}
}
