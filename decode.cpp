#include <iostream>
#include<string>
#include<string.h>
#include <vector>

#include <chrono> 
using namespace std::chrono;

using namespace std;

void swapChar(char A, char B);
void swapString(string *less, string *more);
int findMatch(vector <string> sorted, string original, int len);
string encodedArray(vector <string> toEncode, int len);
string freq(string lastElem, int len);
void insertionDecompressed(char *A, int len);
void mergeDecompressed(char *A, int lo, int hi);
void Merge(char  *A, int start, int mid, int end);
int indexCast(string input);

int main (int argc, char *argv[])
{			
	auto start = high_resolution_clock::now();
	
	while(cin.good()&&!cin.eof())
	{ 

		int index=0, freq= 0, i = 0, len=0, lastLen= 0, j = 0, x=0, lines = 0;
		string toDecode="", indexIn=" ";
		
		getline(cin, indexIn);
		
		
		if(!indexIn.empty())
		{

			x =  indexCast(indexIn);

			getline(cin, toDecode); 

			len = toDecode.length();
            toDecode = toDecode.substr(0, len-1);		//needed to remove last space character appended to my encoded files

            len = toDecode.length();
			char last[len];
			
			while(i < len)
			{	
				
				if(toDecode[i]>'0' && toDecode[i]< '9' )
				{
					freq = (int)toDecode[i] -'0';
					
					if(toDecode[i+1] != ' ')
					{
						cout<<"here"<<endl;
						freq = freq*10 + (int)toDecode[i+1] - 48; 
						cout<<freq<<endl;
						++i;						
					}
					if(toDecode[i+1] != ' ')
					{
						cout<<"here"<<endl;
						freq = freq*10 + (int) toDecode[i+1]- 48;
						cout<<freq<<endl;
						++i;
					}
				}
				i=i+2;
				cout<<"here "<<freq<<endl;
				for(int f=0; f<freq; ++f)
				{	
					if (toDecode[i] != '\0'){
						last[j] = toDecode[i];
						++j;				
					}
				}
				i = i+2;
			}
			last[j] = '\0';
		
			lastLen = strlen(last);

			char first[lastLen];

			for (i = 0; i< lastLen; ++i)
			{
				first[i] = last[i];
			}
			
			if(strcmp(argv[1],"insertion")==0)
				insertionDecompressed(first, lastLen);
			else if(strcmp(argv[1],"merge")==0)
			{	
				mergeDecompressed(first, lastLen-1,0);
			}
			else
				cout<<"Please enter a valid command"<<endl;

			int next[lastLen];
			bool present[lastLen];
			for (int i=0; i < lastLen ; i++)
			{
				present[i] = false;
			} 

			for (int j = 0; j< lastLen; ++j)
			{
				char c = first[j];
				//cout<<endl<<first[j]<<" index of first = "<<j;
				for(i=0; i < lastLen; i++)
				{
					//cout << "c: " << c << " last[i]: " << last[i] << " i: " << i << " j: " << j << endl;
					if (c == last[i] && present[i] != true)
					{
						//cout<<endl<<"index of match = "<<i<<endl;
						next[j] = i;
						//cout << "Adding: " << i << " at: " << j << endl;
						present[i] = true;
						i = lastLen;
					}
				}
			}

			x = next[x];

			//cout<<endl;
			for ( i = 0; i<lastLen; ++i)
			{
				cout<<last[x];
				x= next[x];
			}
			cout<<endl;
		}			
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << endl; 
	
	return 0;
}
int indexCast(string input)
{
	int index;
	int k = 1;
	int i=0;
	
	for(i; i<input.length(); ++i)
	{
		if(input[i]>='0'&& input[i]<='9')			//has to be a number
		{
			index = index*k + (int)input[i]-48; 	//k moves the value to the next place (1,10,100,1000)
			k= k*10;								// which accomodates for multiple place values.
		}
	}
	
	return index;
}
void swapChar(char *A, char *B)		//values being passed by ref
{	
 	char temp = *A;				//swap the actual values
 	*A = *B;
 	*B = temp;
}
void insertionDecompressed(char* A, int len)
{
	int sorted, i;
	char* p = A;
	char* beg = p;
	char* end = p+len-1;

	do
	{
		sorted = 0;

		for (p = beg; p< end; ++p)			//go through array
		{
			while (*(p+1)<*p)					//is it less?
			{
				swapChar((p+1),p);		
				sorted = 1;
			}	
		}	
	}while(sorted == 1);
}
void mergeDecompressed(char* Array, int high, int low)
{
	
	int mid;
	if(low<high)
	{
		mid = (low+high)/2;
		mergeDecompressed(Array, mid, low);
		mergeDecompressed(Array, high, mid+1);
		Merge(Array, low, mid, high);
	}
	
}
void Merge(char* A, int start, int mid, int end)
{
	char temp[5000];
	char* p = A;
	char* beg = p;
	char* pEnd = (p+end-1);

	int i = start, j = mid + 1, k = start;
	
	while(i <=mid && j <= end)
	{
		if(*(p+i) < *(p+j))
		{
			temp[k] = *(p+i);
			++k; ++i;
		}
		else 
		{
			temp[k] = *(p+j);
			++k; ++j;
		}
	}
	while(i <= mid)
	{
		temp[k] = *(p+i);
		++k;
		++i;
	}
	while(j <= end)
	{
		temp[k] = *(p+j);
		++k;
		++j;
	}
	for(i = start; i< k; ++i)
	{
		*(p+i) = temp[i];
	}
	
	A = p;
}


