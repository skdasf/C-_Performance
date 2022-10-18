

#include <iostream>

class Target
{
public:
  virtual ~Target() {}
  
  virtual void request() = 0;
  // ...
};


class Adaptee
{
public:
  void specificRequest()
  {
    std::cout << "specific request" << std::endl;
  }
  // ...
};


class Adapter : public Target
{
public:
  Adapter() : adaptee() {}
  
  ~Adapter()
  {
    delete adaptee;
  }
  
  void request()
  {
    adaptee->specificRequest();
  // ...
  }
  // ...

private:
  Adaptee *adaptee;
  // ...
};


int main()
{
  Target *t = new Adapter();
  t->request();
  delete t;
  
  return 0;
}
