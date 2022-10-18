

#include <iostream>
#include <map>


class Flyweight
{
public:
  virtual ~Flyweight() {}
  virtual void operation() = 0;
  // ...
};


class UnsharedConcreteFlyweight : public Flyweight
{
public:
  UnsharedConcreteFlyweight( const int intrinsic_state ) :
    state( intrinsic_state ) {}
  
  ~UnsharedConcreteFlyweight() {}
  
  void operation()
  {
    std::cout << "Unshared Flyweight with state " << state << std::endl;
  }
  // ...
  
private:
  int state;
  // ...
};


class ConcreteFlyweight : public Flyweight
{
public:
  ConcreteFlyweight( const int all_state ) :
    state( all_state ) {}
  
  ~ConcreteFlyweight() {}
  
  void operation()
  {
    std::cout << "Concrete Flyweight with state " << state << std::endl;
  }
  // ...
  
private:
  int state;
  // ...
};


class FlyweightFactory
{
public:
  ~FlyweightFactory()
  {
    for ( auto it = flies.begin(); it != flies.end(); it++ )
    {
        delete it->second;
    }
    flies.clear();
  }
  
  Flyweight *getFlyweight( const int key )
  {
    if ( flies.find( key ) != flies.end() )
    {
      return flies[ key ];
    }
    Flyweight *fly = new ConcreteFlyweight( key );
    flies.insert( std::pair<int, Flyweight *>( key, fly ) );
    return fly;
  }
  // ...

private:
  std::map<int, Flyweight*> flies;
  // ...
};


int main()
{
  FlyweightFactory *factory = new FlyweightFactory;
  factory->getFlyweight(1)->operation();
  factory->getFlyweight(2)->operation();
  delete factory;
  return 0;
}
