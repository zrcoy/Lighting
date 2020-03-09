#ifndef __ObjectPool_H__
#define __ObjectPool_H__

template <class MyType> class ObjectPool
{
protected:
    std::vector<MyType> m_Objects;

public:
    ObjectPool()
    {
    }

    virtual ~ObjectPool()
    {
        while( m_Objects.empty() == false )
        {
            delete m_Objects.back();
            m_Objects.pop_back();
        }
    }

    void AddNewObjectToPool(MyType object)
    {
        m_Objects.push_back( object );
    }

    MyType GetObjectFromPool()
    {
        if( m_Objects.empty() )
            return nullptr;

        MyType pObject = m_Objects.back();
        m_Objects.pop_back();
        return pObject;
    }

    void ReturnObject(MyType object)
    {
        m_Objects.push_back( object );
    }
};

#endif //__ObjectPool_H__
