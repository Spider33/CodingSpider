///*
//定义：整个系统生命周期里，保证一个类只能产生一个实例，确保该类的唯一性
//
//分类：懒汉式、饿汉式
//
//特点：
//	构造函数和析构函数为private类型，禁止外部构造和析构
//	构造拷贝和赋值构造函数为private类型，目的是禁止外部拷贝和赋值，确保实例的唯一性
//	类里有个获取实例的静态函数，可以全局访问
//
//
//懒汉式是以时间换空间，适应于访问量较小时；推荐使用内部静态变量的懒汉单例，代码量少
//饿汉式是以空间换时间，适应于访问量较大时，或者线程比较多的的情况
//*/
//
//
//#include<iostream>
//#include<mutex>
//#include<thread>
//using namespace std;
//
//class Singleton {
//private:
//	Singleton();
//	~Singleton();
//
//	//拷贝构造函数、赋值函数构造为私有函数
//	Singleton(const Singleton& single);
//	const Singleton& operator = (const Singleton& single);
//
//private:
//	static Singleton* instance;
//	static std::mutex m_Mutex;
//
//public:
//	static Singleton* getInstance();
//
//
//};
//
////初始化静态成员变量
//Singleton* Singleton::instance = NULL;
//mutex Singleton::m_Mutex;
//
//Singleton* Singleton::getInstance() {
//	//  这里使用了两个 if判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
//	//  避免每次调用 GetInstance的方法都加锁，锁的开销毕竟还是有点大的。
//	if (instance == NULL) {
//		std::unique_lock<std::mutex>	lock(m_Mutex);
//		if (instance == NULL)
//			instance = new (std::nothrow)	Singleton;
//	}
//	return instance;
//}
//
//Singleton::Singleton() {
//	std::cout << "构造函数" << std::endl;
//}
//
//Singleton::~Singleton() {
//	std::cout << "析构函数" << std::endl;
//	std::unique_lock<std::mutex>	lock(m_Mutex);
//	if (instance) {
//		delete instance;
//		instance == NULL;
//	}
//}
//
//
////////////////////////////////////////////////////////////////////////////////////
////内部静态变量的懒汉单例（C++11线程安全）
////////////////////////////////////////////////////////////////////////////////////
//
//class Singleton1 {
//public:
//	static Singleton1* getInstance();
//
//private:
//	Singleton1();
//	~Singleton1();
//
//	Singleton1(const Singleton1& single);
//	const Singleton1& operator=(const Singleton1& single);
//};
//
//Singleton1* Singleton1::getInstance() {
//	// 局部静态特性的方式实现单实例
//	static Singleton1 single;
//	return &single;
//}
//
//Singleton1::Singleton1() {
//	std::cout << "构造函数1" << std::endl;
//}
//
//Singleton1::~Singleton1() {
//	std::cout << "析构函数1" << std::endl;
//}
//
//
//
///////////////////////////////////////////////////////////////////
////饿汉式——线程安全
///////////////////////////////////////////////////////////////////
//
//class Singleton2 {
//public:
//	static Singleton2* getInstance();
//
//private:
//	Singleton2();
//	~Singleton2();
//
//	Singleton2(const Singleton2& single);
//	const Singleton2& operator=(const Singleton2& single);
//	// 唯一单实例对象指针
//	static Singleton2* instance;
//};
//
//Singleton2* Singleton2::instance = new 	Singleton2();
//
//Singleton2* Singleton2::getInstance() {
//	
//	return instance;
//}
//
//Singleton2::Singleton2() {
//	std::cout << "构造函数2" << std::endl;
//}
//
//Singleton2::~Singleton2() {
//	std::cout << "析构函数2" << std::endl;
//	if (instance)
//	{
//		delete instance;
//		instance = NULL;
//	}
//}
//
//void func()
//{
//	Singleton* s = Singleton::getInstance();
//	Singleton1* s1 = Singleton1::getInstance();
//	Singleton2* s2 = Singleton2::getInstance();
//}
//
//int main() {
//	//声明多个线程
//	thread T[30];
//	for (int i = 0; i < 30; i++)
//	{
//		T[i] = thread(func);
//	}
//
//	//调用多个线程
//	for (int i = 0; i < 30; i++)
//	{
//		T[i].join();
//	}
//
//	system("pause");
//	return 0;
//}
