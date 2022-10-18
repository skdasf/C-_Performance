#pragma once
#include "Observe_Subject.hpp"

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const int state) :
        observer_state(state) {
    }

    ~ConcreteObserver() {}

    int getState(); 

    void update(Subject* subject); // 注册的对象，通过这个参数，达到广播的效果。
    // ...

private:
    int observer_state;
    // ...
};

class ConcreteSubject : public Subject {
public:
    ~ConcreteSubject() {}

    int getState(); 

    void setState(const int s); 

private:
    int subject_state;
    // ...
};