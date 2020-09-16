import java.util.Set;
import java.util.HashSet;

public class Ecole {
	private final String nom;
	private final int nbPlace;
	private Set<Eleve> inscrits;

	public Ecole(String nom, int nbPlace) {
		super();
		this.nom = nom;
		this.nbPlace = nbPlace;
		this.inscrits = new HashSet<Eleve>();
	}

	public String getNom() {
		return nom;
	}

	public int getNbPlace() {
		return nbPlace;
	}

	public boolean ajouterEleve(Eleve e) {
		if (nbPlace == inscrits.size())
			return false;
		if (inscrits.contains(e))
			return false;
		inscrits.add(e);
		return true;
	}

	public boolean estComplet() {
		return inscrits.size() == nbPlace;
	}

	@Override
	public String toString() {
		String s = "Ecole [nom=" + nom + ", nbPlace=" + nbPlace;
		if (!inscrits.isEmpty()) {
			s += ", inscrits=";
			for (Eleve e : inscrits) {
				s += e.getPrenom() + " " + e.getNom() + ",";
			}
			s = s.substring(0, s.length() - 1);
		}
		s += "]";
		return s;
	}

}
