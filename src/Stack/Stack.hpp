#include <stdexcept>

template <typename T>
class Stack {
protected:
	struct Node {
		T data;
		Node * below;
	};

	Node * top;

public:
	Stack() : top(nullptr) {}

	~Stack() {
		Node * tmp;
		while (top != nullptr) {
      tmp = top;
      top = top->below;
			delete tmp;
		}
	}

	void push(T data) {
    Node * tmp = new Node;
    tmp->data = data;
    tmp->below = nullptr;

    if (top == nullptr) {
      top = tmp;
    } else {
      tmp->below = top;
      top = tmp;
    }
	}

	T getTop() const {
		if (top == nullptr) {
			throw std::out_of_range("Stack is empty");
		} else {
  		return top->data;
    }
	}

	T pull() {
		if (top == nullptr) {
			throw std::out_of_range("Stack is empty");
		} else {
      Node * tmp;
      tmp = top;
      T dataToReturn = tmp->data;
      top = top->below;

      delete tmp;
      return dataToReturn;
    }
  }

  bool isEmpty() {
    if (top == nullptr) {
      return true;
    } else {
      return false;
    }
  }
};