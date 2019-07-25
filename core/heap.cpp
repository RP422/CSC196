#include "heap.h"
#include "assert.h"
#include "types.h"

#include <new>
#include <iostream>

#define MEMORY_SIGNATURE 0xDEADCA75 //3735931509

heap::~heap()
{
	//free(m_alloc_head);
	report();
	ASSERT_MSG(m_allocations == 0, "Memory leak.");
}

void * heap::allocate(size_t size)
{
	size_t total_size = size + sizeof(alloc_header);
	u8* memory = static_cast<u8*>(malloc(total_size));
	alloc_header* header = (alloc_header*)(memory);
	header->size = size;
	header->signature = MEMORY_SIGNATURE;

	header->next = m_alloc_head;
	header->prev = nullptr;

	if (m_alloc_head != nullptr)
	{
		m_alloc_head->prev = header;
	}

	m_alloc_head = header;

	// Updating stats
	m_allocated += size;
	m_allocations++;

	m_allocated_total += size;
	m_allocations_total++;

	if (m_allocated > m_allocated_peak)
	{
		m_allocated_peak = m_allocated;
	}

	void* ptr = memory + sizeof(alloc_header);

	return ptr;
}

void heap::free(void * ptr)
{
	alloc_header* header = (alloc_header*)((u8*)ptr - sizeof(alloc_header));
	//ASSERT(header->signature == MEMORY_SIGNATURE);

	if (header->signature == MEMORY_SIGNATURE)
	{
		free(header);
	}
}

void heap::report()
{
	std::cout << "Total Allocated: " << m_allocated_total << std::endl;
	std::cout << "Total Freed: " << m_freed << std::endl;
	std::cout << std::endl;
	std::cout << "Currently Allocated: " << m_allocated << std::endl;
	std::cout << "Current Allocations: " << m_allocations << std::endl;
}

void heap::free(alloc_header * header)
{
	if (header->prev == nullptr)
	{
		ASSERT(header == m_alloc_head);
		m_alloc_head = header->next;
	}
	else
	{
		header->prev->next = header->next;
	}

	if (header->next != nullptr)
	{
		header->next->prev = header->prev;
	}

	m_allocated -= header->size;
	m_freed += header->size;

	m_allocations--;
	::free(header);
}
