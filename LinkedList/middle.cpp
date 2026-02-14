struct Node{
    int data;
    Node* next;
};


Node* getMiddle(Node* head){
    Node* slow = head;
    Node* fast = head -> next;

    /*
        If we need 2nd element of middle in even length, change 
        Node* fast = head -> next; to
        Node* fast = head;
    */

    while(fast != NULL){
        fast = fast -> next;
        if(fast != NULL){
            fast = fast -> next;
            slow = slow -> next;
        }
    }

    return slow;
}