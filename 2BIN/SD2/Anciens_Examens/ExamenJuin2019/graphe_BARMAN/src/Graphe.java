import java.io.File;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Queue;
import java.util.Set;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class Graphe {
	
	private List<Vol> vols; // liste d'arc

	// A COMPLETER
	class SAXHandler extends DefaultHandler {
		
		private String currentSourceAirport;
		private String currentDestinationAirport;
		private String airline;
		private boolean isFlight;
		
		@Override
		public void startDocument() throws SAXException {
			vols = new ArrayList<Vol>();
		}
		
		@Override
		public void startElement(String url, String localName, String qName, Attributes attributes) throws SAXException {
			
			
			if(qName.equalsIgnoreCase("airport")) {
				currentSourceAirport = attributes.getValue("iata");
			}
			
			if(qName.equalsIgnoreCase("flight")) {
				airline = attributes.getValue("airline");
				isFlight = true;
			}
		}
		
		@Override
		public void characters(char[] ch, int start, int length) throws SAXException {
			// Chaque CDATA est traité différement; voila pourquoi il y a des conditions
			if (isFlight) {
				currentDestinationAirport = new String(ch, start, length);
				vols.add(new Vol(currentSourceAirport, currentDestinationAirport, airline));
				isFlight = false;
			}
		}
	}

	// A COMPLETER
	// imprime les code iata des aeroports dans l'ordre d'un parcours BFS depuis la
	// source
	// il n'est pas necessaire de verifier que la source est un code iata d'un
	// aeroport existant
	public void bfs(String source) {
		
		Queue<String> file = new ArrayDeque<String>(); // file
		Set<String> isVisited = new HashSet<>();	// marquage
		
		file.add(source);
		isVisited.add(source);
		String current;
		
		while (!file.isEmpty()) {
			current = file.poll();
			System.out.println(current);
			for (int i = 0; i < vols.size(); i++) {
				String depart = vols.get(i).getIataSource();
				String destination = vols.get(i).getIataDestination();
				if (depart.equals(current) && !isVisited.contains(destination)) {
					file.add(destination);
					isVisited.add(destination);
				}
			}
		}
		
	}

	public static void main(String[] args) throws Exception {
		try {
			File inputFile = new File("vols.xml");
			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser saxParser = factory.newSAXParser();
			Graphe g = new Graphe();
			Graphe.SAXHandler userHandler = g.new SAXHandler();
			saxParser.parse(inputFile, userHandler);
			g.bfs("JFK");
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}
