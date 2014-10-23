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
	std::clog << std::endl;
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	array1[0].data = 1;
}

// delete[] must be done to release resource for traditional pointer.
void Func2(void)
{
	std::clog << std::endl;
	MyClass *array2(nullptr);
	array2 = new MyClass[3];
	array2[0].data = 2;
	delete[] array2;
}

// reset() creates new pointer and deletes the old one.
void Func3(void)
{
	std::clog << std::endl;
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	array1[0].data = 1;
	array1.reset(new MyClass[2]);
}

// std::move() moves the pointer without reallocation.
void Func4(void)
{
	std::clog << std::endl;
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	std::unique_ptr<MyClass[]> array2 = std::move(array1);
	array1.reset();	// unnecessary.
}

// release() moves the pointer to the traditional pointer.
// The std::unique_ptr object become empty.
void Func5(void)
{
	std::clog << std::endl;
	std::unique_ptr<MyClass> pointer1(new MyClass);
	std::unique_ptr<MyClass[]> array1(new MyClass[3]);
	MyClass *p(nullptr), *p_array(nullptr);
	p = pointer1.release();
	p_array = array1.release();
	// NOTE: It must be delete[] instead of delete if it was an array.
	// NOTE: It must be delete instead of delete[] if it was not an array.
	// delete or delete[] does NOT change the value of the pointer back to nullptr.
	delete p;
	delete[] p_array;
}

int main(void)
{
	Func1();
	Func2();
	Func3();
	Func4();
	Func5();
}