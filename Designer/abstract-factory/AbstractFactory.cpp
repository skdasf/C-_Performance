
#include <iostream>

class ProductA
{
public:
  virtual ~ProductA() {}
  
  virtual const char* getName() = 0;
  // ...
};


class ConcreteProductAX : public ProductA
{
public:
  ~ConcreteProductAX() {}
  
  const char* getName()
  {
    return "A-X";
  }
  // ...
};

class ConcreteProductAY : public ProductA
{
public:
  ~ConcreteProductAY() {}
  
  const char* getName()
  {
    return "A-Y";
  }
  // ...
};


class ProductB
{
public:
  virtual ~ProductB() {}
  
  virtual const char* getName() = 0;
  // ...
};


class ConcreteProductBX : public ProductB
{
public:
  ~ConcreteProductBX() {}
  
  const char* getName()
  {
    return "B-X";
  }
  // ...
};

class ConcreteProductBY : public ProductB
{
public:
  ~ConcreteProductBY() {}
  
  const char* getName()
  {
    return "B-Y";
  }
  // ...
};

/*
 * Abstract Factory
 * provides an abstract interface for creating a family of products
 */
class AbstractFactory
{
public:
  virtual ~AbstractFactory() {}
  
  virtual ProductA *createProductA() = 0;
  virtual ProductB *createProductB() = 0;
};

/*
 * Concrete Factory X and Y
 * each concrete factory create a family of products and client uses
 * one of these factories so it never has to instantiate a product object
 */
class ConcreteFactoryX : public AbstractFactory
{
public:
  ~ConcreteFactoryX() {}
  
  ProductA *createProductA()
  {
    return new ConcreteProductAX();
  }
  ProductB *createProductB()
  {
    return new ConcreteProductBX();
  }
  // ...
};

class ConcreteFactoryY : public AbstractFactory
{
public:
  ~ConcreteFactoryY() {}

  ProductA *createProductA()
  {
    return new ConcreteProductAY();
  }
  ProductB *createProductB()
  {
    return new ConcreteProductBY();
  }
  // ...
};


int main()
{
  ConcreteFactoryX *factoryX = new ConcreteFactoryX();
  ConcreteFactoryY *factoryY = new ConcreteFactoryY();

  ProductA *p1 = factoryX->createProductA();
  std::cout << "Product: " << p1->getName() << std::endl;
  
  ProductA *p2 = factoryY->createProductA();
  std::cout << "Product: " << p2->getName() << std::endl;
  
  delete p1;
  delete p2;
  
  delete factoryX;
  delete factoryY;
  
  return 0;
}
