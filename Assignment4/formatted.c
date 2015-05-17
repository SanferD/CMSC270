public class FindMostCommonArray {
	public static void main(String[] args) {
		Scanner input = null;
		try {
			input = new Scanner(new File("numbers.txt"));
		}
		catch (Exception ex) {
			ex.printStackTrace();
		}
		int N = 0;
		while(input.hasNextInt()) {
			int unused = input.nextInt();
			N++;
		}
		input.close();
		int[] A = new int[N];
		try {
			input = new Scanner(new File("numbers.txt"));
		}
		catch (Exception ex) {
			ex.printStackTrace();
		}
		int n = 0;
		while(input.hasNextInt()) {
			A[n] = input.nextInt();
			n++;
		}
		input.close();
		int smallest = A[0];
		int largest = smallest;
		for(n = 1;
		n < A.length;
		n++) {
			if (A[n] < smallest) {
				smallest = A[n];
			}
			if (A[n] > largest) {
				largest = A[n];
			}
		}
		int greatestCount = 0;
		int mostCommonNumber = 0;
		for (int x = smallest;
		x <= largest;
		x++) {
			int counter = 0;
			for(n = 0;
			n < A.length;
			n++) {
				if (A[n] == x) {
					counter++;
				}
			}
			if(counter > mostCommonNumber) {
				greatestCount = counter;
				mostCommonNumber = x;
			}
		}
		System.out.println("The number " + mostCommonNumber + " appears most often.");
		System.out.println("It appears " + greatestCount + " times in the file.");
	}
}
