struct Node{
    int data;
    Node* next;
};


Node* getMiddle(Node* head){
    Node* slow = head;
    Node* fast = head -> next;

    while(fast != NULL){
        fast = fast -> next;
        if(fast != NULL){
            fast = fast -> next;
            slow = slow -> next;
        }
    }

    return slow;
}