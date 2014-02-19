/*
 
 Review for CS1124 Exam 2 : Abstract Classes and Advanced Polymorphism
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu 
 
 */

#include <iostream>
#include <vector>

using namespace std;

class Shape
{
private:
    int sides;
    int area;
public:
    Shape (const int& sd) : sides(sd), area(0) {} // Area is 0 until we calculate it!
    virtual void display() = 0; // How are you setting a function equal to 0?
    virtual int getSides() { return sides; }
    virtual int calcArea() = 0; // YOU DID IT AGAIN WHAT'S WRONG WITH YOU?!
};

class Circle : public Shape
{
private:
    int radius;
    int diameter;
public:
    Circle(const int& rd) : Shape(1), radius(rd), diameter(rd * 2) {}
    void display() { cout << "I'm a Circle with radius " << radius << " and diameter " << diameter << endl; }
    int calcArea()
    {
        cout << "Circle::Area" << endl;
        return 0;
    }
};

class Polygon : public Shape
{
public:
    Polygon (const int& sd) : Shape(sd) {}
    void display() { cout << "I'm a Polygon with " << getSides() << " sides!" << endl; }
    //    int calcArea()
    //    {
    //        cout << "Polygon::calcArea()";
    //        return 0;
    //    }
};

int main(int argc, const char * argv[])
{
    /*
     I really like shapes.
     But I can't do this: Shape triangle(3);
     
     Yup, that's right. Shape is an abstract class, and abstract classes cannot have objects created of themselves as standalone instances.
     */
    
    // Let's try again, with a different shape, because I want some variety in my life:
    Circle round(2);
    // And let's see what we have!
    round.display();
    // ...hmm, nice, what's the area on that?
    round.calcArea();
    
    /* Another shape would be nice, I WANT ANOTHER SHAPE WHY DOESN'T IT WORK?
     
     Polygon triangle(3); / This is also an abstract class! We didn't implement calcArea() yet,
     so it remains purely abstract. Uncomment calcArea under Polygon, then
     this will run happily! /
     
     */
    
    // Everything works as it should, nice! Let's make some pointers:
    
    Circle* ptrc = &round; // Types match, this is all fine, no surprise.
    
    /* It's fairly obvious why we can't do this: they are pointing to different types!
     Circle* ptrc2 = &triangle;
     Polygon& ptrp2 = &round;
     */
    
    Shape* ptrs1 = &round;
    
    // Coolio, let's give these a shot:
    ptrc->display();
    ptrs1->display();
    ptrs1->calcArea();
    ptrc->calcArea();
    
    /*
     Very nice, they all work as we'd want them to. ptrs1, although a pointer to shape, runs Circle::calcArea()
     due to calcArea being a pure virtual function.
     */
    
    
}

