#pragma once

#include<algorithm>
#include<iomanip>
#include<iostream>
#include<functional>
#include<optional>
#include<ostream>
#include<sstream>

#include<stdio.h>
#include<stdlib.h>


namespace demangling
// 命名空间，C++符号名解析(name demangling)
{
    static std::optional<std::string> execute(const std::string& command,int* exit_status=nullptr)
    // 函数签名，static说明函数作用域在编译单元内
    // 什么是编译单元？一个编译单元通常包括一个源文件(.cpp)，这个源文件通过
    // #include去包含的所有头文件，以及所有的宏展开的结果
    // 注意在项目当中，每个源文件(.cpp)会生成一个独立的编译单元，而
    // 编译器会独立处理每个编译单元
    // 编译单元之间的链接是由链接器完成的
    // 所以现在可以详细解释这个#pragma once是什么意思了,虽然说这个.hpp文件可能被很多
    // 个源文件(.cpp)包含,但是#pragma once会保证在同一编译单元当中
    // 只被包含一次,前面提到的链接器(Linker)就是把一大堆的目标文件(.obj)
    // 合并成一个可执行文件

    // std::optional<>是什么?是一个C++17特性,用来表示后面"<>"当中的类型所指的东西是
    // "可能存在也可能不存在的"，这里的意思就是，可能返回std::string也可能返回空值
    // 这个函数的作用是:当命令被执行成功的时候，返回包含命令输出的字符串
    // 如果命令执行失败了，就返回std::nullopt，这也是一个C++17特性
    // 他就是表示"无值"

    // 函数的第一个参数是一个string表示命令，而且还是个const表示这个参数是不会被函数修改的
    // 第二个参数输一个表示退出状态的int指针，不过默认是nullptr，如果
    // 用户非常关心这个命令执行的状态，比如他觉得成功了就把状态设置为1，不成功就是0
    // 那么它可以用一个int表示这个并且写入到传入参数的那个int*所指的地方去

    {
        std::string result;
        // 最终结果会用字符串来表示

        FILE* pipe=popen(command.c_str(),"r");
        // popen是C标准库的函数，他创建一个pipe并且执行一个命令，它的返回值是FILE* 
        // 这个FILE*指针指向"用于读取命令输入的文件流"
        // 如果这个FILE*指针创建失败，那就会返回NULL

        // command参数用的是command.c_str()，首先c_str()是std::string的成员函数，
        // 用于把这个string转化成C风格的字符串(以NULL结尾的字符数组)
        // modes参数有两种，一个是r(read)，一个是w(write)
        // r表示读取命令的输出，w表示向命令输入数据

        // 单论这行代码，这是一个典型的进程间通信(IPC)的例子
        // 使用pipe来捕获子进程执行的命令的输出
        // 这种方式在需要在C++程序中执行外部命令并处理其输出时非常常用

        // 我来举个例子说明"r"参数的作用,也就是什么叫做"读取命令的输出"
        // 比如我用这个函数运行ls -la这个命令(execute("ls -la"))
        // 本来应该输出类似于下面的东西(在终端中)
        // total 20
        // drwxr-xr-x  3 root root 4096 Mar 15 11:00 .
        // drwxr-xr-x  4 root root 4096 Mar 15 10:59 ..
        // -rw-r--r--  1 root root 2048 Mar 15 11:00 utils.hpp
        // -rw-r--r--  1 root root 1234 Mar 15 11:00 main.cpp
        // drwxr-xr-x  2 root root 4096 Mar 15 11:00 build
        // 但现在他们都被重定向到pipe中了,我们的程序下面就可以读取这些输出

        // 再说说参数"w"的作用,也就是什么叫做"向命令输入数据"
        // 比如我自己写了个程序可以sort一些东西
        // 那么我们可以先用popen(command:sort,modes:"w")来启动一个pipe和一个新的
        // 进程来运行sort命令
        // 注意这时候程序并不知道要sort什么东西,那么我们就可以用fprintf(pipe,"str")
        // 来向这个进程写入那些我们要排序的字符串
        // 当写完了之后,我们再写一行pclose(pipe)
        // 来把pipe关闭,相当于船关上了舱门,这时候进程(或者叫sort命令)
        // 就会真的开始工作来排序那些我们给他的字符串

        if(!pipe)
            return std::nullopt;
        // 这里可以理解为pipe创建失败了
        // 那么返回std::nullopt,表示并没有执行什么东西

        // 接下来是读取已执行的命令的输出
        char buffer[128];
        // 创建一个缓冲区,命令的输出从命令->缓冲区->到rusult字符串

        while(fgets(buffer,sizeof(buffer),pipe)!=nullptr)
        {
            result+=buffer;
        }
        // 这里是一次一次的通过fgets来读取pipe当中的数据
        // 也就是命令的输出
        // fgets有三个参数，第一个类型是char*,就是说把读到的数据
        // 放到这个char*所指的地方去
        // 第二个是int，表示一次最多读取int-1个字符，最后一个要留给结束符\0
        // 第三个是FILE*，指定要读取的文件流，这里是一个
        // 通过popen创建的管道，也就是命令输出的数据流

        int status=pclose(pipe);
        // 通过调用pclose来关闭pipe，并且获取命令的退出状态
        // 0代表成功执行，非0代表执行失败
        // -1代表pclose调用失败

        if (exit_status) 
        {
            *exit_status=status;
        }
        // 如果用户传入的exit_status不会空(注意这是一个int*变量)
        // 那么就把status写入到exit_status所指的地方去

        if (status!=0)
            return std::nullopt;
        // 如果status不是0代表命令执行出了问题，就返回空值
        // 如果status是0代表命令执行成功，就返回result
        return result;
    }


    static bool can_demangle()
    // 同上，这个static代表函数的作用域只在当前编译单元内
    {
        static std::optional<bool> available;
        // 一个available来表示即将检查的命令是否可用

        if (available.has_value())
            return *available;
        // 缓存检查，如果available有值，那么直接返回这个值
        // 这里解释一下为什么可以对available做解引用运算
        // 因为available不是一个bool，是一个std::optional<bool>
        // 这其实是一个包装器，bool是他里面的东西
        // 所以用*其实是把这个bool拿出来
        // 所以如下的赋值运算:*available=true是正常的

        int exec_status;
        execute("c++filt --version",&exec_status);
        // 尝试执行这个命令，并将命令执行的状态返回值存入exec_status
        // 如果exec_status是0，那么表示命令执行成功，available就设置为true
        // 如果exec_status不是0，那么表示命令执行失败，available就设置为false
        available=(exec_status==0);

        // 如果available是false，那么就输出警告信息
        if(!available)
        {
            std::cerr<<"\033[33mWarning: c++filt could not be found, so type names will be mangled.\033[0m\n\n";
        }

        return *available;
    }

    static std::string demangle(const std::string& mangled)
    // 传入的mangled是被编译器编码过的符号名
    // 举个例子有个函数签名是int add,编码完了可能是_Z3addii
    {
        if(!can_demangle())
            return mangled;
        // 检查之前的符号解析是否可用，调用can_demangle()函数其实就是在测试
        // 能否正常执行"c++file --version"指令
        // 如果不可用就直接返回mangled,也就是被编译器编码过的函数名


        auto demangled=execute("echo "+mangled+"| c++filt -t");
        // 尝试执行"echo"+mangled+"| c++filt -t"指令
        // 获取返回值，注意这里的返回值类型是std::optional<std::string>
        // 内容是命令执行后的输出

        if(!demangled.has_value())
            return mangled;
        // 如果demangled没有值，意思也就是说命令执行失败了
        // 就返回被编码过后的符号名

        auto rstrip=[](std::string str)
        {
            // 这是一个lambda函数，按值传递，会赋值一个str
            // 空的[]表示捕获所有变量，这里就是捕获str
            // 后面括号里的是真正的参数

            // 这里解释一下lambda函数当中捕获的概念，有点类似于换个方法传递参数

            // int x = 10;
            // int y = 20;

            // // 捕获所有外部变量
            // auto lambda1 = [=]() { 
            //     std::cout << x << y; // 可以使用 x 和 y
            // };

            // // 不捕获任何外部变量
            // auto lambda2 = []() {
            //     // std::cout << x; // 错误！不能访问 x
            // };

            // [=]代表捕获所有外部变量，也就是cpp文件当中的，[&]是按引用捕获
            // []代表不捕获任何外部变量
            // [x]代表捕获外部变量x，那么lambda函数内就可以使用x
            // [&x]代表按引用捕获外部变量x，那么lambda函数内就可以修改x

            auto end=std::find_if_not(str.rbegin(),str.rend(),isspace).base();
            // str.rbegin()和str.rend()是两个反向迭代器
            // str.rbegin()指向字符串的末尾，str.rend()指向字符串的开头
            // isspace是获取某char是不是空白字符
            // std::find_if_not是找到第一个不是空白字符的位置(从右往左)
            // 然后用base()把反向迭代器转换成正向迭代器

            // 举个例子，比如传入std::string str = "Hello World   \n\t  ";
            // 那么std::find_if_not(str.rbegin(),str.rend(),isspace)会找到这个d，也就是从右往左
            // 第一个不是空白字符的位置
            // 所以这个.base()是让这个d变成一个正向迭代器，这样他就指向d后面的那个字符(当然也就是空字符)
            // 所以我只要erase掉从end到str.end()(字符串真正的结尾处)的空格
            // 就删掉了字符串右边所有的空白字符

            str.erase(end,str.end());
            return str;
        };

        return rstrip(*demangled);
        // 把命令执行的输出去掉字符串右边的空字符，然后返回
    }

    template<typename T>
    struct Demangle
    {
        friend std::ostream& operator<<(std::ostream &os,const Demangle &t)
        {
            return os<<t.name();
        }
        // 这里定义了一个友元函数，意思是他可以访问Demangle的private成员
        // 注意友元函数不是类成员函数，所以没有this指针
        //这个函数的返回值是std::ostream&类型，即标准输出流
        // 这里在重载<<运算符，传入参数有两个，一个是标准输出流std::ostream &os(引用传入)
        // 还有一个是结构体Demangle的引用const Demangle &t
        // 然后把t.name()返回的字符串写入到os(输出流)当中
        // 这里非常有趣，当我们调用这个函数:std::cout<<Demangle<int>()的时候，其实
        // 第一个参数就是std::cout,第二个参数是Demangle<int>的实例化，也就是t
        // 或者我们可以以更详细的方法调用 
        // Demangle<int> temp
        // operator<<(std::cout,temp)
        // 注意这传入的temp会被自动转换成引用

        static const std::string& name()
        // 这里的static和上面的不一样，这里说的意思是不实例化对象，可以直接调用这个函数
        // 注意这是在结构体/类当中特有的static性质
        // 返回const std::string&类型
        {
            static auto name=demangle(typeid(T).name());
            // name是执行那句(demangle函数里面有写)命令返回的std::string
            // static在这里的意思是，name只会在第一次被调用的时候初始化一次
            // 之后每次调用name()都会返回这个初始化好的name
            // typeid是C++标准库的函数，用于获取类型信息
            // 比如typeid(int).name()可能会输出类似"i"的编码
            return name;
        }
    };
}

