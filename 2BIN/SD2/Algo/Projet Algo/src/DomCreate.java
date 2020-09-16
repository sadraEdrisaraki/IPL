
import java.io.File;
import java.util.LinkedList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.*;

public class DomCreate {
	
	private Document doc;
	private Element rootElement;
	private LinkedList<Troncon> solution;
	private String depart;
	private String arrivee;
	private String fichierNom;
	private String algo;
	
	public DomCreate(LinkedList<Troncon> solution, String depart, String arrivee, String fichierNom, String algo) {
		try {
			this.solution = solution;
			this.depart = depart;
			this.arrivee = arrivee;
			this.fichierNom = fichierNom;
			this.algo = algo;
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			this.doc = dBuilder.newDocument();
			this.createRootElement();
			this.createTrajet();
			this.enregistrementFichier();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void createRootElement() {
		
		this.rootElement =  this.doc.createElement("trajet");
		doc.appendChild(rootElement);
		
		Attr depart = doc.createAttribute("depart");
		depart.setValue(this.depart);
		Attr destination = doc.createAttribute("destination");
		destination.setValue(this.arrivee);
		rootElement.setAttributeNode(depart);
		rootElement.setAttributeNode(destination);
	}
	
	
	private void createTrajet() {
		
		String lignePrecedente = "";
		Element deplacement = null;
		int dureeTotal = 0;
		int nbTronconstotal = 0;
		
		for (Troncon troncon : solution) {
			
			/* Si la ligne est la même que celle précedemment ajouté */
			if (lignePrecedente.equals(troncon.getLigne().getNom())) {
				//Met à jour
				setAttributElement(deplacement, "arrivee", troncon.getArrivee().getNom());
				
				int nbtroncon = Integer.parseInt(deplacement.getAttribute("nbTroncon"));
				nbtroncon += 1;
				setAttributElement(deplacement, "nbTroncon", Integer.toString(nbtroncon));
				
				int duree = Integer.parseInt(deplacement.getAttribute("duree"));
				duree += troncon.getDuree();
				setAttributElement(deplacement, "duree", Integer.toString(duree));
				
				dureeTotal += troncon.getDuree();
				nbTronconstotal += 1;
				
			} else {
				deplacement = this.doc.createElement("deplacement");
				deplacement.appendChild(doc.createTextNode(troncon.getLigne().getNom()));
				this.rootElement.appendChild(deplacement);
				
				if (this.algo.equalsIgnoreCase("DFS")) {
					setAttributElement(deplacement, "attenteMoyenne", Integer.toString(troncon.getLigne().getAttenteMoyenne()));
				} else {
					setAttributElement(deplacement, "attenteMoyenne", Integer.toString(0));
				}
				setAttributElement(deplacement, "arrivee", troncon.getArrivee().getNom());
				setAttributElement(deplacement, "depart", troncon.getDepart().getNom());
				setAttributElement(deplacement, "direction", troncon.getLigne().getDestination());
				setAttributElement(deplacement, "duree", Integer.toString(troncon.getDuree()));
				setAttributElement(deplacement, "nbTroncon", Integer.toString(1));
				setAttributElement(deplacement, "type", troncon.getLigne().getType());
				
				dureeTotal += Integer.parseInt(deplacement.getAttribute("attenteMoyenne"));
				dureeTotal += troncon.getDuree();
				nbTronconstotal += 1;
			}
			lignePrecedente = troncon.getLigne().getNom();
		}
		
		
		setAttributElement(rootElement, "duree", Integer.toString(dureeTotal)); // Attente moyene + duree du trajet
		setAttributElement(rootElement, "nbTroncons", Integer.toString(nbTronconstotal));
	}
	
	/**
	 * Crée un attribut pour l'élement en question 
	 * @param element
	 * @param nomAttribut
	 * @param valeurAttribut
	 */
	private void setAttributElement(Element element, String nomAttribut, String valeurAttribut) {
		
		Attr currentAttribut = doc.createAttribute(nomAttribut);
		currentAttribut.setValue(valeurAttribut);
		element.setAttributeNode(currentAttribut);
	}
	
	private void enregistrementFichier() throws TransformerException {
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		DOMSource source = new DOMSource(this.doc);
		StreamResult result = new StreamResult(new File(fichierNom));
		transformer.transform(source, result);
		
	}
	
	
}
