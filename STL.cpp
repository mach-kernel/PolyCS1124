/*
 
 Review for CS1124 Final : Templates
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu 
 
 */

#include <iostream>
#include <vector>

using namespace std;

// Let's make a linked list class as we have previously:

struct Node
{
    Node* next;
    int data;
    Node (const int& dt, Node* nx) : data(dt), next(nx) {}
};


/*
 
 Solution A:
 
 struct NodeS
 {
 NodeS* next;
 string data;
 NodeS (const string& dt, Node* nx) : data(dt), next(nx) {}
 };
 
 void dispNode(NodeS* head)
 {
 if (!head)
 cout << "Invalid list" << endl;
 cout << "Data: " << head->data << endl;
 if (!head->next)
 return;
 dispNode(head->next);
 }
 
 -----------------------------------------------------------
 
 Solution B:
 
 template <class T>
 struct Node
 {
 Node* next;
 T data;
 Node (const T& dt, Node* nx) : data(dt), next(nx) {}
 };
 
 template <class T>
 void dispNode(Node<T>* head)
 {
 if (!head)
 cout << "Invalid list" << endl;
 cout << "Data: " << head->data << endl;
 if (!head->next)
 return;
 dispNode(head->next);
 }
 
 */


// And let's make a nice little display function for it, using the recursion we just learned

void dispNode(Node* head)
{
    if (!head)
        cout << "Invalid list" << endl;
    cout << "Data: " << head->data << endl;
    if (!head->next)
        return;
    dispNode(head->next);
}

int main(int argc, const char * argv[])
{
    // Neat, let's make a Node!
    Node* intParty = new Node(7, new Node(8, new Node (9, nullptr)));
    dispNode(intParty);
    
    // Wow these things are pretty great, let's store other stuff too!
    Node* stringParty = new Node("C++", new Node("is totally like", new Node("the best evarrr!", nullptr)));
    Node* doubleParty = new Node(1.3, new Node(2.7, new Node(3.3, nullptr)));
    
    /*
     Wait a second! It won't run! David, you KNOW the struct you made only takes ints! What's wrong with you?!
     OK OK fine, go uncomment Solution A and change stringParty to type of NodeS. Yes, there is an overload for
     dispNode now as we're displaying a different object (NodeS != Node).
     
     Now, let's look at our nodes!
     */
    
    dispNode(stringParty);
    dispNode(doubleParty);
    
    /*
     A: Sweet, my strings work, but what gives, why are my doubles being truncated?!
     
     Well, when you pass your double to the int taking Node, it is automagically cast to double by
     dropping the tail end (everything after the .) of whatever you passed in.
     
     
     B: This language sucks. Am I going to have to write a Node class for everything I want to use with
     linked lists? Why can't it be nice like doing vector<whatever>?
     
     It can. Go comment out all of the current structs and dispNode functions, change NodeS to Node,
     and implement Solution B by uncommenting it.
     
     
     C: It still doesn't compile, the compiler is telling me that I have to use template arguments...?
     
     Remember when you were telling me about how awesome using vector<whatever> is? Well, just as you
     are telling the vector that it will be filled with objects of type whatever, you have to tell
     our new Node class that it will be filled with objects of whatever you choose.
     
     Some examples:
     
     Node<int>
     Node<string>
     Node<double>
     Node<cats>
     Node<foundingFathers>
     Node<monicaLewinskiSympathizers>
     
     Go fix the existing Nodes by specifying the types which they are to contain, and then re-run the program.
     I did one of the lines for you:
     
     Node<string>* stringParty = new Node<string>("C++", new Node<string>("is totally like", new Node<string>("the best evarrr!", nullptr)));
     
     This is truly, in my personal opinion, the beauty of C++ at its core.
     
     */
    
}