template <typename T>
static auto type()
{
    return demangling::Demangle<T>{};
    // 返回值是一个Demangle结构体的实例
    // {}的意思是空的结构体的初始化列表，注意这是必须的，如果没有{}那其实是在声明函数，而不是创建实例
}

template <typename T>
static auto type(T&& v)
// 这里的&&代表接受通用引用，可以是左值也可以是右值
{
    return type<std::remove_cvref_t<T>>();
    // type是刚刚定义的，std::remove_cvref_t的意思是把T的const volatile和引用修饰符去掉
    // 只保留类型本身
}


template <typename Container>
std::string pit(Container& c,typename Container::iterator it)
// 返回一个std::string，传入参数一个是容器的引用，一个是容器的迭代器
{
    using Iterator=typename Container::iterator;

    std::stringstream ss;
    ss<<"Iterator{ ";

    ss<<"pos= ";

    if (std::begin(c)!=std::end(c) && it!=std::end(c))
    // 判断条件:容器不为空，而且迭代器没有指向容器末尾
    {
        ss<<"end()";
    }

    else {
        auto pos=std::distance(std::begin(c),it);
        // std::distance返回两个迭代器之间的距离，也就是元素个数
        ss<<"begin()";

        if(pos>0)
        {
            ss<<" + "<<pos;
        }
    }

    if(it!=std::end(c))
    {
        ss<<", ";
        ss<<"element= "<<*it;

    }

    ss<<"}";

    return ss.str();
}


