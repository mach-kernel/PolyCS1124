/*

 Review for CS1124 Exam 2 : Basic Class Inheritance
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu 
 
*/

#include <iostream>

using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person (const string& nm, const int& ag) : name(nm), age(ag) {}
    void display() { cout << "Name: " << name << " Age: " << age << endl; }
    /*
    string getName() { return name; }
    int getAge() { return age; }
    */
};

class Worker : public Person
{
private:
    string title;
    int salary;
public:
    /* 
     Constructors:
     You can NOT initialize fields which your class does not own.
     Attempting to do : name(nm), age(ag) will cause an ERROR!
     */
    
    Worker(const string& nm, const int& ag, const string& tt, const int& sr) :
    Person (nm, ag), title(tt), salary(sr) {}
    
    /* Attempt 1:
    void display()
    { cout << "Name: " << name << " Age: " << age << " Title: " << title << " Salary " << endl; }
    */
    
    /* Attempt 2:
    
    void display()
    {
        cout << "Name: " << getName() << " Age: " << getAge() << " Title: " << title << " Salary: " << salary << endl;
    }
     
    */
    
};

int main(int argc, const char * argv[])
{
    Person D("David", 18);
    Worker J("John", 19, "Construction", 45000);
    
    /* Assignment: what we can't do
     
    D = J; / Compiler cast error, you can NOT assign a base class
             to a derived class? Why? The fields do not match up (obvious)
             and your base class does not 'care' what is derived 
             from it /
    */
    
    // J = D; This works, but I have not overloaded operator=()
    
    // Pointers, you can:
    
    Person* ptrp = &D;
    Worker* ptrw = &J; // These two should be fairly obvious as they are of the same type
    
    // This works because Worker J is inherited by class Person; workers are people, right?
    Person* ptrp2 = &J;
    
    /* Pointers, you can NOT:
     
    Worker* ptrw2 = &D; / Fails because D is *just* a person, NOT a worker.
                          Not all people work (re: Congress) /
    */
    
    // Let's see what's going on with display!
    D.display();
    J.display();
    
    /*
     D.display() behaves as expected, but why isn't J.display() showing us 
     John's title and salary? What gives?
     
     Yes - we didn't write a display function for Worker yet. Go uncomment "Attempt 1".
     What's wrong? "David, you're no good at programming, it doesn't compile!"
     
     You're right, it doesn't? Why? If your IDE/compiler error log doesn't tell you
     or you can't figure it out: name and age are PRIVATE members of Person.
     ----------------------------------------------------------------------------------
     "But display worked on J! Stop lying!"
     
     Answer: Yes it did, all public members/functions are inhertied other than:
     operator=() (I'll talk about this in the next example)
     Constructor/Destructor ("Make your own bed, clean your own room")
     friend (keyword) functions
     
     "How do we fix it?"
     
     Answer: Remember how all public members/functions are inherited (or rather, almost all)?
     If we make getters/setters in the base class, they will trickle down to our derived class!

     Comment out "Attempt 1" again, and uncomment "Attempt 2"
     
     */
}

