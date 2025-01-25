#include<iostream>
using namespace std;


class IntervalHeap
{
	int hsize; //number of elements in heap;
	int maxsize; //size of the array
	int** h;
public:

	IntervalHeap(int s = 100)
	{
		maxsize = s;
		hsize = 0;
		h = new int* [2];
		h[0] = new int[maxsize];     //store the lower end of closed interval
		h[1] = new int[maxsize];     //store the higher end of closed interval
	}

	void initialize()
	{
		for (int i = 0;i < 2;i++)
		{
			for (int j = 0;j < maxsize;j++)
			{
				h[i][j] = -1;
			}
		}
	}


	// check for up n down values
	bool validity(int left, int right)
	{
		if (left < right)
		{
			return true;
		}
		return false;
	}

	void swap(int*& arr, int i, int parent)
	{
		int temp = arr[parent];
		arr[parent] = arr[i];
		arr[i] = temp;
	}

	void swap(int**& h, int hsize)
	{
		int temp = h[0][(hsize / 2) - 1];
		h[0][(hsize / 2) - 1] = h[1][(hsize / 2) - 1];
		h[1][(hsize / 2) - 1] = temp;
	}

	// reheap up for min heap

	void reheapUp_min(int*& arr, int i)
	{

		int parent;
		if (i > 0)
		{ // tree is not empty
			parent = (i - 1) / 2;
			if (arr[parent] > arr[i])
			{
				swap(arr, i, parent);
				if (!validity(h[0][parent], h[1][parent]))
				{
					shifting(h, parent);
				}
				reheapUp_min(arr, parent);

			}
		}

	}


	// reheap down for min

	void reheapDown_min(int*& arr, int n, int i)
	{

		int leastChild, rightChild, leftChild;
		leftChild = 2 * i + 1;
		rightChild = 2 * i + 2;
		if (leftChild <= n)
		{ // left child is part of the heap
			if (leftChild == n) // only one child

				leastChild = leftChild;

			else {

				if (arr[leftChild] <= arr[rightChild])

					leastChild = leftChild;        // change

				else

					leastChild = rightChild;    //change

			}
			if (arr[i] > arr[leastChild])
			{
				swap(arr, i, leastChild);
				if (!validity(h[0][leastChild], h[1][leastChild]))
				{
					shifting(h, leastChild);
				}
				reheapDown_min(arr, n, leastChild);
			}
		}

	}


	// reheap up for max heap

	void reheapUp_max(int*& arr, int i)
	{

		int parent;
		if (i > 0)
		{ // tree is not empty
			parent = (i - 1) / 2;
			if (arr[parent] < arr[i])
			{
				swap(arr, i, parent);
				if (!validity(h[0][parent], h[1][parent]))
				{
					shifting(h, parent);
				}
				reheapUp_max(arr, parent);

			}
		}

	}

	// reheap down for max

	void reheapDown_max(int*& arr, int n, int i)
	{
		int maxChild, rightChild, leftChild;
		leftChild = 2 * i + 1;
		rightChild = 2 * i + 2;
		if (leftChild <= n)
		{                               // left child is part of the heap
			if (leftChild == n)
			{                           // only one child
				maxChild = leftChild;
			}

			else
			{

				if (arr[leftChild] <= arr[rightChild])

					maxChild = rightChild;

				else

					maxChild = leftChild;

			}
			if (arr[i] < arr[maxChild])
			{
				swap(arr, i, maxChild);
				if (!validity(h[0][maxChild], h[1][maxChild]))
				{
					shifting(h, maxChild);
				}
				reheapDown_max(arr, n, maxChild);
			}
		}

	}


