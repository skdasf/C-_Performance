

#include <iostream>
#include <vector>


class Memento
{
private:

  friend class Originator;
  
  Memento( const int s ) : state( s ) {}
  
  void setState( const int s )
  {
    state = s;
  }
  
  int getState()
  {
    return state;
  }
  // ...

private:
  int state;
  // ...
};


class Originator
{
public:

  void setState( const int s )
  {
    std::cout << "Set state to " << s << "." << std::endl;
    state = s;
  }
  
  // implemented only for printing purpose
  int getState()
  {
    return state;
  }
  
  void setMemento( Memento* const m )
  {
    state = m->getState();
  }
  
  Memento *createMemento()
  {
    return new Memento( state );
  }

private:
  int state;
  // ...
};


class CareTaker
{
public:
  CareTaker( Originator* const o ) : originator( o ) {}
  
  ~CareTaker()
  {
    for ( unsigned int i = 0; i < history.size(); i++ )
    {
      delete history.at( i );
    }
    history.clear();
  }
  
  void save()
  {
    std::cout << "Save state." << std::endl;
    history.push_back( originator->createMemento() );
  }
  
  void undo()
  {
    if ( history.empty() )
    {
      std::cout << "Unable to undo state." << std::endl;
      return;
    }
    
    Memento *m = history.back();
    originator->setMemento( m );
    std::cout << "Undo state." << std::endl;
    
    history.pop_back();
    delete m;
  }
  // ...

private:
  Originator *originator;
  std::vector<Memento*> history;
  // ...
};


int main()
{
  Originator *originator = new Originator();
  CareTaker *caretaker = new CareTaker( originator );
  
  originator->setState( 1 );
  caretaker->save();
  
  originator->setState( 2 );
  caretaker->save();
  
  originator->setState( 3 );
  caretaker->undo();
  
  std::cout << "Actual state is " << originator->getState() << "." << std::endl;
  
  delete originator;
  delete caretaker;
  
  return 0;
}
