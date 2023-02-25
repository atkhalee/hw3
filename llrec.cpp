#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

//

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
	smaller = larger = NULL;
	if(head == nullptr){
		return;
	}else{
		llpivot(head->next, smaller, larger, pivot);
		if(head->val > pivot){
				//add to larger
				Node* temp = larger;
				larger = head;
				larger->next =temp;
				
		}
		if(head->val <= pivot){
			//Add to smaller
				Node* temp = smaller;
				smaller = head;
				smaller->next =temp;

		}
		
	}
	head = NULL;
}