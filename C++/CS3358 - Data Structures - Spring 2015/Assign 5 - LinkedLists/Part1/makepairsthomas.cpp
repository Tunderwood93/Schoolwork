Node* MakeDistinctPairs(Node*& headPtr)
{
    if(headPtr == NULL || headPtr->link == NULL) return 0;
    
    Node* ourHead = headPtr;
    Node* cur = headPtr;
    Node* pre = headPtr;
    bool  duplicateFound = false;
	
    
    while (cur->link)
    {
        while (cur != NULL)
        {
            pre = cur;
            cur = cur->link;
            
            if ((!duplicateFound) && cur->data == ourHead->data) // did we find a duplicate
            {
                duplicateFound = true;
                
                if (ourHead->link != cur)
                {
                    if (cur->link != NULL) // rearrange for duplicates
                    {
                        pre->link = cur->link;
                        cur->link = ourHead->link;
                        ourHead->link = cur;
                        
                        if (cur->link)
                        {
                            pre = cur;
                            cur = cur->link;
                        }
                    }
                    else
                    {
                        pre->link = cur->link;
                        cur->link = ourHead->link;
                        ourHead->link = cur;
                        cur = 0;
                    }
                }
            }
            
            if (duplicateFound && ourHead->link != cur)
            {
                
                if ((cur) && cur->data == ourHead->data)
                {
                    Node* nodeToRemove = pre->link;
                    cur = cur->link;
                    pre->link = cur;
                    delete nodeToRemove;
                    
                }
            }
            
            if(!(duplicateFound) && (cur->link == NULL))
            {
                Node* duplicate = new Node;
                duplicate->data= ourHead->data;
                duplicate->link =  ourHead->link;
                ourHead->link = duplicate;
                cur = NULL;
            }
            
        }
        
		duplicateFound = false;
        
		if(ourHead->link->link == NULL) return 0;
		else
		{
			ourHead = ourHead->link->link;
            cur = ourHead;
		}
        
	}
    if (pre->data != cur->data)
    {
        Node *newNodePtr = new Node;
        newNodePtr->data = cur->data;
        newNodePtr->link = 0;
        cur->link = newNodePtr;
    }
    
    return 0;
}
