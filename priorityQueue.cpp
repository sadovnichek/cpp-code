template <typename T>
class MinPriorityQueue
{
public:
	int currentSize;

	MinPriorityQueue(int maxSize)
	{
		this->maxSize = maxSize;
		for (int i = 0; i <= maxSize; i++)
		{
			heap.push_back(make_pair(0, 0));
		}
		this->currentSize = 0;
	}

	void insert(T priority, T element)
	{
		if (currentSize == maxSize)
			exit(-1);
		this->currentSize++;
		heap[this->currentSize] = make_pair(priority, element);
		up(this->currentSize);
	}

	long extractMinElement()
	{
		long result = heap[1].second;
		heap[1] = heap[this->currentSize];
		this->currentSize--;
		down(1);
		return result;
	}

	void remove(int index)
	{
		heap[index].first = LONG_MIN;
		up(index);
		extractMinElement();
	}

	void changePriority(int index, T priority)
	{
		T oldPriority = heap[index].first;
		heap[index].first = priority;
		if (priority < oldPriority)
		{
			up(index);
		}
		else
		{
			down(index);
		}
	}

	T getElementWithMinPriority()
	{
		return heap[1].second;
	}

	T getMinPriority()
	{
		return heap[1].first;
	}

private:
	int maxSize;
	vector<pair<T, T>> heap;

	int parent(int index)
	{
		return ceil(index/ 2.0);
	}

	int leftChild(int index)
	{
		return 2 * index;
	}

	int rightChild(int index)
	{
		return 2 * index + 1;
	}

	void down(int index)
	{
		int minIndex = index;
		int leftChildIndex = leftChild(index);
		if (leftChildIndex <= currentSize && heap[leftChildIndex] < heap[minIndex])
			minIndex = leftChildIndex;
		int rightChildIndex = rightChild(index);
		if (rightChildIndex <= currentSize && heap[rightChildIndex] < heap[minIndex])
			minIndex = rightChildIndex;
		if (minIndex != index)
		{
			swap(heap[minIndex], heap[index]);
			down(minIndex);
		}
	}

	void up(int index)
	{
		int parentIndex = parent(index);
		if (heap[parentIndex] > heap[index])
		{
			swap(heap[parentIndex], heap[index]);
			up(parent(index));
		}
	}
};
