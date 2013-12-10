/*
 
 Review for CS1124 Exam 2 : Class Initialization
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu (ladies, feel free to send code)
 
 Updated 12/10/12!
 
 */


#include <iostream>

using namespace std;

class Base
{
public:
    Base() { cout << "Base" << endl; }
    ~Base() { cout << "BYE BASE" << endl; }
};

class Cupcake
{
public:
    Cupcake() { cout << "Cupcake" << endl; }
    ~Cupcake() { cout << "BYE CUPCAKE" << endl; }
};

class Derived : public Base
{
private:
    Cupcake cupcake;
public:
    Derived() { cout << "Derived" << endl; }
    ~Derived() { cout << "BYE DERIVED" << endl; }
};

int main()
{
    // What do you think is going to happen? Run the program, and look!
    Derived der;
    
    /* Assume we're creating an instance of Foo, this is what happens:
     
     class Boo // 2
     {
     public:
     Boo() {}
     };
     
     class Foo : public Boo (Compiler starts here, oh look, we're extending from Boo, let's make boo!) // 1
     {
     private:
     int something;
     Bar bar; (It looks like we have another object, let's make bar!) // 3
     public:
     Foo () {} (Finally, let's make Foo itself) // 4
     };
     
     The sequence for construction is as follows:
     1. If there is an inherited class, construct it as per this sequence.
     2. Construct private members of class.
     3. Construct the class itself. 
     
     The sequence for destruction is as follows:
     1. Call own destructor.
     2. Call private members' destructors. 
     3. If there is an inherited class, call its destructor as well.
     
     
     My professor does not like listing private: members first because of some odd reason, but,
     if you use my notation it is easy to understand the above. You just follow the class intialization
     "all the way down". Start on the first line of the class, move down to the private, then finally
     the constructor in public. It's a lot more 'logical'.
     
     */
    
}
