///*
//���壺����ϵͳ�����������֤һ����ֻ�ܲ���һ��ʵ����ȷ�������Ψһ��
//
//���ࣺ����ʽ������ʽ
//
//�ص㣺
//	���캯������������Ϊprivate���ͣ���ֹ�ⲿ���������
//	���쿽���͸�ֵ���캯��Ϊprivate���ͣ�Ŀ���ǽ�ֹ�ⲿ�����͸�ֵ��ȷ��ʵ����Ψһ��
//	�����и���ȡʵ���ľ�̬����������ȫ�ַ���
//
//
//����ʽ����ʱ�任�ռ䣬��Ӧ�ڷ�������Сʱ���Ƽ�ʹ���ڲ���̬������������������������
//����ʽ���Կռ任ʱ�䣬��Ӧ�ڷ������ϴ�ʱ�������̱߳Ƚ϶�ĵ����
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
//	//�������캯������ֵ��������Ϊ˽�к���
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
////��ʼ����̬��Ա����
//Singleton* Singleton::instance = NULL;
//mutex Singleton::m_Mutex;
//
//Singleton* Singleton::getInstance() {
//	//  ����ʹ�������� if�ж����ļ�����Ϊ˫�������ô��ǣ�ֻ���ж�ָ��Ϊ�յ�ʱ��ż�����
//	//  ����ÿ�ε��� GetInstance�ķ��������������Ŀ����Ͼ������е��ġ�
//	if (instance == NULL) {
//		std::unique_lock<std::mutex>	lock(m_Mutex);
//		if (instance == NULL)
//			instance = new (std::nothrow)	Singleton;
//	}
//	return instance;
//}
//
//Singleton::Singleton() {
//	std::cout << "���캯��" << std::endl;
//}
//
//Singleton::~Singleton() {
//	std::cout << "��������" << std::endl;
//	std::unique_lock<std::mutex>	lock(m_Mutex);
//	if (instance) {
//		delete instance;
//		instance == NULL;
//	}
//}
//
//
////////////////////////////////////////////////////////////////////////////////////
////�ڲ���̬����������������C++11�̰߳�ȫ��
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
//	// �ֲ���̬���Եķ�ʽʵ�ֵ�ʵ��
//	static Singleton1 single;
//	return &single;
//}
//
//Singleton1::Singleton1() {
//	std::cout << "���캯��1" << std::endl;
//}
//
//Singleton1::~Singleton1() {
//	std::cout << "��������1" << std::endl;
//}
//
//
//
///////////////////////////////////////////////////////////////////
////����ʽ�����̰߳�ȫ
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
//	// Ψһ��ʵ������ָ��
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
//	std::cout << "���캯��2" << std::endl;
//}
//
//Singleton2::~Singleton2() {
//	std::cout << "��������2" << std::endl;
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
//	//��������߳�
//	thread T[30];
//	for (int i = 0; i < 30; i++)
//	{
//		T[i] = thread(func);
//	}
//
//	//���ö���߳�
//	for (int i = 0; i < 30; i++)
//	{
//		T[i].join();
//	}
//
//	system("pause");
//	return 0;
//}
