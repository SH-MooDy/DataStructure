void func(Node *first, int lower, int upper) {
    if(first == nullptr) { return; }

    Node *p = first, Node *q = nullptr;
    while(p->next != nullptr) {
        if(p->data >= lower && p->data <= upper) {
            if(p == first) {
                first = p->next;
                delete p;
                p = first;
            }
            else {
                
            }
        }
        q = p;
        p = p->next;
    }
}