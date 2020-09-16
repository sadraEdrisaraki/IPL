import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class ListeDArc extends Graph{
	
	private ArrayList<Flight> flights; // list d'arcs

	public ListeDArc() {
		super();
		flights = new ArrayList<Flight>();
	}

	@Override
	// Complexité: ?
	protected void ajouterSommet(Airport a) {	
		//à compléter
	}

	@Override
	// Complexité: O(1)
	protected void ajouterArc(Flight f) {
		flights.add(f);
	}

	@Override
	// Complexité: O(m)
	public Set<Flight> arcsSortants(Airport a) {
		
		Set<Flight> vols = new HashSet<Flight>(); 
		
		//O(m)
		for (Flight flight : flights) {
			if (a.equals(flight.getSource())) {
				vols.add(flight);
			}
		}
		
		return vols;
	}

	@Override
	// Complexité: O(m)
	public boolean sontAdjacents(Airport a1, Airport a2) {
		
		for (Flight flight : flights) {
			
			Airport airport_source = flight.getSource();
			Airport airport_dest = flight.getDestination();
			
			if (airport_source.equals(a1) && airport_dest.equals(a2)) {
				return true;
			}
			
			if (airport_source.equals(a2) && airport_dest.equals(a1)) {
				return true;
			}
		}
		return false;
	}

}
