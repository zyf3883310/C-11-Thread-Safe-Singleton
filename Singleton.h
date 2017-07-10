#ifndef _SINGLETON_H_ 
#define _SINGLETON_H_
#include <stdlib.h>
#include <assert.h>
#include <thread>
#include <mutex>

template <typename T>
class CSingleton
{
public:
	static T& GetInstance()
	{
		std::call_once(flag, &CSingleton::Init);
		assert(m_instance != NULL);
		return *m_instance;
	}
	
private:
	static void Init()
	{
		m_instance = new T;
		if (m_instance)
		{
			::atexit(Release);
		}
	}
	static void Release()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = NULL;
		}
	}
	CSingleton() {}
	~CSingleton() {}
	CSingleton(const CSingleton& rhs);
	CSingleton& operator=(const CSingleton& rhs);
private:
	static std::once_flag flag;
	static T* m_instance;

};

template <typename T>
std::once_flag CSingleton<T>::flag;

template <typename T>
T* CSingleton<T>::m_instance = NULL;

#endif //_SINGLETON_H_ 
