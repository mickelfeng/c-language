/*************************************************************************
各种排序算法的思路、效率和具体实现，
包括插入排序（直接插入排序，折半插入排序，希尔排序）、交换排序（冒泡排序，快速排序）、选择排序（简单选择排序，堆排序）、
2-路归并排序。

************************/
#include<iostream>
using namespace std;

typedef int ElementType;

/*
 *<<直接插入排序>>
 *    为了实现N个数的排序，将后面N-1个数依次插入到前面已排好的子序列中，
 *假定刚开始第1个数是一个已排好序的子序列。经过N-1趟就能得到一个有序序列。
 *****时间复杂度：最好情况O(n)，最坏情况O(n^2)，平均情况O(n^2).
 *****空间复杂度：O(1)
 *****稳定性：稳定
 */
void InsertSort(ElementType A[], int n)
{
	int i,j;
	ElementType temp;  // 临时变量

	for(i=1; i<n; ++i)
	{
		temp = A[i]; 
		for(j = i; j>0 && A[j-1]>temp; --j)
			A[j] = A[j-1];
		A[j] = temp;
	}
}




/*
 *<<折半插入排序>>
 *    与直接插入排序不同的是，折半插入排序不是边比较边移动，而是将比较和移
 *动操作分离出来，即先折半查找出元素的待插入位置，然后再统一地移动待插入位
 *置之后的所有元素。不难看出折半插入排序仅仅是减少了比较的次数。
 *****时间复杂度：O(n^2)
 *****空间复杂度：O(1)
 *****稳定性：稳定
 */
void BinaryInsertSort(ElementType A[], int n)
{
	int i, j, low, high, mid;
	ElementType temp;
	for(i=1; i<n; ++i)
	{
		temp = A[i];
		low = 0; high = i-1;  // 设置折半查找的范围
		while(low <= high)
		{
			mid = (low+high)/2;  // 取中间点
			if(A[mid] > temp)
				high = mid-1;
			else
				low = mid+1;
		}

		for(j=i-1; j>=high+1; --j) // 统一后移
			A[j+1] = A[j];
		A[high+1] = temp;    // 插入
	}
}




/*
 *<<希尔排序>>
 *    希尔排序通过比较相距一定间隔的元素，即形如L[i,i+d,i+2d,...i+kd]的序列
 *然后缩小间距，再对各分组序列进行排序。直到只比较相邻元素的最后一趟排序为
 *止，即最后的间距为1。希尔排序有时也叫做*缩小增量排序*
 *****时间复杂度：依赖于增量序列的选择，但最坏情况才为O(N^2)
 *****空间复杂度：O(1)
 *****稳定性：不稳定
 */
void ShellSort(ElementType A[], int n)
{
	int i, j, dk;   // dk是增量
    ElementType temp;
    
	for(dk=n/2; dk>0; dk/=2)  // 增量变化
	{
		for(i=dk; i<n; ++i)  // 每个分组序列进行直接插入排序
		{
			temp = A[i];
			for(j=i-dk; j>=0 && A[j]>temp; j-=dk)
				A[j+dk] = A[j];  // 后移
			A[j+dk] = temp;
		}
	}
}




/*
 *<<冒泡排序>>
 *    冒泡排序的基本思想是从后往前（或从前往后）两两比较相邻元素的值，若为
 *逆序，则交换它们，直到序列比较完。我们称它为一趟冒泡。每一趟冒泡都会将一
 *个元素放置到其最终位置上。
 *****时间复杂度：最好情况O(n)，最坏情况O(n^2)，平均情况O(n^2)
 *****空间复杂度：O(1)
 *****稳定性：稳定
 */
