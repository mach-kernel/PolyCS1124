/*
 
 Review for CS1124 Exam 2 : Operator Overloading (Easy)
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu (ladies, feel free to send code)
 
 */

#include <iostream>
#include <vector>

using namespace std;

class Cat
{
private:
    string name;
    int age;
    int lives;
public:
    Cat(const string& nm, const int& ag) : name(nm), age(ag), lives(9) {} // All cats have 9 lives, obviously.
    
    /* Copy constructor (part of the 'big three')
     
     Takes another object of cat and uses its values to instantiate another Cat.
     
     */
    
    Cat(const Cat& passed)
    {
        name = passed.name;
        age = passed.age;
        lives = passed.lives;
    }
    
    string getName() { return name; }
    
    void display(ostream& lhs) // Why don't you just use cout?!
    {
        lhs << "-----Cat information-----" << endl
        << "Name: " << name << endl << "Age: " << age
        << endl << "Lives: " << lives << endl <<
        "-------------------------" << endl << endl;
    }
    
    /* Assignment operator overload (ALWAYS A MEMBER FUNCTION)
     
     Assume we have two cats, Fritz and Steve:
     Fritz = Steve;
     
     It is called upon by Fritz with Steve as an argument, but because Fritz is of the same class as Steve (Cat),
     Fritz has access to Steve's data. Fritz copies over all of Steve's fields and returns a dereferenced
     version of himself by reference.
     
     */
    
    Cat& operator=(const Cat& rhs)
    {
        name = rhs.name;
        age = rhs.age;
        lives = rhs.lives;
        return *this; // this is a pointer, you are returning a dereferenced version of this instance.
    }
    
    /* Increment/Decrement Overload (as members - my personal preference)
     
     Prefix (Return type of Cat&, no arguments):
     
     What it does:
     1. Increment lives.
     2. Return derefrenced REFERENCE of itself.
     ----------------------------------------------------
     Postfix (Return type of cat, argument of dummy int):
     
     What it does:
     1. Make a copy of the current object with the same parameters (copy constructor is useful here);
     2. Increments the current instance.
     3. Returns a NON-INCREMENTED COPY of itself.
     
     */
    
    Cat& operator++()
    {
        ++lives;
        return *this;
    }
    
    Cat& operator--()
    {
        --lives;
        return *this;
    }
    
    Cat operator++(int)
    {
        Cat temp = Cat(*this);
        ++(*this);
        return temp;
    }
    
    Cat operator--(int)
    {
        Cat temp = Cat(*this);
        --*(this);
        return temp;
    }
};

class Kennel
{
private:
    string name;
    vector<Cat*> cats;
public:
    Kennel (const string& nm) : name(nm), cats(0, nullptr) {} // New Kennels don't have any cats unless we add them.
    
    void give(Cat* cat){ cats.push_back(cat); }
    
    void display(ostream& lhs)
    {
        lhs << "Kennel contents:" << endl << endl;
        for (size_t i=0; i < cats.size(); ++i)
            cats[i]->display(lhs);
        lhs << "End of kennel contents." << endl;
    }
    
    Cat* adopt(const string& name)
    {
        Cat* temp = nullptr;
        for (size_t i=0; i < cats.size(); ++i)
        {
            if (name == cats[i]->getName())
            {
                temp = cats[i];
                cats.erase(cats.begin() + i);
            }
        }
        if (!temp)
            cerr << "Cat by name " << name << " not found!" << endl;
        return temp;
    }
    
    void donate(Cat* ct)
    {
        for (size_t i=0; i < cats.size(); ++i)
        {
            if (ct == cats[i])
            {
                cats.erase(cats.begin() + i);
            }
        }
    }
    
    Cat* operator[](const int& index)
    {
        if (index > cats.size())
            return nullptr;
        else
            return cats[index];
    }
    
};

