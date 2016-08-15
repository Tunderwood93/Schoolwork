// File: StrTab.cpp - implementation file for StrTab class
//       (Uses a hash table as the underlying representation.)
//       (See StrTab.h for more documentation.)

#include <string>
#include <iostream>
#include "StrTab.h"
using namespace std;

// Implementation notes: StrTab constructor
//   Allocates the array (sized INITIAL_BUCKET_COUNT) of buckets
//   and initializes each bucket to the empty list.
StrTab::StrTab() : buckets(new stNode*[INITIAL_BUCKET_COUNT]), numBuckets(INITIAL_BUCKET_COUNT)
{
	for(int i = 0; i < numBuckets; i++)
	{
		buckets[i] = new stNode; 
		buckets[i]->key = "";
		buckets[i]->value = "";
		buckets[i]->link = NULL; 
	}
}

// Implementation notes: StrTab destructor
//   Frees the allocated cells.
StrTab::~StrTab()
{
	for(int i = 0; i < INITIAL_BUCKET_COUNT; i++)
	{
		delete buckets[i];
	}

	delete [] buckets; 
}

// Implementation notes: get
//   Calls findNode to search the linked list for the matching key:
//     index_into_buckets_array = hasCode_return_value % numBuckets
//   If match is found, get returns the associated value (string).
//   If no match is found, get returns the empty string.
string StrTab::get(const string& key) const
{
	int index = hashCode(key) % numBuckets;
	stNode * current = findNode(index, key); 

	if(current != 0)
		return current->value;
	else
		return "";
}

// Implementation notes: put
//   Calls findNode to search the linked list for the matching key:
//     index_into_buckets_array = hasCode_return_value % numBuckets
//   If a node (with matching key) already exists, put simply resets the
//   value field. If no matching key is found, put adds a new node to
//   the beginning of the list for that chain.
void StrTab::put(const string& key, const string& value)
{ 
	int index = hashCode(key) % numBuckets; 

	if(findNode(index, key) == 0)
	{
		stNode * current = buckets[index];
		
		while(current->link != NULL)
		{
			current = current->link;
		}

		stNode * newNode = new stNode;
		current->link = newNode;
		newNode->key = key;
		newNode->value = value;
		newNode->link = NULL; 
	}
	else
	{
		findNode(index,key)->value = "";
	}	
}

// Implementation notes: private helper function findNode
//   Finds a node (in the chain for the specified bucket) that matches
//   key. If a match is found, the return value is a pointer to the
//   node containing the matching key. If no match is found, findNode
//   returns 0 (null pointer).
StrTab::stNode* StrTab::findNode(int bucket, const string& key) const
{
	stNode * cursor = buckets[bucket];

	while(cursor != NULL) 
	{
		if(cursor->key == key)
			return cursor;
		else
			cursor = cursor->link;
	}
   return 0; // dummy null pointer returned
}

// Implementation notes: hashCode
//   Takes a string key and uses it to derive a hash code, which is a
//   nonnegative integer related to the key by a deterministic function
//   that distributes keys well across the space of integers.
//   The specific algorithm used here is called djb2 after the initials
//   of its inventor, Daniel J. Bernstein, Professor of Mathematics at the
//   the University of Illinois at Chicago.
int hashCode(const string& str)
{
	unsigned long hash = 5381;
	unsigned int c;
	
	for(unsigned int i = 0; i < str.length(); i++)
	{
		c = str[i];
		hash += ((hash << 5) + hash) + c;
	}

	return hash; 
}

