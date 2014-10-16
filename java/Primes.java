/*
 * @Author:	Jeff Berube
 * @Title:	Primes (Java)
 * @Description:	Finds all the primes from 1 to MAX using NUMTHREADS threads.
 *
 * @Usage:	primes <MAX> <NUMTHREADS>
 *
 *		<MAX>		Integer number between 4 and MAXINT (Usually 2^31).
 *				The program will calculate primes between 1 and MAX.
 *
 *		<NUMTHREADS>	Integer number between 1 and 50.
 *				The program will split the workload amongst NUMTHREADS
 *				threads.
 *
 */

public class Primes {

	/* Define class variables */
	public static int max, numthreads;

	public static void main(String[] args) {

		/* Test to see the minimum of arguments is met */
		if (args.length < 2) {

			System.out.println("Invalid number of arguments.");
			System.out.println("Usage: primes <MAX> <NUMTHREADS>");

			return;			

		}

		/* Parse integers out of command line arguments */
		max = Integer.parseInt(args[0]);
		numthreads = Integer.parseInt(args[1]);

		/* Test error conditions before running program */
		if (max < 4) {
			
			System.out.println("MAX must be greater than 4.");
			return;

		} else if (numthreads < 1 || numthreads > 50) {
		
			System.out.println("NUMTHREADS must be between 1 and 50");
			return;

		}

		/* Create variables */
		int i = 0, interval, start, end;
		Thread[] threads = new Thread[numthreads];

		interval = max / numthreads;

		/* Create threads */
		while (i < numthreads) {

			start = (i * interval) + 1;

			if (i == numthreads - 1 && max % numthreads != 0)
				interval = max / numthreads + (max % numthreads);

			end = start + interval - 1;

			threads[i] = new Thread(new Sieve(start, end, i));
			threads[i].start();
	
			i++;

		}

		/* Wait on threads to finish */
		i = 0;

		while (i < numthreads) {
		
			try {

				threads[i++].join();
			
			} catch (InterruptedException ie) {}

		}

		/* One last little output for prettiness */
		System.out.println("\n\n");

	}	

}

class Sieve implements Runnable {

	private int start, end, threadnum, flag = 0, index = 0;
	private int[] primes;
	private long lStartTime, lEndTime, execTime;

	public Sieve(int start, int end, int threadnum) {

		this.start = start;
		this.end = end;
		this.threadnum = threadnum;

		this.primes = new int[(end - start) / 2];

	}

	public void run() {

		/* Store time at start of thread */
		lStartTime = System.currentTimeMillis();

		/* Super magical sieve algorithm */
		int i, j;

		for (i = start; i < end; ++i) {

			flag = 0;

			for (j = 2; j <= i/2; ++j) {

				if (i % j == 0) {

					flag = 1;
					break;

				}

			}	

			/* If number is prime, store in array */
			if (flag == 0) primes[index++] = i;

		}		

		/* Calculate thread runtime */
		execTime = System.currentTimeMillis() - lStartTime;

		/* Output results */
		dumpPrimes();

	}

	/* Dumps all the primes found in the thread to standard output */
	public synchronized void dumpPrimes() {

		synchronized (System.out) {

			System.out.println("\n\nThread: " + threadnum + "\tStart: " 
				+ start + "\tEnd: " + end 
				+ "\tExecution time: " + execTime + "ms");

			System.out.print("Primes: ");

			int i = 0;

			while (i < index) {

				System.out.print(primes[i] + " ");
				i++;

			}

		}

	}


}
