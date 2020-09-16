package ex3;

import static java.time.temporal.ChronoUnit.MILLIS;

import java.time.LocalTime;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class LocationPatins {
	
	private int[] casiers; // contient toutes les pointures; l'indice correspond au casier
	// LinkedList utilise fifo et lifo en O(1)
	private Map<Integer, LinkedList<Integer>> pointuresParCasier; // 38: [0,5,6,8...], 41: [1,2,3,9...] ...
	private Map<Integer, LocalTime> casierReserves;
	
	public LocationPatins(int[] casiers) {
		this.casiers = casiers;
		pointuresParCasier = new HashMap<>();
		casierReserves = new HashMap<>();
		
		for (int i = 0; i < casiers.length; i++) { // O(n)
			
			if (!pointuresParCasier.containsKey(casiers[i])) { // la pointure n'est pas présente dans la map
				pointuresParCasier.put(casiers[i], new LinkedList<>());
			}
			
			pointuresParCasier.get(casiers[i]).add(i);
		}
		
	}

	// date1 < date2
	private static double prix(LocalTime date1, LocalTime date2) {
		// 1 euro par milliseconde (c'est assez cher en effet)
		return MILLIS.between(date1, date2) ;
	}

	// Reservation casier
	public int attribuerCasierAvecPatins(int pointure) {
		if (pointure < 33 || pointure > 48)
			throw new IllegalArgumentException();
		LocalTime l = LocalTime.now();
		
		if (!pointuresParCasier.get(pointure).isEmpty()) {
			int numeroCasier = pointuresParCasier.get(pointure).removeFirst(); // FIFO
			casierReserves.put(numeroCasier, l);
			return numeroCasier;
		}
		
		return -1;

	}

	public double libererCasier(int numeroCasier) {
		// rajoute le casier dans les casiers disponible
		pointuresParCasier.get(this.casiers[numeroCasier]).add(numeroCasier);
		LocalTime heure = casierReserves.remove(numeroCasier); // O(1)
		return prix(heure, LocalTime.now());
	}

}
