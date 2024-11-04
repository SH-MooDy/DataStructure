void printBinary(int n) {
    for(int i = n; i > 0;) {
        int biNum = i%2;
        stack.push(biNum);
        i /= 2;
    }

    while(!stack.empty()) {
        cout << stack.pop() << endl;
    }
}