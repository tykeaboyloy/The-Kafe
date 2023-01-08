#ifndef STYLE_H_INCLUDED
#define STYLE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<iomanip>
using namespace std;
//   Style for main
  /*void ccolor(int clr){

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, clr);

//the above code displays colorful background. if you want colorful then you can remove the above comment but not the code, only comment//
}
*/

//   Style for main

void change_color(int style, int color) {
    cout << "\033["<<style<<";"<<color<<"m";
}

void resetcolor() {
    cout << "\033[0m\n";
}

void cls(){
	system("clear");
}

void loadingbar(void){

	for (int i=0;i<=100;i+=5){

		cls();


		cout<<"\n\n\n\n\n\n\n\t\t\t\t";
		cout<<i<<"%% Loading...\n\n\t\t";
		cout<<"";

		for (int j=0; j<i;j+=2){

		//	ccolor(160+j);
			//printf(" ");
			cout<<" ";
		//	ccolor(26);

		}
		usleep(100000);
		if(i==90 || i==50 || i==96 || i==83){
			usleep(100000);
		}

	}

}

void middle1(void){

	cout<<"\n\n\n\n\n\n\n";
}

void middtab1(void){
	cout<<"\t\t\t\t\t";
}
void intro()

{
    cout << "\n\n\n";
    usleep(100000);
    cout << "\t\t * * *  **** *      ****  ***   ***   ****   " << endl;
    usleep(100000);
    cout << "\t\t * * * *     *     *     *   * * * * *        "<< endl;
    usleep(100000);
    cout << "\t\t * * * ***** *     *     *   * * * * *****    " << endl;
    usleep(100000);
    cout << "\t\t * * * *     *     *     *   * * * * *         " << endl;
    usleep(100000);
    cout << "\t\t  ***   **** *****  ****  ***  * * *  ****     " << endl;
    usleep(100000);
    cout<<endl;
    cout<<"\t\t=============================================\n"<<endl;
    usleep(500000);
    cout<<"\t\t   THIS IS COFFEE SHOP MANEGEMENT SYSTEM \n"<<endl;
    usleep(500000);
    cout<<"\t\t============================================="<<endl;
    usleep(500000);
    cout << "\n\n";
    cout<<"\t\t press any key to continue...";
    //cin.ignore();
    cin.get();
}

// End style
void br(int line){
	for(int i=0; i<line;i++){
		cout << "\n";
	}
}

void pre(int tab){

	for(int i=0; i<tab;i++){
		cout << "\t";
	}

}
void span(int space){

	for(int i=0; i<space;i++){
	  cout << "\t";
	}

}
//  funtion main-menu
int main_menu(){
    int opt;
    cls();
    cout<<"\n\n";
    cout<<"   ========================== Welcome to a Kafé =========================="<<endl;
	br(2); pre(3); cout<<">> 1. Login as a customer:"; usleep(100000);
	br(2); pre(3); cout<<">> 2. Login as admin"; usleep(100000);
	br(2); pre(3); cout<<">> 3. Sign up";  usleep(100000);
	br(2); pre(3); cout<<">> 4. Exit";  usleep(100000);
	br(3);
	cout<<"   ======================================================================="<<endl;
	br(2); cout<<">> Please select: "; cin>>opt;
	br(1);
	return opt;
}

#endif // STYLE_H_INCLUDED