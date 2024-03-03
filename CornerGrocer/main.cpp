// Faris Malik
// 2/23/24
// Project 3, CS 210
// Program that loads data from a file, prints all item frequencies, saves data to a file and also prints our histograms
#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies;

public:
    // Load data from the input file
    void loadData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return;
        }
        std::string item;
        while (file >> item) {
            itemFrequencies[item]++;
        }
        file.close();
    }

    // Print the frequency of a specific item
    void printFrequency(const std::string& item) {
        if (itemFrequencies.find(item) != itemFrequencies.end()) {
            std::cout << item << ": " << itemFrequencies[item] << std::endl;
        }
        else {
            std::cout << "Item not found." << std::endl;
        }
    }

    // Print frequencies of all items
    void printAllFrequencies() {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Print a histogram of the item frequencies
    void printHistogram() {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << ": ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    // Save the frequency data to a file
    void saveData(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open " << filename << " for writing." << std::endl;
            return;
        }
        for (const auto& pair : itemFrequencies) {
            outFile << pair.first << " " << pair.second << std::endl;
        }
        outFile.close();
    }
};

int main() {
    ItemTracker tracker;
    tracker.loadData("CS210_Project_Three_Input_File.txt");
    tracker.saveData("frequency.dat"); // Backup data at the start

    while (true) {
        std::cout << "\nMenu:\n1. Search Item Frequency\n2. Print All Frequencies\n3. Print Histogram\n4. Exit\nEnter your choice: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next line
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        std::string item;
        switch (choice) {
        case 1:
            std::cout << "Enter item name to search: ";
            std::cin >> item;
            tracker.printFrequency(item);
            break;
        case 2:
            tracker.printAllFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            std::cout << "Exiting program." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}