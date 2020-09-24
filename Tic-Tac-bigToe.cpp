#include <iostream>
#include <string>
#include <vector>

void DisplayGrid();

void InputAndExec();
void PlayerSwitch();
int WinConditionCheck();

std::vector<char> grid { '1','2','3','4','5','6','7','8','9' };

char players[2] = { 'X', 'O' };
int playerIndex = 1;


int main()
{
    do
    {
        DisplayGrid();
        PlayerSwitch();
        /*InputAndExec();
        int x = WinConditionCheck();
        if (x != 2)
        {
            std::cout << "\nPlayer " << players[x] << " wins! Congrats!";

        }
        */
    } while (true);
}

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
    int playerInput = 0;
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
            return;
        }
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Choose a number from the grid above! \n";
    }
}
int WinConditionCheck()
{
    char winner = 'Ø';
    //Horisontal
    for (auto i = 0; i < 7; i+3)
    {
        if (grid.at(i) == grid.at(i + 1) == grid.at(i + 2))
        {
            winner = grid.at(i);
            if (winner == 'X')
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }
    //Vertical win check
    for (auto i = 0; i < 3; i++)
    {
        if (grid.at(i) == grid.at(i + 3) == grid.at(i + 6))
        {
            winner = grid.at(i);
            if (winner == 'X')
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }
    }

    return 2;
}
void PlayerSwitch()
{
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