import java.io.File;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

public class Main {
	public static void main(String[] args) {
		try {
			File inputFile = new File("stib.xml");
			//File inputFile = new File("stibattente0.xml");
			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser saxParser = factory.newSAXParser();
			SAXHandler userhandler = new SAXHandler();
			saxParser.parse(inputFile, userhandler);
			Graph g = userhandler.getGraph();
			g.calculerCheminMinimisantNombreTroncons("MALIBRAN", "ALMA", "output.xml");
		    g.calculerCheminMinimisantTempsTransport("MALIBRAN", "ALMA", "output2.xml");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
