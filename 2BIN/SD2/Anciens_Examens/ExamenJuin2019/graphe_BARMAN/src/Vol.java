
public class Vol {
	private final String iataSource;
	private final String iataDestination;
	private final String compagnie;

	public Vol(String iataSource, String iataDestination, String compagnie) {
		this.iataSource = iataSource;
		this.iataDestination = iataDestination;
		this.compagnie = compagnie;
	}
	public String getIataSource() {
		return iataSource;
	}
	public String getIataDestination() {
		return iataDestination;
	}
	public String getCompagnie() {
		return compagnie;
	}
	@Override
	public String toString() {
		return "Vol [iataSource=" + iataSource + ", iataDestination=" + iataDestination + ", compagnie=" + compagnie
				+ "]";
	}
}
