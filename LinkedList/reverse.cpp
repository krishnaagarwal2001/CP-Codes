struct Node{
    int data;
    Node* next;
};

void reverseRecursively(Node* curNode, Node* head){
    //last Node
    if(curNode -> next == NULL){
        head = curNode;
        return;
    }

    reverse(curNode -> next);

    curNode -> next -> next = curNode;
    curNode -> next = NULL;
}

Node* reverseIterative(Node* head){
    Node* prevNode = NULL;
    Node* curNode = head;

    while(curNode != NULL){
        Node* temp = curNode -> next;
        curNode -> next = prevNode;
        prevNode = curNode;
        curNode = temp;
    }

   return prevNode;
}