#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

fstream adminlist;
struct Admin
{
    string name;
    string password;
    int age;
    Admin *next, *prev;
};

struct AdminList
{
    int n;
    Admin *head, *tail;
};

AdminList *createEmptyAdminList()
{
    AdminList *adls = new AdminList;

    adls->n = 0;
    adls->head = NULL;
    adls->tail = NULL;
    return adls;
}
void readAdmin(AdminList *list)
{
    Admin *admin;
    string name;
    string password;
    int age;
    adminlist.open("file/adminList.txt", ios::in);
    if (adminlist.is_open())
    {
        while (adminlist >> name >> password >> age)
        {
            admin = new Admin;
            admin->name = name;
            admin->password = password;
            admin->age = age;
            if (list->n == 0)
            {
                list->head = admin;
                list->tail = admin;
            }
            else
            {
                list->tail->next = admin;
                admin->prev = list->tail;
                list->tail = admin;
            }
            list->n = list->n + 1;
        }
    }
    else
    {
        cout << "File not open\n";
        exit(1);
    }
    adminlist.close();
}

void StoreAdmin(AdminList *ls)
{
    Admin *tmp;
    tmp = ls->head;

    adminlist.open("file/adminList.txt", ios::out);
    while (tmp != NULL)
    {
        adminlist << tmp->name << " " << tmp->password << " " << tmp->age << "\n";
        tmp = tmp->next;
    }
    adminlist.close();
}

void insertAdmin(AdminList *list, string name, string password, int age)
{
    Admin *admin = new Admin;
    admin->name = name;
    admin->password = password;
    admin->next = NULL;
    admin->prev = NULL;
    admin->age = age;

    if (list->n == 0)
    {
        list->head = admin;
        list->tail = admin;
    }
    else
    {
        list->tail->next = admin;
        admin->prev = list->tail;
        list->tail = admin;
    }
    list->n = list->n + 1;
    StoreAdmin(list);
}
string encryptionAdmin(string password)
{
    for (int i = 0; i < password.length(); i++)
    {
        password[i] = int(password[i]) + 2;
    }
    return password;
}

void signupAdmin(AdminList *list, string name, string password, string cPassword, int age)
{
    if (password == cPassword)
    {
        password = encryptionAdmin(password);
        insertAdmin(list, name, password, age);
        cout << "\n>> Sign up successful." << endl;
        sleep(1);
    }
    else
    {
        cout << "\n>> Password does not match." << endl;
        sleep(1);
    }
}
void displayAdminList(AdminList *list)
{
    cout << "=======================Admin=====================" << endl;
    cout << "Name"
         << "\t\t\t\t\t\t"
         << "Age" << endl;
    Admin *tmp = list->head;
    while (tmp != NULL)
    {
        cout << tmp->name << "\t\t\t\t\t\t" << tmp->age << endl;
        tmp = tmp->next;
    }
    cout << "=================================================" << endl;
}
void deleteAdmin(AdminList *ls, string search_name, string password)
{
    int found = 0;
    Admin *tmp1, *tmp, *tmp2;
    tmp = ls->head;

    while (tmp != NULL)
    {
        if (tmp->name == search_name && tmp->password == encryption(password))
        { // At the Start
            if (tmp->prev == NULL)
            {
                ls->head = tmp->next;
                delete tmp;
                ls->n = ls->n - 1;
                found = 1;
                break;
            }
            else if (tmp->next == NULL)
            { // At the Tail
                ls->tail = tmp->prev;
                ls->tail->next = NULL;
                delete tmp;
                ls->n = ls->n - 1;
                found = 1;
                break;
            }
            else
            { // In between
                tmp1 = tmp->prev;
                tmp2 = tmp->next;
                tmp1->next = tmp2;
                tmp2->prev = tmp1;
                delete tmp;
                ls->n = ls->n - 1;
                found = 1;
                break;
            }
        }
        tmp = tmp->next;
    }

    if (found == 1)
    {
        cout << ">> Delete successful!" << endl;
        sleep(1);
    }
    else
    {
        cout << ">> Information not correct." << endl;
        sleep(1);
    }
    StoreAdmin(ls);
}

string editAdmin(AdminList *ls, int choice, string name)
{
    Admin *tmp = ls->head;
    string confirm, newName, newPass;
    if (choice == 1)
    {
        while (tmp != NULL)
        {
            if (tmp->name == name)
            {
                cout << ">> Enter your new Name: ";
                cin >> newName;
                cout << ">> Please enter your password: ";
                cin >> confirm;
                if (encryptionAdmin(confirm) == tmp->password)
                {
                    tmp->name = newName;
                    StoreAdmin(ls);
                    cout << "\n>> Edit successful" << endl;
                    sleep(1);
                    break;
                }
                else
                {
                    cout << "\n>> Password is incorrect";
                    break;
                }
            }
            tmp = tmp->next;
        }
    }
    else if (choice == 2)
    {
        newName = name;
        while (tmp != NULL)
        {
            if (tmp->name == name)
            {
                cout << ">> Please enter your old password: ";
                cin >> confirm;
                cout << ">> Please enter your new password: ";
                cin >> newPass;
                if (encryptionAdmin(confirm) == tmp->password)
                {
                    tmp->password = encryptionAdmin(newPass);
                    StoreAdmin(ls);
                    cout << ">> Edit successful" << endl;
                    sleep(1);
                    break;
                }
                else
                {
                    cout << ">> Password is incorrect" << endl;
                    break;
                }
            }
            tmp = tmp->next;
        }
    }
    return newName;
}

void editAdminByOther(AdminList *ls, int choice, string name)
{
    Admin *tmp = ls->head;
    string newName, newPass;
    if (choice == 1)
    {
        while (tmp != NULL)
        {
            if (tmp->name == name)
            {
                cout << ">> Enter your new name: ";
                cin >> newName;
                tmp->name = newName;
                StoreAdmin(ls);
                cout << ">> Edit successful" << endl;
                sleep(1);
                break;
            }
            tmp = tmp->next;
        }
    }
    if (choice == 2)
    {
        while (tmp != NULL)
        {
            if (tmp->name == name)
            {
                cout << ">> Please enter your new password: ";
                cin >> newPass;
                tmp->password = encryptionAdmin(newPass);
                StoreAdmin(ls);
                cout << ">> Edit successful" << endl;
                sleep(1);
                break;
            }
            tmp = tmp->next;
        }
    }
}

int loginAdmin(AdminList *ls, string name, string password)
{
    Admin *tmp = ls->head;
    int authenticate = 0;
    password = encryptionAdmin(password);
    while (tmp != NULL)
    {
        if (name == tmp->name && password == tmp->password)
        {
            authenticate = 1;
        }
        tmp = tmp->next;
    }
    return authenticate;
}