// File: StrTab.h - header file for StrTab class
// CLASS PROVIDED: StrTab (A table class in which the keys and values are strings.)
//
// CONSTRUCTOR
//   StrTab()
//     Pre:  (none)
//     Post: Initializes invoking StrTab to empty table.
//
// CONSTANT MEMBER FUNCTIONS (ACCESSORS)
//   std::string get(const std::string & key) const
//     Pre:  (none)
//     Post: Returns value associated with key or empty string if key is unassociated.
//
// MODIFICATION MEMBER FUNCTIONS (MUTATORS)
//   void put(const std::string& key, const std::string& value)
//     Pre:  (none)
//     Post: Associates key with value in this StrTab.
//
// NON-MEMBER FUNCTIONS
//   int hashCode(const std::string & key)
//     Pre:  (none)
//     Post: Returns the hash code for key.
//
// ILLEGAL TO COPY
//   Copy construction/assignment may NOT be used with StrTab objects.

#ifndef STR_TAB
#define STR_TAB

#include <string>

class StrTab
{
public:
   StrTab();
   ~StrTab();
   std::string get(const std::string & key) const;
   void put(const std::string& key, const std::string& value);
private:
   // definition for nodes in a bucket's linked list (chain)
   struct stNode
   {
      std::string key;
      std::string value;
      stNode* link;
   };

   // class-level constant
   static const int INITIAL_BUCKET_COUNT = 13;
   // instance-level variables
   stNode** buckets;  // dynamic array of pointers to stNode's
   int numBuckets;    // number of buckets in the array

   // private helper function
   stNode* findNode(int bucket, const std::string & key) const;

   // disabling copy construction/assignment
   StrTab(const StrTab& src) { }
   StrTab& operator=(const StrTab& src) { return *this; }
};

int hashCode(const std::string & key);

#endif

