// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.



#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;
void IntSet::resize(int new_capacity)
{
   // Please Write the Re-size function
   int * new_array; 

   if(new_capacity == capacity)
   {
      // do nothing
   }

   if(new_capacity < used)
   {
      cout << "The Resize Function has set the new_cap = to the invoking objected used" << endl;
      new_capacity = used; 
   }

   new_array = new int[new_capacity];
   //Copy code goes below 
   for(int i = 0;  i < size(); i++)
   {
      new_array[i] = *&data[i];
   }
   delete [ ] data; 
   data = new_array;
   capacity = new_capacity; 
   cout << "The New capacity after resize is: " << capacity << " " << endl;
   cout << "The Array was succesfully resized" << endl; 
}

IntSet::IntSet(int initial_capacity) //My Constructor should be complete. Feb-9th-15 3:03pm
{
   data = NULL; //creating a double pointer here
   used = 0;
   capacity = initial_capacity;
   
   data = new int[initial_capacity];

   for(int i = 0; i < capacity; i++) // I need to replace this with an initilizer list
   {
      data[i] = 0; 
   }
}

IntSet::IntSet(const IntSet& src) // This is the Copy constructor y(x) or y = x "initalize bag y(data) as a copy of x(src)"
{
   data = new int[src.capacity];
   capacity = src.capacity;
   used = src.used;
   
   //I need to manually write my copy function here copy the (src) to the invoking object (data)? Pay attention to this code
   for(int i = 0; i < used; i++)
   {
      data[i] = *&src.data[i]; // If something weird fucks up look here first, remove the dereference address operator. 
   }

}

IntSet::~IntSet()
{
   delete [ ] data; 
}

IntSet& IntSet::operator=(const IntSet& rhs) // PAGE 188 FOR WRITING ASSIGNMENT OPERATOR
{
   int * temp_ptr;

   //Checking for possible self assignment;
   if(this == &rhs)
   {
      //Do nothing
   }

   if(capacity != rhs.capacity)
   {
      // Manually done, possibly call resize when implemented. 
      temp_ptr = new int[rhs.capacity];
      delete [ ] data; 
      data = temp_ptr; 
      capacity = rhs.capacity;  
   }
   used = rhs.used;
   //Copy array code below
  return *this;
}

int IntSet::size() const
{
   return capacity; 
}

bool IntSet::isEmpty() const
{
   if(used == 0)
   {
      return true; 
   }
   return false;
}

int IntSet::contains(int anInt) const
{
   for(int i = 0; i < capacity; i++)
   {
      if(data[i] == anInt)
      {
         return 1;
      }
   }
   return 0; 
}
//   bool isSubsetOf(const IntSet& otherIntSet) const
//     Pre:  (none)
//     Post: True is returned if all elements of the invoking IntSet
//           are also elements of otherIntSet, otherwise false is
//           returned.
//           By definition, true is returned if the invoking IntSet
//           is empty (i.e., an empty IntSet is always isSubsetOf
//           another IntSet, even if the other IntSet is also empty).
bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{  
   if(used && otherIntSet.used == 0)
   {
      return true; 
   }
   else
   {
      for(int i = 0; i < used; i++)// Traverse the invoking array
      {
         if(otherIntSet.contains(i) != 1) // If the other intset DOES NOT contain a value from our original array, return false 
         {
            return false; 
         }
      } 
   }
   return true; // dummy value returned
}

int IntSet::newToThis(const IntSet& otherIntSet) const //THIS FUNCTION IS TESTED AND WORKING 11:52PM FEB-10TH-15
{
   //int tempVal = 1; 
   int newElements = otherIntSet.used;

   if((used == 0) && (otherIntSet.used != 0))  
   {
      return otherIntSet.used;
   }
   else if((used == 0) && (otherIntSet.used == 0))
   {
      return 0;
   }
   else
   {
      for(int i = 0; i < used; i++)
      {
         for(int j = 0; j < otherIntSet.used; j++)
         {
            if(data[i] == otherIntSet.data[j])
            {
               newElements--;
            }
         }
      }
      return newElements;
   }
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

void IntSet::reset()
{
   used = 0; 
}

bool IntSet::add(int anInt) //WE SEEM TO BE WORKING CORRECTLY
{
   // Please write the add function. 
   if(used == capacity)
   {
      resize(used + 1);
      cout << "You've hit the resize condition in the add function" << endl;
   }

   if(used < size() && contains(anInt) == 0)
   {
      data[used] = anInt;
      used++;
      cout << "After adding the value, used is: " << used << " " << endl;
      return true;
   }
   return false; 
}

bool IntSet::remove(int anInt)
{
   for(int i = 0; i < capacity; i++)
   {
      if(data[i] == anInt)
      {
         for(int i; i < used - 1; i++) // If more complation errors, add i; before i < used
         {
            data[i] = data[i + 1];
         }
         data[used - 1] = 0;
         used--; 
         return true; 
      }
   }
   return false; 
}

void IntSet::unionWith(const IntSet& otherIntSet)
{
   int tempval = 0; 

   for(int i = 0; i < otherIntSet.used; i++) // THIS APPEARS TO BE WORKING CORRECTLY. 
   {
      tempval = otherIntSet.data[i];
      add(tempval);
   }
}
//   void intersect(const IntSet& otherIntSet)
//     Pre:  (none)
//     Post: All elements of the invoking IntSet that are not also (If array 1 contains an element array 2 doesn't remove it)
//           elements of otherIntSet have been removed from the
//           invoking IntSet.
void IntSet::intersect(const IntSet& otherIntSet) //I'm only removing values 1 at a time using this method, IE you have to run intersect more than once. 
{
   int tempval = 0;
   for(int i = 0; i < used; i++)
   { 
      tempval = this->data[i]; //Possibly replace with IntSet.data[i]
      if(otherIntSet.contains(tempval) != 1)
      {
         cout << "U hit remove if statement" << endl;
         remove(tempval); 
      }
   }
}
//   void subtract(const IntSet& otherIntSet)
//     Pre:  (none)
//     Post: All elements of otherIntSet have been removed from
//           ther invoking IntSet.
//     Note: Removing any element in otherIntSet that is not an
//           element of the invoking IntSet will have no effect
//           on the latter.
void IntSet::subtract(const IntSet& otherIntSet) // I don't work, I don't know why. I cause a seg fault 
{
   int tempval = 0; 

   for(int i = 0; i < otherIntSet.used; i++) 
   {
      tempval = otherIntSet.data[i];
      remove(tempval);
   }
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   //Still need to write code to compare sets. 
    if(is1.size() == is2.size())
   {
      if((is1.newToThis(is2) == 0))
      {
         return true;
      }
   }
   return false; 
}


