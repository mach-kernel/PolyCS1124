/*
 
 Review for CS1124 Exam 2 : Advanced Class Inheritance and Basic Polymorphism
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu (ladies, feel free to send code)
 
 */

#include <iostream>
#include <vector>

using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person (const string& nm, const int& ag) : name(nm), age(ag) {}
    
    void display() { cout << "Name: " << name << " Age: " << age << endl; }
    string getName() { return name; }
    int getAge() { return age; }
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
    
    void display()
    {
        cout << "Name: " << getName() << " Age: " << getAge() << " Title: " << title << " Salary: " << salary << endl;
    }
    string getTitle() { return title; }
    int getSalary() { return salary; }
};

int main(int argc, const char * argv[])
{
    Person D("David", 18);
    Worker J("John", 19, "Construction", 45000);
    
    Person* ptrp = &D;
    Worker* ptrw = &J;  // These two should be fairly obvious as they are of the same type
    
    Person* ptrp2 = &J; // This works because Worker J is inherited by class Person; workers are people, right?
    
    /* Pointers, you can NOT:
     
     Worker* ptrw2 = &D; / Fails because D is *just* a person, NOT a worker.
     Not all people work (re: Congress) /
     */
    
    // OK, so now display works as we wanted it to! :)
    D.display();
    J.display();
    
    // And it works as expected with our pointers too! Yay!
    ptrp->display();
    ptrw->display();
    
    // Wait a minute...why am I not getting all of J's info again?!
    ptrp2->display();
    
    // Because prettier output!
    cout << endl << endl;
    
    /*
     J is a worker, you are right! ptrp2, however, is a pointer to Person.
     The compiler understands that J is a derived Person, but sees that
     the type referenced by pointer is directly Person, so it calls the
     "Person" display method.
     
     Let's bend a spoon with our minds:
     */
    
    // Behaves as expected, right?
    cout << "Name: " << ptrw->getName();
    cout << ", title " << ptrw->getTitle() << endl;
    
    cout << "Name: " << ptrp2->getName();
    /* This does not compile: cout << ", title " << ptrp2->getTitle();
     
     clang (my compiler) says that there is no getTitle() in Person. clang is right!
     */
    
    cout << endl << endl;
    
    // People and Workers all pay taxes: let's make a database. Pointers are much smaller than storing entire objects! :)
    vector<Person*> IRS;
    
    IRS.push_back(ptrp); // David
    IRS.push_back(ptrw); // John
    
    // Take a deep breath, it's audit season: the IRS wants to display everyone's info, and if they work, their salary/title!
    
    for (size_t i = 0; i < IRS.size(); i++)
        IRS[i]->display();
    
    /* ...John's a worker, is he evading taxes again? WHERE. IS. HIS. SALARY. AND. TITLE?!
     
     We're running into the same problem we ran into before. Since the IRS tracks all people,
     and not all people work - it would be silly to make an array for an occupation (or lack thereof).
     
     Whilst David is just a Person, John is a Working (Worker) : Person, and his enhanced display() function
     is NOT a member of the Person class. The compiler is doing what it did before.
     
     --------------------------------------------------------------------------------------------------------
     
     "How do we fix it?"
     This is actually a pretty easy fix. Go prepend the keyword "virtual" to the function prototype of display() in Person. (protip: put it before void)
     Re-run the example. It works now. :)
     
     "What does this do?"
     OK: Virtual functions in C++ are functions which may be overriden in derived classes by specifying another function with the same signature.
     You must have the same function name with the same return type and the same arguments (quantity and type, I'm unsure about variable naming convention
     but I'd be consistent if I were you).
     
     This works in our example because we already have a display() function defined in Worker that suits the aforementioned criterion.
     
     "But it's not virtual in Worker"
     It is, virtuality is inherent from base classes. You can write virtual before the function in the derived classes if you wish (I usually do this to remind
     myself of what I'm doing), but it's not necessary.
     
     */
}

