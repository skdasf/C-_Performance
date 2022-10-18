

#include <iostream>


class Singleton
{
public:

  Singleton( Singleton const& ) = delete;
  Singleton& operator=( Singleton const& ) = delete;

  static Singleton* get()
  {
    if ( !instance )
    {
      instance = new Singleton();
    }    
    return instance;
  }
  
  static void restart()
  {
    if ( instance )
    {
      delete instance;
    }
  }
  
  void tell()
  {
    std::cout << "This is Singleton." << std::endl;
    // ...
  }
  // ...

private:
  Singleton() {}
  static Singleton *instance;
  // ...
};

Singleton* Singleton::instance = nullptr;


int main()
{
  Singleton::get()->tell();
  Singleton::restart();
  
  return 0;
}
