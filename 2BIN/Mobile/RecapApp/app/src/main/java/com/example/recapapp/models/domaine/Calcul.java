package com.example.recapapp.models.domaine;

public class Calcul {
	private String calcul;
	private double res;

	public Calcul(String calcul, double res) {
		super();
		this.calcul = calcul;
		this.res = res;
	}

	public String getCalcul() {
		return calcul;
	}

	public double getRes() {
		return res;
	}
}
