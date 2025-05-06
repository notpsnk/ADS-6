// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* link;

    explicit Node(const T& val) {
      data = val;
      link = nullptr;
    }
  };

  Node* first = nullptr;

 public:
  TPQueue() {}

  ~TPQueue() {
    Node* walker = first;
    while (walker != nullptr) {
      Node* garbage = walker;
      walker = walker->link;
      delete garbage;
    }
  }

  void push(const T& item) {
    Node* unit = new Node(item);

    if (!first || item.prior > first->data.prior) {
      unit->link = first;
      return;
    }

    Node* scout = first;
    while (scout->link && scout->link->data.prior >= item.prior) {
      scout = scout->link;
    }

    unit->link = scout->link;
    scout->link = unit;
  }

  T pop() {
    if (first == nullptr)
      throw std::runtime_error("Queue is empty");

    Node* temp = first;
    T result = temp->data;
    first = first->link;
    delete temp;
    return result;
  }

  bool isEmpty() const {
    return first == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
