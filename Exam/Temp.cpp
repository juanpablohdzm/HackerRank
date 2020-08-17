#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdarg> //va_arg...
#include <functional>
namespace fs = std::filesystem;

class Interface
{
public:
	virtual void Get() = 0;
	virtual void Set() = 0;
};

class A : public Interface
{
public:
	void TestFunction()
	{
		std::cout << "Test Function in object" << std::endl;
	}
	A()
	{
		std::cout << "Default" << std::endl;
	}
	A(const A& other)
	{
		std::cout << "Copy" << std::endl;
	}

	A(const A&& other)
	{
		std::cout << "Move" << std::endl;
	}

	void operator=(const A& other)
	{
		std::cout << "Assignment" << std::endl;
	}

	void Get() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void Set() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};
class B
{
public:
	void Get()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	void Set() 
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};

void TestFunction()
{
	std::cout << "Test Function" << std::endl;

}

template<typename Args>
void VariadicFunction(size_t n, ...)
{
	va_list  args;
	va_start(args, n);
	for (size_t i = 0; i < n; i++)
	{
		std::cout << va_arg(args, Args) << std::endl;
	}
	va_end(args);
}

template<typename Args>
void Callbacks(size_t count, ...)
{
	va_list args;
	va_start(args, count);
	for (size_t i = 0; i < count; i++)
	{
		auto f = va_arg(args, Args);
		f();
	}
	va_end(args);
}

template<class Class, typename Args>
void Callbacks(Class* obj, size_t count, ...)
{
	va_list args;
	va_start(args, count);
	for (size_t i = 0; i < count; i++)
	{
		(obj->*va_arg(args, Args))();
	}
	va_end(args);
}


class Singleton
{
private:
	Singleton()
	{
		std::cout << "Hello" << std::endl;
	}

public:
	Singleton(const Singleton& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;

	int a = 0;
	static Singleton* get_instance()
	{
		static Singleton instance;
		return &instance;
	}
};

template<class Class = Interface>
class ConditionClass
{
public:
	ConditionClass()
	{
		static_assert(std::is_base_of<Interface, Class>::value,"Class should inherit from Interface");
	}
	Class obj;

	void Do() { obj.Get(); }
};


int main()
{
	ConditionClass<A> cc;



	Singleton* pt = Singleton::get_instance();
	pt->a = 2;
	Singleton* pr = Singleton::get_instance();
	std::cout << pr->a;

	VariadicFunction<int>(3, 2, 3, 7);

	//std::function<void()> f = []() {std::cout << "Object" << std::endl; };
	void(*p)() = []() {std::cout << "Object" << std::endl; };
	void(*r)() = TestFunction;
	Callbacks<void(*)()>(2, p, r);

	A a;
	Callbacks<A, void(A::*)()>(&a, 3, &A::TestFunction, &A::TestFunction, &A::TestFunction);


	int m[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
	std::vector<int> n(9);
	std::copy(&m[0][0], &m[0][0] + 9, n.begin());

	std::vector<A> vec1(4);
	A vec2[4];
	std::copy(vec1.begin(), vec1.end(), vec2);

	int** k = new int* [3]{};
	for (size_t i = 0; i < 3; i++)
	{
		k[i] = new int[3]{};
		for (size_t j = 0; j < 3; j++)
		{
			k[i][j] = j;
		}
	}

	for (size_t i = 0; i < 3; i++)
	{
		delete[] k[i];
	}
	delete[] k;


	for (size_t i = 0; i < 9; i++)
	{
		int* j = &m[0][0] + i;
		std::cout << *j << std::endl;
	}


	fs::create_directory("Tests");
	{
		std::ofstream file("Tests/Hello.txt");
		if (file.is_open())
		{
			file << "Hello World\n";
			file << "Second world";
		}
		file.close();
	}
	{
		std::ifstream file("Tests/Hello.txt", std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			const size_t size = static_cast<size_t>(file.tellg());
			file.seekg(0);
			std::string line(size, '\0');
			file.read(line.data(), size);
			std::cout << line << std::endl;
			file.seekg(0);
			while (!file.eof())
			{
				std::string l;
				getline(file, l);
				std::cout << l;
			}
			file.close();
		}
	}
}
