#include <iostream>
#include <exception>
#include <tuple>
#include <type_traits>
#include <atomic>
#include <thread>
#include <functional>

#if !defined(defDX_S)
#define defDX_S(x)		#x
#endif
#if !defined(defDX_S_)
#define defDX_S_(x)		defDX_S(x)
#endif
#if !defined(defDX_S__LINE__)
#define defDX_S__LINE__	defDX_S_(__LINE__)
#endif
#if !defined(defDX__FILELINE)
#define defDX__FILELINE		(__FILE__  " line " defDX_S__LINE__)
#endif

#ifndef ERROR_

#if defined(_WIN32)
#define ERROR_				{ ::std::cout << "![EXCPT]" << (const char*)defDX__FILELINE << ::std::endl; 	\
							throw ::std::exception(); }
#elif defined(__unix__)
#if defined(__linux__)
#define ERROR_				try {																			\
                            	throw ::std::exception();													\
							} catch (::std::exception& x) {													\
								::std::cout << "![EXCPT]" << (const char*)defDX__FILELINE << ::std::endl;	\
							}
#else
#error This UNIX operating system is not supported by dx::NN
#endif
#else
#error This operating system is not supported by dx::NN
#endif

#endif
#ifndef ER_IF
#define ER_IF(x, beforeExc, AfterExc) if ( (x) ) { beforeExc ERROR_ AfterExc }
#endif
#ifndef ER_IFN
#define ER_IFN(x, beforeExc, AfterExc) if ( !(x) ) { beforeExc ERROR_ AfterExc }
#endif

namespace print_func_
{
    template<typename T1, typename T2>
    void print_spec_(T1, T2);
}
void func1(int, double);
template<typename T>
void func1(int, T);
template<typename T>
void func1(T, int);
template<typename T>
void func1(T, T);
template<typename T1, typename T2>
void func1(T1, T2);

template<typename T, typename I = ::std::enable_if_t<::std::is_integral_v<T>>>
auto _sum(T) -> T;
template<typename T, typename... U, typename I = ::std::enable_if_t<::std::is_integral_v<T>>>
auto _sum(T, U...) -> T;

template<typename T, typename... Ts>
auto concat(T t, Ts... ts) -> auto
{
    if constexpr (sizeof...(ts) > 0)
    {
        return [=](auto... parameters) -> auto
            {
                return t(concat(ts...)(parameters...));
            };
    }
    else
    {
        return [=](auto... parameters) -> auto
            {
                return t(parameters...);
            };
    }
}

int spec_sum_foo(int, int, int, int);
void spec_print_foo(int);
class Base;
void somefunc(Base&);
int&& takesomeint();
int& _lvalue();
int&& _xvalue();
int _prvalue();

template<typename T,
    typename IntT = int,
    typename FloatT = double>
struct somestruct {};
struct somestruct2
{
    int num;
    float some;
    double some2;

    somestruct2(int anum, float asome = 0.f, double asome2 = 1.) : num(anum), some(asome), some2(asome2) {};
};

// abstract class
class Base
{
protected:
    int inf;

public:
    Base(int arg)
    {
        inf = arg;
    }
    virtual ~Base() = default;

    virtual void print_info() = 0;
    virtual void change_info(int arg) = 0;
};

class DerivedFromBase : public Base
{
private:
    int information;

public:
    DerivedFromBase(int base_arg, int arg) : Base(base_arg)
    {
        information = arg;
    }

    virtual void print_info() override
    {
        ::print_func_::print_spec_(inf, information);
    }

    virtual void change_info(int arg) override
    {
        information = arg;
    }
};

class DerivedFromBase2 : public Base
{
private:
    int information;

public:
    DerivedFromBase2(int base_arg, int arg) : Base(base_arg)
    {
        information = arg;
    }

    virtual void print_info() override
    {
        ::print_func_::print_spec_(inf, information);
    }

    virtual void change_info(int arg) override
    {
        information = arg;
    }
};

template<typename T, typename Y>
class Outter
{
public:
    T propI;
    Y propI2;

    template<typename U>
    void operator()(U val)
    {
        ::std::cout << "called operator<U>(): " << val << ::std::endl;
    }

    class PureInner
    {
    public:
        T propInner1;
        Y propInner2;
    };
};

template<typename T, typename Y>
class Instrument
{
public:
    T propI;
    Y propI2;

    template<typename U>
    void operator()(U val)
    {
        ::std::cout << "called operator<U>(): " << val << ::std::endl;
    }

    template<typename TI, typename YI>
    class Inner
    {
    public:
        TI propInner1;
        YI propInner2;
    };
};

