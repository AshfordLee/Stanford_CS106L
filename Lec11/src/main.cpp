#include<iostream>
#include<type_traits>
#include<unordered_set>
#include<vector>

#include"utils.hpp"

template<typename T>
T min_basic(T a,T b)
{
    return a<b? a:b;
}

void test_min_basic()
{
    int int_min=min_basic<int>(106,107);
    out()<<"min_basic<int>(106,107): "<<result<<int_min<<end;
    // 这里result是在utils.hpp里面定义的
    // 在输出完了"min_basic<int>(106,107): "(以我们设置的格式)后
    // 要用result调整回默认格式然后输出int_min

    double double_min=min_basic<double>(42.5, 3.14);
    out()<<"min_basic<double>(42.5, 3.14): "<<result<<double_min<<end;

    std::string string_min=min_basic<std::string>("Jacob","Fabio");
    out()<<"min_basic<std::string>(\"Jacob\",\"Fabio\"): "<<result<<string_min<<end;

    std::string expr {"min_basic(\"Jacob\",\"Fabio\"):"};
    auto string_min_bad=min_basic("Jacob","Fabio");
    out() << "Type of " + expr << result << type(string_min_bad) << end;
    out() << expr << result << string_min_bad << end;
}

template <typename T>
T min_ref(const T& a,const T& b)
{
    return a<b? a:b;
}

void test_min_ref()
{
    int int_min=min_ref(106,107);
    // 注意其实这里编译器会自动把两个int变成int&,属于是自动推断
    out()<<"min_ref<int>(106,107): "<<result<<int_min<<end;

    double double_min=min_ref(42.5,3.14);
    out()<<"min_ref<double>(42.5,3.14): "<<result<<double_min<<end;

    // 前两个可以用隐式变量传递，等于我也不告诉编译器传入的是什么
    // 编译器会自己推断

    // std::string string_min=min_ref("Arwen","Aragorn");
    // 这里编译会报错，因为传入字符串常量的时候，这两个其实都是const char*型变量
    // 所以min_ref传回的也是const char*,而我们想把它赋值给std::string
    // 所以会报错

    // 但我们可以改成这样：
    // const char* string_min_pointer=min_ref("Arwen","Aragorn");
    // 这样回传一个const char*,不过要注意，这里min_ref
    // 其实是在比较两个const char*字符串的内存地址并且返回较小的那个
    // 并不是返回根据ASCII码去比较的大小
    // 假如说返回了指向"Arwen"的指针const char*
    // 那我们执行std::cout<<string_min_pointer<<std::endl;
    // 是会打印出"Arwen"的

    std::string string_min=min_ref<std::string>("Arwen","Aragorn");
    // 显式告诉编译器，传入的是两个std::string!
    // 这里内存发生了什么？我们传入的是两个字面量
    // 这两个字面量是存在rodata段(只读数据段)的
    // 所以其实是创造了两个std::string对象(堆上)，用于copy这两个传入的
    // 字符串字面量，然后后面再对那两个std::string对象进行一系列比较
}

template <typename U,typename V>
auto min_flex(const U& a,const V& b)
{
    return a<b? a:b;
}

void test_min_flex()
{
    std::string expr {"min_flex(106,107.5):"};
    auto min_elem=min_flex(106,107.5);

    out()<<"Type of "+expr<<result<<type(min_elem)<<end;
    out()<<expr<<result<<min_elem<<end;
}


template <typename TIterator,typename TValue>
TIterator find(TIterator begin,TIterator end,TValue value)
{
    for (auto it=begin;it!=end;++it)
    {
        if (*it==value)
        {
            return it;
        }
    }
    return end;
}


