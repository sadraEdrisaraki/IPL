package com.example.recapapp.models.domaine;

public class Configuration {
	private int min;
	private int max;

	public Configuration(int min, int max) {
		this.min = min;
		this.max = max;
	}

	public int getMax() {
		return max;
	}

	public int getMin() {
		return min;
	}

	public void setMin(int min) {
		if (max > min) {
			this.min = min;
		}

	}

	public void setMax(int max) {
		if (max > min) {
			this.max = max;
		}

	}

}
