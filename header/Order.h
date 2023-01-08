#include <iostream>
#include <ctime>
// #include "CoffeeList.h" //depend on this header
using namespace std;

fstream receipt;
fstream history;
fstream userHistory;

int counts = 0;

struct Purchase
{
    int found;
    string name;
    float price;
    int amount;
    string user;
    int exist;
    Purchase *next, *prev;
};

struct Receipt
{
    int n;
    Purchase *head, *tail;
};

Receipt *createEmptyReceipt()
{
    Receipt *r = new Receipt;
    r->n = 0;
    r->head = NULL;
    r->tail = NULL;
    return r;
}

void storeReceipt(Receipt *r)
{
    Purchase *tmp;
    tmp = r->head;

    receipt.open("file/receipt.txt", ios::out);
    while (tmp != NULL)
    {
        receipt << tmp->name << " " << tmp->price << " " << tmp->amount << "\n";
        tmp = tmp->next;
    }
    receipt.close();
}

void addReceipt(Receipt *r, string newName, float newPrice, int newAmount, string newUser)
{
    Purchase *p = new Purchase;
    p->name = newName;
    p->price = newPrice;
    p->amount = newAmount;
    p->user = newUser;
    p->exist = 0;
    p->next = NULL;
    p->prev = NULL;

    if (r->n == 0)
    {
        r->head = p;
        r->tail = p;
    }
    else
    {
        r->tail->next = p;
        p->prev = r->tail;
        r->tail = p;
    }
    r->n = r->n + 1;
}

float Total(Receipt *r)
{
    Purchase *tmp = r->head;
    float coffeePrice = 0, sumCoffee = 0, total = 0;

    while (tmp != NULL)
    {
        coffeePrice = tmp->price * tmp->amount;
        sumCoffee = sumCoffee + coffeePrice;
        total = total + coffeePrice;
        tmp = tmp->next;
    }
    return total;
}

void storeHistory(Receipt *r)
{
    Purchase *tmp;
    time_t now = time(0);
    char *dt = ctime(&now);
    tmp = r->head;

    receipt.open("file/history.txt", ios::app);
    receipt << "User: " << tmp->user << endl;
    receipt << dt;
    receipt << "=======================================\n";
    receipt << " Name\t\t\tPrice\tAmount\n";
    receipt << "=======================================\n";
    while (tmp != NULL)
    {
        receipt << " " << tmp->name << "   "
                << "\t\t$" << tmp->price << "\t" << tmp->amount << "\n";
        tmp = tmp->next;
    }
    receipt << "=======================================\n";
    receipt << "\t\t\tTotal:\t$" << Total(r) << endl;
    receipt << endl;
    receipt.close();
    counts = counts + 1;
}

void displayReceipt(Receipt *r)
{
    Purchase *tmp;
    float total = Total(r);
    tmp = r->head;

    cout << "=======================================\n";
    cout << " Name\t\t\tPrice\tAmount\n";
    cout << "=======================================\n";
    while (tmp != NULL)
    {
        cout << " " << tmp->name << "   "
             << "\t\t$" << tmp->price << "\t" << tmp->amount << "\n";
        sleep(1);
        tmp = tmp->next;
    }
    cout << "=======================================\n";
    cout << " \t\t\tTotal:\t$" << total;
}

Purchase check_product(List *ls, int selected_id)
{
    Coffee *tmp;
    int found = 0;
    string name;
    float price;
    tmp = ls->head;

    while (tmp != NULL)
    {
        if (tmp->ID == selected_id)
        {
            name = tmp->name;
            price = tmp->price;
            found = 1;
            break;
        }
        tmp = tmp->next;
    }
    Purchase result = {found, name, price};
    return result;
}

bool check_amount(int selected_amount)
{
    if (selected_amount < 0)
    {
        cout << ">> Invalid Amount\n";
        return false;
    }
    else
    {
        return true;
    }
}

string check_name(List *ls, int selected_id)
{
    Coffee *tmp = ls->head;
    string drink;
    while (tmp != NULL)
    {
        if (tmp->ID == selected_id)
        {
            drink = tmp->name;
            break;
        }
        tmp = tmp->next;
    }
    return drink;
}

int check_purchase(Receipt *r, List *ls, int selected_id)
{
    Purchase *tmp = r->head;
    int found = 0;
    string drink = check_name(ls, selected_id);
    while (tmp != NULL)
    {
        if (tmp->name == drink)
        {
            tmp->exist = 1;
            found = 1;
            break;
        }
        else
        {
            tmp->exist = 0;
            found = 0;
        }
        tmp = tmp->next;
    }
    return found;
}

void add_purchase(Receipt *r, int selected_amount)
{
    Purchase *tmp = r->head;
    while (tmp != NULL)
    {
        if (tmp->exist == 1)
        {
            tmp->amount = tmp->amount + selected_amount;
            break;
        }
        tmp = tmp->next;
    }
}

void add_amount(List *ls, int selected_id, int selected_amount)
{
    Coffee *tmp;
    tmp = ls->head;

    while (tmp != NULL)
    {
        if (tmp->ID == selected_id)
        {
            tmp->amount = tmp->amount + selected_amount;
            break;
        }
        tmp = tmp->next;
    }
}

void show_history()
{
    string line;
    history.open("file/history.txt", ios::in);
    if (history.is_open())
    {
        while (getline(history, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File not open" << endl;
        exit(1);
    }
    history.close();
}

// void order(List *ls, Receipt *r, string user)
// {
//     Purchase p;
//     int selected_id, selected_amount;
//     cout<<"\nSelect drink via ID: "; cin>>selected_id;
//     p = check_product(ls, selected_id);
//     if (p.found == 1) {
//         cout<<"Please select an amount: "; cin>>selected_amount;
//         add_amount(ls, selected_id, selected_amount);
//     } else {
//         cout<<"This ID does not exist" << endl;
//     }
//     addReceipt(r, p.name, p.price, selected_amount, user);
//     StoreList(ls);
// }

// Old order function just keeping it just in case
// if (p.found == 1)
// {
//     cout << "Please select an amount: ";
//     cin >> selected_amount;
//     check_a = check_amount(selected_amount);
//     while (check_a==false) {
//         cout << "\nPlease select an amount: ";
//         cin >> selected_amount;
//         check_a = check_amount(selected_amount);
//     }
//     if (selected_amount==0) {
//         loop=1;
//     }
//     if (check_p==1) {
//         add_purchase(r, selected_amount);
//         loop=0;
//     }
//     else {
//         add_amount(kafeList, selected_id, selected_amount);
//         loop=0;
//     }
// } else {
//     cout << "This ID does not exist" << endl;
//     loop=0;
// }