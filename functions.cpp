#include <conio.h>
#include "log_in_system.h"

using namespace std;

vector<user>data;




istream &operator>> (stringstream &in, user& x  )
{
    in>>x.id>>x.pasword>>x.Email>>x.Phone;

}

void check_operation(string& number)
{
    //takes the chosen opertaion as a string
    string chosen_opperation;
    //loops through that string
    for (int i = 0; i < number.length(); i++)
    {
        //if i is a digit it is appeanded
        if (isdigit(number[i]))
        {
            chosen_opperation.push_back(number[i]);
        }
    }
    //lenght of the string is not the same anymore it means that it icnulded a letter
    if (chosen_opperation.length() != number.length())
    {
        //ask the user to enter a new chioce
        cout << "Invalid input, please try again: ";
        cin >> number;
        cin.ignore();
        //re-apply the same function
        check_operation(number);
    }
}


void get_data()
{
    // vector<user>data;
    int ctr = 0;
    my_file.open(file_name, ios::in);
    while (getline(my_file , text))
    {
        data.push_back(user());
        ctr++;
    }
    my_file.close();
    my_file.open(file_name, ios::in);

    for (int i=0 ; i<ctr ; i++)
    {
        getline(my_file,text);
        line << text;
        line>>data[i];
        line.str("");
        //line.clear();

    }
    my_file.close();

}

void put_data()
{
    // vector<user>data;
    my_file.close();
    my_file.open(file_name, ios::out);
    for (int i=0 ; i<data.size();i++ )
        my_file<<data[i].id<<" "<<data[i].pasword<<" "<<data[i].Email<<" "<<data[i].Phone<<" "<<endl;

    my_file.close();


}




bool strongPass(string password)
{
    int specialChar=0,lowerChar=0,upperChar=0,digit=0,ctr=0;
    for(auto chr:password)
    {
        ctr++;
        if(isalpha(chr))
        {
            if(islower(chr))
                lowerChar++;

            else
                upperChar++;

        }
        else if(isdigit(chr))
            digit++;

        else
            specialChar++;
    }

    if(ctr <8 || ctr > 30)
        ctr =0;

    return specialChar*digit*upperChar*lowerChar*ctr;
}


string coverPassword()
{
    char c;
    string pass;
    while ((c=_getch()) != 13)
    {

    // put it onto the back of the password
    // output a '*' character
        if ( c =='\b')
        {
            pass.pop_back();
            putch('\b');
            putch(' ');
            putch('\b');
        }
        else
        {

            pass.push_back(c);
            _putch('*');
        }
    }
    return pass;



}

bool valid_phone(string& phone)
{
    regex check("01([0]|[1]|[2]|[5])([0-9]{8})");

    return regex_match(phone, check);
}


bool valid_email(string& email)
{
    regex check("([_]?[a-zA-Z0-9]+[_.]?[a-zA-Z]*[0-9]*[_.]?[a-zA-Z]*[0-9]*)+\\@([a-zA-Z])+\\.(com)");
    return regex_match(email, check);
}

bool valid_UserName(string& username)
{
    regex check("^[a-zA-Z0-9._]{1,30}$");
    return regex_match(username, check);
}

string PassWord()
{
    string pass="",pass2="";
    char c;

    cout<<"\nPlease Enter a Strong Password\nNOTE: a strong password should have one or more of:\n"
        <<"lower-case letters,upper-case letters,numbers, special symbols AND length of [8:30] \n" <<endl<<"enter password :  ";

    while(1)
    {
        pass=coverPassword();
        if (strongPass(pass)==1)
            break;
        cout<<"\nyou entered a weak password try again\n";
        PassWord();
    }
    cout<<"\nconfirm password :  ";
    pass2 = coverPassword();
    if (pass == pass2) return pass;

    return PassWord();

}

void UserData()
{
    // vector<user>data;
    string temp;
    int x = 0;
    data.push_back(user());

    //Taking username
    while(1)
    {
        x=0;
        cout<<"\nTo create a valid username you can only use litters (upper/lower case),( _ ),(.) and numbers";
        cout<<"\nEnter Username: ";
        cin>>temp;
        for(int i =0 ; i<data.size();i++)
        {
            if(temp==data[i].id)
            {
                cout<<"\nOps!! this username is already taken,try a new one"<<endl;
                UserData();

                x=1;
                break;
            }

        }
        if (x == 1)
            continue;

        if(valid_UserName(temp)==0)
        {
            cout<<"\nthis user is in invalid form";

            continue;
        }
        break;
    }

    data[data.size()-1].id=temp;



    //Taking user's Email
    while(1)
    {

        x=0;
        cout<<"\nEnter your E-Mail: ";
        cin>>temp;
        for(int i =0 ; i<data.size();i++)
        {
            if(temp==data[i].Email)
            {
                cout<<"\nThis E-Mail address is already used";

                x=1;
                break;
            }
        }
        if (x==1)
            continue;
        if(valid_email(temp)==0)
        {
            cout<<"\nthis Email is in invalid form";
            continue;
        }
        break;
    }
    data[data.size()-1].Email=temp;


    //Taking user's phone number
    while(1)
    {
        cout<<endl<<"enter a phone number starting with (010) or (011) or (012) or (015) followed by (8)digits \nno parentheses, hyphens, dots, or spaces are allowed : ";
        cin>>temp;

        if(valid_phone(temp)==0)
        {
            cout<<"this number is incorrect";
            continue;
        }
        break;
    }

    data[data.size()-1].Phone=temp;


    //PASSWORD
    temp=PassWord();
    for (int i=0 ; i<temp.size();i++ ) temp[i]+=(2*i);
    data[data.size()-1].pasword=temp;


}

void login()
{
    char c;
    string tempId , tempPass;
    int x=0;

    cout<<"\nPlease enter your username: ";
    cin>>tempId;
    bool flag =false;

    for(int i =0 ; i<data.size();i++)
    {

        if(tempId==data[i].id)
        {
            flag = true;
            cout<<"\nPlease enter your Password: ";
            tempPass = coverPassword() ;
            for (int i=0 ; i<tempPass.size();i++ ) tempPass[i]+=(2*i);

            if(tempPass==data[i].pasword)
            {

                cout<<"\nSuccessful login, Welcome Back "<< tempId<<endl;
            }
            else
            {
                cout<<"\nFailed login. Try again!"<<endl;
                login();
            }

        }


    }

    if(!flag)
    {
        cout<<"\nThis username is not found maybe you need to register "<<endl;

    }

}

void change_password()
{
    char c;
    string tempId , tempPass ,newPass;
    int x=0;

    cout<<"\nPlease enter your username: ";
    cin>>tempId;
    bool flag = false;
    for(int i =0 ; i<data.size();i++)
    {

        if(tempId==data[i].id)
        {
            flag = true;
            cout<<"\nPlease enter your OLd Password: ";
            tempPass = coverPassword();
            for (int j=0 ; j<tempPass.size();j++ ) tempPass[j]+=(2*j);

            if(tempPass==data[i].pasword)
            {

               newPass = PassWord();
                for (int j=0 ; j<newPass.size();j++ ) newPass[j]+=(2*j);
               data[i].pasword=newPass;
            }
            else
            {
                cout<<"\nYour old password is wrong , Try again!"<<endl;
                change_password();
            }
        }


    }

    if(!flag)
    {
        cout<<"\nThis username is not found maybe you need to register "<<endl;

    }


}