/*
 
 Output operators (as non-members, always, and non-friends, preferably):
 
 Assume: cout << Cat;
 
 Return ostream by reference, take an ostream by referencem and a Cat.
 
 1. Call the Cat's display function which takes the ostream you were passed (also by reference),
 and uses it to output the information.
 2. Return the ostream.
 
 Fun fact:
 I named the ostream& argument as lhs because it's the cout from the above statement (and it's to the left of the operator).
 
 */

ostream& operator<<(ostream& lhs, Cat& rhs)
{
    rhs.display(lhs);
    return lhs;
}

ostream& operator<<(ostream& lhs, Kennel& rhs)
{
    rhs.display(lhs);
    return lhs;
}

int main(int argc, const char * argv[])
{
    // Let's make some cats on the heap
    Cat* Garfield = new Cat("Garfield", 5);
    Cat* Sylvester = new Cat("Sylvester", 4);
    Cat* Felix = new Cat("Felix", 7);
    
    // They're so cute!
    cout << *Garfield << *Sylvester << *Felix;
    
    // Let's also make a kennel and give them these cats
    Kennel* meowCentral = new Kennel("MeowCentral");
    
    meowCentral->give(Garfield);
    meowCentral->give(Sylvester);
    meowCentral->give(Felix);
    
    // Garfield is a hit, so the kennel wants a copy of him - so they clone him:
    Cat* Clonefield = new Cat("Clonefield", 8);
    *Clonefield = *Garfield;
    cout << *Clonefield << endl;
    
    // Then they cage him, but since he is a mutant, he is donated to science:
    meowCentral->give(Clonefield);
    meowCentral->donate(Clonefield);
    
    // This kennel now has three cats, wonderful!
    cout << *meowCentral << endl;
    
    // Young Sally comes along and adopts Garfield, thus he gets removed from the kennel.
    meowCentral->adopt("Garfield");
    cout << *meowCentral << endl;
    
    // She steps on his tail and Garfield loses two lives:
    (*Garfield)--; // I return a non-decremented copy
    --(*Garfield); // I return a decremented copy.
    cout << *Garfield << endl;
    
    /*
     
     "Wait a second, you used two different notations to remove lives from Garfield!
     Does (*Garfield)-- and --(*Garfield) do the same thing?!"
     
     Yes and no.
     
     The simple explanation is:
     
     (*Garfield)-- decrements his lives after any other operators in the expression use his value.
     --(*Garfield) decrements his lives before any other operators in the expression use his value.
     
     After playing with a debugger, the complex explanation:
     (I did this with a byte, complex objects have way more 'stuff' in them, but the logic applies):
     
     Assume:
     
     byte value;
     byte alpha = value++;
     byte beta = ++value;
     
     Pre:
     
     inc[value];
     mov[beta], [value];
     
     Post:
     
     move[alpha], [value];
     inc [value];
     
     */
    
    // Sally finds out that she has a subliminal hatred for cats and returns her to the kennel; since we push_back() he gets the last cage
    meowCentral->give(Garfield);
    
    // The kennel's vet only knows Garfield by his cage location (he was added to the end):
    cout << *meowCentral << endl;
    // It appears that cage #2 has Garfield (index starts at 0)
    cout << *((*meowCentral)[2]);
    
    // The vet gives Garfield his lives back, then he looks at the whole kennel again:
    (*((*meowCentral)[2]))++;
    ++(*((*meowCentral)[2]));
    cout << *((*meowCentral)[2]);
    
    /*
     
     "Why are you driving me crazy with your pointer notation?!"
     This is to help force you to understand what is a pointer, what is not, and when you need to dereference something.
     
     "Help me understand the above?"
     
     meowCentral is a pointer to Kennel.
     Kennel[i] returns a pointer to Cat.
     
     What I did was a somewhat convoluted version of doing:
     meowCentral->operator[](2)->operator++();
     
     *meowCentral is meowCentral de-referenced.
     (*meowCentral)[i] is meowCentral->operator[](i);
     (*((*meowCentral)[i]))++ is the result of the above de-referenced and incremented via postfix
     
     */
    
}

