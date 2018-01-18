#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>   
#include "assert.h" 

#define MIN 0       
#define MAX 999  

#define Random(x) (rand() % x)

class MaxHeapEmptyException{
    public:
        MaxHeapEmptyException(std::string m):message(m){}
        std::string message;
};

//For the element at index n
//Left child index is 2n+1
//Right child index is 2n+2
//Parent index is (n-1)/2
class MaxHeap
{
    public:
        MaxHeap():size(0)
        {
            //default size 20;
            allocatedSize = 20;
            data = new int[allocatedSize];
        }

        MaxHeap(int s):size(0), allocatedSize(s)
        {
            //if the required size passed in is less than 20
            //use the default min size 20
            if(s<20)
                allocatedSize = 20;
            data = new int[allocatedSize];
        }

        ~MaxHeap()
        {
            if(data!=NULL)
                delete[] data;
        }

        void Insert(int value)
        {
            if(size==allocatedSize)
            {
                allocatedSize = allocatedSize*2;
                int* temp = data;
                data = new int[allocatedSize]; 
                Copy(temp, data, size);
                delete[] temp;
            }

            //append the new value to the heap tail, and bubble it up.
            data[size] = value;
            BubbleUp(size);
            size++;
        }

        int Max()
        {
            //in case of the heap is empty
            //We should throw exception or implement a version of 
            //bool TryGetMax(int& val)
            if(size>0)
                return data[0];
            else
                throw MaxHeapEmptyException("The heap is empty");
        }

        int PopupMax()
        {
            int retVal;
            if(size>0)
            {
                retVal = data[0];
                Swap(0, size-1);
                size--;
                BubbleDown(0);
                return retVal;
            }
            else
                throw MaxHeapEmptyException("The heap is empty"); 
        }

        void Delete(int i)
        {
            Swap(i, size-1);
            size--;
            
            if(data[i]>data[(i-1)/2])
            {
                BubbleUp(i);
            }
            else
            {
                BubbleDown(i);
            }
        }

        void Update(int i, int value)
        {
            data[i] = value;
            if(data[i]>data[(i-1)/2])
            {
                BubbleUp(i);
            }
            else
            {
                BubbleDown(i);
            }
        }

    private:
        MaxHeap(const MaxHeap& heap){};
        MaxHeap& operator=(const MaxHeap& heap){};
        int size;
        int allocatedSize;
        int* data;

        void Copy(int* source, int* target, int size)
        {
            for(int i=0;i<size;i++)
            {
                target[i] = source[i];
            }
        }

        void BubbleUp(int i)
        {
            //Already bubbled to the root
            //equal or less than its parent. Good
            if(i==0 || data[i]<=data[(i-1)/2])
            {
                return;
            }
            else
            {
                Swap(i, (i-1)/2);
                BubbleUp((i-1)/2);    
            }
        }

        void BubbleDown(int i)
        {
            //3 cases:
            //1: parent is the biggest
            //2: left child is the biggest
            //3: right child is the biggest
            
            //already to the leaf
            if(i>=size/2) 
                return;

            if(2*i+2<=size-1)
            {
                //both children exists
                if(data[i]>=data[2*i+1] && data[i]>=data[2*i+2])
                    return;

                if(data[2*i+1]>=data[i] && data[2*i+1]>=data[2*i+2])
                {
                    Swap(i, 2*i+1);
                    BubbleDown(2*i+1);
                }
                else
                {
                    Swap(i, 2*i+2);
                    BubbleDown(2*i+2);
                }

            }
            else
            {
                //only left child
                if(data[i]<data[2*i+1])
                    Swap(i, 2*i+1);
            }
        }

        void Swap(int i, int j)
        {
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
};

int main()
{
    MaxHeap heap(10);

    srand((unsigned)time(NULL));

	int array[100];
	int n = 100;
	while (n--)
	{
        heap.Insert(MIN + rand() % (MAX + MIN - 1));
	}
    
    heap.Delete(50);
    heap.Delete(50);
    heap.Update(2, 142857);
    heap.Update(13, -142857);
    heap.Insert(999);
    heap.Insert(0);

    n = 100;
    while (n--)
	{
        array[n] = heap.PopupMax();
	}

	n = 100;
	while (n--)
	{
		if (n > 0) assert(array[n] >= array[n - 1]);

		std::cout << array[n] << std::endl;
	}
}