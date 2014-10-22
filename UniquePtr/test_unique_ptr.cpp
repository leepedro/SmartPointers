#include <iostream>
#include <memory>

// If std::vector<T> is undesired or prohibited,
// then std::unique_ptr<T[]> can be used as an alternative of a dynamic array T * = new T[].


class MyClass
{
public:
	MyClass() { std::clog << "ctor" << std::endl; }
	~MyClass() { std::clog << "dtor" << std::endl; }
	int data = 0;

private:

};

// std::unique_ptr takes care of resource release.
void Func1(void)
{
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	array1[0].data = 1;
}

// delete[] must be done to release resource.
void Func2(void)
{
	MyClass *array2 = new MyClass[3];
	array2[0].data = 2;
	delete[] array2;
}

// reset() creates new pointer and deletes the old one.
void Func3(void)
{
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	array1[0].data = 1;
	array1.reset(new MyClass[2]);
}

int main(void)
{
	Func1();
	Func2();
	Func3();
}