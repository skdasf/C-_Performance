

#include <iostream>


class State
{
public:
  virtual ~State() { /* ... */ }
  virtual void handle() = 0;
  // ...
};


class ConcreteStateA : public State
{
public:
  ~ConcreteStateA() { /* ... */ }
  
  void handle()
  {
    std::cout << "State A handled." << std::endl;
  }

};

class ConcreteStateB : public State
{
public:
  ~ConcreteStateB() { /* ... */ }
  
  void handle()
  {
    std::cout << "State B handled." << std::endl;
  }
  // ...
};


class Context
{
public:
  Context() : state() { /* ... */ }
  
  ~Context()
  {
    delete state;
  }
  
  void setState( State* const s )
  {
    if ( state )
    {
      delete state;
    }
    state = s;
  }
  
  void request()
  {
    state->handle();
  }
  // ...

private:
  State *state;
  // ...
};


int main()
{
  Context *context = new Context();
  
  context->setState( new ConcreteStateA() );
  context->request();
  
  context->setState( new ConcreteStateB() );
  context->request();
  
  delete context;
  return 0;
}
