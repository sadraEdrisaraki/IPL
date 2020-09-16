import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class Inscription {
	
	private Ecole[] ecoles; // retient toutes les �coles
	private Map<Ecole, Queue<Eleve>> demandes;
	private Map<Eleve, Set<Ecole>> demandesEleves;
	private Set<Eleve> inscriptions; //  eleves d�j� inscrit
	//vous pouvez rajouter des attributs
	
	//� compl�ter: initialisation des attributs
	public Inscription(Ecole... ecoles){
		this.ecoles=ecoles;
		this.demandes = new HashMap<Ecole, Queue<Eleve>>();
		this.demandesEleves = new HashMap<Eleve, Set<Ecole>>();
		this.inscriptions = new HashSet<Eleve>();
		
		for (int i = 0; i < this.ecoles.length; i++) {
			this.demandes.put(this.ecoles[i], new LinkedList<Eleve>());
		}
	}
	
	// enregistre la demande d'inscription d'un �l�ve � une �cole.
	// Lance une RunTimeException si l'�l�ve a d�j� fait 3 demandes d'inscription
	// Complexit�: O(1) 
	public void demandeInscription(Eleve eleve,Ecole ecole){
		//ajoute l'eleve si pas ajouter
		if (!demandesEleves.containsKey(eleve)) {
			demandesEleves.put(eleve, new HashSet<Ecole>());
		}
		
		if (demandesEleves.get(eleve).size() == 3) {
			throw new RuntimeException();
		}
		
		demandesEleves.get(eleve).add(ecole);
		demandes.get(ecole).add(eleve);
		
	}
	
	// parcourt les demandes d'inscription des �l�ves et inscrit les �l�ves selon
	// l'ordre premier arriv� premier servi. Pour inscrire un �l�ve,
	// il faut appeler la m�thode ajouterEleve de la classe Ecole. 
	// Les �l�ves d�j� inscrits dans une autre �cole ne sont pas inscrits.
	// Complexit�: O(n(log(n)))
	
	public void remplirEcole(Ecole ecole) {
		// parcourir toute les �coles pour laqulle il a fait une demande pour voir si l'�l�ves est d�j� inscrit
		while (!demandes.get(ecole).isEmpty()) {
			Eleve aInscrire = demandes.get(ecole).poll();
			if (!inscriptions.contains(aInscrire)) { // eleve dej� insris dans une autre ecole
				if(ecole.ajouterEleve(aInscrire)) {
					inscriptions.add(aInscrire);
				}
			}
		}
		
	}
}