void BubbleSort(ElementType A[], int n)
{
	for(int i=0; i<n-1; ++i)
	{
		bool flag = false;   // 表示本次冒泡是否发生交换的标志
		for(int j=n-1; j>i; --j) // 从后往前
		{
			if(A[j-1] > A[j]) 
			{
				flag = true;
				// 交换
				A[j-1] = A[j-1]^A[j];
				A[j] = A[j-1]^A[j];
				A[j-1] = A[j-1]^A[j];
			}
		}

		if(flag == false)
			return;
	}
}




/*
 *<<快速排序>>
 *    快速排序是对冒泡排序的一种改进。其基本思想是基于分治法：在待排序表L[n]
 *中任取一个元素pivot作为基准，通过一趟排序将序列划分为两部分L[1...K-1]和
 *L[k+1...n]，是的L[1...k-1]中的所有元素都小于pivot，而L[k+1...n]中所有元素
 *都大于或等于pivot。则pivot放在了其最终位置L(k)上。然后，分别递归地对两个子
 *序列重复上述过程，直至每部分内只有一个元素或空为止，即所有元素放在了其最终
 *位置上。
 *****时间复杂度：快排的运行时间与划分是否对称有关，最坏情况O(n^2),最好情况
 *O(nlogn),平均情况为O(nlogn)
 *****空间复杂度：由于需要递归工作栈，最坏情况为O(n)，平均情况为O(logn)
 *****稳定性：不稳定
 */
int Partition(ElementType A[], int low, int high)
{
	// 划分操作有很多版本，这里就总以当前表中第一个元素作为枢纽/基准
	ElementType pivot = A[low];
	while(low < high)
	{
		while(low<high && A[high]>=pivot)
			--high;
		A[low] = A[high];  // 将比枢纽值小的元素移到左端
		while(low<high && A[low]<=pivot)
			++low;
		A[high] = A[low];  // 将比枢纽值大的元素移到右端
	}

	A[low] = pivot;  // 枢纽元素放到最终位置
	return low;      // 返回枢纽元素的位置
}

void QuickSort(ElementType A[], int low, int high)
{
	if(low < high)  // 递归跳出的条件
	{
		int pivotPos = Partition(A, low, high); // 划分操作，返回基准元素的最终位置
		QuickSort(A, low, pivotPos-1);  // 递归
		QuickSort(A, pivotPos+1, high);
	}
}




/*
 *<<简单选择排序>>
 *    选择排序的算法思想很简单，假设序列为L[n]，第i趟排序即从L[i...n]中选择
 *关键字最小的元素与L(i)交换，每一趟排序可以确定一个元素的最终位置。经过n-1
 *趟排序就可以使得序列有序了。
 *****时间复杂度：始终是O(n^2)
 *****空间复杂度：O(1)
 *****稳定性：不稳定
 */
void SelectedSort(ElementType A[], int n)
{
	for(int i=0; i<n-1; ++i)  // 一共进行n-1趟
	{
		int minPos = i;  // 记录最小元素的位置

		for(int j=i+1; j<n; ++j)
			if(A[j] < A[minPos])
				minPos = j;

		if(minPos != i)  // 与第i个位置交换
		{
			A[i] = A[i]^A[minPos];
			A[minPos] = A[i]^A[minPos];
			A[i] = A[i]^A[minPos];
		}
	}
}




/*
 *<<堆排序>>
 *    堆排序是一种树形选择排序方法，在排序过程中，将L[n]看成是一棵完全二叉
 *树的顺序存储结构，利用完全二叉树中双亲节点和孩子节点之间的内在关系，在当
 *前无序区中选择关键字最大（或最小）的元素。堆排序的思路是：首先将序列L[n]
 *的n个元素建成初始堆，由于堆本身的特点（以大根堆为例），堆顶元素就是最大
 *值。输出堆顶元素后，通常将堆底元素送入堆顶，此时根结点已不满足大根堆的性
 *质，堆被破坏，将堆顶元素向下调整使其继续保持大根堆的性质，再输出堆顶元素。
 *如此重复，直到堆中仅剩下一个元素为止。
 *****时间复杂度：O(nlogn)
 *****空间复杂度：O(1)
 *****稳定性：不稳定
 */