	// inserting
	void insert(int d)
	{
		if (hsize == 0)    // inserting at the very start
		{
			h[0][0] = d;
			hsize++;
		}

		// odd track

		else if (hsize % 2 != 0)   // when size is odd
		{
			if (h[1][hsize / 2] == -1)
			{
				h[1][hsize / 2] = d;
				hsize++;

				if (!validity(h[0][(hsize / 2) - 1], h[1][(hsize / 2) - 1]))
				{
					swap(h, hsize);
				}
			}
			else if (h[0][hsize / 2] == -1)
			{
				h[0][hsize / 2] = d;
				hsize++;

				if (!validity(h[0][(hsize / 2) - 1], h[1][(hsize / 2) - 1]))
				{
					swap(h, hsize);
				}

			}

			reheapUp_max(h[1], (hsize / 2) - 1);
			reheapUp_min(h[0], (hsize / 2) - 1);

			if (!validity(h[0][(hsize / 2) - 1], h[1][(hsize / 2) - 1]))
			{
				swap(h, hsize);
			}
		}

		//even track

		else                     // when size is even
		{
			if (d < h[0][(hsize / 2) - 1])
			{
				h[0][hsize / 2] = d;
				hsize++;
				reheapUp_min(h[0], (hsize / 2));
			}
			else if (d > h[1][(hsize / 2) - 1])
			{
				h[1][hsize / 2] = d;
				hsize++;
				reheapUp_max(h[1], (hsize / 2));
			}
			else
			{
				h[0][hsize / 2] = d;
				hsize++;
				reheapUp_min(h[0], (hsize / 2));
			}
		}

	}


	//deleting
	void deletion()
	{
		cout << "Deletion performed\n";
		// even track
		if (hsize % 2 == 0)
		{
			int lmin = h[0][(hsize / 2) - 1];
			h[0][0] = lmin;
			int lmax = h[1][(hsize / 2) - 1];
			h[1][0] = lmax;
			h[0][(hsize / 2) - 1] = -1;
			h[1][(hsize / 2) - 1] = -1;
			hsize = hsize - 2;
			reheapDown_min(h[0], (hsize / 2) - 1, 0);
			reheapDown_max(h[1], (hsize / 2) - 1, 0);

			/*if (!validity(h[0][(hsize / 2) - 1], h[1][(hsize / 2) - 1]))
			{
				swap(h, hsize);
			}*/
		}

		//odd track
		else if (hsize % 2 != 0)
		{
			if (h[1][hsize / 2] == -1)  // case when max heap is empty
			{
				int lmin = h[0][hsize / 2];
				h[0][0] = lmin;
				h[0][hsize / 2] = -1;
				hsize = hsize - 1;
				reheapDown_min(h[0], (hsize / 2) - 1, 0);

				int lmax = h[1][(hsize / 2) - 1];
				h[1][0] = lmax;
				h[1][(hsize / 2) - 1] = -1;
				hsize = hsize - 1;
				reheapDown_max(h[1], (hsize / 2) - 1, 0);
			}

			else if (h[0][hsize / 2] == -1)  // case when min heap is empty
			{
				int lmax = h[1][hsize / 2];
				h[1][0] = lmax;
				h[1][hsize / 2] = -1;
				hsize--;
				reheapDown_max(h[1], (hsize / 2) - 1, 0);

				int lmin = h[0][(hsize / 2) - 1];
				h[0][0] = lmin;
				h[0][(hsize / 2) - 1] = -1;
				hsize--;
				reheapDown_min(h[0], (hsize / 2) - 1, 0);
			}
		}
	}


	// searching

	bool EvensearchMin(int s, int u)
	{
		int i = 0;
		while (h[0][i] != -1 && h[0][i] != s)
		{
			i++;
		}
		if (h[0][i] == s)
		{
			h[0][i] = u;
			if (!validity(h[0][i], h[1][i]))
			{
				shifting(h, i);
			}
			reheapUp_min(h[0], i);
			reheapUp_max(h[1], i);
			reheapDown_min(h[0], ((hsize / 2) - 1), 0);
			reheapDown_max(h[1], ((hsize / 2) - 1), 0);

			return true;
		}
		return false;
	}


