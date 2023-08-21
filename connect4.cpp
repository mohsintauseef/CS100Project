// Connect4_1.0.cpp: This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

const int rows=6, columns=7;
int counter=1;
bool gamewin= false,gamedraw=false;

void createNewBoard(char board[rows][columns])
{
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<columns;j++)
        {
            board[i][j]='*';
        }
    }
}

void createOldBoard( char board[rows][columns])
{
    ifstream myfile;
    myfile.open("Project.txt");

    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<columns;j++)
        {
            myfile>>board[i][j];
        }
    }
    myfile.close();
}

void displayBoard(char board[rows][columns])
{
    cout<<endl;
    cout<<setw(55)<<"-1-2-3-4-5-6-7-"<<endl;
    for (int i=0;i<rows;i++)
    {
        cout<<setw(40)<<"|";
        for(int j=0;j<columns;j++)
        {
            cout<<setw(2)<<board[i][j];
        }
        cout<<setw(2)<<"|"<<endl;
    }
    cout<<endl;
}

void storeBoard(char board[rows][columns])
{
    ofstream myfile;
    myfile.open("Project.txt");

    for (int i=0;i<rows;i++)
    {

        for(int j=0;j<columns;j++)
        {
            myfile<<board[i][j];
        }
        myfile<<endl;
    }
    myfile<<endl;
    myfile.close();
}

void checkForWinner (char board[rows][columns])
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            if(board[i][j]==board[i+1][j] && board[i+1][j]==board[i+2][j] && board[i+2][j]==board[i+3][j])
            {
                if (board[i][j]!='*' && board[i+1][j]!='*' && board[i+2][j]!='*' && board[i+3][j]!='*')
                {
                    gamewin=true;
                }
            }
            if(board[i][j]==board[i][j+1] && board[i][j+1]==board[i][j+2] && board[i][j+2]==board[i][j+3])
            {
                if (board[i][j]!='*' && board[i][j+1]!='*' && board[i][j+2]!='*' && board[i][j+3]!='*')
                {
                    gamewin=true;
                }
            }
            if(board[i][j]==board[i+1][j+1] && board[i+1][j+1]==board[i+2][j+2] && board[i+2][j+2]==board[i+3][j+3])
            {
                if (board[i][j]!='*' && board[i+1][j+1]!='*' && board[i+2][j+2]!='*' && board[i+3][j+3]!='*')
                {
                    gamewin=true;
                }
            }
            if(board[i][j]==board[i+1][j-1] && board[i+1][j-1]==board[i+2][j-2] && board[i+2][j-2]==board[i+3][j-3])
            {
                if (board[i][j]!='*' && board[i+1][j-1]!='*' && board[i+2][j-2]!='*' && board[i+3][j-3]!='*')
                {
                    gamewin=true;
                }
            }

        }
    }
}

void intro(char board[rows][columns], string &p1,string &p2)
{
    int input=-1;
    cout<<setw(60)<<" W E L C O M E  T O  C O N N E C T 4\n"<<endl;
    cout<<"The rules of the game are the followinng: \n"<<endl;
    cout<<"1. Players must connect 4 of the same symbols in a sequence to win."<<endl;
    cout<<"2. Players alternate in turns."<<endl;
    cout<<"3. Players will input a number to choose a column  and the symbol will be placed in the bottom most available slot of that column. "<<endl;
    cout<<"4. The game ends when there is a sequence of 4 (diagonal, vertical or horizontal) or a stalemate.\n"<<endl;
    system("pause");
     
    cout<<"Player One please enter your name: ";
    getline(cin,p1);
    cout<<"Player Two please enter your name: ";
    getline(cin,p2);

    choice: cout<<endl<<"Would you like to continue the previous game ?\nPress 1 if you want to continue previous game.\nPress 2 if you want to start new game.\nChoose Option: ";
    cin>>input;
    if(input==1)
    {
        createOldBoard(board);
        checkForWinner(board);
        for (int i=0;i<rows;i++)
        {
            for (int j=0;j<columns;j++)
            {
                if(board[i][j]!='*')
                {
                    counter++;
                }
            }
        }
        if (counter>=42)
        {
            gamedraw=true;
        }
        
    }
    else if ( input==2)
    {
        createNewBoard(board);
    }
    else if(cin.fail() || input<1 || input>2)
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Please enter either 1 or 2."<<endl;
        goto choice;
    }
}

void playerOneTurn(char board[rows][columns], string p1)
{
    int count=0,currentcolumn=-1;
    point: cout<<"Player One please choose a column number between 1 and 7: ";
    cin>>currentcolumn;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Please enter a number."<<endl;
        goto point;
    }
    if(currentcolumn<1 || currentcolumn>7)
    {
        cout<<"Column number is out of range please try another number."<<endl;
        goto point;
    }
    while(count==0)
    {
        for (int i=5;i>=0;i--)
        {
            if(board[i][currentcolumn-1]=='*')
            {
                board[i][currentcolumn-1]='X';
                ++count;
                i=-1;
            }
        }
        if (count==0)
        {
            cout<<"Column is full please try a different column"<<endl;
            cout<<"Player One please choose a column number between 1 and 7: ";
            cin>>currentcolumn;
        }
    }
    counter=counter+1;
    checkForWinner(board);
    storeBoard(board);
}

void playerTwoTurn(char board[rows][columns], string p2)
{
    int count=0,currentcolumn=-1;
    point: cout<<"Player Two please choose a column number between 1 and 7: ";
    cin>>currentcolumn;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Please enter a number."<<endl;
        goto point;
    }
    if(currentcolumn<1 || currentcolumn>7)
    {
        cout<<"Column number is out of range please try another number."<<endl;
        goto point;
    }
    while(count==0)
    {
        for (int i=5;i>=0;i--)
        {
            if(board[i][currentcolumn-1]=='*')
            {
                board[i][currentcolumn-1]='O';
                ++count;
                i=-1;
            }
        }
        if (count==0)
        {
            cout<<"Column is full please try a different column"<<endl;
            cout<<"Player Two please choose a column number between 1 and 7: ";
            cin>>currentcolumn;
        }
    }
    counter=counter+1;
    checkForWinner(board);
    if(counter>=42)
    {
        gamedraw=true;
    }
    storeBoard(board);
}


int main()
{
    string p1="", p2="";
    char board[rows][columns];
    intro(board,p1,p2);
    if(gamewin || gamedraw)
    {
        displayBoard(board);
        cout<<"Sorry! The previous game had already finished."<<endl;
        goto end;
    }
    displayBoard(board);
    cout<<"\nPlayer One your symbol is X."<<endl;
    cout<<"Player Two your symbol is O."<<endl;
    

    while(!gamewin && !gamedraw)
    {
        if(counter%2 != 0 && !gamewin && !gamedraw)
        {
            playerOneTurn(board,p1);
            displayBoard(board);
        }
        else if(counter%2==0 && !gamewin && !gamedraw)
        {
            playerTwoTurn(board,p2);
            displayBoard(board);
        }
    }
    
    if(gamewin && counter%2==0)
    {   
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        cout<<setw(80)<<"!! Congratulations to "<<p1<<" for beating "<<p2<<" in connect 4.!!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    } 
    else if(gamewin && counter%2!=0)
    {
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        cout<<setw(80)<<"!! Congratulations to "<<p2<<" for beating "<<p1<<" in connect 4.!!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    }

    if(!gamewin && gamedraw)
    {
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        cout<<setw(80)<<"!! "<<p1<<" and "<<p2<<" were too well matched and the game ended in a draw.!!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    }
    
    end: return 0;
}
