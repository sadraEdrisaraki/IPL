
public class Troncon {
	
	private Station depart;
	private Station arrivee;
	private int duree;
	private Ligne ligne;
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((arrivee == null) ? 0 : arrivee.hashCode());
		result = prime * result + ((depart == null) ? 0 : depart.hashCode());
		result = prime * result + duree;
		result = prime * result + ((ligne == null) ? 0 : ligne.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Troncon other = (Troncon) obj;
		if (arrivee == null) {
			if (other.arrivee != null)
				return false;
		} else if (!arrivee.equals(other.arrivee))
			return false;
		if (depart == null) {
			if (other.depart != null)
				return false;
		} else if (!depart.equals(other.depart))
			return false;
		if (duree != other.duree)
			return false;
		if (ligne == null) {
			if (other.ligne != null)
				return false;
		} else if (!ligne.equals(other.ligne))
			return false;
		return true;
	}

	public Troncon(Station depart , Station arrivee , int duree , Ligne ligne) {
		this.depart = depart;
		this.arrivee = arrivee;
		this.duree = duree;
		this.ligne = ligne;
	}

	public Station getDepart() {
		return depart;
	}

	public void setDepart(Station depart) {
		this.depart = depart;
	}

	public Station getArrivee() {
		return arrivee;
	}

	public void setArrivee(Station arrivee) {
		this.arrivee = arrivee;
	}

	public int getDuree() {
		return duree;
	}

	public void setDuree(int duree) {
		this.duree = duree;
	}

	public Ligne getLigne() {
		return ligne;
	}

	public void setLigne(Ligne ligne) {
		this.ligne = ligne;
	}

	@Override
	public String toString() {
		return "Troncon [depart=" + depart.getNom() + ", arrivee=" + arrivee.getNom() + ", duree ="+ duree +"]";
	}
	
	

}
