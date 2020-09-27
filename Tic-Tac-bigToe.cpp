#include <iostream>
#include <string>
#include <vector>

//Here we declare the functions that i will define further down.
//these functions are tied to the gameplay loop
void DisplayGrid();
void InputAndExec();
void PlayerSwitch();
int WinConditionCheck();

//These are the main functions between games.
void GamePvP();
void GamePvE();
void MainMenu();

//The reason i went with global variables was to limit the amount of calls, and passing variables to functions and getting...
//the right return variables. Only the important variables are global.
std::vector<char> grid { '1','2','3','4','5','6','7','8','9' };

char players[2] { 'X', 'O' };
int playerIndex = 1;


int main()
{
    //Greeting when first running the application
    std::cout << "Welcome to Tic-Tac-(Big)Toe \n";
    MainMenu();
    return 0;
}

void MainMenu()
{
    int answer = NULL;
    std::cout << "What would you like to play? \n";
    std::cout << " 1 : Player VS Player \n" << " 2 : Player VS Computer \n \n" << " 8 : Exit Game \n";
    std::cout << "Select a gamemode : ";
    std::cin >> answer;

    //here we do the corresponding code execution based on what the user typed in. 

    // I wanted to avoid using a while loop here, because of the thought that it would be a loop, in a loop, in a loop... for ever. 
    // So instead i just kept to Functions executions.
    // I don't know for sure whether this is the best solution or not, but it works! :D 


    switch (answer)
    {
    case 0:
        //I have to include cin.clear and cin.ignore before calling MainMenu() again, to stop it from looping forever.
        system("CLS");
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        MainMenu();
        break;
    case 1:
        GamePvP();
        break;
    case 2:
        GamePvE();
        break;
    case 8:
        std::cout << "Closing Game";
        return;
    default:
        //I have to include cin.clear and cin.ignore before calling MainMenu() again, to stop it from looping forever.
        system("CLS");
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        MainMenu();
        break;
    }
}

int moves = 0;
void GamePvP()
{
    playerIndex = 0;
    bool GameOver = false;
    moves = 0;
    //The reason why i fill out the grid here, is because everytime the game restarts...
    //I need to make sure its a new grid. so it clears the board from the last game.
    grid = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    do
    {
        //as the functions says it displays the grid. 
        DisplayGrid();
        
        //This is for getting input, aswell as 
        InputAndExec();
        
        //Here i run the Win Condition function and store the result of that test in my X variable. 
        //Then we proceed to check weather that the winner was either X or O. 
        int x = WinConditionCheck();
        if (x == 0 || x == 1)
        {
            //The reason for Display Grid is just to update the display so you could see where the
            //Where the winning connections were!
            DisplayGrid();
            std::cout << "\nPlayer " << players[x] << " wins! Congrats! \n";
            GameOver = true;
            system("pause");
        }
        //I keep a count of the total amount of moves. and if the total number of moves is 9, and wincheck returns false. then it has to be a tie.
        else if (moves == 9)
        {
            //Tie
            DisplayGrid();
            std::cout << "\n [- TIE -] \n";
            GameOver = true;
            system("pause");
        }
    } while (!GameOver);
    
    //Clears screen and returns to Main Menu
    system("CLS");
    MainMenu();
}

void GamePvE()
{
    playerIndex = 0;
    bool GameOver = false;
    moves = 0;

    system("CLS");
    MainMenu();
}

