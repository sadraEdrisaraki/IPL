
public class Test {
	public static void main(String[] args) throws InterruptedException{
		Ecole ipl= new Ecole("IPL",2);
		Ecole ucl= new Ecole("UCL",1);
		Ecole ephec= new Ecole("ephec",1);
		Ecole ulb= new Ecole("ulb",1);
		Eleve cd= new Eleve ("Christophe", "Damas");
		Eleve jvm = new Eleve ("Jose","Vander Meulen");
		Eleve el= new Eleve("Emmeline","Leconte");
		Eleve gs= new Eleve("Gregory","Seront");
		Inscription i=new Inscription(ipl,ucl,ephec,ulb);
		i.demandeInscription(cd, ipl);
		i.demandeInscription(cd, ucl);
		i.demandeInscription(jvm, ipl);
		i.demandeInscription(jvm, ucl);
		i.demandeInscription(el, ipl);
		i.demandeInscription(el, ucl);
		i.demandeInscription(gs, ipl);
		i.demandeInscription(gs, ucl);
		i.demandeInscription(gs, ulb);
		i.remplirEcole(ipl);
		i.remplirEcole(ucl);
		i.remplirEcole(ephec);
		i.remplirEcole(ulb);
		System.out.println(ipl);
		System.out.println("--------------");
		System.out.println(ucl);
		System.out.println("--------------");		
		System.out.println(ephec);
		System.out.println("--------------");
		System.out.println(ulb);
		System.out.println("--------------");
		Thread.sleep(5);
		i.demandeInscription(gs, ephec);
	}
}
