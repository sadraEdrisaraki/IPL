package ex2;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class ControleDAcces {
	
	
	private Map<Badge, Employe> allBadges; // Les Badges par employé; sert a recuperer le badge de l'employé;
											// deux même badges ne peuvent pas être dans la map; la map ne peut pas contenir 2 clés les mêmes
	private Set<Employe> presents;	// evite les doublons; un emplye peut pas être présent deux fois
	
	public ControleDAcces(){
		allBadges = new HashMap<>();
		presents = new HashSet<>();
	}
	
	// associe le badge à un employé
	public void donnerBadge (Badge b, Employe e){
		allBadges.put(b, e); // O(1)
	}
	
	// met à jour les employés présents dans le batiment
	public void entrerBatiment (Badge b){
		Employe empl = allBadges.get(b);
		if (empl != null)
			presents.add(empl);
	}

	// met à jour les employés présents dans le batiment
	public void sortirBatiment (Badge b){
		Employe empl = allBadges.get(b);
		if (empl != null)
			presents.remove(empl);
	}
	
	// renvoie vrai si l'employé est dans le batiment, faux sinon
	public boolean estDansBatiment (Employe e){
		return presents.contains(e); // O(1)
	}

}
