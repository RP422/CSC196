#pragma once

#include <string>
#include <map>


template<typename TBase>
class CreatorBase
{
public:
	virtual TBase* Create() const = 0; // Abstract method in abstract class
};


template<typename T, typename TBase>
class Creator : public CreatorBase<TBase>
{
public:
	virtual TBase* Create() const { return new T; }
};


template<typename TBase>
class Spawner : public CreatorBase<TBase>
{
public:
	Spawner(TBase* instance) : m_instance(instance) {}
	virtual ~Spawner()
	{
		delete m_instance;
	}

	virtual TBase* Create() const { return m_instance->Clone(); }

private:
	TBase* m_instance = nullptr;
};


// It's not a good idea to not include definitions when you have templates like this.
template<typename TBase, typename TKey = std::string>
class Factory 
{
public:
	TBase* Create(TKey key)
	{
		TBase* obj = nullptr;

		// Equivilant to var
		auto iterator = m_regestry.find(key);
		
		if (iterator != m_regestry.end())
		{
			CreatorBase<TBase>* creator = (*iterator).second;
			//CreatorBase<TBase>* creator = iterator->second;

			obj = creator->Create();
		}

		return obj;
	}
	~Factory()
	{
		for (const auto& iterator : m_regestry)
		{
			delete iterator.second;
		}

		m_regestry.clear();
	}

	void Register(TKey key, CreatorBase<TBase>* creator)
	{
		if (m_regestry.find(key) == m_regestry.end())
		{
			m_regestry[key] = creator;
		}
	}

private:
	using registry_t = std::map<TKey, CreatorBase<TBase>*>;
	registry_t m_regestry;
};

class factory
{
public:
	factory();
	~factory();
};
