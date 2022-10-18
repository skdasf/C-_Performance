

#include <iostream>
#include <string>


class Product
{
public:
  virtual ~Product() {}
  
  virtual std::string getName() = 0;
  // ...
};


class ConcreteProductA : public Product
{
public:
  ~ConcreteProductA() {}
  
  std::string getName()
  {
    return "type A";
  }
  // ...
};


class ConcreteProductB : public Product
{
public:
  ~ConcreteProductB() {}
  
  std::string getName()
  {
    return "type B";
  }
  // ...
};


class Creator
{
public:
  virtual ~Creator() {}
  
  virtual Product* createProductA() = 0;
  virtual Product* createProductB() = 0;
  
  virtual void removeProduct( Product *product ) = 0;
  
  // ...
};


class ConcreteCreator : public Creator
{
public:
  ~ConcreteCreator() {}
  
  Product* createProductA()
  {
    return new ConcreteProductA();
  }
  
  Product* createProductB()
  {
    return new ConcreteProductB();
  }
  
  void removeProduct( Product *product )
  {
    delete product;
  }
  // ...
};


int main()
{
  Creator *creator = new ConcreteCreator();
  
  Product *p1 = creator->createProductA();
  std::cout << "Product: " << p1->getName() << std::endl;
  creator->removeProduct( p1 );
  
  Product *p2 = creator->createProductB();
  std::cout << "Product: " << p2->getName() << std::endl;
  creator->removeProduct( p2 );
  
  delete creator;
  return 0;
}
