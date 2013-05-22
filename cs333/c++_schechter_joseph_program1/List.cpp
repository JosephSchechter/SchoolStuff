#include "List.h"
using namespace std;

typedef int ElementType;

// -------------------------------------
// ------------Node class---------------
// -------------------------------------

// 
// Create a linked list node by setting its data to the input parameter
// and the next node in the linked list to NULL (0)
Node::Node(ElementType data_input) {
   data = data_input;
   next = 0;
}

// Default constructor leaves data items unspecified
Node::Node() {
}

// -------------------------------------
// ------------List class---------------
// -------------------------------------
			
//
// Default constructor creates an empty list
//
List::List() {
   list_head = NULL;
   num_elements = 0;
}

//
// Delete all the elements in the linked list when the list is deleted
//
List::~List() {
   Node *next_node;
   Node *current_node = list_head;

   while (current_node != NULL) {
      next_node = current_node->next;
      delete(current_node);
      current_node = next_node;
   }	
}

//
// Add a single element to the head of the linked list
//
int List::insert(ElementType data_input) {

   Node *new_node = new Node(data_input);
   //ADDED 9/19/10 to check for failure
   if(new_node == NULL){
	cout << "\nFAIL GRACEFULLY\n";
	return -1;
   }
   
   if (list_head == 0) {
      list_head = new_node;
   } else {
      new_node->next = list_head;
      list_head = new_node;	
   }
   num_elements++;
   return 0;
}

//
// Remove a single element from the head of the linked list
//
void List::remove() {

   if (list_head == NULL)
      return;	

   Node *new_head = list_head->next;
   delete(list_head);
   list_head = new_head;
   num_elements--;
}

//
// Print all the elements in the linked list
//
void List::show()
{
   cout << "List of " << num_elements << " elements: " ;
   Node *current_node = list_head;
   while (current_node != NULL) {
      cout << current_node->data << " ";
      current_node = current_node->next;
   }
   cout << endl;
}

//
// splitOddEven()
//
List *List::splitOddEven()
{
// This function splits the list in two, adding the the elements
// with odd integer values into a new linked list, and keeping only
// those elements with even integer values in the list on which
// this function is called. The function returns a pointer to
// the new (heap allocated) list with the odd elements in it. If the
// original list is empty, or if there are no odd elements, the
// function returns a pointer to a new empty List (not a NULL
// pointer). 

	List *rlist = new List;
	
	if(num_elements == 0)
	{
//		cout << "\nNo elements in the list\n";
		return rlist;
	}
	
	ElementType oddnum;
	
	
/*	
	cout << "\nTest1\n";
	//Do the head
	bool headChecked = false;
	while (headChecked == false && list_head != NULL)	//will keep checking and taking out the head until the head is even or if we run out of variables
	{
		if(list_head->data % 2 != 0) 	//is odd
		{
	cout << "\nTest2\n";
			temp3 = list_head;
			list_head = temp3->next;
			num_elements--;
			oddnum = temp3->data;
			delete temp3;
			temp3 = NULL;
			rlist->insert(oddnum);
		}
		
		else if(list_head->data % 2 == 0)	//is even
		{
			headChecked = true;
		}
	}
*/
	
//	cout << "\nTest3\n";
	Node * place = list_head;
	Node * placePlus1 = NULL;
	Node * temp4 = NULL;
	
	//Checks every one except the 1st (head)
	bool end = false;
	while(place->next != NULL && end == false)
	{
		placePlus1 = place->next;
		if((placePlus1->data % 2 != 0) || (placePlus1->data == 1)) //is odd
		{
//			cout << "\nTest4\n";
			temp4 = placePlus1;
			place->next = placePlus1->next;	//p+1 is not in the order anymore
			num_elements--;
			oddnum = temp4->data;
			//temp4->next = NULL;
			//place = placePlus1;
			if(place->next == NULL)
			{
				delete temp4;
				temp4 = NULL;
				rlist->insert(oddnum);
				end = true;
			}
			else 
			{
				place = place->next; //move onto next one after the recently removed item
				delete temp4;
				temp4 = NULL;
				rlist->insert(oddnum);
			}
		}
		else //is even
		{
			place = placePlus1;
		}
	}
	
	//check the head
//	cout << "\nTest5\n";
	if((list_head->data % 2 != 0) || (list_head->data == 1))//is odd
	{
		Node * temp3 = list_head;
		if(num_elements == 1)//just the head
		{
			list_head = NULL;
			oddnum = temp3->data;
			delete temp3;
			temp3 = NULL;
		}
		else //has more than 1 element
		{
			oddnum = temp3->data;
			list_head = temp3->next; //new head is the 1st's next
			delete temp3;
			temp3 = NULL;
		}
		num_elements--;
	}
	
	
	
	return rlist;
	
	
	cout << "List::splitBigSmall() not yet implemented." << endl;  
	return(rlist);
}

