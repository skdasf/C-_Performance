
#include <iostream>


class AbstractClass
{
public:
  virtual ~AbstractClass() {}
  
  void templateMethod()
  {
    // ...
    primitiveOperation1();
    // ...
    primitiveOperation2();
    // ...
  }
  
  virtual void primitiveOperation1() = 0;
  virtual void primitiveOperation2() = 0;
  // ...
};


class ConcreteClass : public AbstractClass
{
public:
  ~ConcreteClass() {}
  
  void primitiveOperation1()
  {
    std::cout << "Primitive operation 1" << std::endl;
    // ...
  }
  
  void primitiveOperation2()
  {
    std::cout << "Primitive operation 2" << std::endl;
    // ...
  }
  // ...
};


int main()
{
  AbstractClass *tm = new ConcreteClass;
  tm->templateMethod();
  
  delete tm;
  return 0;
}
