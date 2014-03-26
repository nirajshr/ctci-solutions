template <typename T>
class Node {
  public:
    Node (T const& value) : next(0), val(value) {}
    void appendToTail(T const& value) {
      Node<T>* end = new Node<T>(value);

      Node<T>* n = this;
      while (n->next) {
        n = n->next;
      }
      n->next = end;
    }

    Node* next;
    T val;
};

template <typename T>
class Stack {
  public:
    Stack() : top(0) {}
    ~Stack() {
      while(top) {
        Node<T>* temp = top->next;
        delete top;
        top = temp;
      }
    }

    bool empty() {
      return !top;
    }

    T peek() {
      return top->val;
    }

    T pop() {
      T val = top->val;
      Node<T>* next = top->next;
      delete top;
      top = next;
      return val;
    }

    void push(T const& value) {
      Node<T>* temp = top;

      top = new Node<T>(value);
      top->next = temp;
    }

  private:
    Node<T>* top;
};

template <typename T>
class Queue {
  public:
    Queue() : first(0), last(0) {}

  private:
    Node<T>* first;
    Node<T>* last;
};
