// COMPILE WITH g++/MinGW ONLY!!!
// This is because of ncurses
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include <cstring>
#include <fstream>

#if __has_include(<ncurses.h>)
# include <ncurses.h>
#else
# include <ncurses/ncurses.h>
#endif

int input_nums(const char* str) {
	auto out = std::unique_ptr<unsigned int>(new unsigned int()); // This will be out
	std::cout << str; // Ask what to enter
	while (!(std::cin >> *out)){ // Request correct user input
	// if any illegal char will be entered, it wll ask for it again
	std::cin.clear(); 
	std::cin.ignore(100,'\n');
	}
	// And out
	return *out;
}

int next_gen(std::vector<std::vector<char>> &playSpace, std::vector<std::vector<char>> &next_arr){
	int count_cells = 0; // Alive cells
	for (int i = playSpace.size()-1; i > -1; i--)
		for (int j = playSpace[i].size()-1; j > -1; j--) {
			// Border detection
			bool border[] = {true,true,true,true}; // up, left, down,right

			if (i == 0) border[0] = false; // Upper border
			if (i == playSpace.size()-1) border[2] = false; // Down border

			if (j == 0) border[1] = false; // Left border
			if (j == playSpace[i].size()-1) border[3] = false; // Right border

			// Count neighboring cells
			int count_neighbors = 0;
			for (int k = i - border[0]; k <= i + border[2]; k++)
				for (int l = j - border[1]; l <= j + border[3]; l++)
					if (playSpace[k][l] != ' ') count_neighbors++;

			// RULE IMPLEMENTATION
			// Cell can live for 12 cycles and with 2 or 3 neighbors (+1 to include cell itself)
			if ((count_neighbors == 3 || count_neighbors == 4) && playSpace[i][j] != ' ' && playSpace[i][j] != 'B') {
				if (playSpace[i][j] == '9') next_arr[i][j] = 'A'; // Use 12-digit system to align output
				else next_arr[i][j]++; // Cell aging 
			}
			else next_arr[i][j] = ' '; //else it will die

			if (playSpace[i][j] == ' ' && count_neighbors == 3) //spawn cell if exactly 3 neighbors exist (counter doesnt count cells, so no +1)
				next_arr[i][j] = '1'; 

			if (playSpace[i][j] != ' ') count_cells++; // Sount living cells
		}
	return count_cells; // Return ounter of living cells
}

int print_arr(std::vector<std::vector<char>> &next_arr) {
	auto write_workout = std::unique_ptr<std::ofstream>(new std::ofstream("work.out")); // Write to file
	// For each elemrnt in file, write to it
	// Output to console and file
	for(auto i: next_arr){
		for(auto j:i) {
			addch(j);
			*write_workout << j;
		}
		addch('\n');
		*write_workout << '\n';
	}
	write_workout->close(); // Close file to write to it

	return next_gen(*std::unique_ptr<std::vector<std::vector<char>>>(new std::vector<std::vector<char>> (next_arr)), next_arr); // Return alive cells to save space
}

int main(int argc, char** argv) {	
	// Seed gen
	// used nullptr to have an idea of undefined variable 
	unsigned *seed = nullptr;
	// Scanning command line parameters to find "seed"
	for (int i = 1; i < argc; i++) {
		// if it finds "seed"
		if (!strcmp(argv[i], "seed") && seed == nullptr) {
			// seed gets unsigned type
			seed = new unsigned();
			// and gets a seed from next parameter
			// if not, user will enter it
			if (i == argc - 1 || !(*seed = atoi(argv[i+1]))) *seed = input_nums("Seed (number): "); 
			else break;
			}
		else {
			// if parameter is not set right, user will be promted about how to use commands 
			std::cerr << "Usage: " << argv[0] << " [seed {seed number}]";
			return 0; // and program will be terminated
		}
	}
	if (seed == nullptr) // if seed it unset (launch without command line params) it equals unixtime
		seed = new unsigned(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	std::cout << "Seed: " << *seed << "\n";
	srand(*seed); // Apply and delete seed
	delete seed;

	// generate playing field
	std::vector <std::vector <char>> playSpace (input_nums("Playing space height: "), std::vector<char>( input_nums("Playing space width: "))); 
	std::vector<char> chars(input_nums("Char count: ")); //generate char array

	// generate symbols inside
	for (int i = chars.size()-1; i >= 0; i--)
		chars[i] = 'a' + (rand() % 26);

	char bact = chars[rand() % chars.size()]; //generate bacteria

	std::ofstream write_workdat("work.dat");
	
	// map bacterias
	for (int i = playSpace.size() - 1; i >= 0; i--){
		for (int j = playSpace[i].size() - 1; j >= 0; j--){
			playSpace[i][j] = chars[rand() % chars.size()];
			write_workdat << playSpace[i][j];
			playSpace[i][j] = (playSpace[i][j] == bact ? '1' : ' ');
		}
		write_workdat << '\n';
	}
	write_workdat.close();

	int gen = input_nums("Generations: "); // ask for generations

	// init screen
	initscr();
	cbreak();
    noecho();

	int alive = 1;

	//walk through generations
	for (int j = 0; j < gen; j++){
		clear(); // Clear console to not litter output

		//measure function execution time to reduce blinking
		auto before = std::chrono::high_resolution_clock::now();

		printw("Gen: %d\n", j+1); // Print current gen

		alive = print_arr(playSpace); // Start function to walk through generations

		// If everyone died end function
		if (alive == 0) {printw("Everyone died"); break;}
		printw("%d cells alive", alive);

		refresh(); // Update console output

		// Second part of blinking reducement - wait until everything is drawn
		std::this_thread::sleep_for(std::chrono::milliseconds(75) - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - before));
	}
	// if generations will end
	if (alive != 0) printw("\nGenerations ended"); 
	// Wait for user input befor exit
	printw("\nPress any key to exit"); 
	refresh();
	getch();
	endwin();
}

