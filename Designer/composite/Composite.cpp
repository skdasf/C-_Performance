

#include <iostream>
#include <vector>


class Component
{
public:
  virtual ~Component() {}
  
  virtual Component *getChild( int )
  {
    return 0;
  }
  
  virtual void add( Component * ) { /* ... */ }
  virtual void remove( int ) { /* ... */ }
  
  virtual void operation() = 0;
};

class Composite : public Component
{
public:
  ~Composite()
  {
    for ( unsigned int i = 0; i < children.size(); i++ )
    {
      delete children[ i ];
    }
  }
  
  Component *getChild( const unsigned int index )
  {
    return children[ index ];
  }
  
  void add( Component *component )
  {
    children.push_back( component );
  }
  
  void remove( const unsigned int index )
  {
    Component *child = children[ index ];
    children.erase( children.begin() + index );
    delete child;
  }
  
  void operation()
  {
    for ( unsigned int i = 0; i < children.size(); i++ )
    {
      children[ i ]->operation();
    }
  }
  
private:
  std::vector<Component*> children;
};


class Leaf : public Component
{
public:
  Leaf( const int i ) : id( i ) {}
  
  ~Leaf() {}
  
  void operation()
  {
    std::cout << "Leaf "<< id <<" operation" << std::endl;
  }

private:
  int id;
};


int main()
{
  Composite composite;
  
  for ( unsigned int i = 0; i < 5; i++ )
  {
    composite.add( new Leaf( i ) );
  }
  
  composite.remove( 0 );
  composite.operation();
  
  return 0;
}
