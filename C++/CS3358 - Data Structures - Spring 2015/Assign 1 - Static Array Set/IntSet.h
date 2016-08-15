//NO MODIFYING
// FILE: IntSet.h - header file for IntSet class
// CLASS PROVIDED: IntSet (a container class for a set of
//                 int values)
//
// CONSTANT
//   static const int MAX_SIZE = ____
//     IntSet::MAX_SIZE is the highest # of elements an IntSet
//     can accommodate.
//
// CONSTRUCTOR
//   IntSet()
//     Pre:  (none)
//     Post: The invoking IntSet is initialized to an empty
//           IntSet (i.e., one containing no elements).
//
// CONSTANT MEMBER FUNCTIONS (ACCESSORS)
//   int size() const
//     Pre:  (none)
//     Post: Number of elements in the invoking IntSet is returned.
//   bool isEmpty() const
//     Pre:  (none)
//     Post: True is returned if the invoking IntSet has no elements,
//           otherwise false is returned.
//   int contains(int anInt) const
//     Pre:  (none)
//     Post: 1 is returned if the invoking IntSet has anInt as an
//           element, otherwise 0 is returned.
//   bool isSubsetOf(const IntSet& otherIntSet) const
//     Pre:  (none)
//     Post: True is returned if all elements of the invoking IntSet
//           are also elements of otherIntSet, otherwise false is
//           returned.
//           By definition, true is returned if the invoking IntSet
//           is empty (i.e., an empty IntSet is always isSubsetOf
//           another IntSet, even if the other IntSet is also empty).
//   int newToThis(const IntSet& otherIntSet) const
//     Pre:  (none)
//     Post: Number of otherIntSet elements that are new to the
//           invoking IntSet (i.e., the invoking IntSet doesn't have)
//           is returned.
//   void DumpData(std::ostream& out) const
//     Pre:  (none)
//     Post: Contents of the invoking IntSet have been inserted into
//           out with 2 spaces separating one item from another if
//           if there are 2 or more items.
//
// MODIFICATION MEMBER FUNCTIONS (MUTATORS)
//   void reset()
//     Pre:  (none)
//     Post: The invoking IntSet is reset to become an empty
//           IntSet.
//   bool add(int anInt)
//     Pre:  (contains(anInt) == 1) ? size() <= MAX_SIZE : size() < MAX_SIZE
//     Post: If contains(anInt) returns 0, anInt has been
//           added to the invoking IntSet as a new element and
//           true is returned, otherwise the invoking IntSet is
//           unchanged and false is returned.
//   bool remove(int anInt)
//     Pre:  (none)
//     Post: If contains(anInt) returns 1, anInt has been
//           removed from the invoking IntSet and true is
//           returned, otherwise the invoking IntSet is unchanged
//           and false is returned.
//   void unionWith(const IntSet& otherIntSet)
//     Pre:  size() + newToThis(otherIntSet) <= MAX_SIZE
//     Post: All elements of otherIntSet have been added to the
//           invoking IntSet.
//     Note: Adding any element in otherIntSet that is already an
//           element of the invoking IntSet will have no effect
//           on the latter.
//   void intersect(const IntSet& otherIntSet)
//     Pre:  (none)
//     Post: All elements of the invoking IntSet that are not also
//           elements of otherIntSet have been removed from the
//           invoking IntSet.
//   void subtract(const IntSet& otherIntSet)
//     Pre:  (none)
//     Post: All elements of otherIntSet have been removed from
//           ther invoking IntSet.
//     Note: Removing any element in otherIntSet that is not an
//           element of the invoking IntSet will have no effect
//           on the latter.
//
// NON-MEMBER FUNCTIONS
//   bool equal(const IntSet& is1, const IntSet& is2)
//     Pre:  (none)
//     Post: True is returned if is1 and is2 have the same elements,
//           otherwise false is returned.
//           By definition, two empty IntSet's are equal.

#ifndef INT_SET_H
#define INT_SET_H

#include <iostream>

class IntSet
{
public:
   static const int MAX_SIZE = 10;
   IntSet();
   int size() const;
   bool isEmpty() const;
   int contains(int anInt) const;
   bool isSubsetOf(const IntSet& otherIntSet) const;
   int newToThis(const IntSet& otherIntSet) const;
   void DumpData(std::ostream& out) const;
   void reset();
   bool add(int anInt);
   bool remove(int anInt);
   void unionWith(const IntSet& otherIntSet);
   void intersect(const IntSet& otherIntSet);
   void subtract(const IntSet& otherIntSet);

private:
   int data[MAX_SIZE];
   int used;
};

bool equal(const IntSet& is1, const IntSet& is2);

#endif