	bool EvensearchMax(int s, int u)
	{
		int i = 0;
		int j = 0;
		while (h[1][i] != -1 && h[1][i] != s)
		{
			i++;
		}
		if (h[1][i] == s)
		{
			h[1][i] = u;
			if (!validity(h[0][i], h[1][i]))
			{
				shifting(h, i);
			}
			reheapUp_max(h[1], i);
			reheapUp_min(h[0], i);
			reheapDown_max(h[1], ((hsize / 2) - 1), i);
			reheapDown_min(h[0], ((hsize / 2) - 1), i);

			return true;
		}
		return false;
	}



	bool OddsearchMin(int s, int u)
	{
		int i = 0;
		while (h[0][i] != -1 && h[0][i] != s)
		{
			i++;
		}
		if (h[0][i] == s)
		{

			if (i != hsize / 2)
			{
				if (h[0][hsize / 2] == -1)
				{
					h[0][i] = u;

					shifting(h, hsize / 2);

					if (!validity(h[0][i], h[1][i]))
					{
						shifting(h, i);
					}
					reheapUp_min(h[0], i);
					reheapUp_max(h[1], i);
					reheapDown_min(h[0], ((hsize / 2)), i);
					reheapDown_max(h[1], ((hsize / 2) - 1), i);
				}
				else
				{
					h[0][i] = u;
					if (!validity(h[0][i], h[1][i]))
					{
						shifting(h, i);
					}
					reheapUp_min(h[0], i);
					reheapUp_max(h[1], i);
					reheapDown_min(h[0], ((hsize / 2)), i);
					reheapDown_max(h[1], ((hsize / 2) - 1), i);
				}
			}
			else
			{
				if (i == hsize / 2)
				{
					h[0][i] = u;
					reheapUp_min(h[0], i);
				}
			}
			return true;
		}
		return false;
	}




	bool OddsearchMax(int s, int u)
	{
		int i = 0;
		while (h[1][i] != -1 && h[1][i] != s)
		{
			i++;
		}
		if (h[1][i] == s)
		{

			if (i != hsize / 2)
			{
				if (h[1][hsize / 2] == -1)
				{
					h[1][i] = u;

					shifting(h, hsize / 2);

					if (!validity(h[0][i], h[1][i]))
					{
						shifting(h, i);
					}
					reheapUp_min(h[0], i);
					reheapUp_max(h[1], i);
					reheapDown_min(h[0], ((hsize / 2) - 1), i);
					reheapDown_max(h[1], ((hsize / 2)), i);
				}

				else if (h[0][hsize / 2] == -1)
				{
					h[1][i] = u;

					if (!validity(h[0][i], h[1][i]))
					{
						shifting(h, i);
					}
					reheapUp_min(h[0], i);
					reheapUp_max(h[1], i);
					reheapDown_min(h[0], ((hsize / 2) - 1), i);
					reheapDown_max(h[1], ((hsize / 2)), i);
				}
			}
			else
			{
				if (i == hsize / 2)
				{
					h[1][i] = u;
					reheapUp_max(h[1], i);
				}
			}
			return true;
		}
		return false;
	}


	void shifting(int**& h, int i)
	{
		int temp = h[0][i];
		h[0][i] = h[1][i];
		h[1][i] = temp;
	}

	// updation

	void update(int s, int u)
	{
		cout << "Updating\n";

		if (hsize % 2 == 0)
		{
			EvensearchMin(s, u);
			EvensearchMax(s, u);
		}

		else if (hsize % 2 != 0)
		{
			OddsearchMin(s, u);
			OddsearchMax(s, u);
		}


	}



	void Display()
	{
		std::cout << "Interval Heap:\n";
		for (int i = 0; i < (hsize / 2) + 1; ++i)
		{
			cout << "(" << h[0][i] << ", " << h[1][i] << ")";
		}
		cout << "\n";
	}

	~IntervalHeap()
	{
		// Deallocate memory for the 2D array
		delete[] h[0];
		delete[] h[1];
		delete[] h;
	}

};

int main()
{
	IntervalHeap h1;
	h1.initialize();
	h1.insert(2);
	h1.insert(30);
	h1.Display();


	h1.insert(15);


	h1.Display();

	h1.update(5, 17);
	h1.Display();




	return 0;
}