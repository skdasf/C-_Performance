#include "Concreate.hpp"

int ConcreteObserver::getState() {
    return observer_state;
}

void ConcreteObserver::update(Subject* subject) {
    observer_state = subject->getState();
    std::cout << "Observer state updated." << std::endl;
}

int ConcreteSubject::getState() {
    return subject_state;
}

void ConcreteSubject::setState(const int s) {
    subject_state = s;
}
