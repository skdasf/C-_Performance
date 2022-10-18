

#include <iostream>
#include <map>


class Context
{
public:
  void set( const std::string& var, const bool value)
  {
    vars.insert( std::pair<std::string, bool>( var, value ) );
  }
  
  bool get( const std::string& exp )
  {
    return vars[ exp ];
  }
  // ...

private:
  std::map<std::string, bool> vars;
  // ...
};


class AbstractExpression
{
public:
  virtual ~AbstractExpression() {}
  
  virtual bool interpret( Context* const )
  {
    return false;
  }
  // ...
};


class TerminalExpression : public AbstractExpression
{
public:
  TerminalExpression( const std::string& val ) : value( val ) {}
  
  ~TerminalExpression() {}
  
  bool interpret( Context* const context )
  {
    return context->get( value );
  }
  // ...
  
private:
  std::string value;
  // ...
};


class NonterminalExpression : public AbstractExpression
{
public:
  NonterminalExpression( AbstractExpression *left, AbstractExpression *right ) : 
    lop( left ), rop( right ) {}
  
  ~NonterminalExpression()
  {
    delete lop;
    delete rop;
  }
  
  bool interpret( Context *const context )
  {
    return lop->interpret( context ) && rop->interpret( context );
  }
  // ...
  
private:
  AbstractExpression *lop;
  AbstractExpression *rop;
  // ...
};


int main()
{

  AbstractExpression *A = new TerminalExpression("A");
  AbstractExpression *B = new TerminalExpression("B");
  AbstractExpression *exp = new NonterminalExpression( A, B );
  
  Context context;
  context.set( "A", true );
  context.set( "B", false );
  
  std::cout << context.get( "A" ) << " AND " << context.get( "B" );
  std::cout << " = " << exp->interpret( &context ) << std::endl;
  
  delete exp;
  return 0;
}
