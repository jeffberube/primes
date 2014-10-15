class Primes {

	int max, numthreads;

	public static void main(String[] args) {

		int max = Integer.parseInt(args[1]);
		int numthreads = 		

		if (args.length < 2) {

			System.out.println("Invalid number of arguments.");
			System.out.println("primes <MAX> <NUMTHREADS>");

			return;			

		} else if ( ) {

			

		}

		

	}	

}

class Sieve implements Runnable {

	private int start, end, threadnum, flag = 0, index = 0;
	private int[] primes;
	private long lStartTime, lEndtime, execTime

	public Sieve(int start, int end, int threadnum) {

		this.start = start;
		this.end = end;
		this.threadnum = threadnum;

		this.primes = new int()[(end - start) / 2];

	}

	public void run() {

		lStartTime = new Date().getTime();

		int i, j;

		for (i = start; i < end; ++i) {

			flag = 0;

			for (j = 2; j <= i/2; ++j) {

				if (i % j == 0) {

					flag = 1;
					break;

				}

			}	

			if (!flag) primes[index++] = i;

		}		

		lEndTime = new Date().getTime();

		execTime = lEndTime - lStartTime;

		dumpPrimes();

	}

	public synchronized dumpPrimes() {

		System.out.println("\n\nThread: " + threadnum + "\tStart: " + start + "\tEnd: " + end
							+ "\tExecution time: " + execTime);

		System.out.print("Primes: ");

		int i = 0;

		while (i < index) {

			System.out.print(primes[i] + " ");

		}

	}


}
