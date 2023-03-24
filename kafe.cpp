#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "./header/Style.h"
#include "./header/CoffeeList.h"
#include "./header/Users.h"
#include "./header/Admin.h"
#include "./header/Order.h"
using namespace std;
//dfskfsf
int main()
{
    system("clear");
    change_color(0, 32);
    string currentUser;
    int authenticate = 0;
    AdminList *adminList = createEmptyAdminList();
    UserList *userList = createEmptyUserList();
    List *kafeList = createEmptyList();

    readFile(kafeList);
    readUser(userList);
    readAdmin(adminList);
    intro();
    while (authenticate == 0)
    {
        int choice = main_menu();
        system("clear");
        if (choice == 1)
        {
            string name, password;
            pre(3);
            cout << "=============== User Login ===============";
            br(2);
            pre(3);
            cout << "    Please enter name: ";
            cin >> name;
            br(1);
            pre(3);
            cout << "    Please enter password: ";
            cin >> password;
            authenticate = login(userList, name, password);
            if (authenticate == 1)
            {
                br(1);
                pre(3);
                cout << "    logged in" << endl;
                currentUser = name;
                sleep(1);
            }
            else
            {
                br(1);
                pre(3);
                cout << "    Password is not correct." << endl;
                sleep(1);
            }
            while (authenticate == 1)
            {
                system("clear");
                int choose;
                cout << "   ============================= User ============================" << endl;
                br(2);
                pre(3);
                cout << ">> 1. Make an order";
                br(2);
                pre(3);
                cout << ">> 2. Logout";
                br(2);
                pre(3);
                cout << ">> 3. Edit your info";
                br(3);
                cout << "   ===============================================================" << endl;
                br(2);
                cout << ">> Please choose: ";
                cin >> choose;
                switch (choose)
                {
                case 1:
                {
                    Receipt *r = createEmptyReceipt();
                    int opt = 1, choice;
                    while (opt != 0)
                    {
                        // system("clear");
                        // DisplayCoffeeList(kafeList);
                        Purchase p;
                        int selected_id, selected_amount, check_p = 0, loop = 1;
                        bool check_a;
                        while (loop != 0)
                        {
                            system("clear");
                            DisplayCoffeeList(kafeList);
                            cout << "\n>> Select drink via ID: ";
                            cin >> selected_id;
                            p = check_product(kafeList, selected_id);
                            check_p = check_purchase(r, kafeList, selected_id);
                            switch (p.found)
                            {
                            case 1:
                            {
                                cout << ">> Please select an amount: ";
                                cin >> selected_amount;
                                check_a = check_amount(selected_amount);
                                while (!check_a)
                                {
                                    cout << ">> Please select an amount: ";
                                    cin >> selected_amount;
                                    check_a = check_amount(selected_amount);
                                }
                                if (selected_amount == 0)
                                {
                                    loop = 1;
                                    break;
                                }
                                if (check_p == 1)
                                {
                                    add_purchase(r, selected_amount);
                                    add_amount(kafeList, selected_id, selected_amount);
                                    loop = 0;
                                }
                                else
                                {
                                    add_amount(kafeList, selected_id, selected_amount);
                                    loop = 0;
                                }
                                break;
                            }
                            default:
                            {
                                cout << ">> This ID does not exist" << endl;
                                sleep(1);
                                loop = 1;
                                break;
                            }
                            }
                        }
                        if (check_p != 1)
                        {
                            addReceipt(r, p.name, p.price, selected_amount, currentUser);
                            cout << "\n>> Would you like to continue ordering: ";
                            cin >> opt;
                        }
                        else
                        {
                            cout << "\n>> Would you like to continue ordering: ";
                            cin >> opt;
                        }
                    }
                    system("clear");
                    displayReceipt(r);
                    cout << "\n\n>> Please confirm your order: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        StoreList(kafeList);
                        storeReceipt(r);
                        storeHistory(r);
                        cout << "\nThank you for using our service" << endl;
                        cout << "       Have a Nice Day!      " << endl;
                        cout << "\npress any key to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                case 2:
                {
                    authenticate = 0;
                    currentUser = "";
                    break;
                }
                case 3:
                {
                    int stc;

                    system("clear");
                    pre(3);
                    cout << "=============== User Info ===============" << endl;
                    br(2);
                    pre(3);
                    cout << "    What do you want to edit?";
                    br(2);
                    pre(3);
                    cout << "    >> 1.Name";
                    br(2);
                    pre(3);
                    cout << "    >> 2.Password";
                    br(3);
                    pre(3);
                    cout << "=========================================" << endl;
                    br(1);
                    cout << ">> Choose an options: ";
                    cin >> stc;
                    currentUser = editUser(userList, stc, currentUser);
                    break;
                }
                }
            }
        }
        if (choice == 2)
        {
            string name, password;
            pre(3);
            cout << "=============== Admin Login ===============";
            br(2);
            pre(3);
            cout << "  >> Please enter name: ";
            cin >> name;
            br(1);
            pre(3);
            cout << "  >> Please enter password: ";
            cin >> password;
            authenticate = loginAdmin(adminList, name, password);
            if (authenticate == 1)
            {
                br(1);
                pre(3);
                cout << "  >> You are logged in." << endl;
                currentUser = name;
                sleep(1);
            }
            else
            {
                br(1);
                pre(3);
                cout << "  >> Password is not correct." << endl;
                sleep(1);
            }
            while (authenticate == 1)
            {
                system("clear");
                int adminChoice;
                pre(2);
                cout << "================== Admin Panel ==================";
                br(2);
                pre(3);
                cout << ">> 1. Edit your info.";
                br(2);
                pre(3);
                cout << ">> 2. Add another admin account.";
                br(2);
                pre(3);
                cout << ">> 3. Edit admin.";
                br(2);
                pre(3);
                cout << ">> 4. Edit user info.";
                br(2);
                pre(3);
                cout << ">> 5. Edit menu.";
                br(2);
                pre(3);
                cout << ">> 6. Show sale history.";
                br(2);
                pre(3);
                cout << ">> 7. Show best seller.";
                br(2);
                pre(3);
                cout << ">> 8. Logout";
                br(2);
                pre(2);
                cout << "=================================================" << endl;
                br(1);
                cout << ">> Please select: ";
                cin >> adminChoice;
                switch (adminChoice)
                {
                case 1:
                {
                    int stc;
                    system("clear");
                    pre(2);
                    cout << "=============================================";
                    br(2);
                    pre(3);
                    cout << "   What do you want to edit?";
                    br(2);
                    pre(3);
                    cout << "   >> 1.Name";
                    br(2);
                    pre(3);
                    cout << "   >> 2.Password";
                    br(2);
                    pre(2);
                    cout << "=============================================";
                    br(2);
                    cout << ">> Choose an options: ";
                    cin >> stc;
                    currentUser = editAdmin(adminList, stc, currentUser);
                    break;
                }
                case 2:
                {
                    string adminName, adminPassword, adminCPassword;
                    int age;
                    system("clear");
                    pre(2);
                    cout << "=================== Add Admin ===================";
                    br(2);
                    pre(2);
                    cout << "    >> Enter a name: ";
                    cin >> adminName;
                    br(1);
                    pre(2);
                    cout << "    >> Enter your age: ";
                    cin >> age;
                    br(1);
                    pre(2);
                    cout << "    >> Enter a password: ";
                    cin >> adminPassword;
                    br(1);
                    pre(2);
                    cout << "    >> Confirm your password: ";
                    cin >> adminCPassword;
                    signupAdmin(adminList, adminName, adminPassword, adminCPassword, age);
                    break;
                }
                case 3:
                {
                    system("clear");
                    displayAdminList(adminList);
                    int blah = 0;
                    while (blah == 0)
                    {
                        system("clear");
                        displayAdminList(adminList);
                        int z;
                        br(1);
                        cout << "=================== Edit Admin ===================";
                        br(2);
                        cout << "   >> 1. Edit admin info";
                        br(2);
                        cout << "   >> 2. Delete admin";
                        br(2);
                        cout << "   >> 3. Exit";
                        br(2);
                        cout << "==================================================";
                        br(2);
                        cout << ">> Enter function id: ";
                        cin >> z;
                        switch (z)
                        {
                        case 1:
                        {
                            system("clear");
                            displayAdminList(adminList);
                            int k;
                            string adminEdit;
                            br(1);
                            cout << ">> Enter the name of admin you want to edit: ";
                            cin >> adminEdit;
                            cout << "\n=============================================";
                            br(2);
                            pre(1);
                            cout << "What do you want to edit?";
                            br(2);
                            pre(1);
                            cout << "   >> 1. Name";
                            br(2);
                            pre(1);
                            cout << "   >> 2. Password";
                            br(2);
                            cout << "=============================================";
                            br(2);
                            cout << ">> Choose: ";
                            cin >> k;
                            editAdminByOther(adminList, k, adminEdit);
                            break;
                        }
                        case 2:
                        {
                            system("clear");
                            displayAdminList(adminList);
                            string rName, rPassword;
                            br(1);
                            cout << ">> Enter the name: ";
                            cin >> rName;
                            cout << ">> Enter password: ";
                            cin >> rPassword;
                            deleteAdmin(adminList, rName, rPassword);
                            break;
                        }
                        case 3:
                        {
                            blah = 1;
                            break;
                        }
                        }
                    }
                    break;
                }
                case 4:
                {
                    int u = 1;
                    while (u == 1)
                    {
                        system("clear");
                        displayUserList(userList);
                        cout << "\n==========================================";
                        br(2);
                        pre(1);
                        cout << ">> 1. Edit User info";
                        br(1);
                        pre(1);
                        cout << ">> 2. Delete User";
                        br(1);
                        pre(1);
                        cout << ">> 3. exit";
                        br(2);
                        cout << "==========================================";
                        br(2);
                        cout << ">> Choose an options: ";
                        cin >> u;
                        switch (u)
                        {
                        case 1:
                        {
                            int b;
                            string w;
                            system("clear");
                            displayUserList(userList);
                            cout << "\nEnter the name of the user you want to edit: ";
                            cin >> w;
                            cout << "\n==========================================";
                            br(2);
                            pre(1);
                            cout << ">> Choose what you want to edit";
                            br(2);
                            pre(1);
                            cout << ">> 1. Name";
                            br(2);
                            pre(1);
                            cout << ">> 2. Password";
                            br(2);
                            cout << "===========================================";
                            br(2);
                            cout << ">> Please choose an options: ";
                            cin >> b;
                            editUserByAdmin(userList, b, w);
                            break;
                        }
                        case 2:
                        {
                            string deleteName;
                            system("clear");
                            displayUserList(userList);
                            cout << "\n>> Enter the name of the user you want to delete: ";
                            cin >> deleteName;
                            deleteUser(userList, deleteName);
                            u = 1;
                            break;
                        }
                        case 3:
                        {
                            u = 0;
                            break;
                        }
                        }
                    }

                    break;
                }

                case 5:
                {
                    int menu = 1;

                    while (menu != 0)
                    {
                        string name, newName;
                        float price, newPrice;

                        system("clear");
                        DisplayCoffeeList(kafeList);
                        int opt;
                        br(1);
                        pre(2);
                        cout << "      ================= Edit Menu =================";
                        br(2);
                        pre(4);
                        cout << ">> 1. Change Name.";
                        br(2);
                        pre(4);
                        cout << ">> 2. Change Price.";
                        br(2);
                        pre(4);
                        cout << ">> 3. Change Name and Price.";
                        br(2);
                        pre(4);
                        cout << ">> 4. Add New Drink.";
                        br(2);
                        pre(4);
                        cout << ">> 5. Remove Drink.";
                        br(2);
                        pre(4);
                        cout << ">> 6. Return to main menu.";
                        br(2);
                        pre(2);
                        cout << "      ==============================================" << endl;
                        br(1);
                        cout << ">> Please select: ";
                        cin >> opt;

                        switch (opt)
                        {
                        case 1:
                        {
                            cout << "\n>> Change Name" << endl;
                            cout << ">> Enter the name: ";
                            cin >> name;
                            cout << ">> Enter the new name: ";
                            cin >> newName;
                            ChangeName(kafeList, name, newName);
                            break;
                        }
                        case 2:
                        {
                            cout << "\n>> Change Price" << endl;
                            cout << ">> Enter the name: ";
                            cin >> name;
                            cout << ">> Enter the new price: ";
                            cin >> newPrice;
                            ChangePricebyName(kafeList, name, newPrice);
                            break;
                        }
                        case 3:
                        {
                            cout << "\n>> Change Name and Price" << endl;
                            cout << ">> Enter the name: ";
                            cin >> name;
                            cout << ">> Enter the new name: ";
                            cin >> newName;
                            cout << ">> Enter the new price: ";
                            cin >> newPrice;
                            ChangeNameAndPrice(kafeList, name, newName, newPrice);
                            break;
                        }
                        case 4:
                        {
                            cout << "\n>> Add Drink" << endl;
                            cout << ">> Enter drink name: ";
                            cin >> name;
                            cout << ">> Enter drink price: ";
                            cin >> price;
                            insertList(kafeList, name, price);
                            break;
                        }
                        case 5:
                        {
                            cout << "\n>> Remove Drink" << endl;
                            cout << ">> Enter the drink name: ";
                            cin >> name;
                            deleteByName(kafeList, name);
                            break;
                        }

                        case 6:
                        {
                            StoreList(kafeList);
                            menu = 0;

                            break;
                        }
                        }
                    }
                    break;
                }

                case 6:
                {
                    system("clear");
                    br(1);
                    pre(2);
                    cout << "======== Sale History ========\n"
                         << endl;
                    show_history();
                    pre(1);
                    cout << "\npress any key to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

                case 7:
                {
                    system("clear");
                    cout << "===================== Best Seller =====================" << endl;
                    cout << "-------------------------------------------------------\n";
                    cout << "Rank\tName\t\t\tPrice\t\tordered\n";
                    cout << "-------------------------------------------------------\n";
                    bestSeller(kafeList);
                    cout << "\npress any key to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

                case 8:
                {
                    authenticate = 0;
                    currentUser = "";
                    break;
                }
                }
            }
        }
        if (choice == 3)
        {
            string name, password, cPassword;
            pre(3);
            cout << "=============== Registration ===============";
            br(2);
            pre(3);
            cout << ">> Enter your name: ";
            cin >> name;
            br(1);
            pre(3);
            cout << ">> Enter your password: ";
            cin >> password;
            br(1);
            pre(3);
            cout << ">> Please confirm your password: ";
            cin >> cPassword;

            int state = signup(userList, name, password, cPassword);
            if (state == 1)
            {
                br(1);
                pre(3);
                cout << ">> Sign up successful." << endl;
                sleep(1);
            }
            else
            {
                br(1);
                pre(3);
                cout << ">> Password does not match." << endl;
                sleep(1);
            }
        }
        if (choice == 4)
        {
            exit(0);
        }
    }
}