void AdjustDown(ElementType A[], int i, int len)
{
	ElementType temp = A[i];  // 暂存A[i]
    
	for(int largest=2*i+1; largest<len; largest=2*largest+1)
	{
		if(largest!=len-1 && A[largest+1]>A[largest])
			++largest;         // 如果右子结点大
		if(temp < A[largest])
		{
			A[i] = A[largest];
			i = largest;         // 记录交换后的位置
		}
		else
			break;
	}
	A[i] = temp;    // 被筛选结点的值放入最终位置
}
void BuildMaxHeap(ElementType A[], int len)
{
	for(int i=len/2-1; i>=0; --i)  // 从i=[n/2]~1，反复调整堆
		AdjustDown(A, i, len);
}
void HeapSort(ElementType A[], int n)
{
	BuildMaxHeap(A, n);       // 初始建堆
	for(int i=n-1; i>0; --i)  // n-1趟的交换和建堆过程 
	{
		// 输出最大的堆顶元素（和堆底元素交换）
		A[0] = A[0]^A[i];
		A[i] = A[0]^A[i];
		A[0] = A[0]^A[i];
		// 调整，把剩余的n-1个元素整理成堆
		AdjustDown(A, 0, i);   
	}
}
	



/*
 *<<2-路归并排序>>
 *    顾名思义，2-路归并就是将2个有序表组合成一个新的有序表。假定待排序表
 *有n个元素，则可以看成是n个有序的子表，每个子表长度为1，然后两两归并...不
 *停重复，直到合成一个长度为n的有序序列为止。Merge()函数是将前后相邻的两个
 *有序表归并为一个有序表，设A[low...mid]和A[mid+1...high]存放在同一顺序表的
 *相邻位置上，先将它们复制到辅助数组B中。每次从对应B中的两个段取出一个元素
 *进行比较，将较小者放入A中。
 *****时间复杂度：每一趟归并为O(n),共log2n趟，所以时间为O(nlog2n)
 *****空间复杂度：O(n)
 *****稳定性：稳定
 */
ElementType *B = new ElementType[13];  // 和数组A一样大
void Merge(ElementType A[], int low, int mid, int high)
{
	int i, j, k;
	for(k=low; k<=high; ++k)
		B[k] = A[k];             // 将A中所有元素复制到B
	for(i=low,j=mid+1,k=i; i<=mid&&j<=high; ++k)
	{
		if(B[i] <= B[j])      // 比较B的左右两段序列中的元素
			A[k] = B[i++];    // 将较小值复制到A中
		else
			A[k] = B[j++];
	}
	while(i<=mid)  A[k++] = B[i++];   // 若第一个表未检测完，复制
	while(j<=high) A[k++] = B[j++];   // 若第二个表未检测完，复制
}

void MergeSort(ElementType A[], int low, int high)
{
	if(low < high)
	{
		int mid = (low + high)/2;
		MergeSort(A, low, mid);       // 对左侧子序列进行递归排序
		MergeSort(A, mid+1, high);    // 对右侧子序列进行递归排序
		Merge(A, low, mid, high);     // 归并
	}
}





/*
 * 输出函数
 */
void print(ElementType A[], int n)
{
	for(int i=0; i<n; ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}


/*
 * 主函数
 */
int main()
{
	ElementType Arr[13] = {5,2,1,8,3,6,4,7,0,9,12,10,11};
	//InsertSort(Arr, 13);
	//BinaryInsertSort(Arr, 13);
	//ShellSort(Arr, 13);
	//BubbleSort(Arr, 13);
	//QuickSort(Arr, 0, 12);
	//SelectedSort(Arr, 13);
	//HeapSort(Arr, 13);
	//MergeSort(Arr, 0, 12);
	print(Arr, 13);
	return 0;
}