void test_find()
{
    std::vector<int> v {1,2,3,4,5};
    auto it1=::find<std::vector<int>::iterator,int>(v.begin(),v.end(),3);
    // 为什么这里要用::find?因为怕命名冲突
    // 因为find函数在标准库当中也有，所以这里用::find
    // ::表示明确指定使用全局作用域的find

    out()<<"find<std::vector<int>::iterator, int>(v.begin(), v.end(), 3): "<<result<<pit(v,it1)<<end;

    std::string expr2{"find(v.begin(),v.end(),10): "};
    auto it2=::find(v.begin(),v.end(),10);

    using TIterator2=decltype(it2);
    // 获取迭代器的类型，这里就是std::vector<int>::iterator
    using TValue2=typename std::iterator_traits<TIterator2>::value_type;
    // 获取迭代器所指的值的类型，这里就是int

    out()<<expr2<<result<<"Titerator= "<<type<TIterator2>()<<end;
    // 输出std::vector<int>::iterator
    out()<<expr2<<result<<"TValue= "<<type<TValue2>()<<end;
    // 输出int
    out()<<expr2<<result<<pit(v,it2)<<end;

    std::unordered_set<std::string> us {"hello","there","welcome","to","cs106l!"};
    std::string expr3 { "find(us.begin(), us.end(), \"welcome\"): "};
    auto it3=::find(us.begin(),us.end(),"welcome");

    using TIterator3=decltype(it3);
    using TValue3=typename std::iterator_traits<TIterator3>::value_type;
    out() << expr3 << result << "TIterator = " << type<TIterator3>() << end;
    out() << expr3 << result << "TValue = " << type<TValue3>() << end;
    out() << expr3 << result << pit(us, it3) << end;
}


template <typename T>
concept Comparable=requires(T a,T b)
{
    {a<b}->std::convertible_to<bool>;
};

template <Comparable T>
T min_constrained(const T& a,const T& b)
{
    return a<b? a:b;
}

void test_min_constrained()
{
    min_constrained(10,20);

    auto satisfies=[](auto val)
    {
        // 传入一个参数，获取这个参数的类型，并且检查这个类型是否满足Comparable概念
        // 如果满足，就输出Yes!，否则输出No!
        using T=decltype(val);
        out()<<type(val).name()+" is Comparable<T>: " << result;

        if constexpr(Comparable<T>) std::cout<<"Yes!";

        else std::cout<<"No!";

        std::cout<<end;
    };

    satisfies(5);
    satisfies(std::stringstream {});
    satisfies("Hello World!");
    satisfies(std::vector<int> { 1, 2, 3 });
}

template<Comparable T>
T min_var(const T& v)
{
    return v;
}
// 单个值求最小值，其实是一个base condition

template <Comparable T,Comparable... Args>
// 这里定义了单个参数和参数包
T min_var(const T& v,const Args&... rest)
{
    // v是第一个参数，rest...是后面的参数包展开
    auto m =min_var<T>(rest...);
    return v<m? v:m;
}

void test_min_var()
{
    auto m1=min_var(1);
    out()<<"min_var(1): "<<result<<m1<<end;

    auto m2=min_var(2,1);
    out()<<"min_var(2,1): "<<result<<m2<<end;

    auto m3=min_var<std::string>("cool","varadic","template");
    out()<<"min_var<std::string>(\"cool\",\"varadic\",\"template\"): "<<result<<m3<<end;

    std::string expr4 {"min_var(10,2.5,3.0f): "};
    auto m4=min_var(10,2.5,3.0f);
    out()<<expr4<<result<<m4<<end;
    out()<<"Type of "<<expr4<<result<<type(m4)<<end;

    std::string expr5{"min_var<double>(10,2.5,3.0f): "};
    auto m5=min_var<double>(10,2.5,3.0f);
    out()<<expr5<<result<<m5<<end;
    out()<<"Type of "<<expr5<<result<<type(m5)<<end;



}

test(test_min_basic);
test(test_min_ref);
test(test_min_flex);
test(test_find);
test(test_min_constrained);
test(test_min_var);
// 注意这个通过宏添加的测试是比main执行早的
// 所以当main执行的时候，这些测试已经
// 被添加到了测试储存器里面去

int main()
{
    return testing::run_tests();
}
