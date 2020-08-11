///*
//在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。
//
//
//工厂模式的实现方式可分别::简单工厂模式   工厂方法模式	抽象工厂模式
//
//简单工厂模式，需要去修改工厂类，这违背了开闭法则。
//工厂方式模式和抽象工厂模式，都需要增加一个对应的产品的具体工厂类，这就会增大了代码的编写量。
//
//*/
//
//#include<iostream>
//using namespace std;
//
///*
//简单工厂模式：生产同一等级结构中的任意产品,扩展性差
//
//简单工厂模式的结构组成：
//
//工厂类(ShoesFactory)：工厂模式的核心类，会定义一个用于创建指定的具体实例对象的接口。
//抽象产品类(Shoes)：是具体产品类的继承的父类或实现的接口。
//具体产品类(NiKeShoes\AdidasShoes\LiNingShoes)：工厂类所创建的对象就是此具体产品实例。
//*/
//
//
//////抽象产品类
//class Shoes {
//public:
//    virtual ~Shoes() {};
//    virtual void Show() = 0;
//};
//
////具体产品
//class NikiShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
//    }
//};
//
//class AdidasShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "我是阿迪达斯球鞋，我的广告语:Impossible is nothing" << std::endl;
//    }
//};
//
//class LiNingShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "我是李宁球鞋，我的广告语：Everything is possible" << std::endl;
//    }
//};
//
//
//
////工厂类
//enum SHOES_TYPE
//{
//    NIKE,
//    LINING,
//    ADIDAS
//};
//
//class ShoesFactory {
//public:
//    Shoes* CreateShoes(SHOES_TYPE type)
//    {
//        switch (type)
//        {
//        case NIKE:
//            return new NikiShoes();
//            break;
//        case LINING:
//            return new LiNingShoes();
//            break;
//        case ADIDAS:
//            return new AdidasShoes();
//            break;
//        default:
//            return NULL;
//            break;
//        }
//    }
//};
//
//
//
///*
//工厂方法模式:生产统一等级结构中的固定产品。
//
//
//工厂方法模式的结构组成：
//抽象工厂类厂（ShoesFactory）：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
//具体工厂类（NiKeProducer\AdidasProducer\LiNingProducer）：继承于抽象工厂，实现创建对应具体产品对象的方式。
//抽象产品类（Shoes）：它是具体产品继承的父类（基类）。
//具体产品类（NiKeShoes\AdidasShoes\LiNingShoes）：具体工厂所创建的对象，就是此类。
//
//*/
//
//// 总鞋厂
//class ShoesFactory
//{
//public:
//    virtual Shoes* CreateShoes() = 0;
//    virtual ~ShoesFactory() {}
//};
//
//// 耐克生产者/生产链
//class NiKeProducer : public ShoesFactory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new NiKeShoes();
//    }
//};
//
//// 阿迪达斯生产者/生产链
//class AdidasProducer : public ShoesFactory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new AdidasShoes();
//    }
//};
//
//// 李宁生产者/生产链
//class LiNingProducer : public ShoesFactory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new LiNingShoes();
//    }
//};
//
//
//
//
///*
//抽象工厂类：生产不同产品族的全部产品。
//
//
//
//
//抽象工厂类厂（ShoesFactory）：工厂方法模式的核心类，提供创建具体产品的接口，由具体工厂类实现。
//具体工厂类（NiKeProducer）：继承于抽象工厂，实现创建对应具体产品对象的方式。
//抽象产品类（Shoes\Clothe）：它是具体产品继承的父类（基类）。
//具体产品类（NiKeShoes\NiKeClothe）：具体工厂所创建的对象，就是此类。
//*/
//
//// 基类 衣服
//class Clothe
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Clothe() {}
//};
//
//// 耐克衣服
//class NiKeClothe : public Clothe
//{
//public:
//    void Show()
//    {
//        std::cout << "我是耐克衣服，时尚我最在行！" << std::endl;
//    }
//};
//
//// 基类 鞋子
//class Shoes
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Shoes() {}
//};
//
//// 耐克鞋子
//class NiKeShoes : public Shoes
//{
//public:
//    void Show()
//    {
//        std::cout << "我是耐克球鞋，让你酷起来！" << std::endl;
//    }
//};
//
//// 总厂
//class Factory
//{
//public:
//    virtual Shoes* CreateShoes() = 0;
//    virtual Clothe* CreateClothe() = 0;
//    virtual ~Factory() {}
//};
//
//// 耐克生产者/生产链
//class NiKeProducer : public Factory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new NiKeShoes();
//    }
//
//    Clothe* CreateClothe()
//    {
//        return new NiKeClothe();
//    }
//};
//
//
//
//
//
//
///*
//模板工厂：针对工厂方法模式封装成模板工厂类，那么这样在新增产品时，是不需要新增具体的工厂类，减少了代码的编写量。
//
//
//
//
//*/
//
//// 基类 鞋子
//class Shoes
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Shoes() {}
//};
//
//// 耐克鞋子
//class NiKeShoes : public Shoes
//{
//public:
//    void Show()
//    {
//        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
//    }
//};
//
//// 基类 衣服
//class Clothe
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Clothe() {}
//};
//
//// 优衣库衣服
//class UniqloClothe : public Clothe
//{
//public:
//    void Show()
//    {
//        std::cout << "我是优衣库衣服，我的广告语：I am Uniqlo" << std::endl;
//    }
//};
//
//
//// 抽象模板工厂类
//// 模板参数：AbstractProduct_t 产品抽象类
//template <class AbstractProduct_t>
//class AbstractFactory
//{
//public:
//    virtual AbstractProduct_t* CreateProduct() = 0;
//    virtual ~AbstractFactory() {}
//};
//
//// 具体模板工厂类
//// 模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
//template <class AbstractProduct_t, class ConcreteProduct_t>
//class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
//{
//public:
//    AbstractProduct_t* CreateProduct()
//    {
//        return new ConcreteProduct_t();
//    }
//};