/**
 * @file objects.cpp
 * @author ben@cs.unc.edu
 * @brief Basic rules of cpp objects
 */

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the std::set library.
#include <set>
// Includes the C++ string library.
#include <string>
// Includes the std::vector library.
#include <vector>
// Includes the std::unordered map library.
#include <unordered_map>

//Generally, don't do this
//using namespace std;
//it is considered poor style, potentially annoying for reading and extending the code later


//a class!
class Base {
public:
  //ctor?
  //if omitted, a default (no args) ctor is generated that
  //default constructs base classes and then each member in order
  
  //A default copy constructor is generated that takes one argument, Base, and copies its members into this object's members
  //implicit copy ctor
  //Base(const Base& other) : name_(other.name_) {}

  void print() const {
    std::cout << "(" << name_ << ")\n";
  }

  void setName(std::string s){
    name_ = s;
  }

  std::string getName() const {
    return name_;
  }

  //dtor
  //if omitted, a default dtor destructs class members, then base class(es)

private:
  std::string name_;
};

//Derived *inherits from* Base. The public here means this inheritance is visible to all.
class Derived : public Base {

public:
    //ctor w/ initializer list (after the colon)
    //Base class default ctor is implicitly called first during initialization
    //Then init members.  Always try to match initialization order to declaration order.
    Derived(std::string name, size_t age) : age_(age){
        //do some other setup
        setName(name);
    }

    //This is not java!
    //This print decl is *hiding* Base::print.  Not great!
    void print() const {
        std::cout << "(" << getName() << ", " << age_ << ")\n";
    }


private:
    size_t age_;        

};

class Base2 {
public:

  //once we have explicit ctor, all automatic ctors vanish
  Base2(std::string s) : name_(s) {}

  //someone might override, better make it virtual so the compiler knows we don't want hiding for this name
  virtual void print() const {
    std::cout << "(" << name_ << ")\n";
  }

  void setName(std::string s){
    name_ = s;
  }

  std::string getName() const {
    return name_;
  }

  //why should this be virtual?
  virtual ~Base2() {
    std::cout << name_ << " is napping" << std::endl;
  }

private:
  std::string name_;
};

//Derived *inherits from* Base. The public here means this inheritance is visible to all.
class Derived2 : public Base2 {

public:
    //Base class default ctor no longer exists!  Better call it ourselves
    //Then init members.  Always try to match this list to actual init order (base class first!)
    Derived2(std::string name, size_t age) : Base2(name), age_(age){}

    //override here will be a compiler error unless there is a virtual print to override.  It is not necessary to make this work.
    void print() const override{
        std::cout << "{" << std::endl;
        Base2::print();
        std::cout << "(age:"  << age_ << ")\n";
        std::cout << "}" << std::endl;
    }

    ~Derived2() {
        std::cout << "Derived2 dtor" << std::endl;
    }


private:
    size_t age_;        

};


int main() {
    //variable declared, default ctor called (no args)
    Base b;
    b.setName("Ben");
    std::cout << "Base Ben:" << std::endl;
    //ptr to b
    Base * b_ptr = &b;
    //b.print()
    b_ptr->print();
    std::cout << std::endl;
    //(Ben)

    Derived d("Rafa", 1);
    std::cout << "Derived Rafa:" << std::endl;
    d.print();
    std::cout << std::endl;
    //(Rafa, 1)
    
    //upcast!
    Base b2 = d;
    std::cout << "Derived Rafa (sliced):" << std::endl;
    b2.print();
    std::cout << std::endl;
    //(Rafa)
    //Oh no!  This is not polymorphism in C++, its object slicing!
    //Compiler resolved this to Base::print
   
    //If we use a reference (or ptr) to Base,
    //the object isn't sliced, it retains info about the derived class
    Base& b3(d);
    std::cout << "Derived Rafa (hidden):" << std::endl;
    b3.print();
    std::cout << std::endl;
    //(Rafa)
    //Disaster!  This is not polymorphism in C++, because print is hidden, not overridden


    //By using vritual/override, and references/ptrs, we are telling the compiler to back off and resolve the function call at runtime
    //If you want to understand more about this process, search for "vtable"
    Derived2 d2("Rafa", 1);
    Base2& b4(d2);
    std::cout << "Derived Rafa (virtual):" << std::endl;
    b4.print();
    //note the dtor order.
    //Derived dtor, derived members, base dtor, base members
    
}
