#ifndef OBJECTGUARD
#define OBJECTGUARD

template <typename T>
class ObjectGuard
{
    T* m_object;
public:
    ObjectGuard(T* i_object) : m_object(i_object){}
    ~ObjectGuard(){ delete m_object; }
};

#endif // OBJECTGUARD

