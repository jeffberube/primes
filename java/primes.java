class Primes {

	int max, numthreads;

	public static void main(String[] args) {

	}	

}

class Sieve implements Runnable {

	private int start, end;
	private int[] primes;

	public Sieve(int start, int end) {

		this.start = start;
		this.end = end;

		this.primes = new int()[(end - start) / 2];

	}

	public void run() {

		

	}


}
