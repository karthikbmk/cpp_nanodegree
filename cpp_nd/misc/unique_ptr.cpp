#include <iostream>
#include <memory>

using namespace std;

class A
{
    public:
        void display()
        {
            cout << "Hello Putty\n";
        }

};

int main()
{
    unique_ptr<A> ptr_1(new A);
    ptr_1->display();

    cout << "ptr_1 addr " << ptr_1.get() << "\n";

    unique_ptr<A> ptr_2 = move(ptr_1);

    cout << "ptr_1 addr " << ptr_1.get() << "\n";
    cout << "ptr_2 addr " << ptr_2.get() << "\n";

    unique_ptr<A> ptr_3 = move(ptr_2);

    cout << "ptr_1 addr " << ptr_1.get() << "\n";
    cout << "ptr_2 addr " << ptr_2.get() << "\n";
    cout << "ptr_3 addr " << ptr_3.get() << "\n";

}