template<typename T>
class Weapon
{
//friend class Instrument<T>;
public:
    T propW;
    
    template< template<typename, typename> typename C, typename U, typename Y>
    Weapon(C<U, Y> instrum)
    {
        if (typeid(C<U, Y>) == typeid(Instrument<U, Y>))
        {
            ::std::cout << "called Weapon(Instrument<U, Y>)" << ::std::endl;
        }
        else if (typeid(C<U, Y>) == typeid(Outter<U, Y>))
        {
            ::std::cout << "called Weapon(Outter<U, Y>)" << ::std::endl;
        }
        ::std::cout << "constructor Weapon: " << instrum.propI << ::std::endl;
        ::std::cout << "constructor Weapon: " << instrum.propI2 << ::std::endl;
        instrum(2);
    }

    template<typename R, typename I = ::std::enable_if_t<::std::is_same_v<::std::decay_t<R>, int>>>
    void check_for_int(R)
    {
       ::std::cout << "int<,>" << ::std::endl;
    }

    template<typename R, typename I = ::std::enable_if_t<::std::is_same_v<::std::decay_t<R>, int>>>
    void check_for_int(R*)
    {
       ::std::cout << "int<,>" << ::std::endl;
    }

    /*
    template<typename R>
    void check_for_int(::std::enable_if_t<::std::is_same_v<::std::decay_t<R>, int>, int>)           // ERROR: couldn't deduce template parameter 'R'
    {
       ::std::cout << "int(,)" << ::std::endl;
    }

    template<typename R>
    void check_for_int(::std::decay_t<R>)                                                           // ERROR: couldn't deduce template parameter 'R'
    {
       ::std::cout << "int(,)" << ::std::endl;
    }
    */

    template<typename R, typename I = ::std::enable_if_t<::std::is_same_v<::std::decay_t<R>, int>>>
    void check_for_int()
    {
       ::std::cout << "int<,>" << ::std::endl;
    }
};

