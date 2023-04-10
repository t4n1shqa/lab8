#include <time.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapify(int arr[], int n, int i) {
  
  int big = i; 
  int R = 2*i + 2; 
  int L = 2*i + 1; 

  if (R < n && arr[R] > arr[big]) {
    big = R;
  }
  
  if (L < n && arr[L] > arr[big]) {
    big = L;
  }

  if (big != i) {
    int temp = arr[i];
    arr[i] = arr[big];
    arr[big] = temp;
    heapify(arr, n, big);
  }
}


void maxHeap(int arr[], int n) {
  int x;
  x = (n/2) - 1;
  for (int i = x;i >= 0; i--) {
    heapify(arr,n,i);
  }
}


void heapSort(int arr[], int n)
{
  maxHeap(arr,n); 
  for (int i = n - 1; i >= 0; i--) {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    heapify(arr, i, 0);  
  }
}


void merge(int pData[], int l, int m, int r){
  int a, b, c;
  int n1 = m - l + 1;
  int n2 = r - m;
  
  int *l1 = (int*)malloc(n1*sizeof(int));
  extraMemoryAllocated = extraMemoryAllocated + n1;
  int *r1 = (int*)malloc(n2*sizeof(int));
  extraMemoryAllocated = extraMemoryAllocated + n2;

  for (a = 0; a < n1; a++){
    l1[a] = pData[l+a];
  }
  for (b = 0; b < n2; b++){
    r1[b] = pData[m + 1 +b];
  }

  a = 0;
  b = 0;
  c = l;

  while (a < n1 && b < n2){
    if (l1[a] <= r1[b]){
      pData[c] = l1[a];
      a++;
    }else{
      pData[c] = r1[b];
      b++;
    }
    c++;
  }

  while (a < n1){
    pData[c] = l1[a];
    a++;
    c++;
  }
  while (b < n2){
    pData[c] = r1[b];
    b++;
    c++;
  }
  free(l1);
  free(r1);
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
  int m;
	if (l < r){
    m = (l + r) / 2;
    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);

    merge(pData, l, m, r);
  }
}


// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100 && i<dataSz;++i) // (change) added && to check that i is less than dataSz
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	if (sz > 0) {
    for (i=sz;i<dataSz;++i) // (change) added if statement
	   {
		printf("%d ",pData[i]);
	   }
  }
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
