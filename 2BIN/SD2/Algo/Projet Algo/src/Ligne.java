
public class Ligne {
	
	private String nom;
	private String source;
	private String destination;
	private String type;
	private int attenteMoyenne;
	
	public Ligne() {
		super();
	}

	public Ligne(String nom, String source, String destination, String type, int attenteMoyenne) {
		super();
		this.nom = nom;
		this.source = source;
		this.destination = destination;
		this.type = type;
		this.attenteMoyenne = attenteMoyenne;
	}


	public String getNom() {
		return nom;
	}


	public void setNom(String nom) {
		this.nom = nom;
	}


	public String getSource() {
		return source;
	}


	public void setSource(String source) {
		this.source = source;
	}


	public String getDestination() {
		return destination;
	}


	public void setDestination(String destination) {
		this.destination = destination;
	}


	public String getType() {
		return type;
	}


	public void setType(String type) {
		this.type = type;
	}


	public int getAttenteMoyenne() {
		return attenteMoyenne;
	}


	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + attenteMoyenne;
		result = prime * result + ((destination == null) ? 0 : destination.hashCode());
		result = prime * result + ((nom == null) ? 0 : nom.hashCode());
		result = prime * result + ((source == null) ? 0 : source.hashCode());
		result = prime * result + ((type == null) ? 0 : type.hashCode());
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
		Ligne other = (Ligne) obj;
		if (attenteMoyenne != other.attenteMoyenne)
			return false;
		if (destination == null) {
			if (other.destination != null)
				return false;
		} else if (!destination.equals(other.destination))
			return false;
		if (nom == null) {
			if (other.nom != null)
				return false;
		} else if (!nom.equals(other.nom))
			return false;
		if (source == null) {
			if (other.source != null)
				return false;
		} else if (!source.equals(other.source))
			return false;
		if (type == null) {
			if (other.type != null)
				return false;
		} else if (!type.equals(other.type))
			return false;
		return true;
	}

	public void setAttenteMoyenne(int attenteMoyenne) {
		this.attenteMoyenne = attenteMoyenne;
	}


	@Override
	public String toString() {
		return "Ligne [nom=" + nom + ", source=" + source + ", destination=" + destination + ", type=" + type
				+ ", attenteMoyenne=" + attenteMoyenne + "]";
	}
	
	
	

}