int main()
{
    // Pointers and Refs
    int instanseInt = 2;
    int instanseInt2 = 3;

    int* pInstInt1 = &instanseInt;
    int* const cpInstInt1 = &instanseInt;
    const int* const cpInstInt2 = &instanseInt;         // same
    int const* const cpInstInt3 = &instanseInt;         // same
    const int* pInstInt2 = &instanseInt;                // same
    int const* pInstInt3 = &instanseInt;                // same
    ::std::cout << "Pointers 1: " << *pInstInt1 << ' ' << *cpInstInt1 << ' ' << *cpInstInt2 << ' ' << *cpInstInt3 << ' ' << *pInstInt2 << ' ' << *pInstInt3 << ::std::endl;
    pInstInt1 = &instanseInt2;
    //cpInstInt1 = &instanseInt2;                       // ERROR: const ptr
    //cpInstInt2 = &instanseInt2;                       // ERROR: const ptr
    //cpInstInt3 = &instanseInt2;                       // ERROR: const ptr
    *cpInstInt1 = 4;
    //*pInstInt2 = 8;                                  // ERROR: ptr to const
    //*pInstInt3 = 9;                                  // ERROR: ptr to const
    pInstInt2 = &instanseInt2;
    pInstInt3 = &instanseInt2;
    ::std::cout << "Pointers 2: " << *pInstInt1 << ' ' << *cpInstInt1 << ' ' << *cpInstInt2 << ' ' << *cpInstInt3 << ' ' << *pInstInt2<< ' ' << *pInstInt3 << ::std::endl;

    int& rfInstInt1 = instanseInt;
    //int& const crfInstInt1 = instanseInt;             // ERROR: cannot be applied
    //int const& const crfInstInt2 = instanseInt;       // ERROR: cannot be applied
    //const int& const crfInstInt3 = instanseInt;       // ERROR: cannot be applied
    int const& rfInstInt2 = instanseInt;
    const int& rfInstInt3 = instanseInt;
    ::std::cout << "Refs 1: " << rfInstInt1 << ' ' << rfInstInt2 << ' ' << rfInstInt3 << ::std::endl;
    rfInstInt1 = instanseInt2;
    //rfInstInt2 = 2;                                   // ERROR: ref to const
    //rfInstInt3 = 6;                                   // ERROR: ref to const
    ::std::cout << "Refs 2: " << rfInstInt1 << ' ' << rfInstInt2 << ' ' << rfInstInt3 << ::std::endl;

    //C++17
    auto x1 = {0};                                      // ::std::initializer_list_<int>
    auto x2 = 0;                                        // int
    auto x3 {0};                                        // int
    auto x4 = {0, 1, 2};                                // ::std::initializer_list_<int>
    //auto x5 {0, 1, 2};                                // ERROR

    auto y1 = x1;                                       // ::std::initializer_list_<int>
    auto y2 = x2;                                       // int
    auto y3 = x3;                                       // int
    auto y4 = x4;                                       // ::std::initializer_list_<int>

    auto* px1 = &x1;                                    // ::std::initializer_list_<int>*
    auto& rx1 = x1;                                     // ::std::initializer_list_<int>&
    auto&& _rx1 = x1;                                   // ::std::initializer_list_<int>&
    auto&& rvx1 = ::std::move(x1);                      // ::std::initializer_list_<int>&&
    decltype(x1) _x1 = x1;                              // ::std::initializer_list_<int>
    decltype(auto) __x1 = x1;                           // ::std::initializer_list_<int>

    ::std::tuple<int, int, int> tpl1(1, 2, 3);
    auto [a, b, c] = tpl1;
    ::std::cout << a << ::std::endl;
    ::std::cout << b << ::std::endl;
    ::std::cout << c << ::std::endl;

    // Templates
    //func1(1, 1);                                      // ERROR: ambiguous call
    //func1<int>(1, 1);                                 // ERROR: ambiguous call
    func1<int, int>(1, 1);                              // void func1(T1 a, T2 b)
    func1(1, 1.2);                                      // void func1(int a, double b)
    func1("hello", "world");                            // void func1(T a, T b)
    func1("hello", 'c');                                // void func1(T1 a, T2 b)
    auto pfunc1 = func1<int, double>;
    auto pfunc2 = func1<const char*, const char*>;
    ::std::cout << &pfunc1 << ::std::endl;
    ::std::cout << &pfunc2 << ::std::endl;

    // Constraints and concepts



    // (sub Templates) Static Polymorphism
    Instrument<double, int> instr1;
    instr1.propI = 5.5;
    instr1.propI2 = 7;
    Outter<double, int> instr2;
    instr2.propI = 246.75;
    instr2.propI2 = 2357;
    Weapon<int> wp1(instr1);
    Weapon<int> wp2(instr2);

    Outter<double, double>::PureInner inner1;
    Instrument<double, double>::template Inner<double, int> inner2;
    //Weapon<int> wp3(inner1);                                              // ERROR inner1 is not an template class
    //Weapon<int> wp4(inner2);                                              // ERROR inner2 is an template class, but it have no variables propI and propI2) \
                                                                                & no match for call to 'Instrument<double, double>::Inner<double, int>'
    //end of Static Polymorphism

    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int<int>();
    wp1.check_for_int<const int>();
    wp1.check_for_int<volatile int>();
    wp1.check_for_int<const volatile int>();
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int<int&>();
    wp1.check_for_int<int&&>();
    wp1.check_for_int<const int&>();
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int<const int&&>();
    wp1.check_for_int<volatile int&>();
    wp1.check_for_int<volatile int&&>();
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int<const volatile int&>();
    wp1.check_for_int<const volatile int&&>();
    //wp1.check_for_int<int*>();                                            // ERROR
    ::std::cout << "-----------------------" << ::std::endl;

    wp1.check_for_int(static_cast<int>(1));
    wp1.check_for_int(static_cast<const int>(1));
    wp1.check_for_int(static_cast<volatile int>(1));
    wp1.check_for_int(static_cast<const volatile int>(1));
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int(static_cast<int&>(x3));
    wp1.check_for_int(static_cast<int&&>(1));
    wp1.check_for_int(static_cast<const int&>(1));
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int(static_cast<const int&&>(1));
    wp1.check_for_int(static_cast<volatile int&>(x3));
    wp1.check_for_int(static_cast<volatile int&&>(1));
    ::std::cout << "-----------------------" << ::std::endl;
    wp1.check_for_int(static_cast<const volatile int&>(x3));
    wp1.check_for_int(static_cast<const volatile int&&>(1));
    wp1.check_for_int(static_cast<int*>(&x3));
    ::std::cout << "-----------------------" << ::std::endl;

    ::std::cout << _sum(1) << '\n' << _sum(1, 2, 3, 4, 5) << ::std::endl;
    ::std::cout << ::std::endl;
    //::std::cout << _sum(1, 2., 3, 4., 5);                                 // ERROR: there are types which are not is_integral

    auto confoo1( concat([](int a) { return a + 1; }, [](int a, int b, int c, int d) { return a + b + c + d; }) );
    ::std::cout << "hey - " << confoo1(1, 2, 3, 4) << ::std::endl; // For some functions f, g, h, ...  -  f(g(h(a1, ..., aN)));

    //somestruct<char, .FloatT = float> testStruct;                 // ERROR: a similar extension (sometimes called keyword \
                                                                        arguments) was proposed earlier in the C++ standardization process by Roland \
                                                                        Hartinger (see Section 6.5.1 of [StroustrupDnE]).
                                                                    // Although technically sound, the \
                                                                        proposal was ultimately not accepted into the language for various reasons.

    // Dynamic Polymorphism
    //Base base1(10);                                           // ERROR since in class Base there are pure virtual functions
    DerivedFromBase drv1(11, 1);
    DerivedFromBase2 drv2(12, 1);
    DerivedFromBase2* drv3 = new DerivedFromBase2(13, 3);
    somefunc(drv1);                                             // OK, since : -> public <- Base
    somefunc(drv2);                                             // OK, since : -> public <- Base
    delete drv3;                                                // there is necessary to declare virtual ~Base() = default;
    // end of Dynamic Polymorphism

    // Atomic/Thread
    /*volatile */::std::atomic<bool> amb1(true);
    ::std::atomic<bool> amb2(false);
    size_t res_from_lambda1 = {0};
    ::std::thread thr1([&, i{ static_cast</*volatile */size_t>(1) }]() mutable -> void
        {                                                               // if -> <sometype (not void)> then, if do not returned any value, then compiler can optimize it
            //volatile size_t i = 1;                                                    // alternative
            while(amb1.load())
            {
                ++i;
                if (i >= 10000000)
                {
                    ::std::cout << "reached!" << ::std::endl;
                    amb2.store(true);
                }
                if (amb2.load())
                {
                    ::std::cout << "changed!" << ::std::endl;
                    amb1.store(false);
                }
            }
            ::std::cout << "finished!" << ::std::endl;
            //return i;                                                 // work
            //return 1;                                                 // also work
        });
    ::std::cout << res_from_lambda1 << ::std::endl;
    thr1.join();

    ::std::atomic_int amfirst(0);
    ::std::atomic_int amsecond(0);
    ::std::function thrfoo1([&]() -> void
        {
            amfirst.store(1, ::std::memory_order_release);
            amsecond.store(1, ::std::memory_order_release);
        });
    ::std::function thrfoo2([&]() -> void
        {
            while (amsecond.load(::std::memory_order_acquire) == 0) continue;
            ER_IFN(amfirst.load(::std::memory_order_acquire) == 1,,);
        });
    ::std::thread thr2(thrfoo2);
    ::std::thread thr3(thrfoo1);
    thr2.join();
    thr3.join();

    // Expressions (some-values) and Ref Types
    int explicit_someInt = takesomeint();
    auto someInt1 = takesomeint();
    //decltype(auto) someInt2 = takesomeint();                          // ERROR
    decltype(takesomeint()) expr_xxx1 = takesomeint();
    decltype((takesomeint())) expr_xxx2 = takesomeint();
    ::std::cout << explicit_someInt << '\n' << someInt1 << '\n';
    ::std::cout << expr_xxx1 << '\n';                                   // ?
    ::std::cout << expr_xxx2 << ::std::endl;                            // ?

    if constexpr (::std::is_lvalue_reference<decltype(takesomeint())>::value)
    {
        ::std::cout << "expression is lvalue" << ::std::endl;
    }
    else if constexpr (::std::is_rvalue_reference<decltype(takesomeint())>::value)
    {
        ::std::cout << "expression is xvalue" << ::std::endl;
    }
    else
    {
        ::std::cout << "expression is prvalue" << ::std::endl;
    }

    if constexpr (::std::is_lvalue_reference<decltype((takesomeint()))>::value)
    {
        ::std::cout << "expression is lvalue" << ::std::endl;
    }
    else if constexpr (::std::is_rvalue_reference<decltype((takesomeint()))>::value)
    {
        ::std::cout << "expression is xvalue" << ::std::endl;
    }
    else
    {
        ::std::cout << "expression is prvalue" << ::std::endl;
    }

    int sampleInt = 67;
    //int&& rSampleInt = sampleInt;                                     // ERROR: rvalue can not be bind to an lvalue
    int&& rSampleInt2 = ::std::move(sampleInt);
    int&& rSampleInt3 = static_cast<int&&>(sampleInt);
    ::std::cout << "just rvalue cast:\n";
    ::std::cout << sampleInt << ' ' << rSampleInt2 << ' ' << rSampleInt3 << '\n';
    sampleInt = 68;
    ::std::cout << sampleInt << ' ' << rSampleInt2 << ' ' << rSampleInt3 << '\n';
    rSampleInt2 = 12;
    rSampleInt3 = 85;
    ::std::cout << sampleInt << ' ' << rSampleInt2 << ' ' << rSampleInt3 << ::std::endl;

    ::std::string&& s = ::std::string{ "sample of string" };
    ::std::cout << ::std::is_lvalue_reference<decltype(s)>::value << ' ';                           // false
    ::std::cout << ::std::is_rvalue_reference<decltype(s)>::value << ' ';                           // true (s as declared)
    ::std::cout << ::std::is_same<decltype(s), ::std::string&>::value << ' ';                       // false
    ::std::cout << ::std::is_same<decltype(s), ::std::string&&>::value << ' ';                      // true
    ::std::cout << ::std::is_lvalue_reference<decltype((s))>::value << ' ';                         // true (s is an lvalue)
    ::std::cout << ::std::is_rvalue_reference<decltype((s))>::value << ' ';                         // false
    ::std::cout << ::std::is_same<decltype((s)), ::std::string&>::value << ' ';                     // true (T& signals an lvalue)
    ::std::cout << ::std::is_same<decltype((s)), ::std::string&&>::value << ::std::endl;            // false

    ::std::cout << ::std::is_same_v<decltype(_lvalue()), int&> << ' ';                              // yields true because result is lvalue
    ::std::cout << ::std::is_same_v<decltype((_lvalue())), int&> << ' ';                            // yields true because result is lvalue
    ::std::cout << ::std::is_same_v<decltype((_lvalue())), int&&> << ' ';                           // yields false
    ::std::cout << ::std::is_same_v<decltype(_xvalue()), int&&> << ' ';                             // yields true because result is xvalue
    ::std::cout << ::std::is_same_v<decltype((_xvalue())), int&> << ' ';                            // yields false
    ::std::cout << ::std::is_same_v<decltype((_xvalue())), int&&> << ' ';                           // yields true because result is xvalue
    ::std::cout << ::std::is_same_v<decltype(_prvalue()), int> << ' ';                              // yields true because result is prvalue
    ::std::cout << ::std::is_same_v<decltype((_prvalue())), int> << ::std::endl;                    // yields true because result is prvalue

    int& lref1 = _lvalue();                     // OK: lvalue reference can bind to an lvalue
    //int& lref3 = _prvalue();                  // ERROR: lvalue reference cannot bind to a prvalue
    //int& lref2 = _xvalue();                   // ERROR: lvalue reference cannot bind to an xvalue
    //int&& rref1 = _lvalue();                  // ERROR: rvalue reference cannot bind to an lvalue
    int&& rref2 = _prvalue();                   // OK: rvalue reference can bind to a prvalue
    int&& rref3 = _xvalue();                    // OK: rvalue reference can bind to an xrvalue

    return 0;
}

