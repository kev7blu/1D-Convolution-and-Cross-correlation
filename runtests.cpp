#include <iostream>
#include <vector>

template<typename T>
std::vector<T> xcorr(const std::vector<T>& a, const std::vector<T>& b) //keep a the same and shift b across
{
//adding 0's to work
	std::vector<int> NewA((((b.size() * 2) + a.size()) - 2)); //more room for 0's

	size_t j = (b.size() - 1);//start copying here

	//copy function
	for (size_t n = 0; a.size() != n ; j++, n++)
	{
		NewA[j] = a[n];
	}
	
//actually the code for xcorrelation
	std::vector<int> results(a.size() + b.size() -1);
	auto z = NewA.size() - b.size() + 1; //end size

	for (size_t n = 0; n != z; n++) //moves vector a
	{
		int total = 0;
		size_t i = 0;
		size_t begin = n;

		while(i != b.size())
		{
			total += (NewA[begin] * b[i]);
			i ++;
			begin++;
		}
		results[n] = total;
	}
	return results;
}

template<typename T>
std::vector<T> conv(const std::vector<T>& a, const std::vector<T>& b) //reverse b and keep a the same
{
//reverse vector
	std::vector<int> rev(b.size());
	
	int front = 0;
	int back = b.size() - 1;

	while(back > -1)
	{
		rev[front] = b[back];
		front++;
		back--;
	}
	
//adding 0's to work
	std::vector<int> NewA((((b.size() * 2) + a.size()) - 2)); //more room for 0's

	size_t j = (b.size() - 1);//start copying here

	//copy function
	for (size_t n = 0; a.size() != n ; j++, n++)
	{
		NewA[j] = a[n];
	}
	
//the actually code to convolution
	std::vector<int> results(a.size() + b.size() -1);
	auto z = NewA.size() - b.size() + 1; //end size

	for (size_t n = 0; n != z; n++) //moves vector a
	{
		int total = 0;
		size_t i = 0;
		size_t begin = n;

		while(i != rev.size())
		{
			total += (NewA[begin] * rev[i]);
			i ++;
			begin++;
		}
		results[n] = total;
	}
	return results;
}

template<typename T>
void printVector(const std::vector<T>& c)
{
	std::cout << "[ ";
	for (auto n: c)
	{
		std::cout << n << " ";
	}
	
	std::cout << "]";
	std::cout << "\n"<< std::endl;
}

int main()
{
	std::vector<int> a{1,2,3};
	std::vector<int> b{1,2,3};

//print a
	std::cout << "Vector a";
	printVector(a);

//print b
	std::cout << "Vector b";
	printVector(b);

//conv [1, 4, 10, 12, 9]
	std::cout << "--CONVULUTION--" << std::endl;

	std::vector<int> resultConv = conv(a,b);

	printVector(resultConv);

//xcorr [3, 8, 14, 8, 3]
	std::cout << "--XCORRELATION--" << std::endl;

	std::vector<int> resultXcorr = xcorr(a,b);

	printVector(resultXcorr);

	return 0;
}
