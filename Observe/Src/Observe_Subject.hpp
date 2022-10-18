#pragma once
#include <iostream>
#include <vector>

class Subject;

/*
 * Observer
 * defines an updating interface for objects that should be notified
 * of changes in a subject
 */
class Observer {
public:
    virtual ~Observer() {}

    virtual int getState() = 0;
    virtual void update(Subject* subject) = 0;
    // ...
};



class Subject {
public:
    virtual ~Subject() {}

    void attach(Observer* observer);
    void detach(const int index);

    void notify();
    virtual int getState() = 0;
    virtual void setState(const int s) = 0;
    // ...

private:
    std::vector<Observer*> observers;
    // ...
};