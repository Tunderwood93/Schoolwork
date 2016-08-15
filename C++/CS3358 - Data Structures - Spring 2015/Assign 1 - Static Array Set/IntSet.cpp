// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
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
//     from data[used] through data[IntSet::MAX_SIZE - 1].
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
//TODO: FINISH FUNCTIONS, TEST IMPLIMENTATION, REMOVE COMMENTS AND PREP FOR TURN IN. 
#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet()
{
   //It seems like, this constructor works. 
   data[MAX_SIZE];
   used = 0;
}

int IntSet::size() const { return used; }

bool IntSet::isEmpty() const
{
   if(used == 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}

int IntSet::contains(int anInt) const //bool except return 1 or 0
{
   //From what I can tell this function is implimented. 
   for(int i = 0; i < MAX_SIZE; i++)
   {
      if(data[i] == anInt)
      {
         return 1;
      }
   }
   return 0; 
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   cout << "isSubsetOf() is not implemented yet..." << endl;
   return false; // dummy value returned
}

int IntSet::newToThis(const IntSet& otherIntSet) const  
{
   //From what I can tell this function is implimented. 
   int tempVal = 1; 
   int newElements = otherIntSet.size();

   if((size() == 0) && (otherIntSet.size() != 0))  
   {
      return otherIntSet.size();
   }
   else if((size() == 0) && (otherIntSet.size() == 0))
   {
      return 0;
   }
   else
   {
      for(int i = 0; i < size(); i++)
      {
         for(int j = 0; j < otherIntSet.size(); j++)
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
   for(int i = 0; i < MAX_SIZE; i++)
   {
      data[i] = NULL;
   }
   used = 0;
   //cout << "reset() is not implemented yet..." << endl;
}

bool IntSet::add(int anInt)
{
   //As far as I can tell, this function is finished? 
   if(size() < MAX_SIZE && contains(anInt) == 0)
   {
      data[used] = anInt;
      used++;
      return true;
   }
   return false; 
}

bool IntSet::remove(int anInt)
{
   //From what I can tell this function is finished? Shifting works 
   for(int i = 0; i < MAX_SIZE; i++)
   {
      if(data[i] == anInt)
      {
         for(i; i < used - 1; i++) // If more complation errors, add i; before i < used
         {
            data[i] = data[i + 1];
         }
         data[used - 1] = NULL;
         used--; 
         return true; 
      }
   }
   return false; // dummy value returned
}
//   void unionWith(const IntSet& otherIntSet)
//     Pre:  size() + newToThis(otherIntSet) <= MAX_SIZE
//     Post: All elements of otherIntSet have been added to the
//           invoking IntSet.
//     Note: Adding any element in otherIntSet that is already an
//           element of the invoking IntSet will have no effect
//           on the latter.
void IntSet::unionWith(const IntSet& otherIntSet)
{
   int tempDataSet[MAX_SIZE];
   int tempVal = otherIntSet.size();
   //int indexVal = size();

   if((size() + newToThis(otherIntSet)) <= MAX_SIZE)
   {
      //cout << "We have entered the if statement" << endl;
      for(int i = 0; i < MAX_SIZE; i++)
      {
         //cout << "We have entered the for loop" << endl;
         if(data[i] != otherIntSet.data[i])
         {
            //cout << "We have entered the second if statement" << endl;
            add((data[(size() + 1)] = otherIntSet.data[i]));
         }
      }
   }
}

void IntSet::intersect(const IntSet& otherIntSet)
{
   cout << "intersect() is not implemented yet..." << endl;
}

void IntSet::subtract(const IntSet& otherIntSet)
{
   cout << "subtract() is not implemented yet..." << endl;
}

bool equal(const IntSet& is1, const IntSet& is2) 
{
   if(is1.size() == is2.size())
   {
      if((is1.newToThis(is2) == 0))
      {
         return true;
      }
   }
   return false; 
}


