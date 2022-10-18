#include "Concreate.hpp"
// 一对多的观察者模式。  广播
//Subject：目标，知道它的观察者，提供注册和删除观察者对象的接口

//Observer：观察者，为那些在目标发生改变时需获得通知的对象定义一个更新接口

//ConcreteSubject：具体目标，存储对象状态，状态改变时，向各个观察者发出通知

//ConcreteObserver：具体观察者，维护一个指向ConcreteSubject对象的引用，存储有关状态，实现更新接口update，使自身状态与Subject的状态保持一致
int main()  {

    ConcreteObserver observer1(1); // Observer :两个方法 ： GetState方法，Observe实体使用。 unpdate。给Subject中的Observes提供unpdate方法。
    ConcreteObserver observer2(2); // 状态量改变时，需要被通知的接口。

    std::cout << "Observer 1 state: " << observer1.getState() << std::endl;
    std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

    Subject* subject = new ConcreteSubject(); // attach  增加Observe实体对象。
    subject->attach(&observer1); // 注册观察者
    subject->attach(&observer2);

    subject->setState(10); // suject 对象设置状态量 --- 当一个状态量改变时，通知所有Observe
    subject->notify();//  利用Observer中的update方法更新 其中的状态量

    std::cout << "Observer 1 state: " << observer1.getState() << std::endl;  // 状态更新了
    std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

    delete subject;
    return 0;
}
