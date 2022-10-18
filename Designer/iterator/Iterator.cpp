

#include <iostream>
#include <stdexcept>
#include <vector>

class Iterator;
class ConcreteAggregate;


class Aggregate
{
public:
  virtual ~Aggregate() {}
  
  virtual Iterator *createIterator() = 0;
  // ...
};


class ConcreteAggregate : public Aggregate
{
public:
  ConcreteAggregate( const unsigned int size )
  {
    list = new int[size]();
    count = size;
  }
  
  ~ConcreteAggregate()
  {
    delete[] list;
  }
  
  Iterator *createIterator();
  
  unsigned int size() const
  {
    return count;
  }
  
  int at( unsigned int index )
  {
    return list[ index ];
  }
  // ...

private:
  int *list;
  unsigned int count;
  // ...
};

class Iterator
{
public:
  virtual ~Iterator() { /* ... */ }
  
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual int currentItem() const = 0;
  // ...
};


class ConcreteIterator : public Iterator
{
public:
  ConcreteIterator( ConcreteAggregate *l ) :
    list( l ), index( 0 ) {}
  
  ~ConcreteIterator() {}
  
  void first()
  {
    index = 0;
  }
  
  void next()
  {
    index++;
  }
  
  bool isDone() const
  {
    return ( index >= list->size() );
  }
  
  int currentItem() const
  {
    if ( isDone() )
    {
      return -1;
    }
    return list->at(index);
  }
  // ...

private:
  ConcreteAggregate *list;
  unsigned int index;
  // ...
};

Iterator *ConcreteAggregate::createIterator()
{
  return new ConcreteIterator( this );
}


int main()
{
  unsigned int size = 5;
  ConcreteAggregate list = ConcreteAggregate( size );
  
  Iterator *it = list.createIterator();
  for ( ; !it->isDone(); it->next())
  {
    std::cout << "Item value: " << it->currentItem() << std::endl;
  }
  
  delete it;
  return 0;
}