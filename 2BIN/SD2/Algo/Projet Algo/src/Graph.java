import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.Set;

public class Graph {
	
	// Représentation en liste d'adjascence
	private Map<Station, Set<Troncon>> listeAdj = new HashMap<Station , Set<Troncon>>();
	// Pour retrouver une station en fonction de son nom facilement en O(1)
	private Map<String, Station> stations = new HashMap<String, Station>();
	
	public Graph() {}
	
	public Station ajouterStation(String nomStation) {
		Station station = new Station(nomStation);
		listeAdj.put(station, new HashSet<Troncon>());
		stations.put(nomStation, station);
		return station;
	}
	
	
	public void ajouterTroncon(Troncon troncon) {
		Station station = troncon.getDepart();
		listeAdj.get(station).add(troncon);
	}
	
	/**
	 * Algo BFS pour calculer le chemin minimisant le nombre de tronçons
	 * @param source Le noeud de départ
	 * @param dest	 Le noeud d'arrivé
	 * @param fichier Le fichier où sera écrit le résultat
	 */
	public void calculerCheminMinimisantNombreTroncons(String source , String dest, String fichier) {
		
		if (stations.get(source) == null || stations.get(dest) == null) {
			throw new NoSuchElementException("Pas de stations correspondantent");
		}
		
		System.out.println("Calcul du chemin minimisant le nombre de tronçons de : " +
		source + " à " + dest);
		
		Queue<Station> stationsAVisite = new ArrayDeque<Station>(); // file
		Set<Station> stationsVisite = new HashSet<Station>(); // station marqué
		Map<Station, Troncon> chemin = new HashMap<Station, Troncon>(); // conserve l'arc par lequel on est venu.
		
		stationsAVisite.add(stations.get(source));
		stationsVisite.add(stations.get(source));
		
		while (!stationsAVisite.isEmpty() && !stationsVisite.contains(stations.get(dest))) {
			Station currentStation = stationsAVisite.poll();
			for(Troncon troncon : listeAdj.get(currentStation)) {
				if (!stationsVisite.contains(troncon.getArrivee())) {
					stationsAVisite.add(troncon.getArrivee());
					stationsVisite.add(troncon.getArrivee());
					chemin.put(troncon.getArrivee(), troncon);
				}
			}
		}
		
		LinkedList<Troncon> sol = trouveSolution(chemin, dest, source);
		
		new DomCreate(sol, source, dest, fichier, "DFS");
	}
	
	public LinkedList<Troncon> trouveSolution(Map<Station, Troncon> chemin, String dest, String source) {
		
		LinkedList<Troncon> solution = new LinkedList<Troncon>();
		// Remonte le graphe en partant de la destination
		Troncon tronconCourrant = chemin.get(stations.get(dest));
		// Parcours tant qu'on est pas remonté à la source.
		while(!tronconCourrant.getDepart().getNom().equals(stations.get(source).getNom())) {
			solution.addFirst(tronconCourrant);
			tronconCourrant = chemin.get(tronconCourrant.getDepart());
		}
		solution.addFirst(tronconCourrant);
		
		return solution;
	}
	
	/**
	 * Algorithme de Dijkstra 
	 * Complexité : O(n*n)
	 * @param source Le noeud de départ
	 * @param dest	 Le noeud d'arrivé
	 * @param fichierSortie Le fichier où sera écrit le résultat
	 */
	public void calculerCheminMinimisantTempsTransport(String source, String dest, String fichierSortie) {
		
		if (stations.get(source) == null || stations.get(dest) == null) {
			throw new NoSuchElementException("Les stations n'existent pas");
		}
		
		System.out.println("Calcul du chemin minimisant le temps dans les transports de : " +
		source + " à " + dest);
		
		Map<Station, Troncon> chemin = new HashMap<Station, Troncon>();	
		Set<Station> stationsAVisiste = new HashSet<Station>();	// contient tous les noeuds
		Map<Station, Integer> dist = new HashMap<Station, Integer>(); // contient les distances à partir de la source
		
		// Initialise les distances et rajoute les noeuds dans une structure de données
		// Tous les autres noeuds mise à part la source on une distance infini
		listeAdj.forEach((k, v) -> { // O(n * 1 ) = O (n) 
			if (k.getNom().equals(source)) {
				dist.put(k, 0); // O(1)
			} else {
				dist.put(k, Integer.MAX_VALUE); // O(1)
			}
			stationsAVisiste.add(k); // O(1)
		});
		
		// Au début on commence à la source : complexité totale : O(n*n)
		while (!stationsAVisiste.isEmpty()) { 
			Station currentStation = getPlusCourteDistance(stationsAVisiste, dist); // O(n)
			stationsAVisiste.remove(currentStation);
			if (currentStation == null) {
				stationsAVisiste.clear();
			} else {
				// Parcours tous les voisins de la station courante -- Au debut donc tout ceux de la source
				for(Troncon troncon : listeAdj.get(currentStation)) { // O(|A|)
					int distance = dist.get(currentStation) + troncon.getDuree();
					// Si la distance est plus courte que dans la structure
					if (distance < dist.get(troncon.getArrivee())) {
						dist.put(troncon.getArrivee(), distance);	// met à jour la distance: O(1) dans le pire cas O(n) comme avec la boucle(while) on risque de parcourir tous les sommets
						chemin.put(troncon.getArrivee(), troncon);
					}
				}
			}
		}
		LinkedList<Troncon> sol = trouveSolution(chemin, dest, source);
		
		new DomCreate(sol, source, dest, fichierSortie, "Dijkstra");
	}
	
	/**
	 * Complexité : O(n)
	 * Cherche la station ayant la distance la plus petite, méthode utilisé pour l'algorithme de Dijkstra
	 * @param stationsAVisite	les stations par lequelles nous ne sommes pas encore passé
	 * @param dist				la structure qui retient les distances
	 * @return
	 */
	private Station getPlusCourteDistance(Set<Station> stationsAVisite, Map<Station, Integer> dist) {
		Station stationPlusProche = null;
		int distancePlusCourte = Integer.MAX_VALUE;
		for (Station stationCourante : stationsAVisite) {
			int distance = dist.get(stationCourante);
			if (distance < distancePlusCourte) {
				distancePlusCourte = distance;
				stationPlusProche = stationCourante;
			}
		}
		return stationPlusProche;
	}
}
