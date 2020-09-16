import java.io.File;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class Graph {
	private Map<String, Set<String>> borders = new HashMap<String, Set<String>>(); // liste d'adjacence

	// imprime les différents pays dans l'ordre d'un parcours DFS depuis la source
	// il n'est pas nécéssaire de vérifier que la source est un code d'un pays
	// existant
	public void dfs(String source) {
		// récursif
		Set<String> isVisited = new HashSet<String>();
		dfsRecursive(source, isVisited);
	}
	
	public void dfsRecursive(String current, Set<String> isVisited) {
		isVisited.add(current);
		System.out.print(current+ " ");
		for (String adjacent: borders.get(current)) {
			if(!isVisited.contains(adjacent)) {
				dfsRecursive(adjacent, isVisited);
			}
		}
	}

	class SAXHandler extends DefaultHandler {
		
		private Set<String> currentBorders;
		private boolean isCountry;
		
		@Override
		public void startElement(String uri, String localName, String qName, Attributes attributes)
				throws SAXException {
			
			if (qName.equalsIgnoreCase("country")) {
				currentBorders = new HashSet<String>();
				String frontieres = attributes.getValue("borders");
				if (frontieres.length() >0) {
					for(String voisins : frontieres.split(",")) {
						currentBorders.add(voisins);
					}
				}
				isCountry = true;
			}
		}
		
		@Override
		public void characters(char[] ch, int start, int length) throws SAXException {
			
			if(isCountry) {
				isCountry = false;
				borders.put(new String(ch,start, length), currentBorders);
			}
		}
	}
	
	
	

	public static void main(String[] args) throws Exception {
		try {
			File inputFile = new File("countries.xml");
			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser saxParser = factory.newSAXParser();
			Graph g = new Graph();
			Graph.SAXHandler userHandler = g.new SAXHandler();
			saxParser.parse(inputFile, userHandler);
			g.dfs("USA");
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}