//Game Loop functions
void DisplayGrid()
{
    system("CLS");
    for (auto x = 0; x < grid.size(); x++)
    {
        std::cout << "| " << grid.at(x) << " ";
        if (x == 2 || x == 5 || x == 8)
        {
            std::cout << "|" << std::endl;
        }
        
    }
}
void InputAndExec()
{
    //The reason for this being a long long int, is because i kept getting build errors because i was doing a arithmetic overflow warning
    //So i then "upgraded" to this to remove that error.
    long long int playerInput = 0;
    std::cout << "[" << players[playerIndex] << "] turn : ";
    
    //Gets input from console and store the answer in the playerInput variable
    
    std::cin >> playerInput;
    
    if (playerInput-1 <= 8 && playerInput-1 >= 0)
    {
        if (grid.at(playerInput-1) == 'X' || grid.at(playerInput-1) == 'O')
        {
            std::cout << "Invalid selection, you cannot select a place that has already been taken! \n";
            InputAndExec();
            return;
        }
        else
        {
            grid[playerInput-1] = players[playerIndex];
            moves++;
            PlayerSwitch();
            return;
        }
    }
    else // This else is to catch any input that isn't an integer. then repeat.
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Choose a number from the grid above! \n";
    }
}
int WinConditionCheck()
{

    //Here im just creating a variable that checks for winner, and then returns the player index number...
    //which corresponds with a char in players[].
    char winner = 'Ø';
    
    char a, b, c;

    //Horizontal
    for (long int i = 1; i <= 7; i+=3)
    {
        // These variables are temp just for storing values so the if statement further down stays relativly clean and easy to debug.
        a = grid.at(i);
        b = grid.at(i-1);
        c = grid.at(i+1);
        //What these variables check store is what is in the grid at the spesific point. They only hold that info based on the current iteration.

        //This if statement then checks weather or not they are all the same, it doesn't matter if its X or O. Aslong as all of them are the same...
        //it then continues to the next check
        if (a == b && b == c)
        {
            //Here we grab the character value of the winning row, then we do a check as to who won. then return a int value.
            //This int value that is returned, corresponds with the index of the players[], where X = 0, and O = 1. 
            winner = grid.at(i);
            if (winner == 'X')
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    
    //Vertical win check
    for (long int i = 0; i < 3; i++)
    {
        //Here i grab a the current iterator and add the required grid locations to make a check. 
        //im just using a, b and c because it really doesn't require to be that spesific. These are temp variables that...
        //have a single purpose, which is to check weather or not they are the same. 

        a = grid.at(i);
        b = grid.at(i + 3);
        c = grid.at(i + 6);

        //This if statement just checks that all the temp variables are the same, and by that we can determine that we have a winner.
        //Since the temp varibles are set to check the one beneath another, this then checks the colum for a win condition.
        if (a == b && b == c)
        {
            //Here we grab the character value of the winning row, then we do a check as to who won. then return a int value.
            //This int value that is returned, corresponds with the index of the players[], where X = 0, and O = 1. 
            winner = grid.at(i);
            if (winner == 'X')
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }

    //For the diagonal checks, all i have to do, since there are only two options. i will hardcode those checks. 
    //The reason for that is because of time, i could most likly come up with a clever solution, however it would end up taking way longer..
    //Than simply writing it out. This is only Tic-Tac-Toe. 
    
#pragma region DiagonalChecks

    //Diagonal Check 1
    a = grid.at(2);
    b = grid.at(4);
    c = grid.at(6);
    std::cout << a << b << c;

    if (a == b && b == c)
    {
        //Same as before, we grab the variable at a this time, and return the correct index in players[].
        winner = b;
        if (winner == 'X')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    //Diagonal Check 2
    a = grid.at(0);
    b = grid.at(4);
    c = grid.at(8);
    if (a == b && b == c)
    {
        //Same as before, we grab the variable at a this time, and return the correct index in players[]. 
        winner = b;
        if (winner == 'X')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    
#pragma endregion


    return 2;
}
void PlayerSwitch()
{
    //This function just inverts the player index. I think there is a better and prettier way to do this, however this will do for now.
    //Its not pretty, but i added an easter-egg incase something went horribly wrong! 
    switch (playerIndex)
    {
    case 0 : 
        playerIndex = 1;
        break;
    case 1 :
        playerIndex = 0;
        break;
    default:
        std::cout << "WTF just happened, im just gonna try something\n";
        playerIndex = 0;
        break;
    }
}