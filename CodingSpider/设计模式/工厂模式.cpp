///*
//�ڹ���ģʽ�У������ڴ�������ʱ����Կͻ��˱�¶�����߼���������ͨ��ʹ��һ����ͬ�Ľӿ���ָ���´����Ķ���
//
//
//����ģʽ��ʵ�ַ�ʽ�ɷֱ�::�򵥹���ģʽ   ��������ģʽ	���󹤳�ģʽ
//
//�򵥹���ģʽ����Ҫȥ�޸Ĺ����࣬��Υ���˿��շ���
//������ʽģʽ�ͳ��󹤳�ģʽ������Ҫ����һ����Ӧ�Ĳ�Ʒ�ľ��幤���࣬��ͻ������˴���ı�д����
//
//*/
//
//#include<iostream>
//using namespace std;
//
///*
//�򵥹���ģʽ������ͬһ�ȼ��ṹ�е������Ʒ,��չ�Բ�
//
//�򵥹���ģʽ�Ľṹ��ɣ�
//
//������(ShoesFactory)������ģʽ�ĺ����࣬�ᶨ��һ�����ڴ���ָ���ľ���ʵ������Ľӿڡ�
//�����Ʒ��(Shoes)���Ǿ����Ʒ��ļ̳еĸ����ʵ�ֵĽӿڡ�
//�����Ʒ��(NiKeShoes\AdidasShoes\LiNingShoes)���������������Ķ�����Ǵ˾����Ʒʵ����
//*/
//
//
//////�����Ʒ��
//class Shoes {
//public:
//    virtual ~Shoes() {};
//    virtual void Show() = 0;
//};
//
////�����Ʒ
//class NikiShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
//    }
//};
//
//class AdidasShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "���ǰ��ϴ�˹��Ь���ҵĹ����:Impossible is nothing" << std::endl;
//    }
//};
//
//class LiNingShoes : public Shoes {
//public:
//    void Show() {
//        std::cout << "����������Ь���ҵĹ���Everything is possible" << std::endl;
//    }
//};
//
//
//
////������
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
//��������ģʽ:����ͳһ�ȼ��ṹ�еĹ̶���Ʒ��
//
//
//��������ģʽ�Ľṹ��ɣ�
//���󹤳��೧��ShoesFactory������������ģʽ�ĺ����࣬�ṩ���������Ʒ�Ľӿڣ��ɾ��幤����ʵ�֡�
//���幤���ࣨNiKeProducer\AdidasProducer\LiNingProducer�����̳��ڳ��󹤳���ʵ�ִ�����Ӧ�����Ʒ����ķ�ʽ��
//�����Ʒ�ࣨShoes�������Ǿ����Ʒ�̳еĸ��ࣨ���ࣩ��
//�����Ʒ�ࣨNiKeShoes\AdidasShoes\LiNingShoes�������幤���������Ķ��󣬾��Ǵ��ࡣ
//
//*/
//
//// ��Ь��
//class ShoesFactory
//{
//public:
//    virtual Shoes* CreateShoes() = 0;
//    virtual ~ShoesFactory() {}
//};
//
//// �Ϳ�������/������
//class NiKeProducer : public ShoesFactory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new NiKeShoes();
//    }
//};
//
//// ���ϴ�˹������/������
//class AdidasProducer : public ShoesFactory
//{
//public:
//    Shoes* CreateShoes()
//    {
//        return new AdidasShoes();
//    }
//};
//
//// ����������/������
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
//���󹤳��ࣺ������ͬ��Ʒ���ȫ����Ʒ��
//
//
//
//
//���󹤳��೧��ShoesFactory������������ģʽ�ĺ����࣬�ṩ���������Ʒ�Ľӿڣ��ɾ��幤����ʵ�֡�
//���幤���ࣨNiKeProducer�����̳��ڳ��󹤳���ʵ�ִ�����Ӧ�����Ʒ����ķ�ʽ��
//�����Ʒ�ࣨShoes\Clothe�������Ǿ����Ʒ�̳еĸ��ࣨ���ࣩ��
//�����Ʒ�ࣨNiKeShoes\NiKeClothe�������幤���������Ķ��󣬾��Ǵ��ࡣ
//*/
//
//// ���� �·�
//class Clothe
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Clothe() {}
//};
//
//// �Ϳ��·�
//class NiKeClothe : public Clothe
//{
//public:
//    void Show()
//    {
//        std::cout << "�����Ϳ��·���ʱ���������У�" << std::endl;
//    }
//};
//
//// ���� Ь��
//class Shoes
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Shoes() {}
//};
//
//// �Ϳ�Ь��
//class NiKeShoes : public Shoes
//{
//public:
//    void Show()
//    {
//        std::cout << "�����Ϳ���Ь�������������" << std::endl;
//    }
//};
//
//// �ܳ�
//class Factory
//{
//public:
//    virtual Shoes* CreateShoes() = 0;
//    virtual Clothe* CreateClothe() = 0;
//    virtual ~Factory() {}
//};
//
//// �Ϳ�������/������
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
//ģ�幤������Թ�������ģʽ��װ��ģ�幤���࣬��ô������������Ʒʱ���ǲ���Ҫ��������Ĺ����࣬�����˴���ı�д����
//
//
//
//
//*/
//
//// ���� Ь��
//class Shoes
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Shoes() {}
//};
//
//// �Ϳ�Ь��
//class NiKeShoes : public Shoes
//{
//public:
//    void Show()
//    {
//        std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
//    }
//};
//
//// ���� �·�
//class Clothe
//{
//public:
//    virtual void Show() = 0;
//    virtual ~Clothe() {}
//};
//
//// ���¿��·�
//class UniqloClothe : public Clothe
//{
//public:
//    void Show()
//    {
//        std::cout << "�������¿��·����ҵĹ���I am Uniqlo" << std::endl;
//    }
//};
//
//
//// ����ģ�幤����
//// ģ�������AbstractProduct_t ��Ʒ������
//template <class AbstractProduct_t>
//class AbstractFactory
//{
//public:
//    virtual AbstractProduct_t* CreateProduct() = 0;
//    virtual ~AbstractFactory() {}
//};
//
//// ����ģ�幤����
//// ģ�������AbstractProduct_t ��Ʒ�����࣬ConcreteProduct_t ��Ʒ������
//template <class AbstractProduct_t, class ConcreteProduct_t>
//class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
//{
//public:
//    AbstractProduct_t* CreateProduct()
//    {
//        return new ConcreteProduct_t();
//    }
//};