#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
    static T &instance()
    {
        // 不管有多少线程在运行，Call_once()只会被调用一次
        std::call_once(onceFlag_, [&]() -> void {
            if (instance_ == nullptr) {
                instance_ = std::unique_ptr<T>(new T());
            }
        });

        return *instance_;
    }

protected:
    // Singleton() = delete; 阻止编译器合成构造函数，会导致类无法实例化
    Singleton()
    {
        ++count_;
        std::cout << "Singleton construction " << count_ << std::endl;
    }
    virtual ~Singleton()
    {
        --count_;
        std::cout << "Singleton destruction " << count_ << std::endl;
    }

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    static std::unique_ptr<T> instance_;
    static std::once_flag onceFlag_;

    // 检查单例类构造函数调用次数
    static int count_;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_(nullptr);
template <typename T>
std::once_flag Singleton<T>::onceFlag_;
template <typename T>
int Singleton<T>::count_ = 0;

/* 
#include <utils/singleton.hpp>

#include <iostream>
#include <thread>

// 使用方式1
class Test1 : public Singleton<Test1>
{
    // friend 能让 Singleton<T> 访问到 DesignPattern 的构造函数
    friend class Singleton<Test1>;

public:
    Test1()
    {
        ++count_;
        std::cout << "Test1 construction " << count_ << std::endl;
    };
    ~Test1()
    {
        --count_;
        std::cout << "Test1 destruction " << count_ << std::endl;
    };

    void print(int i) { std::cout << "print() " << i << std::endl; }

private:
    // 检查单例类构造函数调用次数
    static int count_;
};
int Test1::count_ = 0;


// 使用方式2
class Test2
{
public:
    Test2()
    {
        ++count_;
        std::cout << "Test2 construction " << count_ << std::endl;
    };
    ~Test2()
    {
        --count_;
        std::cout << "Test2 destruction " << count_ << std::endl;
    };

    void print(int i) { std::cout << "print() " << i << std::endl; }

private:
    // 检查单例类构造函数调用次数
    static int count_;
};
int Test2::count_ = 0;
#define Test2Instance Singleton<Test2>::instance()

void threadFunc()
{
    std::cout << "\n Thread-2: Calling getSingleton2Instance() 10 times: " << std::endl;
    for (int i = 0; i < 20; ++i) {
        Singleton<Test1>::instance().print(i);
    }
}

int main(int argc, char **argv)
{
    std::cout << "****** Thread-safe Singleton by using std::call_once ******" << std::endl;
    std::thread t(threadFunc);

    std::cout << "\n Thread-1: Calling getSingleton2Instance() 10 times: " << std::endl;
    for (int i = 100; i < 120; ++i) {
        Test2Instance.print(i);
    }
    t.join();

    return 0;
}
*/

#endif // __SINGLETON_H__
