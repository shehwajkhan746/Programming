/* Write a C ++ Program for deleting the value at location 2 in a linked list with values 10 20 30 40 50 60 70. Print the list after deletion. Assume that the index value starts from 0.

Instructions
- Write a comment to make your code readable.
- Use descriptive variables in your (Name of the variables should show their purposes).
- Ensure your code compiles without any errors/warnings/deprecations 
- Avoid too many & unnecessary usages of white spaces (newline, spaces, tabs, …)
- Always test the code thoroughly, before saving/submitting exercises/projects. */

// last
#include <iostream>
using namespace std;

// Define the structure for a linked list node
struct ListNode {
    int value;
    ListNode* next;
    
    // Constructor for easy node initialization
    ListNode(int val) : value(val), next(nullptr) {}
};

// Function to print the entire linked list
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "\n";
}

// Function to delete a node at a given index (0-based)
void deleteNodeAtIndex(ListNode*& head, int index) {
    // Return immediately if the list is empty
    if (head == nullptr) return;

    // Handle deletion of the head node (index 0)
    if (index == 0) {
        ListNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        return;
    }

    // Traverse to the node immediately preceding the one we want to delete
    ListNode* current = head;
    for (int i = 0; current != nullptr && i < index - 1; ++i) {
        current = current->next;
    }

    // Stop if the index is out of bounds or the target node doesn't exist
    if (current == nullptr || current->next == nullptr) return;

    // Identify the node to delete and bypass it in the list
    ListNode* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    
    // Free the allocated memory
    delete nodeToDelete;
}

int main() {
    // Initialize the linked list: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70
    ListNode* head = new ListNode(10);
    head->next = new ListNode(20);
    head->next->next = new ListNode(30);
    head->next->next->next = new ListNode(40);
    head->next->next->next->next = new ListNode(50);
    head->next->next->next->next->next = new ListNode(60);
    head->next->next->next->next->next->next = new ListNode(70);

    cout << "Original List: ";
    printList(head);

    // Delete the value at location 2 (which is 30)
    int targetIndex = 2;
    deleteNodeAtIndex(head, targetIndex);

    cout << "List after deleting index " << targetIndex << ": ";
    printList(head);

    // Clean up all remaining nodes to prevent memory leaks
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}

