// CSC196.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Base/assert.h"
#include "Base/memory.h"
#include "Base/smart_ptr.h"
#include "Base/ref_pointer.h"
#include "Base/timer.h"
#include "Base/random.h"
#include "Base/filesystem.h"

#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
#include <random>

void basics()
{
	ASSERT(sizeof(int) == 5, "Invalid int size");
	ASSERT(3 == 5, "That was not smart");

	ref_ptr<int> r1(new int(30));

	// Blocks like this have a self-contained scope. r2 will be destroyed after the block is exited.
	{
		ref_ptr<int> r2 = r1;
	}

	int* p = new int[32];

	delete p;
}

void function()
{
	smart_ptr<int> p(new int(10));
	std::cout << "Value: " << *p << std::endl;
}


void function2()
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	std::cout << start.time_since_epoch().count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::hours>(start.time_since_epoch()).count() << std::endl;

	std::chrono::milliseconds ms = std::chrono::milliseconds(1000);
	std::chrono::microseconds mi = ms;
	std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);

	std::cout << ms.count() << std::endl;
	std::cout << mi.count() << std::endl;
	std::cout << s.count() << std::endl;
}

void function3()
{
	ms_timer t;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << t.elapsed_time() << std::endl;
	std::cout << t.seconds() << std::endl;
}

void randIntro()
{
	//// rand() starts with the same seed if you don't give it one.
	//srand((unsigned int)time(0)); // Don't strictly need the cast here.
	//std::cout << rand() << std::endl;

	std::random_device device;
	std::default_random_engine engine(device());

	std::uniform_int_distribution<int> distribution(1, 6);
	for (int i = 0; i < 20; i++)
	{
		std::cout << distribution(engine) << std::endl;
	}

	std::cout << std::endl;

	std::uniform_real_distribution<float> distribution2(0.0f, 100.0f);
	for (int i = 0; i < 20; i++)
	{
		std::cout << distribution2(engine) << std::endl;
	}

	std::cout << std::endl;

	std::normal_distribution<double> distribution3(50.0f, 30.0f);
	for (int i = 0; i < 20; i++)
	{
		std::cout << distribution3(engine) << std::endl;
	}
}

void randSample()
{
	random_t r;
	for (int i = 0; i < 20; i++)
	{
		std::cout << r() << std::endl;
	}

	std::cout << std::endl;

	random_real_t m;
	for (int i = 0; i < 20; i++)
	{
		std::cout << m() << std::endl;
	}
}

void fileSample()
{
	std::cout << filesystem::file_exists("test.txt") << std::endl;

	char pathname[255];
	filesystem::get_current_path(pathname, 255);

	std::cout << pathname << std::endl;

	filesystem::create_directory("textures/a/b");
	filesystem::set_current_path("textures/a");

	//std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	//filesystem::write_file("vectors.txt", numbers.data(), (numbers.size() * sizeof(int)));

	std::vector<int> newNumbers;
	int* buffer = nullptr;
	size_t size;
	filesystem::read_file("vectors.txt", (void**)(&buffer), size);

	for (int i = 0; i < 5; i++)
	{
		newNumbers.push_back(*(buffer + i));
		std::cout << *(buffer + i) << std::endl;
	}

	filesystem::free_file(buffer);
}

int main()
{
	//basics();

	//function();
	//function2();
	//function3();
	
	//randIntro();
	//randSample();

	fileSample();

	std::cout << std::endl << "Hello World!" << std::endl << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
