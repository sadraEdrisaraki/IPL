import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;


public class ProgrammesEtudiants {
	
	// ajouter/modifier attributs ici
	private Set<Etudiant> etudiants = new TreeSet<Etudiant>(Comparator.comparing(Etudiant::getNbEctsValides).reversed().thenComparing(Etudiant::getNumeroRegistreNational));
	private Map<Etudiant, Set<UniteEnseignement>> etudiantsUEValide = new HashMap<Etudiant, Set<UniteEnseignement>>();
	
	public ProgrammesEtudiants(Etudiant... etudiants) {
		
		for (Etudiant etudiant : etudiants) {
			System.out.println(etudiant.hashCode() + " " + etudiant.getNom());
			this.etudiants.add(etudiant);
			this.etudiantsUEValide.put(etudiant, new HashSet<UniteEnseignement>());
		}
		//initialise ce qu'il faut initialiser si necessaire
		
		System.out.println("-----------------");

	}

	// A COMPLETER	
	// Enregistre la validation de l'unit� d'enseignement par l'�tudiant et met �
	// jour le nombre d'ects valid� par l'�tudiant.
	// Si l'unit� d'enseignement a d�j� �t� valid�e par l'�tudiant, la m�thode 
	// lance une RuntimeException avec le message 'ue d�j� valid�e'
	public void valider(Etudiant e, UniteEnseignement ue) {
		
		System.out.println(e.hashCode() +" " + e.getNom());
		if (!etudiantsUEValide.get(e).add(ue)) { // set donc peut pas ajouter 2 fois la m�me valeur; renvoie false si la valeur est d�j� pr�sente
			throw new RuntimeException("ue d�j� valider");
		}
		
		etudiants.remove(e);// O(log (n))
		e.setNbEctsValides(e.getNbEctsValides() + ue.getNbEcts());
		etudiants.add(e); // O(Log(n)
		
		//O(logn(n))
		/*
		if (etudiantsUEValide.get(e).add(ue)) { // ne contient pas l'ue dans la liste
			etudiantsUEValide.get(e).add(ue); // ajoute l'ue 
			etudiants.remove(e); // (O(log(n))
			e.setNbEctsValides(e.getNbEctsValides() + ue.getNbEcts());
			etudiants.add(e); // (O(log(n))
		} else {
			throw new RuntimeException("ue d�j� valid�e");
		}
		*/
	}
	
	// A COMPLETER
	// affiche la liste de tous les �tudiants (pr�nom, nom et nombre d'ects valid�s)
	// tri�s par le nombre d'ects valid�s
	// Voici un exemple de sortie attendue:
	// Alain Delcourt 10 ects
	// Pol Durant 8 ects
	// Jean Michel 0 ects
	// Si deux �tudiants ont le meme nombre d'ects valid�s, on affiche 
	// les deux �tudiants dans n'importe quel sens.
	public void afficherEtudiantsTriesParEcts() {
		
		Iterator<Etudiant> it = etudiants.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}
	}
	
	public static void main(String[] args) throws InterruptedException {
		Etudiant e1= new Etudiant(123456, "Durant", "Pol");
		Etudiant e2= new Etudiant(123453, "Delcourt", "Alain");
		Etudiant e3= new Etudiant(123452, "Michel", "Jean");
		ProgrammesEtudiants p= new ProgrammesEtudiants(e1,e2,e3);
		UniteEnseignement sd2= new UniteEnseignement("SD2", 4);
		UniteEnseignement bd2= new UniteEnseignement("BD2", 6);
		UniteEnseignement mobile= new UniteEnseignement("Mobile", 4);
		p.valider(e1, sd2);
		p.valider(e1, mobile);
		p.valider(e2, bd2);
		p.valider(e2, mobile);
		p.afficherEtudiantsTriesParEcts();
		Thread.sleep(50); //cette ligne est uniquement presente pour l'affichage
		p.valider(e1, mobile);
	}
}
