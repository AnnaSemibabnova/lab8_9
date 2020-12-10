#include <iostream>
#include <cmath>

using namespace std;
template<class A2>
class Node
{
public:
  Node() :next(nullptr){}
  A2 value;
  Node* next;
};

template<class A1>
class List
{
public:
  List() :head(nullptr),tail(nullptr), size(0) {}
  
  List(List& lhs)
  {
    if (lhs.head == nullptr) throw logic_error("empty list");
    size = lhs.size;
    head = new Node<A1>;
    Node<A1>* tmp = head;
    Node<A1>* ptr = lhs.head;
    for (int i = 1; i < size; i++)
    {
      tmp->next = new Node<A1>;
      tmp = tmp->next;
    }
    tmp = head;
    for (int i = 0; i < size; i++)
    {
      tail = tmp;
      tmp->value = ptr->value;
      ptr = ptr->next;
      tmp = tmp->next;
    }
  }
  List(List&& lhs)
  {
    head = move(lhs.head);
    size = lhs.size;
    lhs.head = nullptr;
    tail = lhs.tail;
    lhs.tail = nullptr;
    lhs.size = 0;
  }
  ~List()
  {
    if (!(*this).IsEmpty()) {
      Node<A1>*tmp = head;

      while (tmp->next != nullptr)
      {
        tmp = tmp->next;
        delete head;
        head = tmp;
      }
    }
  }
  List& operator =(List&& lhs)
  {
    this->head = move(lhs.head);
    this->tail = move(lhs.tail);
    this->size = lhs.size;
    lhs.head = nullptr;
    lhs.tail = nullptr;
    lhs.size = 0;
    return this;
  }
  bool IsEmpty()
  {
    return(head == nullptr);
  }
  int GetSize()
  {
    return size;
  }
  void push_back(const A1& lhs)
  {
    if (!(*this).IsEmpty()) {
      tail->next = new Node<A1>;
      tail->next->value = lhs;
      tail->next->next = nullptr;
      tail = tail->next;
    }
    else
    {
      head = new Node<A1>;
      head->value = lhs;
      head->next = nullptr;
      tail = head;
    }
    size++;
  }

  void push_in_order(const A1& lhs)
  {
    if (!(*this).IsEmpty()) {
      Node<A1>*tmp = head;
      while ((tmp->next != nullptr)&&(tmp->next->value>lhs))
      {
        tmp = tmp->next;
      }
      this->push_after(tmp,lhs);
    }
    else
    {
      head = new Node<A1>;
      head->value = lhs;
      head->next = nullptr;
      tail = head;
    }
    size++;
  }
  void push_front(const A1& lhs)
  {
    Node<A1>* tmp = new Node<A1>;
    tmp->value = lhs;
    tmp->next = head;
    head = tmp;
    size++;
  }
  A1& pop_front()
  {
    if (head == nullptr) throw logic_error("container is empty");
    Node<A1>* tmp = head->next;
    A1 tm = head->value;
    delete head;
    size--;
    head = tmp;
    return tm;
  }
  A1& pop_back()
  {
    if ((*this).IsEmpty()) throw logic_error("container is empty");
    Node<A1>*tmp = head;

    while ((head->next)->next != nullptr)
    {
      head = head->next;
    }
    A1 tmp1 = head->next->value;
    delete head->next;
    head->next = nullptr;
    tail = head;
    head = tmp;
    size--;
    return tmp1;

  }
  List<A1> GCD(const A1& lhs)
  {
    int Size = this->GetSize();
    List<A1>tmp1;
    Node<A1>*tmp = head;

    for(int i=0;i<Size;i++)
    {
      if (lhs % (head->value) == 0) {
        tmp1.push_front(head->value);
      }
      head = head->next;
    }
    head = tmp;
    return tmp1;
  }
  A1& pop(Node<A1>* prev)
  {
    if (prev->next == nullptr) throw logic_error("last_element");
    Node<A1>* del = prev->next;
    Node<A1>* last = del->next;
    A1 ret = del->value;
    delete del;
    prev->next = last;
    size--;
    return ret;

  }
  void push_after(Node<A1>* prev,const A1& data)
  {
    if (prev == nullptr) throw logic_error("nullptr");
    if(prev==head)
    {
      if (data > head->value) {
        this->push_front(data);
      }
      else
      {
        this->push_back(data);
      }
      return;
    }
    Node<A1>*next_after_prev = prev->next;
    prev->next = new Node<A1>;
    prev->next->value = data;
    prev->next->next = next_after_prev;
  }
  void reverse()
  {
    if ((*this).IsEmpty()) throw logic_error("list is empty");
    int Size = this->GetSize();
    Node<A1>*ls = head;
    for(int i=1;i<Size;i++)
    {
      A1 tmp = (*this).pop(ls);
      (*this).push_front(tmp);
    }
    
  }
  void Sort()
  {
    if ((*this).IsEmpty()) throw logic_error("list is empty");
    List<A1>res;
    Node<A1> min;
    Node<A1>* newhead = new Node<A1>;
    newhead->next = head;
    head = newhead;
    min.value = head->next->value;
    min.next = head;
    Node<A1>* t = head;
    while (!(head->next==nullptr))
    {
      Node<A1>* t = head;
      min.value = head->next->value;
      min.next = head;
      for (int i = 0; i < size; i++) {
        
        if (t->next->value < min.value)
        {
          min.value = t->next->value;
          min.next = t;
        }
        t = t->next;
      }
      (*this).pop(min.next);
      res.push_front(min.value);
    }
    delete (*this).head;
    (*this).head = res.head;
    res.head = nullptr;
    size = res.size;
  }
  template<class A1>
  friend ostream& operator<<(ostream& out, List<A1>& lhs)
  {
    Node<A1>*tmp = lhs.head;
    while (tmp->next != nullptr)
    {
      out << tmp->value << "->";
      tmp = tmp->next;
    }
    cout << tmp->value << "\n";
    return out;
  }
private:
  Node<A1>* head;
  Node<A1>* tail;
  int size;
};