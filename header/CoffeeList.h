#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

int newID = 0;
string line;
fstream coffeelist;

struct Coffee
{
    int ID;
    string name;
    float price;
    int amount;
    Coffee *next, *prev;
};

struct List
{
    int n;
    Coffee *head, *tail;
};

List *createEmptyList()
{
    List *ls;
    ls = new List;

    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;

    return ls;
}

void StoreList(List *ls)
{
    Coffee *tmp;
    tmp = ls->head;

    coffeelist.open("file/coffeelist.txt", ios::out);
    while (tmp != NULL)
    {
        coffeelist << tmp->ID << " " << tmp->name << " " << tmp->price << " " << tmp->amount << "\n";
        tmp = tmp->next;
    }
    coffeelist.close();
}

void insertList(List *ls, string newName, float newPrice)
{
    Coffee *c;
    c = new Coffee;
    c->name = newName;
    c->price = newPrice;
    c->ID = ls->n + 1;
    c->next = NULL;
    c->prev = NULL;

    if (ls->n == 0)
    {
        ls->head = c;
        ls->tail = c;
    }
    else
    {
        ls->tail->next = c;
        c->prev = ls->tail;
        ls->tail = c;
    }
    ls->n = ls->n + 1;
    StoreList(ls);
}

void ChangeName(List *ls, string search_name, string newName)
{
    Coffee *t;
    t = ls->head;

    while (t != NULL)
    {
        if (t->name == search_name)
        {
            t->name = newName;
            break;
        }
        t = t->next;
    }
    StoreList(ls);
}

void ChangePricebyName(List *ls, string search_name, float newPrice)
{
    Coffee *t;
    t = ls->head;

    while (t != NULL)
    {
        if (t->name == search_name)
        {
            t->price = newPrice;
            break;
        }
        t = t->next;
    }
    StoreList(ls);
}

void ChangeNameAndPrice(List *ls, string search_name, string newName, float newPrice)
{
    Coffee *t;
    t = ls->head;

    while (t != NULL)
    {
        if (t->name == search_name)
        {
            t->name = newName;
            t->price = newPrice;
            break;
        }
        t = t->next;
    }
    StoreList(ls);
}

int Search_Name(List *ls, string search_name)
{
    Coffee *tmp;
    int found;
    tmp = ls->head;

    while (tmp != NULL)
    {
        if (tmp->name == search_name)
        {
            found = 1;
            break;
        }
        else
        {
            found = 0;
        }
    }
    return found;
}

void DisplayCoffeeList(List *ls)
{
    Coffee *tmp;
    tmp = ls->head;

    pre(3); cout << "=========================================\n";   
    pre(3); cout << "   ID\tName\t\t\tPrice\n";   
    pre(3); cout << "=========================================\n";
    while (tmp != NULL)
    {
        pre(3); cout << "   " << tmp->ID << "\t" << tmp->name << "   "
                     << "\t\t$" << tmp->price << "\n";
        usleep(100000);
        tmp = tmp->next;
    }
    pre(3); cout << "=========================================\n";
}

void readFile(List *ls)
{
    Coffee *tmp;
    int file_id, file_amount;
    string file_name;
    float file_price;
    coffeelist.open("file/coffeelist.txt", ios::in);
    if (coffeelist.is_open())
    {
        while (coffeelist >> file_id >> file_name >> file_price >> file_amount)
        { // this read data and after white-space it count as another data
            tmp = new Coffee;
            tmp->ID = file_id;
            tmp->name = file_name;
            tmp->price = file_price;
            tmp->amount = file_amount;

            if (ls->n == 0)
            {
                ls->head = tmp;
                ls->tail = tmp;
            }
            else
            {
                ls->tail->next = tmp;
                tmp->prev = ls->tail;
                ls->tail = tmp;
            }
            ls->n = ls->n + 1;
        }
    }
    else
    {
        cout << "File not open\n";
        exit(1);
    }
    coffeelist.close();
}

void deleteByName(List *ls, string search_name)
{
    int found = 0;
    Coffee *tmp1, *tmp, *tmp2, *reset_id;
    tmp = ls->head;

    while (tmp != NULL)
    {
        if (tmp->name == search_name)
        { // Only One
            if (tmp->prev == NULL && tmp->next == NULL)
            {
                ls->tail = NULL;
                ls->head = NULL;
                delete tmp;
                ls->n = ls->n - 1;
                break;
            }
            if (tmp->prev == NULL)
            { // At Head
                reset_id = tmp->next;
                ls->head = tmp->next;
                ls->head->prev = NULL;
                found = 1;
                break;
            }
            if (tmp->next == NULL)
            { // At the Tail
                reset_id = tmp;
                ls->tail = tmp->prev;
                ls->tail->next = NULL;
                found = 1;
                break;
            }
            if (tmp->prev != NULL && tmp->next != NULL)
            { // In between
                reset_id = tmp->next;
                tmp1 = tmp->prev;
                tmp2 = tmp->next;
                tmp1->next = tmp2;
                tmp2->prev = tmp1;
                found = 1;
                break;
            }
        }
        tmp = tmp->next;
    }

    // Reset the ID value
    if (found == 1)
    {
        while (reset_id != NULL)
        {
            reset_id->ID = reset_id->ID - 1;
            reset_id = reset_id->next;
        }
        delete tmp;
        ls->n = ls->n - 1;
        StoreList(ls);
    }
}

void bestSeller(List *ls)
{
    int size = ls->n;
    Coffee *tmp = ls->head;

    Coffee *cArr[size];
    for (int i = 0; i < size; i++)
    {
        cArr[i] = tmp;
        tmp = tmp->next;
    }
    for (int u = 0; u < size; u++)
    {
        for (int k = u + 1; k < size; k++)
        {
            if (cArr[u]->amount < cArr[k]->amount)
            {
                Coffee *hold = cArr[u];
                cArr[u] = cArr[k];
                cArr[k] = hold;
            }
            else
            {
                continue;
            }
        }
    }
    for (int z = 0; z < size; z++)
    {
        cout << z + 1 << "\t" << cArr[z]->name << "   \t\t$" << cArr[z]->price << "\t\t" << cArr[z]->amount << endl;
    }
}