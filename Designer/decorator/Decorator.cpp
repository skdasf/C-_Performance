

#include <iostream>


class Component
{
public:
  virtual ~Component() {}
  
  virtual void operation() = 0;
  // ...
};


class ConcreteComponent : public Component
{
public:
  ~ConcreteComponent() {}
  
  void operation()
  {
    std::cout << "Concrete Component operation" << std::endl;
  }
  // ...
};


class Decorator : public Component
{
public:
  ~Decorator() {}
  
  Decorator( Component *c ) : component( c ) {}
  
  virtual void operation()
  {
    component->operation();
  }
  // ...

private:
  Component *component;
};

/*
 * Concrete Decorators
 * add responsibilities to the component (can extend the state
 * of the component)
 */
class ConcreteDecoratorA : public Decorator
{
public:
  ConcreteDecoratorA( Component *c ) : Decorator( c ) {}
  
  void operation()
  {
    Decorator::operation();
    std::cout << "Decorator A" << std::endl;
  }
  // ...
};

class ConcreteDecoratorB : public Decorator
{
public:
  ConcreteDecoratorB( Component *c ) : Decorator( c ) {}
  
  void operation()
  {
    Decorator::operation();
    std::cout << "Decorator B" << std::endl;
  }
  // ...
};


int main()
{
  ConcreteComponent  *cc = new ConcreteComponent();
  ConcreteDecoratorB *db = new ConcreteDecoratorB( cc );
  ConcreteDecoratorA *da = new ConcreteDecoratorA( db );
  
  Component *component = da;
  component->operation();
  
  delete da;
  delete db;
  delete cc;
  
  return 0;
}
