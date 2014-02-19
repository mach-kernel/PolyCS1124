/*
 
 Review for CS1124 Final : Recursion
 
 David Stancu
 Polytechnic Institute of New York University
 ds4028@nyu.edu 
 
 Updated 12/10/12
 
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    Node* next;
    int data;
    Node (const int& dt, Node* nx) : data(dt), next(nx) {}
};

/*
 
 Each recursive function must have (I'm sure there's more but this is the way I "got" it):
 1. A base case that will cause it to (eventually) return.
 2. A case that inherently recognizes (e.g not the base case) that there is more work to be done.
 
 int(main) has all the neat test code - but read everything first!
 
 */

/*
 
 Calculate any Fibonacci number!
 
 --------------------------------------------------------------
 
 NOTE:
 
 F(n) = F(n-1) + F(n-2)
 The sequence itself (for a few digits): 1, 1, 2, 3, 5, 8, ...
 
 --------------------------------------------------------------
 
 What are the steps we have to take to do this recursively? It's easy if you have
 an array with the sequence of the numbers, but what if you don't?
 
 The code below will calculate the sequence up to the point requested,
 which is somewhat inefficient, however, it is a recursive solution:
 
 Imagine we do fib(4);
 
 fib(4) returns fib(3) + fib(2)
 fib(3) returns fib(2) + fib(1)
 fib(2) returns 1
 
 fib(2) + fib(1) are < 3, therefore they both return 1: 1 + 1 = 2
 therefore: fib(3) returns 2.
 
 fib(4) returns 2 + 1 = 3
 
 fib(4) = 3
 
 This looks somewhat annoying to imagine, but the key point that this function
 relies on a return value from itself. Most recursive functions return to themselves,
 although, this is not a requirement.
 
 */

int fib (int index)
{
    if (index < 3) // Note that the first 2 numbers are 1, so return 1!
        return 1;
    else
        return fib(index - 1) + fib(index - 2); // How does this work?
}

/*
 
 Calculate factorials (aka really cheerful mathematics):
 5! = 5 * 4 * 3 * 2 * 1 = 120
 
 Base case: If the number is less than 3, just return the number (2 * 1 = 2, 1 * 1 = 1)
 
 --
 
 If the base case is not met, return the current number multiplied by the factorial of num - 1. This
 works because num * (num - 1)! = num!
 
 Assume we want to find 4!:
 
 3. return 2;
 2. return 3 * factorial (2); // 3 * 2 = 6
 1. return 4 * factorial (3); // 6 * 4 = 24
 
 This should be pretty straightforward!
 
 */

int factorial (int num)
{
    if (num < 3)
        return num;
    return num * factorial(num - 1);
}

/*
 
 Find the last member of a linked list:
 
 Base case: A Node object has no "next" link (head->next == nullptr)
 If this is true, we can return the pointer which was passed in as it is
 the first and last member of the list (e.g. a list with one member)
 
 --
 
 If the base case is not met, we return the last member of the next Node object as its last
 member is also the last member of the head pointer (in a linear singly linked list).
 
 Assume that we pass in a Node* with three members:
 
 1. Base case not met, will return the last of next.
 2. Base case not met, will return the last of next.
 3. Base case met, returning whatever was passed in.
 
 The return value of step 3 will go up to the instance which called it until the 'original'
 instance recieves its value (I'm going to use a dummy address):
 
 3. returns 0xDEADBEEF
 2. returns findLast(head->next); // findLast(head->next) == 0xDEADBEEF, so it returns 0xDEADBEEF
 1. returns findLast(head->next); // findLast(head->next) == return value of step 2
 
 */

Node* findLast (Node* head)
{
    if (!head)
        return nullptr;
    if (!head->next)
        return head;
    return findLast(head->next);
}

/*
 
 Find the length of a linked list:
 
 Base case: The head pointer passed in is nullptr. The length of something that does not exist is zero.
 
 --
 
 If the base case is not met, return the length of the NEXT node and add 1 to it.
 
 The function will continue to loop until the base case is met, and then it will return 1 to the
 instance which previously called it.
 
 I know, this is confusing, but take a look at it this way:
 
 Node* aList; // Assume this has length 4
 
 nodeLen(aList);
 returns: nodeLen(head->next) + 1
 returns: nodeLen(head->next) + 1
 returns: nodeLen(head->next) + 1
 returns: nodeLen(head->next) + 1
 
 I still don't get it, how do you get 4?
 
 Alright, let's number the returns in reverse
 (as this is the way it makes its way up to the 'original' instance):
 
 5: 0
 4: [Return of 5] + 1 // 0 + 1 = 1
 3: [Return of 4] + 1; // 1 + 1 = 2
 2: [Return of 3] + 1; // 2 + 1 = 3
 1: [Return of 2] + 1; // 3 + 1 = 4
 
 */

