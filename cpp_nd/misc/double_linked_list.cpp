#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::string;

namespace custom
{
    template <typename T>
    class list
    {
        private:
            struct node
            {
                T value;
                node *next = nullptr;
                node *prev = nullptr;;
                node(T val)
                {
                    value = val;
                }
            };
            int size = 0;
        public:
            node * head;
            node * tail;
            list()
            {
                head = nullptr;
                tail = nullptr;
            }
            ~list();
            void push_front(T val);
            void push_back(T val);
            T pop_front();
            T pop_back();
            bool isEmpty() const {return (head == nullptr || tail == nullptr);}
            void display();

    };


    template <typename T>
    list <T>::~list()
    {
        node *tmp;
        while(head != nullptr)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    
    template <typename T>
    void list<T>::push_front(T val)
    {
        node *tmp_node = new node(val);

        if (isEmpty())
        {
            head = tmp_node;
            tail = tmp_node;
        }
        else
        {
            tmp_node->next = head;
            head->prev = tmp_node;
            head = tmp_node;
        }
        size += 1;
        
    }

    template <typename T>
    void list<T>::push_back(T val)
    {
        node * tmp = new node(val);
        if (isEmpty())
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tmp->prev = tail;
            tail  = tail->next;
        }
        size -= 1;
    }

    template <typename T>
    void list<T>::display()
    {
        node * tmp = head;
        while(tmp)
        {
            cout << tmp->value << " ";
            tmp = tmp->next;
        }
        cout << "\n";
    }

    template <typename T>
    T list<T>::pop_front()
    {
        T val = -99999;
        if(isEmpty())
        {
            throw ("List is empty");
        }
        else
        {
            val = head->value;
            node *tmp = head;

            //if only 1 node, set both head and tail to nullptr
            if (head->next == nullptr)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                head = head->next;
                head->prev = nullptr;
            }

            tmp->next = nullptr;
            tmp->prev = nullptr;

            delete tmp;
            size -= 1;
        }
        return val;
    }

    template<typename T>
    T list<T>::pop_back()
    {   T val;
        if(isEmpty())
        {
            throw("list alread empty. can't delete");
        }
        else
        {
            val = tail->value;
            node *tmp = tail;
            if (size == 1)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                tail = tail->prev;
                tail->next = nullptr;
            }

            tmp->next = nullptr;
            tmp->prev = nullptr;
            delete tmp;
            size -= 1;
        }        
        return val;
    }

}

int main ()
{
    custom::list<int> dll;
    dll.push_front(1);
    dll.push_front(2);
    dll.push_front(3);
    
    dll.push_back(99);
    dll.push_front(4);
    dll.push_back(100);

    dll.display();
    for(int i =0 ; i < 2; i++)
        dll.pop_front();    
    dll.display();

    dll.pop_back();
    dll.display();
}
