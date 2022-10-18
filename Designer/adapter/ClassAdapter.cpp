

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
  ~Adaptee() {}
  
  void specificRequest()
  {
    std::cout << "specific request" << std::endl;
  }
  // ...

class Adapter : public Target, private Adaptee
{
public:
  virtual void request()
  {
    specificRequest();
  }
  // ...
};


int main()
{
  Target *t = new Adapter();
  t->request();
  delete t;
  
  return 0;
}
