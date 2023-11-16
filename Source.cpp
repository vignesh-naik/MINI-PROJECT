#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

class Film {
public:
    string title;
    string director;

    Film(string t, string d) {
        title = t;
        director = d;
    }
};

class Movie : public Film {
public:
    double rating;
    double year;
    int code;
    static int c;

    Movie(string t, string d, double r, double y) : Film(t, d) {
        rating = r;
        year = y;
        code = c++;
    }
};

int Movie::c = 0;


class MovieDatabase
{
public:
    vector<Movie> movies;
    vector<Movie> watchlist;
    void loadFromFile(string filename)
    {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, director, yearStr, ratingStr;
            double year;
            double rating;
            getline(ss, title, ',');
            getline(ss, director, ',');
            getline(ss, yearStr, ',');
            try {
                year = stod(yearStr);
            }
            catch (...) {
                continue;
            }
            getline(ss, ratingStr, ',');
            try {
                rating = stod(ratingStr);
            }
            catch (...) {
                continue;
            }
            movies.push_back(Movie(title, director, rating, year));
        }
    }
};
class person
{
public:
    string name;
    string email_id;
};
class user: public person, public MovieDatabase
{
    //empty no content
};
int main()
{
    user db;
    db.loadFromFile("movies.csv");
    cout << "\t\t*** WELCOME TO MOVIE WATCHLIST CREATOR *****\t\t" << "\n\n" ;
    cout << "Please Enter your name : ";
    cin.ignore();
    getline(cin, db.name, '\n');
    cout << "Enter your Email ID : ";
    cin.ignore();
    getline(cin, db.email_id, '\n');

    int option;
    do
    {
        cout << "Enter 0 to End the program.\n";
        cout << "Enter 1 to display the list of movies.\n";
        cout << "Enter 2 to apply filters to the list.\n";
        cout << "Enter 3 to enter movies in the watchlist.\n";
        cout << "Enter 4 to display your watchist.\n";
        cout << "Enter 5 to mail your watchlist to yourself.\n";
        cout << "Enter 6 to mail your watchlist to your friend.\n";
        cout << "Enter your option : ";
        cin >> option;
        if(option == 0)
        {
            cout << "\t\t***** ADIOS AMIGOS *****\t\t\n";
            return 0;
        }
        else if(option == 1)
        {
            cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(15) << "RATING" << " |" << endl;
            for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
            {
                cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(15) << i->rating << " |" << endl;
            }
        }
        else if(option == 2)
        {
            int option1;
            do
            {
                cout << "Enter 0 to get out of apply filters mode.\n";
                cout << "Enter 1 to apply filter on rating.\n";
                cout << "Enter 2 to Search a particular title.\n";
                cout << "Enter 3 to Explore movies by a specific director.\n";
                cout << "Enter 4 to apply filter on year of release.\n";
                cout << "Enter your option : ";
                cin >> option1;
                cin.ignore();
                if(option1 == 0)
                {
                    cout << "\n\n";
                    break;
                }
                if(option1 == 1)
                {
                    double rate;
                    cout << "Enter the minimum rating of movies you want : ";
                    cin >> rate;
                    cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(15) << "RATING" << " |" << endl;
                    for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
                    {
                        if(i->rating >= rate)
                            cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(15) << i->rating << " |" << endl;
                        else
                            continue;
                    }
                }
                else if(option1 == 2)
                {
                    string title;
                    cout << "Enter Title of movie you want : ";
                    getline(cin, title, '\n');
                    cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(15) << "RATING" << " |" << endl;
                    int flag = 0;
                    for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
                    {

                        if(i->title == title)
                        {
                            cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(15) << i->rating << " |" << endl;
                            flag = 1;
                        }
                        else
                            continue;
                    }
                    if(flag == 0)
                        cout << "Movie title not found.\n";
                }
                else if(option1 == 3)
                {
                    string director;
                    cout << "Enter director's name : ";
                    getline(cin, director, '\n');
                    cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(35) << "DIRECTOR" << " |" << endl;
                    int flag = 0;
                    for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
                    {
                        if(i->director == director)
                        {
                            cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(35) << i->director << " |" << endl;
                            flag = 1;
                        }
                        else
                            continue;
                    }
                    if(flag == 0)
                        cout << "Director not found.\n";
                }
                else if(option1 == 4)
                {
                    double year;
                    cout << "Enter the year of release of movies you want : ";
                    cin >> year;
                    cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(15) << "YEAR" << " |" << endl;
                    for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
                    {
                        if(i->year >= year)
                            cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(15) << i->year << " |" << endl;
                        else
                            continue;
                    }
                }
            }
            while(option1 > 0 || option1 < 4);
        }
        else if(option == 3)
        {
            vector<int> movieCodes;
            cout << "Enter movie codes (press Ctrl+D to finish):" << endl;
            int code;
            while (cin >> code)
            {
                movieCodes.push_back(code);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for(int code : movieCodes)
            {
               for (vector<Movie>::iterator i = db.movies.begin(); i != db.movies.end(); ++i)
                {
                    if(i->code == code)
                        db.watchlist.push_back(*i);
                    else
                        continue;
                }
            }
        }
        else if(option == 4)
        {
            if(db.watchlist.size() == 0)
            {
                cout << "I SEE YOUR WATCHLIST IS EMPTY!\n\n";
                cout << "Enter 3 to add movies to your watchlist.\n\n";
            }
            else
            {
                cout << "\t\t***** YOUR WATCHLIST *****\t\t\n";
                cout << "| " << setw(5) << "CODE" << "| " << setw(75) << "TITLE" << " | " << setw(15) << "RATING" << " |" << endl;
                for (vector<Movie>::iterator i = db.watchlist.begin(); i != db.watchlist.end(); ++i)
                {
                    cout << "| " << setw(5) << i->code << "| " << setw(75) << i->title << " | " << setw(15) << i->rating << " |" << endl;
                }
            }
        }
        else if(option == 5)
        {
            cout << "\t\t*****YOUR WATCHLIST IS MAILED TO YOU SUCCESSFULLY *****\t\t\n\n";
        }
        else if(option == 6)
        {
            person recipient;
            cout << "Enter your friends name : ";
            cin.ignore();
            getline(cin, recipient.name, '\n');
            cout << "Enter your friends Email ID : ";
            cin.ignore();
            getline(cin, recipient.email_id, '\n');
            cout << "\t\t***** YOUR WATCHLIST IS MAILED TO " << recipient.name << " *****\t\t\n\n";
        }
    }
    while(option > 0 || option < 6);
    return 0;
}
