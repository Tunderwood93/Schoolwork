// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).


//TODO: CURRENT_INDEX DOESN'T ACTUALLY CHANGE TO -1 UNTIL YOU RUN ADVANCE FOR A SECOND TIME. FIX THAT. 
#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_Sp15
{ 

// CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity) : data(new value_type[initial_capacity]), used(0) , current_index(-1) , capacity(initial_capacity)
   {
	  if(initial_capacity <= 0)
	  {
     	 initial_capacity = 1; 
		 data = new value_type[initial_capacity]; //Create an array of 30 spaces to store doubles. 
		 used = 0; 
		 current_index = -1;
		 capacity = initial_capacity; 
	  }
   }

/*
   data = new int[src.capacity];
   capacity = src.capacity;
   used = src.used;
   
   //I need to manually write my copy function here copy the (src) to the invoking object (data)? Pay attention to this code
   for(int i = 0; i < used; i++)
   {
      data[i] = *&src.data[i]; // If something weird fucks up look here first, remove the dereference address operator. 
   }
*/
   sequence::sequence(const sequence& source) // Remeber that a copy constructor works like so... x(src) initalize x with the contents of src. 
   {
      data = new value_type[source.capacity];
      capacity = source.capacity;
      used = source.used; 
      current_index = source.current_index; 

      //Copy is left inclusive ONLY, [First, last) copy(where to begin, where to end, destination)
      // Since Copy is left inclusive (source.data + source.used + 1) should increment 1 past the # used, successfully copying all elements? 
      std::copy(source.data, source.data + used, data);
   }

   sequence::~sequence()
   {
	  delete [ ] data; 
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      value_type * new_array; 

      if(new_capacity == capacity)
      {
         // do nothing
      }

      if(new_capacity < used)
      {
         new_capacity = used; 
      }

      new_array = new value_type[new_capacity];
      //Copy code goes below 
      for(size_type i = 0;  i < size(); i++)
      {
         new_array[i] = *&data[i];
      }
      delete [ ] data; 
      data = new_array;
      capacity = new_capacity; 
   }

   void sequence::start()
   {
      if(used == 0)
      {
         current_index = -1;
      }
      else
      {
         current_index = 0;
      }
   }

   void sequence::advance()
   { 
      if(current_index >= used || current_index >= capacity)
      {
         cout << "Conditional advance statement met - pre reverting to -1 current_index is " << current_index << " " << endl;
         current_index = -1;
         cout << "Conditional advance statement met - post reverting to -1 current_index is " << current_index << " " << endl;
      }
      else
      {
         cout << "Current index pre advnace is " << current_index << " " << endl;
         current_index++;
         cout << "Current index post advnace is " << current_index << " " << endl;
      }
   }
  //The condition where you have no current item and a non-empty array doesn't work.
   //Proper function would add the new item under this condition to the front of the array and set it to the current item
   void sequence::insert(const value_type& entry)
   {
      int curIndxCast = current_index; 
      size_type unsignedCompInt = -1; 
      //cout << "unsignedCompInt is " << unsignedCompInt << endl; 

      if(used > capacity || (used + 1 > capacity))
      {
         resize(capacity * 1.25 + 1);
      }
 

      if(used == 0)
      {


         data[used] = entry;
         current_index = used; 
         used++;
      }
      else if(used >= 1 && (used + 1 <= capacity) && (is_item() == false))  //current_index == unsignedCompInt / is_item() == false / current_index >= unsignedCompInt /  current_index >= used
      {
         cout << "No_index insert statement met - (pre-start)current_index is " << current_index << " " << endl;
         cout << "No_index insert statement met - (pre-start)used is " << used << " " << endl;
         start();
         cout << "No_index insert statement met -  (post-start)current_index is " << current_index << " " << endl;
         cout << "No_index insert statement met - (post-start)used is " << used << " " << endl;

         for(int i = (used - 1); i >= curIndxCast; i--)
         {
            data[i + 1] = data[i]; //Shift all of the array elements starting at the end of the array and including current index to the right by 1. Then insert the new element. 
         }
         data[current_index] = entry;
         used++; 
      }
      else if(used >= 1 && (used + 1 <= capacity))
      {
         for(int i = (used - 1); i >= curIndxCast; i--)
         {
            data[i + 1] = data[i]; //Shift all of the array elements starting at the end of the array and including current index to the right by 1. Then insert the new element. 
         }
         data[current_index] = entry;
         used++; 
      }
      else
      {
         //Empty
      }

   }

   //The condition where you have no current item and a non-empty array doesn't work.
   //Proper function would add the new item under this condition to the front of the array and set it to the current item
   void sequence::attach(const value_type& entry) // Insert after the current item 
   {
      int curIndxCast = current_index;
      
      if(used > capacity || (used + 1 > capacity))
      {
         resize(capacity * 1.25 + 1);
      }
 
      if(used == 0)
      {
         data[used] = entry;
         current_index = used; 
         used++;
      }
      else if(used >= 1 && (used + 1 <= capacity) && (is_item() == false))  //current_index == unsignedCompInt / is_item() == false / current_index >= unsignedCompInt /  current_index >= used
      {
         cout << "No_index insert statement met - (pre-start)current_index is " << current_index << " " << endl;
         cout << "No_index insert statement met - (pre-start)used is " << used << " " << endl;
         start();
         cout << "No_index insert statement met -  (post-start)current_index is " << current_index << " " << endl;
         cout << "No_index insert statement met - (post-start)used is " << used << " " << endl;

         for(int i = (used - 1); i >= curIndxCast; i--)
         {
            data[i + 1] = data[i]; //Shift all of the array elements starting at the end of the array and including current index to the right by 1. Then insert the new element. 
         }
         data[current_index] = entry;
         used++; 
      }
      else if(used >= 1 && (used + 1 <= capacity))
      {

         for(int i = (used - 1); i > curIndxCast; i--)
         {
            data[i + 1] = data[i];  
         }
         current_index++;
         data[current_index] = entry;
         used++; 
      }
      else
      {
         //Empty ATM 
      }
   }

   void sequence::remove_current()
   {
      //int curIndxCast = current_index;
      if(is_item() == true)
      {
         for(size_type i = current_index; i < (used - 1); i++)
         {
            data[i] = data[i + 1];
         }
         used--;
      }
   }

   //Look at old assignment operator from IntSet
   sequence& sequence::operator=(const sequence& source)
   {
	  value_type *new_data;

     if(this == &source)
     {
         //Self Assignment, do nothing. 
     }

     //Consider replacing the code below with the resize function when implimented. 
     if(capacity != source.capacity)
     {
         new_data = new value_type[source.capacity];
         delete [ ] data;
         data = new_data; 
         capacity = source.capacity; 
     }

     used = source.used; 
     current_index = source.current_index;
     std::copy(source.data, (source.data + used), data);
     
     return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used; 
   }

   bool sequence::is_item() const
   {
      size_type compInt = -1;
      if(current_index >= used) // I trucated this if statment, used to be (current_index >= used || current_index >= capacity)
      {
         return false; 
      }
      else if(current_index != compInt)
      {
         return true;
      }
      else
      {
         return false; 
      }
   }

   sequence::value_type sequence::current() const
   {
      if(is_item() == true)
      {
         return data[current_index];
      }
      else
      {
         return value_type(); // dummy value returned (this was also put inside and else statement, remove if abnormal behavior presents)
      }
   }
}
