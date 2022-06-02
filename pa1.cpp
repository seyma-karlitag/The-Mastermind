#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

bool control_e0(char* argv); //Function that checks for negative numbers and non-digit expressions for -r
bool control_e1(int size,char* argv); //function that checks whether a number greater or less than the size of the number is entered
bool control_e2(char* argv); //The function that checks the function so that no expressions other than numbers are entered
bool rand_cont(int rand_num,int arr[],int size); //Check function for secret digits to be different from each other
int game_fonk(int arr[],int size,int argc,char* argv) ; //Function that contains the entered values ​​of the control functions and prints the control parameters.

//-------------------------------------//
//-------Main Menu---------------------//
//-------------------------------------//

int main(int argc,char* argv[])
{
   //defining parameters
   int digit;
   int rand_num;
   int lngth,size;
   int arr[10];
   bool flag;
   char* arg_v;

   srand(time(NULL));

   flag = control_e0(argv[argc-1]); //Function that checks for negative numbers and non-digit expressions for -r

//Checking situations such as missing parameter entry, wrong parameter entry.

if((argc != 3) || !((argv[1][0]=='-' && argv[1][1]=='r') || (argv[1][0]=='-' && argv[1][1]=='u')))  
{
            cout << "E0" << endl;
            exit(1);
         
}

//If the -r parameter is entered, the game is terminated if the next parameter is not entered between 1 and 9

if((argv[1][0]=='-' && argv[1][1]=='r') && (flag))
{
   cout << "E0" << endl;
   exit(1);
}

bool e2=true;

e2=control_e2(argv[argc-1]); //The function that checks the function so that no expressions other than numbers are entered

//If an expression other than a positive number is entered, the program is terminated.

if((argv[1][0]=='-' && argv[1][1]=='u') && !e2 )
{
   cout << "E0" << endl;
   exit(1);
}

if( argv[1][0]=='-' && argv[1][1]=='r')
{
   
   //If -r is entered as a parameter, the entered value is converted to an integer.

    digit = stoi(argv[argc-1]);
    int i=0;
    
    //The first index of the array is randomly assigned a number between 1 and 9

       arr[i] = rand()%9 +1;
       
       //If digit is not 1, i is incremented.

       if(digit != 1)
       {
          i++;
       }

    while(i)
    {
       //rand_num A number between 0 and 9 is randomly assigned
       rand_num = rand() % 9;
       bool flag_1=true;

       //With rand_fonk the previous indexes are checked and if they are not the same as
       // rand_num they are assigned to the index and i is incremented
       flag_1 = rand_cont(rand_num,arr,i-1);
       if(flag_1)
       {
          arr[i] = rand_num;
          i++;
       }
       
       //When i digit is equal, the assignment is stopped and the loop is exited.

       if(i == digit) i=0;
      
      }

    }
       


if(argv[1][0]=='-' && argv[1][1]=='u')
{
   //After all the checks, the value entered after the -u parameter 
   //is converted to a string and the string size is taken.

    string pass = argv[argc-1];
    lngth=pass.length();

    //an error message is printed if the size of the entered value is greater than 9 digits

    if(lngth > 9 ) 
    {
       cout << "E0" << endl;
       exit(1);
    } 
    
    //The received value is converted to an integer and secret_num is assigned.

    int secret_num = stoi(argv[argc-1]);
   
   //If secret_num is 0, error message is written
    if(secret_num == 0)
    {
       cout << "E0" << endl;
       exit(1);
    }
    
    //The last digit of secret_num starts to be indexed according to the number of digits. 
    //The index of the array decreases until the first digit of secret_num.

    for(int j=lngth-1; j>=0; j--)
    {
       arr[j] = secret_num % 10;
       secret_num = secret_num  / 10;
    }

    //If there is more than one of the same number in the entered value, the error message is printed and the program is exited.

    for(int j=0; j<lngth; j++)
    {
       for(int k=j+1; k<lngth; k++)
       {
           if(arr[j] == arr[k])
           {
              cout << "E0" << endl;
              exit(1);
           }

       }
    }

}

//If -u or -r is entered, I assign you to determine the limit of the array.

if( argv[1][0]=='-' && argv[1][1]=='r')  size = digit;
else if(argv[1][0]=='-' && argv[1][1]=='u') size =lngth; 

////defining parameters
bool game=true;
int counter=0;
int found=0;

//The value is taken from the user and if a positive integer value is not 
//entered with the e2_contol function, the error message is written and the program is exited.

cin >>arg_v;
e2 = control_e2(arg_v);

if(!e2)
{
   cout << "E2" << endl;
   exit(1);
}
 while(game)
 {
     //Function that contains the entered values ​​of the control functions and prints the control parameters.
     //it takes the digit value in the right place and when it is equal 
     //to you the program is considered finished
     
     found = game_fonk(arr,size,1,arg_v);
     counter++;

     //The game is ended if the user did not find the correct number after 100 entries

     if(counter == 100 ) 
     {
         if(found<size)
         {
            cout << "FAILED" <<endl;
            game = false;
            exit(1);
         }
     }

     //when you enter the correct number, found is written on the screen and the game is ended.

     else if(found == size && counter<100)
     {
        cout << endl << "FOUND  " << counter << endl;
        game=false;
        exit(1);
     }

     //The value is taken from the user and if a positive integer value is not 
    //entered with the e2_contol function, the error message is written and the program is exited.

     cin >>arg_v;
     e2 = control_e2(arg_v);
    if(!e2)
    {  
         cout << "E2" << endl;
         exit(1);
    }

     
 }
 
  return 0;

}
bool control_e0(char* argv)
{
     bool flag=true;
     string pass = argv;
     int length =pass.length();
    
    //checks that the entered value is not negative and 0 is not entered

    for(int i=0;i<length;i++)
       {

          if((!(pass[0]=='-' && pass[i+1]>'0' && pass[i+1]<='9'&& i<length-1)) ) 

          flag=true;
          if(!(pass[0]>'0' && pass[0]<='9' && length==1))
          flag=true;
         else
         flag=false;
       } 
    
  return flag;
    
}
bool control_e1(int size,char* argv)
{
   //The size of the entered value is checked, if it is not equal, 
   //an error message is printed and the program is exited.
   bool flag=true;
   string pass = argv;
   int length =pass.length();
   if(size!=length) flag=false;

  return flag;
}
bool control_e2(char* argv)
{
   bool flag=true;
   string pass = argv;
   int length =pass.length();
   
   //Control of an expression different from the number in the entered value is provided. 
   //If there is an expression other than a different number, 
   //the error message is written and the program is exited.

   for(int i=0; i<length ; i++)
   {
      if(!(pass[i]>='0' && pass[i]<='9'))
      
         flag = false;
   }
   return flag;
}
bool rand_cont(int rand_num,int arr[],int size)
{
   bool flag=true;

   //It checks the previous indexes and returns false if the same number exists.

   for(int i=size; i>=0 ; i--)
   {
       if(rand_num == arr[i]) 
       {
          flag=false;
       }

   }
   return flag;
}
int game_fonk(int arr[],int size,int argc,char* argv)   
{
    bool flag=true;
    int found=0;
    int num;
    int gamer[size];
    int count_x=0,count_y=0;

    //digit number is checked
    flag = control_e1(size,argv);
    if(!flag)
    {
       cout << "E1" << endl;
       exit(1);
    }
    
    //convert to integer
    num = stoi(argv);
    
    //digits assigned to array indexes

    for(int i=size-1; i>=0 ; i--)
    {
       gamer[i] = num % 10;
       num = num / 10;
    }

    //If the user numbers do not enter different values, an error message is written and the program is exited.
    for(int j=0; j<size; j++)
    {
       for(int k=j+1; k<size; k++)
       {
           if(gamer[j] == gamer[k])
           {
              cout << "E0" << endl;
              exit(1);
           }

       }
    }
    

    //the indexes are compared, if the number is in the right place, conut_x is increased. 
    //If there is a number, but the place is not correct, count_y is increased.

         for(int a=0 ; a<size; a++)
        {
         
           for(int b=0; b<size; b++ )
           {
                if(arr[a] == gamer[b])
                {
                    if(a == b) count_x++;
                    else count_y++;
                }
            }
        }
    
        found = count_x;

        //hints are printed on the screen
        cout << count_x << "  ";
        cout << count_y<<endl ;
    
    //found is returned
    return found;

}