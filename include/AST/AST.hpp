#pragma once
#include <iostream>
#include <vector>
#include <TypeChecker.hpp>

namespace YANKI
{
  enum OpType
  {
    ADD,
    SUB,
    MUL,
    DIV
  };

  enum FactorType
  {
    INT,
    FLOAT,
    STRING
  };

  class FloatFactor : public Visitable
  {
  private:
    float value;

  public:
    void accept(Visitor* v) override
    {
      v->visitFloatFactor(this);
    }

    float getValue() const
    {
      return value;
    }

    void setValue(float val)
    {
      value = val;
    }
  };

  class IntegerFactor : public Visitable
  {
  private:
    int value;

  public:
    void accept(Visitor* v) override
    {
      v->visitIntegerFactor(this);
    }

    int getValue() const
    {
      return value;
    }

    void setValue(int val)
    {
      value = val;
    }
  };

  class StringFactor : public Visitable
  {
  private:
     std::string value;

  public:
    void accept(Visitor* v) override
    {
      v->visitStringFactor(this);
    }

    const std::string& getValue() const
    {
      return value;
    }

    void setValue(const std::string& val)
    {
      value = val;
    }
  };

  class Variable : public Visitable
  {
  private:
    std::string varname;
    Visitable* factor;

  public:

    Variable(std::string name): varname(name){
  
    }

    void accept(Visitor* v) override
    {
      v->visitVariable(this);
    }

    const std::string& getVarName() const
    {
      return varname;
    }

    void setVarName(const std::string& name)
    {
      varname = name;
    }

    Visitable* getFactor() const
    {
      return factor;
    }

    void setFactor(Visitable* fac)
    {
      factor = fac;
    }
  };


  class Operation : public Visitable
  {
  private:
    OpType op;
    Visitable *factor1;
    Visitable *factor2;

  public:
    void accept(Visitor* v) override
    {
      v->visitOperation(this);
    }

    OpType getOp() const
    {
      return op;
    }

    void setOp(OpType operation)
    {
      op = operation;
    }

    Visitable* getFactor1() const
    {
      return factor1;
    }

    void setFactor1(Visitable* fac1)
    {
      factor1 = fac1;
    }

    Visitable* getFactor2() const
    {
      return factor2;
    }

    void setFactor2(Visitable* fac2)
    {
      factor2 = fac2;
    }
  };

  class Statement : public Visitable // represents an expression: an instruction terminated with ";" - END_EXPR
  {
  private:
    std::vector<Visitable*> children;

  public:
    void accept(Visitor* v) override
    {
      v->visitStatement(this);
    }

    inline const std::vector<Visitable*>& getChildren() const
    {
      return children;
    }

    void addChild(Visitable* child)
    {
      children.push_back(child);
    }
  };

  class Program : public Visitable // A list of statements
  {
  private:
    std::vector<Visitable*> children;

  public: // TODO: constructors ?? 

    void accept(Visitor* v) override
    {
      v->visitProgram(this);
    }

    inline const std::vector<Visitable*> getChildren() const
    {
      return children;
    }

    void addChild(Visitable* child)
    {
      children.push_back(child);
    }
  };

  class ASTree {
    Visitable* program;

    public:
    inline const Visitable* getProgram()const{
      return program;
    }

    void setProgram(Visitable* program){
      program = program;
    }

  };

}
