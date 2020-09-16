package com.example.recapapp.models.domaine;

public class GenerateurDAddition extends GenerateurDeCalculs {


	public GenerateurDAddition(Configuration configuration) {
		super(configuration);
	}


	@Override
	public Calcul fournirCalcul() {
		int terme1 = getConfiguration().getMin()
				+ (int) (Math.random() * ((getConfiguration().getMax() - getConfiguration().getMin()) + 1));
		int terme2 = getConfiguration().getMin()
				+ (int) (Math.random() * ((getConfiguration().getMax() - getConfiguration().getMin()) + 1));
		
		return new Calcul(terme1 + " + " + terme2 + " = ", terme1+terme2);
	}

}