int nodeLen (Node* head)
{
    if (!head)
        return 0;
    return nodeLen(head->next) + 1;
}


/*
 
 Copying a linked list:
 
 Base case: The head pointer passed in is nullptr. You cannot return a copy of nothing, so you return
 nullptr.
 
 --
 
 If the base case is not met, return a new Node that has its next pointing to a copy of
 the next node of the current head pointer.
 
 The function will continue to loop through itself until it is called upon the last Node's next. At this 
 point, it will return nullptr to the instance which called it (the last Node) which will have its 
 next parameter filled with nullptr. This makes sense - the last member of the list has no next value.
 
 I know this is a mindful, but look at it this way (assume a list of length 3):
 
 4. returns nullptr.
 3. returns Node(head->data, [4])
 2. returns Node(head->data, [3]) // where [3] is the return value of 3.
 1. returns new Node(head->data, [2]) // where [2] is the return value of 2.
 
 */

Node* copyList (Node* head)
{
    if (!head)
        return nullptr;
    return new Node(head->data, copyList(head->next));
}

/*
 
 Conducting a binary search, read this before attempting: http://en.wikipedia.org/wiki/Binary_search_algorithm
 
 How does it work:
 Binary searches assume that the array is already sorted (either ascending or descending order). In order
 to conduct a binary search you need a left index, a right index, an array, and something to look for.
 
 It takes the array and finds the midpoint index:
 A: If the midpoint == what you're looking for, it will return that midpoint.
 B: If array[midpoint] is > what you're looking for, it will conduct a binary search with the left index
 the same as it was, and the right index set to the midpoint index - 1
 (becuase you already checked the midpoint).
 C: If array[midpoint] is < what you're looking for, it will conduct a binary search with the left index
 set to the midpoint + 1 (same reason as in B), and the right index left to what it was.
 
 OK, but:
 
 When does it know when to stop?
 What if there isn't any value in the array to match what you're looking for?
 What happens if you pass in even numbered arrays (aka the midpoint is not a clean median value)?
 
 1. Whenever array[midpoint] == value, it will pass that midpoint over to its parent instance, which
 will be passed on to the parent's parent and so forth.
 
 2. The left and right indices will approach one another to the point where they will be equal to one another,
 but it does *not* stop there.
 
 Pay attention here, this is important:
 Note: If left == right, then left == right == midpoint: your midpoint will also equal the indices!
 
 Case 1: array[midpoint] > value ==> binSearch(array, midpoint + 1, same right index, same search parameter)
 Ask yourself, is n+1 greater than n?
 
 Case 2: array[midpoint] < value ==> binSearch(array, same left index, midpoint - 1, same search parameter)
 Ask yourself, is n greater than n-1?
 
 3. C++ handles uneven integer division by dropping any fractional remainder on a number:
 
 3/2 = 1.5 --> 1[.5] (drop []) ==> 1
 array[midpoint] will always be valid (no index of .3333 or some odd fraction nobody cares about)
 
 No, it won't mess up your search either, because the next iteration will include the numbers in the middle
 as you increment/decrement the midpoint.
 
 */

int binSearch (int* arr, int left, int right, int want)
{
    if (!arr || left > right)
        return -1;
    int mid = (left + right) / 2;
    if (arr[mid] == want)
        return mid;
    if (arr[mid] > want)
        return binSearch(arr, left, --mid, want);
    else
        return binSearch(arr, ++mid, right, want);
}

int main(int argc, const char * argv[])
{
    cout << fib(20) << endl;
    cout << factorial(5) << endl;
    
    Node* list = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5, nullptr)))));
    cout << nodeLen(list) << endl;
    
    Node* lastofList = findLast(list);
    cout << lastofList->data << endl;
    
    Node* newlist = copyList(list);
    cout << nodeLen(newlist) << endl;
    
    int waldo[10] = {2,4,6,8,10,12,14,16,18,20};
    cout << binSearch(waldo, 0, 10, 18) << endl;
    cout << waldo[binSearch(waldo, 0, 10, 18)] << endl;
}

