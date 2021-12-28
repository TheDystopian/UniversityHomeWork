#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

using std::vector;
using std::string;
using std::cerr; 
using std::cout;
using std::cin;
using std::vector;
using std::ofstream;
using std::unique_ptr;

int input_nums(const char* str) {
	auto out = std::unique_ptr<unsigned int>(new unsigned int()); // This will be out
	std::cout << str; // Ask what to enter
	while (!(std::cin >> *out)) { // Request correct user input
	// if any illegal char will be entered, it wll ask for it again
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	// And out
	return *out;
}

int next_gen(vector<string>& buffer, vector<string>& next_arr) {
	int count_cells = 0; // Alive cells
	for (size_t i = 0; i < buffer.size(); i++)
		for (size_t j = 0; j < buffer[i].length(); j++) {
			// Border detection
			bool border[] = { true,true,true,true }; // up, left, down,right

			if (i == 0) border[0] = false; // Upper border
			if (i == buffer.size() - 1) border[2] = false; // Down border

			if (j == 0) border[1] = false; // Left border
			if (j == buffer[i].length() - 1) border[3] = false; // Right border

			// Count neighboring cells
			int count_neighbors = 0;
			for (size_t k = i - border[0]; k <= i + border[2]; k++)
				for (size_t l = j - border[1]; l <= j + border[3]; l++)
					if (buffer[k][l] != ' ') count_neighbors++;

			// RULE IMPLEMENTATION
			// Cell can live for 12 cycles and with 2 or 3 neighbors (+1 to include cell itself)
			if ((count_neighbors == 3 || count_neighbors == 4) && buffer[i][j] != ' ' && buffer[i][j] != 'B') {
				if (buffer[i][j] == '9') next_arr[i][j] = 'A'; // Use 12-digit system to align output
				else next_arr[i][j]++; // Cell aging 
			}
			else next_arr[i][j] = ' '; //else it will die

			if (buffer[i][j] == ' ' && count_neighbors == 3) //spawn cell if exactly 3 neighbors exist (counter doesnt count cells, so no +1)
				next_arr[i][j] = '1';

			if (buffer[i][j] != ' ') count_cells++; // Sount living cells
		}
	return count_cells; // Return ounter of living cells
}

int print_arr(vector<string>& next_arr){
	
	auto out_func = [](vector<string> next_arr) { // Output (Now more than 30 fricking times faster on my machine !!!)
		cerr.sync_with_stdio(false);
		std::copy(next_arr.begin(), next_arr.end(), std::ostream_iterator<string>(cerr, "\n"));
	};

	auto file_func = [](vector<string> next_arr) { // Write to file
		auto write_workout = std::unique_ptr<std::ofstream>(new std::ofstream("work.out")); 
		std::copy(next_arr.begin(), next_arr.end(), std::ostream_iterator<string>(*write_workout, "\n"));
		write_workout->close();
	};

	std::thread out(out_func, next_arr);
	std::thread file_write(file_func, next_arr); // Multithreading to output it console and to file simultaneously

	file_write.join();
	out.join(); // Wait for them

	return next_gen(*unique_ptr<vector<string>>(new vector<string>(next_arr)), next_arr); // Return alive cells to save space
}

int main(int argc, char** argv) {
	// Seed gen
	// used nullptr to have an idea of undefined variable 
	unsigned* seed = nullptr;
	// Scanning command line parameters to find "seed"
	for (int i = 1; i < argc; i++) {
		// if it finds "seed"
		if (!strcmp(argv[i], "seed") && seed == nullptr) {
			// seed gets unsigned type
			seed = new unsigned();
			// and gets a seed from next parameter
			// if not, user will enter it
			if (i == argc - 1 || !(*seed = atoi(argv[i + 1]))) *seed = input_nums("Seed (number): ");
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

	vector <string> playSpace(input_nums("Playing space height: "), string(input_nums("Playing space width: "),' ') );
	vector<char> chars(input_nums("Char count: ")); //generate char array

	// generate symbols inside
	for (size_t i = chars.size() - 1; i != 0; i--)
		chars[i] = 'a' + (rand() % 26);

	char bact = chars[rand() % chars.size()]; //generate bacteria

	std::ofstream write_workdat("work.dat");

	// map bacterias
	for (size_t i = 0; i < playSpace.size(); i++) {
		for (size_t j = 0; j < playSpace[i].length(); j++) {
			playSpace[i][j] = chars[rand() % chars.size()];
			write_workdat << playSpace[i][j];
			playSpace[i][j] = (playSpace[i][j] == bact ? '1' : ' ');
		}
		write_workdat << '\n';
	}
	write_workdat.close();

	int gen = input_nums("Generations: "); // ask for generations

	system("cls");

	int alive = 1;

	//walk through generations
	for (int i = 0; i < gen; i++) {
		auto before = std::chrono::high_resolution_clock::now();

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

		printf("Gen: %d\n", i + 1); // Print current gen

		alive = print_arr(playSpace); // Start function to walk through generations

		// If everyone died end function
		if (alive == 0) { printf("Everyone died  "); break; }
		printf("%d cells alive      ", alive);
		std::this_thread::sleep_for(std::chrono::milliseconds(50) - (std::chrono::high_resolution_clock::now() - before));
	}
	cerr << "\nPress any key to exit";
	cin.get();
}