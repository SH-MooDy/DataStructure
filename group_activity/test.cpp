Node *merge(Node *first, Node *second) {
    if(Node *first == nullptr && Node *second == nullptr) {
        return;
    }

    if(Node *first == nullptr) {
        return second;
    }
    else if (Node * second == nullptr) {
        return first;
    }
    else {
        Node *p = first;
        while(p != nullptr) {
            p = p->next;
        }
        p->next = second;
        return p;
    }

}