/* ========================================================================= *
 * Test functions/output                                                     *
 * ========================================================================= */

static std::ostream& out()
{
return std::cout << "\033[90m" << std::left << std::setw(60);
// 输出一些东西
// \033是个ASCII字符
// [90m是设置颜色为灰色
// std::left是左对齐
// std::setw是输出字段的宽度
// 示例 out()<<"Hello World"<<Std::endl;
}

static constexpr auto result="\033[0m";

static constexpr auto end="\n";

// 声明result和end
// constexpr意思是编译器在编译的时候就能确定
// consteval的意思是强迫编译器在编译的时候就求值


namespace testing
{
    struct Test
    {
        std::string name;
        std::function<void()> func;
    };
    // 这是一个测试用例的struct
    // 每个测试用例包含两个东西，一个是名称name
    // 还有一个函数包装器func,它里面可以储存任何void类型的函数


    static std::vector<Test> tests;
    // tests用来储存所有的测试用例
    // 这是一个储存Test的vector

    struct TestRegistrar
    {
        TestRegistrar(std::string name,std::function<void()> func)
        // 注册测试用例，构造函数就接受name和func，并且把
        // 他们push到tests当中去
        // 这就是一个测试用例了
        {
            tests.push_back({name,func});
        }
    };

    static int run_tests()
    {
        demangling::can_demangle();
        // 先检查是否可以解析符号名

        const std::string style_bg = "\033[48;5;45m";
        const std::string style_reset = "\033[0m";

        for (const auto& test:tests)
        {
            std::cout<<style_bg
                     <<std::setw(100)
                     <<std::setfill(' ')
                     <<std::left
                     <<test.name
                     <<style_reset
                     <<std::endl;

            test.func();
            // 执行测试函数
            std::cout<<"\n\n";
        }

        return 0;
    }

#define test(func) static testing::TestRegistrar registrar_##func(#func, func)
// 宏定义，传入一个检查函数参数func
// 然后会调用testing::TestRegistrar的构造函数
// 这个构造函数会创建一个testing::TestRegistrar的实例
// 叫做registrar_##func
// 然后传入的参数就是#func和func
// #func作为name传入，func作为func传入
// ##是宏字符串连接:举例如下
// void test_add() {
//     // 测试代码
// }
// test(test_add);

// 相当于
// void test_add() {
//     // 测试代码
// }
// static testing::TestRegistrar registrar_test_add("test_add", test_add);

// 可以看到test_add作为函数名字被连接到了registrar_后面
// test_add和"test_add"被作为参数传入构造器了
}