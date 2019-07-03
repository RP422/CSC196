#pragma once

// A pointer that deconstructs when it goes out of scope.
template<typename T>
class smart_ptr
{
public:
	smart_ptr(T* ptr) : m_ptr(ptr) {}
	~smart_ptr() 
	{ 
		if (m_ptr) 
			delete m_ptr; 
	}

	// This looks weird, but it deletes the functions that have these signature
	smart_ptr(const smart_ptr<T>&) = delete;
	smart_ptr& operator = (const smart_ptr<T>&) = delete;

	T* get() { return m_ptr; }

	T& operator * () { return *m_ptr; }
	T* operator -> () { return m_ptr; }

private:
	T* m_ptr = nullptr;
};