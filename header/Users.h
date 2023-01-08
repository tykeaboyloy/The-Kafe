#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

fstream Userlist;
struct User
{
    string name;
    string password;
    int orderAmouht;
    User *next, *prev;
};

struct UserList
{
    int n;
    User *head, *tail;
};

UserList *createEmptyUserList()
{
    UserList *UList = new UserList;

    UList->n = 0;
    UList->head = NULL;
    UList->tail = NULL;
    return UList;
}
void readUser(UserList *list)
{
    User *user;
    string name;
    string password;
    int order;
    Userlist.open("file/userList.txt", ios::in);
    if (Userlist.is_open())
    {
        while (Userlist >> name >> password >> order)
        {
            user = new User;
            user->name = name;
            user->password = password;
            user->orderAmouht = order;
            if (list->n == 0)
            {
                list->head = user;
                list->tail = user;
            }
            else
            {
                list->tail->next = user;
                user->prev = list->tail;
                list->tail = user;
            }
            list->n = list->n + 1;
        }
    }
    else
    {
        cout << "File not open\n";
        exit(1);
    }
    Userlist.close();
}

void StoreUser(UserList *ls)
{
    User *tmp;
    tmp = ls->head;

    Userlist.open("file/userList.txt", ios::out);
    while (tmp != NULL)
    {
        Userlist << tmp->name << " " << tmp->password << " " << tmp->orderAmouht << "\n";
        tmp = tmp->next;
    }
    Userlist.close();
}

void insertUser(UserList *list, string name, string password)
{
    User *user = new User;
    user->name = name;
    user->password = password;
    user->next = NULL;
    user->prev = NULL;
    user->orderAmouht = 0;

    if (list->n == 0)
    {
        list->head = user;
        list->tail = user;
    }
    else
    {
        list->tail->next = user;
        user->prev = list->tail;
        list->tail = user;
    }
    list->n = list->n + 1;
    StoreUser(list);
}

string encryption(string password)
{
    for (int i = 0; i < password.length(); i++)
    {
        password[i] = int(password[i]) + 2;
    }
    return password;
}

int signup(UserList *list, string name, string password, string cPassword)
{
    int state;
    if (password == cPassword)
    {
        password = encryption(password);
        insertUser(list, name, password);
        state = 1;
    }
    else
    {
        state = 0;
    }
    return state;
}
void displayUserList(UserList *list)
{
    User *tmp = list->head;
    cout << "================User List=================" << endl;
    cout << "username"
         << "\t\t\t\t"
         << "ordered" << endl;
    while (tmp != NULL)
    {
        cout << tmp->name << "\t\t\t\t\t" << tmp->orderAmouht << endl;
        tmp = tmp->next;
    }
    cout << "==========================================" << endl;
}
void deleteUser(UserList *ls, string search_name)
{
    User *tmp1, *tmp, *tmp2;
    tmp = ls->head;
    while (tmp != NULL)
    {
        if (tmp->name == search_name)
        { // At the Start
            if (tmp->prev == NULL)
            {
                ls->head = tmp->next;
                delete tmp;
                ls->n = ls->n - 1;
                StoreUser(ls);
                cout<<">> Delete successful."<<endl;
                break;
            }
            else if (tmp->next == NULL)
            { // At the Tail
                ls->tail = tmp->prev;
                ls->tail->next = NULL;
                delete tmp;
                ls->n = ls->n - 1;
                StoreUser(ls);
                cout<<">> Delete successful."<<endl;
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
                StoreUser(ls);
                cout<<">> Delete successful."<<endl;
                break;
            }
        }
        tmp = tmp->next;
    }
}
string editUser(UserList *ls, int choice, string name)
{
    User *tmp = ls->head;
    string confirm, newName, newPass;
    if (choice == 1)
    {
        while (tmp != NULL)
        {
            if (tmp->name == name)
            {
                cout << ">> Enter your new name: ";
                cin >> newName;
                cout << ">> Please enter your password: ";
                cin >> confirm;
                if (encryption(confirm) == tmp->password)
                {
                    tmp->name = newName;
                    StoreUser(ls);
                    cout << ">> Edit successful" << endl;
                    sleep(1);
                    break;
                }
                else
                {
                    cout << ">> Password is incorrect";
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
                cout << ">> Please enter your old password:";
                cin >> confirm;
                cout << ">> Please enter your new password:";
                cin >> newPass;
                if (encryption(confirm) == tmp->password)
                {
                    tmp->password = encryption(newPass);
                    StoreUser(ls);
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
void editUserByAdmin(UserList *ls, int choice, string name)
{
    User *tmp = ls->head;
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
                StoreUser(ls);
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
                cout << ">> Please enter the new password: ";
                cin >> newPass;
                tmp->password = encryption(newPass);
                StoreUser(ls);
                cout << ">> Edit successful" << endl;
                sleep(1);
                break;
            }
        }
        tmp = tmp->next;
    }
}

int login(UserList *ls, string name, string password)
{
    User *tmp = ls->head;
    int authenticate = 0;
    password = encryption(password);
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