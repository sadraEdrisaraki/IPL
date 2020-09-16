import java.io.File;
import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Graph {
			// Sommet 		// Arc
	private Map<String, Set<String>> borders = new HashMap<String, Set<String>>(); // liste d'adjacence

	// à partir du fichier xml, construit la structure de donnée borders.
	// les clés de borders sont les codes cca3 des différents pays
	// les valeurs sont des ensembles de String contenant les codes cca3 des pays frontaliers
	public Graph(String xmlFile) throws Exception {
	
		try {
			File xmlfile = new File(xmlFile);
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			
			Document document = dBuilder.parse(xmlfile);
			
			NodeList countries = document.getElementsByTagName("country"); // recupère tous les elements country
	
			
			for (int i = 0; i < countries.getLength(); i++) {
				Node nCountry = countries.item(i);
				Element eCountry = (Element) nCountry; // element XML; on peut récupéré des attributs
				
				String cca3 = eCountry.getAttribute("cca3");
				String frontaliers = eCountry.getAttribute("borders");
				
				Set<String> frontieres = new HashSet<>(); 
				if (frontaliers.length() > 0) { // evite de split quand le chaine est = ""
					String front[] = frontaliers.split(","); // borders="AZE,GEO,IRN,TUR" faut split
					for (int j = 0; j < front.length; j++) {
						frontieres.add(front[j]);
					}
				}
				
				this.borders.put(cca3, frontieres);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}		
	
	}

	// imprime les différents pays dans l'ordre d'un parcours BFS depuis la source.
	// il n'est pas nécéssaire de vérifier que la source est un code d'un pays
	// existant
	public void bfs(String source) {
		
		Queue<String> noeudsAVisite = new ArrayDeque<>(); //file 
		Set<String> dejaVisite = new HashSet<>(); // noeud marqué
		
		// Marque la source et dis qu'on doit encore la visité; comme ça on rentre dans la boucle
		noeudsAVisite.add(source);
		dejaVisite.add(source);
		
		while (!noeudsAVisite.isEmpty()) {
			
			String paysCourant = noeudsAVisite.poll();
			System.out.print(paysCourant + " ");
		
			for(String frontieres : borders.get(paysCourant)) {
				if (!dejaVisite.contains(frontieres)) { // le pays n'a pas été visité 
					noeudsAVisite.add(frontieres);
					dejaVisite.add(frontieres);
				}
			}
		}
	}

	//renvoie le nombre de composantes connexes du graphe
	public int nbComposantesConnexes() {
		int nbComposantesConnexes = 0;
		Set<String> dejaVisite = new HashSet<>();
		
		for (Entry<String, Set<String>> entry: borders.entrySet()) {
			
			if (!dejaVisite.contains(entry.getKey())) {
				nbComposantesConnexes++;
				dfs(entry.getKey(), dejaVisite);
			}
		}

		return nbComposantesConnexes;
	}
	
	// dfs récursif
	public void dfs(String noeudCourrant, Set<String> dejaVisite) {
		dejaVisite.add(noeudCourrant);
		
		for (String limitrophes : borders.get(noeudCourrant)) { // noeud adjacent(=fils) au sommet courrant
			if (!dejaVisite.contains(limitrophes)) {
				dfs(limitrophes, dejaVisite);
			}
		}
	}

	public static void main(String[] args) throws Exception {
		Graph g = new Graph("countries.xml");
		g.bfs("USA");
		System.out.println();
		System.out.println(g.nbComposantesConnexes());
	}
}
