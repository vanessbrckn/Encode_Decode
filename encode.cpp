#include <iostream>
#include<string>
#include<string.h>
#include <vector>
#include <chrono> 
using namespace std::chrono;
using namespace std;

vector<string> Shift(string original, int length);
void swapChar(char &A, char &B);
vector<string> insertionSort(vector<string> Array, int len);
void swapString(string *less, string *more);
int findMatch(vector <string> sorted, string original, int len);
string encodedArray(vector <string> toEncode, int len);
string freq(string lastElem, int len);
void Merge(string* A, int start, int mid, int end);
void mergeSort(string* Array, int high, int low);


int main (int argc, char *argv[])
{
	string testString;
	vector<string> shiftedArray;
	int index;
	string lastChar, encodedResult;
	
	//auto start = high_resolution_clock::now(); 
	
	if(argc == 1)
		cout<<"Please Enter a .txt file beginning with \'<\' "<<endl;
	else
	{
		if(strcmp(argv[1],"insertion")==0)
		{
				while(!cin.eof())
				{
					getline(cin, testString); //never got around to changing the variable name
					
					if (testString.empty())
						testString = "\\n";
						
					int len = testString.size();
					
					shiftedArray = Shift(testString, len);
					shiftedArray = 	insertionSort(shiftedArray, len);
			
					index = findMatch(shiftedArray, testString, len);
					
					cout<<index<<endl;	//prints index
				
					lastChar = encodedArray(shiftedArray, len);
					encodedResult = freq(lastChar,len);
					
					cout<<encodedResult<<endl; //prints the encoded line
				}
		}
		else if(strcmp(argv[1],"merge")==0)
		{
			while(!cin.eof())
			{
				getline(cin, testString);
				
				if(testString.empty())
					testString = "\\n";
				
				int len = testString.size();
				
				shiftedArray = Shift(testString, len);
				
				string* temp = shiftedArray.data();

				mergeSort(temp, len-1, 0);
				
				index = findMatch(shiftedArray, testString, len);
					
				cout<<index<<endl;	//prints index
			
				lastChar = encodedArray(shiftedArray, len);
				encodedResult = freq(lastChar,len);
				
				cout<<encodedResult<<'\n'; //prints the encoded line
			}
			
		}
		else
			cout<<"please enter a valid argument";
	}
/*	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
	cout <<"duration = "<< duration.count() << " microseconds"<<endl; */
		
	return 0;	
}
vector<string> Shift(string original, int len)
{
	int ix = 0;
	int j = 1;
	int jx;
	vector<string> shiftedArray;
	
	shiftedArray.push_back(original);
	
	while (j < len )
	{
		char c = original[0];		//save the first character
	
		for(int i = 0; i < len; ++i)
		{
			original[i]= original[i+1];	//shift everything else
		}
				
		original[len-1]= c;		//load the first character in last pos
		shiftedArray.push_back(original);		//put it in the string array
		
		++j;				//do it again for lengeth of original string
	}
	return shiftedArray;
}

void swapChar(char &A, char &B)		//values being passed by ref
{
 	char temp = A;				//swap the actual values
 	A = B;
 	B= temp;
}
void swapString(string *less, string *more)
{
	string temp = *less;
	*less = *more;	
	*more = temp;
}
vector<string> insertionSort(vector<string> Array, int len)
{
	string* p = Array.data();	//using pointers here, p is the address of the passed vector
	string* beginning = p;		//lets keep track of it
	string* end = p+len-1;		//but we need to know where to stop
	int sorted;					//flag
	
	do
	{
		sorted = 0;
		
		for (p=beginning; p< end; ++p)			//go through array
		{
			while (*(p+1)< *p)					//is it less?
			{
				swapString((p+1),p);			//swap until it's not
				sorted = 1;
			}	
		}
	}while( sorted == 1);

	return Array;
}
void mergeSort(string* Array, int high, int low)
{
	
	int mid;
	if(low<high)
	{
		mid = (low+high)/2;
		mergeSort(Array, mid, low);
		mergeSort(Array, high, mid+1);
		Merge(Array, low, mid, high);
	}
	
}
void Merge(string* A, int start, int mid, int end)
{
	vector <string> temp(500);
	string* p = A;
	string* beg = p;
	string* pEnd = (p+end-1);

	int i = start, j = mid + 1, k = start;
	
	while(i <=mid && j <= end)
	{
		if(*(p+i) < *(p+j))
		{
			temp.at(k) = *(p+i);
			++k; ++i;
		}
		else 
		{
			temp.at(k)= *(p+j);
			++k; ++j;
		}
	}
	while(i <= mid)
	{
		temp.at(k) = *(p+i);
		++k;
		++i;
	}
	while(j <= end)
	{
		temp.at(k) = *(p+j);
		++k;
		++j;
	}
	for(i = start; i< k; ++i)
	{
		*(p+i) = temp.at(i);
	}
	
	A = p;
}
int findMatch(vector <string> sorted, string original, int len)
{
	int i = 0;
	int match;
	
	for (i; i<=len-1; ++i)
	{
		if (sorted[i].compare(original) == 0)
			match = i;		
	}
	return match;	
}
string encodedArray(vector <string> toEncode, int len)
{
	int i;
	string compressedArray = "";
	string c;
	
	for(i = 0; i<len; ++i)
	{
		c = toEncode.at(i);						//I need to grab the current string
	    compressedArray= compressedArray + c[len-1];	//and the last element of that string goes to the encoded array
	}

	return compressedArray;
}
string freq(string lastElem, int len)
{
	string encoded = "";
	int ix = 0;
	char a, b;
	string c;

	while(ix < len)
	{
		a = lastElem[ix];
		b = lastElem[ix+1];
		
		int freq = 1;
		
		while(a == b)
		{
			++freq;
			++ix;
			a = lastElem[ix];
			b = lastElem[ix+1];
		}
		
		c = to_string(freq);		//this was my way of turning an int into a char
		encoded = encoded + c +" ";		//append char
		encoded = encoded + lastElem[ix];	//append the char with that freq
		encoded = encoded + " ";			//add a space	
	    ++ix;
	}
	encoded = encoded + '\0';
			
	return encoded;
}
