import java.util.ArrayDeque;
import java.util.Deque;
import java.util.NoSuchElementException;

public class PriorityQueue<Key> {
	private Key[] pq;
	private int n;// number of items on priority queue

	/**
	 * Initializes an empty priority queue with the given initial capacity.
	 *
	 * @param initCapacity
	 *            the initial capacity of this priority queue
	 */
	@SuppressWarnings("unchecked")
	public PriorityQueue(int initCapacity) {
		pq = (Key[]) new Object[initCapacity + 1];
		n = 0;
	}

	public boolean isEmpty() {
		return n == 0;
	}

	public int size() {
		return n;
	}

	private void swim(int k) {
		while (k > 1 && less(k / 2, k)) {
			exch(k, k / 2);
			k = k / 2;
		}
	}

	private void sink(int k) {
		while (2 * k <= n) {
			int j = 2 * k;
			if (j < n && less(j, j + 1))
				j++;
			if (!less(k, j))
				break;
			exch(k, j);
			k = j;
		}
	}

	/**
	 * Adds a new key to this priority queue.
	 *
	 * @param x
	 *            the new key to add to this priority queue
	 */
	public void insert(Key x) {
		pq[++n] = x;
		swim(n);
	}

	/**
	 * Removes and returns a largest key on this priority queue.
	 *
	 * @return a largest key on this priority queue
	 * @throws NoSuchElementException
	 *             if this priority queue is empty
	 */
	public Key delMax() {
		Key max = pq[1];
		exch(1, n--);
		sink(1);
		return max;
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	private boolean less(int i, int j) {
		return ((Comparable) pq[i]).compareTo(pq[j]) < 0;
	}

	private void exch(int i, int j) {
		Key swap = pq[i];
		pq[i] = pq[j];
		pq[j] = swap;
	}

	//les valeurs des n�uds de l�arbre dans l�ordre dfs
	public void dfs() {
		
		Deque<Integer> stack = new ArrayDeque<Integer>(); // contient les positions dans le tableau
		
		Integer current = 1; // l'indice du sommet � visit�
		stack.push(current);
		
		while(!stack.isEmpty()) {
			current = stack.pop(); // on pop car on ne reviendra plus sur le sommet comme on a parcouru ses 2 fils. comme on est dans un arbre on peut faire �a
			System.out.print(pq[current] + " ");
			if ((2*current +1) <= this.n) {
				stack.push(2*current +1);
			}
			if ((2*current) <= this.n) {
				stack.push(2*current);
			}
		}
	}


	public static void main(String[] args) {
		PriorityQueue<Integer> pq = new PriorityQueue<Integer>(10);
		pq.insert(57);
		pq.insert(85);
		pq.insert(44);
		pq.insert(21);
		pq.insert(23);
		pq.insert(52);
		pq.insert(17);
		pq.insert(7);
		pq.insert(95);
		pq.dfs();
	}

}