void func1(int a, double b)
{
    ::std::cout << "void func1(int a, double b):" << ::std::endl;
    ::print_func_::print_spec_(a, b);
}

template<typename T>
void func1(int a, T b)
{
    ::std::cout << "void func1(int a, T b):" << ::std::endl;
    ::print_func_::print_spec_(a, b);
}

template<typename T>
void func1(T a, int b)
{
    ::std::cout << "void func1(T a, int b):" << ::std::endl;
    ::print_func_::print_spec_(a, b);
}

template<typename T>
void func1(T a, T b)
{
    ::std::cout << "void func1(T a, T b):" << ::std::endl;
    ::print_func_::print_spec_(a, b);
}

template<typename T1, typename T2>
void func1(T1 a, T2 b)
{
    ::std::cout << "void func1(T1 a, T2 b):" << ::std::endl;
    ::print_func_::print_spec_(a, b);
}

namespace print_func_
{
    template<typename T1, typename T2>
    void print_spec_(T1 a, T2 b)
    {
        ::std::cout << a << ::std::endl;
        ::std::cout << b << ::std::endl;
    }
}

template<typename T, typename I = ::std::enable_if_t<::std::is_integral_v<T>>>
auto _sum(T val) -> T
{
    return val;
}

template<typename T, typename... U, typename I = ::std::enable_if_t<::std::is_integral_v<T>>>
auto _sum(T val, U... args) -> T
{
    return val + _sum(args...);
}

int spec_sum_foo(int a, int b, int c, int d)
{
    return a + b + c + d;
}

void spec_print_foo(int a)
{
    ::std::cout << a << ::std::endl;
}

void somefunc(Base& somebase)
{
    somebase.print_info();
}

int&& takesomeint()
{
    static int x = 5;
    return ::std::move(x++);
}

int& _lvalue()
{
    int x = 5;
    return x;
}

int&& _xvalue()
{
    int x = 5;
    return ::std::move(x);
}

int _prvalue()
{
    int x = 5;
    return x;
}
