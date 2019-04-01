# CS-201 Portfolio Project
## iMovieSearch
### Mason Mcvicker

## Getting Started
1. Clone the repository: `git clone https://github.com/MasonMcV/portfolio.git`

1. Download the data file: `wget https://datasets.imdbws.com/title.basics.tsv.gz && gunzip title.basics.tsv.gz`

1. Make the project
```
mkdir build
cd build
cmake ..
make
./iMovieSearch
```
## Using iMovieSearch
* Enter name when prompted
    * This will be the name of the file
* When loaded, a search dialog will appear - This is the main screen
    * search for any movie and suggested titles will appear
    * Press up and down arrows to select the desired movie
    * Press enter to add to your movie Journal
* A window will pop up and ask for medium and date.
    * Medium and Date are whatever was last used, but can be changed
    * Press tab to change between Medium and Date
    * Enter to Accept and add to journal
    * Delete to cancel and return to search
* If Accepted, the screen will now show your journal!
    * Press arrow keys to scroll through
    * Enter to edit the Medium and Date
    * Delete to remove the Movie
    * Tab to go back to search and add more movies
* At any time press ESC to exit the program