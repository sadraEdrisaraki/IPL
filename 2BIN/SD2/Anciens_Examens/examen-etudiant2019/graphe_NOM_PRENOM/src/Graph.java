import java.io.File;
import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Queue;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Graph {
	
	// Vous ne pouvez pas rajouter d'autres attributs
	private HashMap<Integer, String>  correspondanceIndiceAirport;
	private HashMap<String, Integer>  correspondanceAirportIndice;
	private String[][] matrice; // matrice d'adjacence 
	
	// A COMPLETER
	// lit le fichier xml et remplit les 3 structures de données
	public Graph(String xmlFile) throws Exception{
		
		correspondanceIndiceAirport = new HashMap<Integer, String>();
		correspondanceAirportIndice = new HashMap<String, Integer>();
		
		try {
			File xmlfile = new File(xmlFile);
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			
			Document document = dBuilder.parse(xmlfile);
			
			NodeList airports = document.getElementsByTagName("airport"); // ensemble des noeuds airport
			
			matrice = new String[airports.getLength()][airports.getLength()];
			
			for (int i = 0; i < airports.getLength(); i++) {
				Node nAirport = airports.item(i);	// récupère le noeud 
				Element eAirport = (Element) nAirport;
				
				correspondanceIndiceAirport.put(i, eAirport.getAttribute("iata"));
				correspondanceAirportIndice.put(eAirport.getAttribute("iata"), i);
			}
			
			NodeList flights = document.getElementsByTagName("flight"); // ensemble de noeuds vols 
		
			for (int i = 0; i < flights.getLength(); i++) {
				Node nFlight = flights.item(i);
				Element eFlight = (Element) nFlight;
				
				Element parent = (Element) eFlight.getParentNode();
				
				int source = correspondanceAirportIndice.get(parent.getAttribute("iata"));
				int destination = correspondanceAirportIndice.get(eFlight.getTextContent());
				matrice[source][destination] = eFlight.getAttribute("airline");
			}
			
			correspondanceAirportIndice.forEach((k,v)->{System.out.println(k +"=" + v);});
			System.out.println(matrice[0][0]);
			
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
	
	// A COMPLETER
	// imprime les code iata des aeroports dans l'ordre d'un parcours BFS depuis la
	// source
	// il n'est pas necessaire de verifier que la source est un code iata d'un
	// aeroport existant
	public void bfs(String source) {
		
		Queue<String> file = new ArrayDeque<String>(); 
		Set<String> isVisited = new HashSet<String>();
		
		file.add(source);
		isVisited.add(source);
		
		while(!file.isEmpty()) {
			String current = file.poll();
			System.out.print(current + " ");
			int indiceCurrent = correspondanceAirportIndice.get(current);
			
			for (int i = 0; i < matrice[indiceCurrent].length; i++) { // parcours les sommets adjacents
				String adjacent = correspondanceIndiceAirport.get(i);
				if (!isVisited.contains(adjacent)) { // le sommet adjacent n'a pas été visité
					file.add(adjacent);
					isVisited.add(adjacent);
				}
			}
		}
	}
	
	
	public static void main(String[] args) throws Exception {
		Graph g= new Graph("flight.xml");
		g.bfs("JFK");
	}
}
