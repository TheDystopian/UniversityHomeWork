#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::vector;
using std::string;
using std::cout;
using std::cin;

constexpr short int fps = 1000 / 60; // FPS cap: Second/Frames

// Input function for numbers
unsigned input_nums(const char* str) {
	unsigned out; // This will be out
	cout << str; // Ask what to enter
	while (!(cin >> out)) { // Request correct user input
	// if any illegal char will be entered, program will ask for it again
		cin.clear();
		cin.ignore(1, '\n');
	}
	return out; // And out
}

// Generate next array
int next_gen(vector<string>& next_arr) {
	int count_cells = 0; // Alive cells
	vector<string> buffer = next_arr; // Copy array for buffering
	for (size_t i = 0; i < buffer.size(); i++)
		for (size_t j = 0; j < buffer[i].length(); j++) {
			// Count neighboring cells
			int count_neighbors = 0;
			for (short int k = -1 + (i == 0); k <= 1 - (i == buffer.size() - 1); k++) // Because true = 1 and false = 0, i can use them as a number
				for (short int l = -1 + (j == 0); l <= 1 - (j == buffer[i].length() - 1); l++)
					if (buffer[i+k][j+l] != ' ') count_neighbors++;

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

// Output next array
void print_arr(vector<string> next_arr) {
	using std::copy;
	using std::ostream_iterator;

	std::thread out([](vector<string> next_arr) { // Output to console
		copy(next_arr.begin(), next_arr.end(), ostream_iterator<string>(cout, "\n"));
	}, next_arr);
	
	std::thread file_write([](vector<string> next_arr) { // Write to file
		auto write_workout = std::unique_ptr<std::ofstream>(new std::ofstream("work.out"));
		copy(next_arr.begin(), next_arr.end(), ostream_iterator<string>(*write_workout, "\n"));
		write_workout->close();
	}, next_arr); // Multithreading to output it console and to file simultaneously
	

	out.join();
	file_write.join(); // Wait for threads to execute
}

int fps_stabilizer(std::chrono::steady_clock::duration &before) { // Shows and stabilizes fps when needed
	unsigned after = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch() - before).count(); // Get execution time

	if (after >= fps) // If code executes not fast, returns current fps
		return 1000 / after;

	std::this_thread::sleep_for(milliseconds(fps - after)); // Wait
	return 1000 / fps; // Return capped fps 
}

// Simulation loop 
void sim_loop(int gen,vector <string> playSpace) {
	system("cls"); // Prepare space for simulation

	int alive = 0; // Alive cells count
	
	for (int i = 0; i < gen; i++) { //walk through generations
		auto before = high_resolution_clock::now().time_since_epoch(); // Start counting time of execution 

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

		printf("Gen: %d\n", i + 1); // Print current gen

		std::thread output(print_arr, playSpace); // Print array with cells

		alive = next_gen(playSpace); // Generate new array
		output.join(); // Wait for output
		if (alive == 0) { printf("Everyone died  "); break; } // If everyone died end function
		printf("%d cells alive      \nFPS: %d  \n",alive, fps_stabilizer(before));
	}
	if (alive != 0) cout << "\nGenerations ended";
}

// Init array
vector <string> arr_make() {
	vector <string> playSpace(input_nums("Playing space height: "), string(input_nums("Playing space width: "), ' ')); // Create new main array
	vector <char> chars(input_nums("Char count: ")); // generate char array

	// generate symbols inside
	for (size_t i = 0; i < chars.size(); i++)
		chars[i] = 'a' + (rand() % 26);

	char bact = chars[rand() % chars.size()]; //generate bacteria

	std::ofstream write_workdat("work.dat");

	// map bacterias
	for (size_t i = 0; i < playSpace.size(); i++) {
		for (size_t j = 0; j < playSpace[i].length(); j++) {
			playSpace[i][j] = chars[rand() % chars.size()];
			write_workdat << playSpace[i][j]; // Write to file
			playSpace[i][j] = (playSpace[i][j] == bact ? '1' : ' '); // Ig it is bacteria char, it changing on the go
		}
		write_workdat << '\n'; // Newline to output more readable work.dat
	}
	write_workdat.close(); // Close file
	return playSpace; // return playing array
}

// Get seed and call function for array
int main(int argc, char** argv) {
	cout.sync_with_stdio(false);
	cin.tie(NULL);

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
		seed = new unsigned(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
	cout << "Seed: " << *seed << "\n";
	srand(*seed); // Apply and delete seed
	delete seed;
	
	sim_loop(input_nums("Generation count: "), arr_make()); // Let's make playing field and launch simulation

	cout << "\nPress any key to exit";
	cin.ignore();
	cin.get();
}