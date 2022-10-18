#include "Concreate.hpp"
// һ�Զ�Ĺ۲���ģʽ��  �㲥
//Subject��Ŀ�֪꣬�����Ĺ۲��ߣ��ṩע���ɾ���۲��߶���Ľӿ�

//Observer���۲��ߣ�Ϊ��Щ��Ŀ�귢���ı�ʱ����֪ͨ�Ķ�����һ�����½ӿ�

//ConcreteSubject������Ŀ�꣬�洢����״̬��״̬�ı�ʱ��������۲��߷���֪ͨ

//ConcreteObserver������۲��ߣ�ά��һ��ָ��ConcreteSubject��������ã��洢�й�״̬��ʵ�ָ��½ӿ�update��ʹ����״̬��Subject��״̬����һ��
int main()  {

    ConcreteObserver observer1(1); // Observer :�������� �� GetState������Observeʵ��ʹ�á� unpdate����Subject�е�Observes�ṩunpdate������
    ConcreteObserver observer2(2); // ״̬���ı�ʱ����Ҫ��֪ͨ�Ľӿڡ�

    std::cout << "Observer 1 state: " << observer1.getState() << std::endl;
    std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

    Subject* subject = new ConcreteSubject(); // attach  ����Observeʵ�����
    subject->attach(&observer1); // ע��۲���
    subject->attach(&observer2);

    subject->setState(10); // suject ��������״̬�� --- ��һ��״̬���ı�ʱ��֪ͨ����Observe
    subject->notify();//  ����Observer�е�update�������� ���е�״̬��

    std::cout << "Observer 1 state: " << observer1.getState() << std::endl;  // ״̬������
    std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

    delete subject;
    return 0;
}
