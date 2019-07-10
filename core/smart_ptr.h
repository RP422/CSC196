#pragma once

// A pointer that deconstructs when it goes out of scope.
template<typename TBase>
class smart_ptr
{
public:
	smart_ptr(TBase* ptr) : m_ptr(ptr) {}
	~smart_ptr() 
	{ 
		if (m_ptr) 
			delete m_ptr; 
	}

	// This looks weird, but it deletes the functions that have these signature
	smart_ptr(const smart_ptr<TBase>&) = delete;
	smart_ptr& operator = (const smart_ptr<TBase>&) = delete;

	TBase* get() { return m_ptr; }

	TBase& operator * () { return *m_ptr; }
	TBase* operator -> () { return m_ptr; }

private:
	TBase* m_ptr = nullptr;
};