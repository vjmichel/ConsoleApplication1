//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

/// draft

class BullsAndCowsGame
{
public:
    BullsAndCowsGame(const int n) : m_number( vector<int>(4,0))
    {
        if (n > 9999 || n < 1000)
        {
            ostringstream msg;
            msg << "The secret number must have 4 digits and no leading zero's: " << n;
            throw std::exception( msg.str().c_str() );
        }
        m_number = convert4DigitIntToVec(n);
        play();
    }
private:
    vector<int> m_number; // num4Digits
    std::map<vector<int>, std::pair<int, int> > m_mapGuessToReport;

    //--------------------------------------------------------------------
    vector<int> convert4DigitIntToVec( int n ) const
    {
        vector<int> result(4, 0);
        result[0] = n / 1000 % 10;
        result[1] = n / 100 % 10;
        result[2] = n / 10 % 10;
        result[3] = n % 10;
        return result;
    }

    //--------------------------------------------------------------------
    void play()
    {
        const int max = 100;
        vector<int> g;
        int i;
        bool guessedRight = false;
        for (i = 0; i < max; ++i)
        {
            g = doComputerGuess();
            bool guessedRight = doHumanReport(g);
            if (guessedRight)
                break;
        }
        if (guessedRight)
            cout << "Computer guessed the secret number in " << i << " guesses." << endl;
        else
            cout << "Computer gives up after " << i << " guesses." << endl;
    }
    
    //--------------------------------------------------------------------
    // return true if the guess is right, otherwise add result to map
    bool doHumanReport(const vector<int>& g)
    {
        int nBulls = 0; // A “bull” is a digit that is on the right position
        int nCows  = 0; // A “cow” is a correct digit that is in the wrong position
        vector<bool> bulls  = { false, false, false, false };
        vector<bool> cows   = { false, false, false, false };

        // bulls
        int i;
        for ( i = 0; i < 4; ++i )
        {
            if (g[i] == m_number[i])
            {
                ++nBulls;
                bulls[i] = true;
            }
        }
        //cows
        for (i = 0; i < 4; ++i)
        {
            if (bulls[i] == false)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (g[i] == m_number[j] && cows[j] == false)
                    {
                        ++nCows;
                        cows[j] == true;
                        break;
                    }
                }
            }
        }

        m_mapGuessToReport[g] = make_pair(nBulls, nCows);

        cout << "Bulls: " << nBulls << ", cows: " << nCows << endl;
        return (nBulls == 4);
    }

    //--------------------------------------------------------------------
    vector<int> doComputerGuess() const
    {
        vector<int> g(4, 0);

        // brute force
        for (int i = 1000; i < 9999; ++i)
        {
            g = convert4DigitIntToVec(i);
        }

        cout << "Computer guess ";
        for (int i = 0; i < 4; ++i ) 
            cout << g[i];
        cout << endl;

        return g;
    }
};


//--------------------------------------------------------------------
int main()
{
    try {
        BullsAndCowsGame game1( 1234 );
        BullsAndCowsGame game2( 234 );
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

	return 0;
}

