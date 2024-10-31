void removeNodesInRange(Node *&head, int lower, int upper) {
    Node *p = head, *q = nullptr;

    // 먼저 lower보다 작은 노드를 건너뜀
    while (p != nullptr && p->data < lower) {
        q = p;
        p = p->next;
    }

    // lower 이상 upper 이하의 노드들을 삭제
    while (p != nullptr && p->data <= upper) {
        Node *temp = p;
        p = p->next;
        if (q == nullptr) {
            // 헤드를 삭제해야 하는 경우
            head = p;
        } else {
            q->next = p;
        }
        delete temp;
    }

    // 연결된 나머지 리스트
    if (q != nullptr) {
        q->next = p;
    }
}
