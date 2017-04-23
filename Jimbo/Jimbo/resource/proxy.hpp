
#ifndef JIMBO_RESOURCE_PROXY_HPP
#define JIMBO_RESOURCE_PROXY_HPP

/////////////////////////////////////////////////////////
// proxy.hpp
//
// Ben Storey
//
// When providing resources we give a proxy class so that we can swap out resources
// behind the scenes whilst still providing a unified interface. For example, so that the
// user doesn't have to do constant == null or isAvailable() checks
//
// Current behaviour is essentially identical to a regular pointer, but in making it a separate
// proxy that gives me options to add in hooks to the resource manager. Ideally it should
// take a lambda function too to update on all function calls
//
// I want to support proxy chaining too, where one proxy pointers to another and the wrapped
// object can still be called directly through the -> operator. To support this we need to change
// the return value when it's pointer also overloads ->. This requires some sfinae magic...
//
// https://jguegant.github.io/blogs/tech/sfinae-introduction.html
//
/////////////////////////////////////////////////////////

#include <utility>
#include <type_traits>

namespace jimbo
{

    // This sfinae magic works nicely. Unfortunately MSVC intellisense isn't smart enough to follow along!! :(
    template <class T> struct has_arrow_operator
    {

        // declval constructs a U type and then we can call operator->() on it. If it can't be called, then we don'thave an arrow
        // decltype(bool()) essentially means test is returning a boolean. It follows the comma operator, which means only
        // the bool() is passed to decltype. The first part is still evaluated however, which can only succeed when operator->() is defined
        template <typename U> static constexpr decltype(std::declval<U>().operator->(), bool()) test(int)
        {
            return true;
        }

        // our "sink", if we end up here then we didn't match the above.
        template <typename U> static constexpr bool test(...)
        {
            return false;
        }

        static constexpr bool value = test<T>(int());
    };

    // Implementation below is the "cleanest", but breaks intellisense :(
#ifndef _MSC_VER
    
    // Regular pointers will fail the has_arrow_operator test because it calls operator->(), but that's okay,
    // as we can also easily test for is_pointer
    template<class T, bool B = has_arrow_operator<T>::value || std::is_pointer<T>::value>
    class Proxy
    {
    public:

        Proxy(T* p) : p_(p) {}
        Proxy(T& p) : p_(&p) {}

        // This is the normal behaviour, where a pointer is returned
        template <bool hasOperator = B, typename std::enable_if< !hasOperator, void>::type * = nullptr >
        const T* operator->() const { return p_; }

        template <bool hasOperator = B, typename std::enable_if< !hasOperator, void>::type * = nullptr >
        T* operator->() { return p_; }

        // And the specialisation, if we have an arrow operator, return a reference instead, and it will chain them together,
        // essentially calling the ->() operator again on the wrapped proxy
        template <bool hasOperator = B, typename std::enable_if< hasOperator, void>::type * = nullptr >
        const T& operator->() const { return *p_; }

        template <bool hasOperator = B, typename std::enable_if< hasOperator, void>::type * = nullptr >
        T& operator->() { return *p_; }

    private:
        T * p_;
    };

#endif 

    // This implementation doesn't break intellisense quite so much (but does if we chain proxies)
#ifdef _MSC_VER 

    // Regular pointers will fail the has_arrow_operator test because it calls operator->(), but that's okay,
    // as we can also easily test for is_pointer
    template<class T, bool hasOperator = has_arrow_operator<T>::value || std::is_pointer<T>::value>
    class Proxy
    {
    public:

        Proxy(T* p) : p_(p) {}
        Proxy(T& p) : p_(&p) {}

        // Normal case, return a pointer
        const T* operator->() const { return p_; }
        T* operator->() { return p_; }

        // No harm to support dereferencing too
        const T& operator*() const { return *p_; }
        T& operator*() { return *p_; }

    private:
        T * p_;
    };

    
    template <class T>
    class Proxy<T, true>
    {
    public:

        Proxy<T, true>(T* p) : p_(p) {}
        Proxy<T, true>(T& p) : p_(&p) {}

        // And the specialisation, if we have an arrow operator, return a reference instead, and it will chain them together,
        // essentially calling the ->() operator again on the wrapped proxy
        const T& operator->() const { return *p_; }
        T& operator->() { return *p_; }

        // No harm to support dereferencing too
        const T& operator*() const { return *p_; }
        T& operator*() { return *p_; }

    private:
        T * p_;
    };

#endif 

    // Similar to make_pair, it allows us to create a proxy without having to keep typing the name of the types
    template <class T> Proxy<T>  make_proxy(T& t) { return Proxy<T>(&t); }
    template <class T> Proxy<T>  make_proxy(T* t) { return Proxy<T>(t);  }
}

#endif // JIMBO_RESOURCE_PROXY_HPP