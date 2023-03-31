// FCAI-CU - Structured Programming course - 2022 - Assignment 4
//Program Name : LOGIN system
// Program Description : saves user's data as login systems using a file of txt to save those data
// Author :  Mariam Esmat Ahmed
// ver5 of Date : 21st of May 2022


#include <bits/stdc++.h>
#include <vector>
#include "functions.cpp"
using namespace std;


int main()
{

    while (1)
    {
        get_data();

        cout<<"\n--------------------------------++++-----------------------------";
        cout<<endl;
        cout <<"\nchoose the operation you want"<<endl<<"\n1.Register\n2.Login\n3.Change Password\nPress any other key to quit\n"<<endl;
        cout<<"--------------------------------++++-----------------------------\n";
        string chosen_opperation;
        cin >> chosen_opperation;
        cin.ignore();
        cout << "\n";
        check_operation(chosen_opperation);
        int choice = stoi(chosen_opperation);
        cin.sync();
        cin.clear() ;


            if (choice == 1)
                UserData();

           else  if (choice == 2)
                login();

            else if (choice == 3)
                change_password();

            else
                {
                    cout << "Thank you for using my program :)\n";
                    break;
                }


        put_data();
    }
    return 0;
}