//
// extractLargest()
//
Node *List::extractLargest()
{
	if(num_elements == 0){
//		cout << "\nNo elements in the list\n";
		return (NULL);
	}
	
	Node * biggest = list_head; //points to 1st node
	Node * place = list_head;	//points to 1st node
	Node * placePlus1 = NULL;
//traverse through the nodes until the place's next = null, starting the biggest value = 1st, then change
//if it gets a bigger #, replace it

	
//	cout <<"\nTEST 1\n";
	
	
	while(place->next != NULL)
	{
		placePlus1 = place->next;
		if(placePlus1->data > biggest->data)
		{
			biggest = placePlus1;
		}
		place = placePlus1;
	}
	
	ElementType huge = biggest->data;
	
	place = list_head;
	placePlus1 = NULL;
	bool extracted =  false;
	
//then once it has the biggest number, traverse through it again, but look at the 
//next in line from inside the previous, if it contains that number
//copy that node pointer to temp to return it
//also change the current pointer to temp's pointer
//set temp->next = 0;
//return temp 
	
	Node * temp = list_head;
	//1st
	if(temp->data == huge)
	{
		list_head = temp->next;
		temp->next = NULL;
		num_elements--;
		extracted = true;
		return temp;
	}
	
	while(extracted  ==  false)
	{
		placePlus1 = place->next;
//		cout <<"\nTEST 4\n";
		if(placePlus1->data == huge)
		{
			
			place->next = placePlus1->next; //p+1 is no longer part of list
			temp = placePlus1;
			extracted = true;
			temp->next = NULL;
			num_elements--;
			return temp;
		}
		place = placePlus1;
	}
//	cout <<"\nTEST 3\n";
	
	cout << "List::extractLargest() not yet implemented." << endl;  
	return (NULL); 
}


//
// splitBigSmall()
//
List *List::splitBigSmall()
{
/*
This function should split the list in half, adding the the elements with the largest values into a new linked list, and keeping only those half of the elements with the smallest values in the list object on which this function is called. The function should return a pointer to the new (heap allocated) list with the larger elements in it. If the original list contains an odd number of elements, then the returned list (with the larger elements in it) should contain one fewer element than the list on which this function is called. If the original list is empty, the function should return a pointer to a new empty List (not a NULL pointer).
*/
	List *rlist = new List;
   
	if(num_elements == 0)
	{
		return rlist;
	}

	//even,	2/2 = 1 element in the big
	//odd,	3/2 = 1 elements in the big
	Node * temp2 = NULL;	//1st
	ElementType tmp;
	for (int i = num_elements/2; i > 0; i--)
	{
		temp2 = extractLargest();
		tmp = temp2->data;
		rlist->insert(tmp);
		delete temp2;
		temp2 = NULL;
	}
	return rlist;
	
	
	
//	cout << "List::splitBigSmall() not yet implemented." << endl;  
	return(rlist);
}

