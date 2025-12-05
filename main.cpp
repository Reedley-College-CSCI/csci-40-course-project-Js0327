#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Dish {
    string cuisine;
    string name;
    int calories;
    double cost;
    string instructions;
};

int loadData(Dish* dishes, int maxSize);
void listCuisines(Dish* dishes, int count);
int listDishesByCuisine(Dish* dishes, int count, const string& cuisine, int* indices);
void showDishDetails(Dish& d);
string toLower(string s);

int main() {
    const int MAX_DISHES = 50;
    Dish* dishes = new Dish[MAX_DISHES]; 
    int dishCount = loadData(dishes, MAX_DISHES);

    if (dishCount == 0) {
        cout << "No data loaded. Check foods.txt file." << endl;
        return 0;
    }

    cout << " Find a food " << endl;

    listCuisines(dishes, dishCount);

    string selectedCuisine;
    cout << "Enter a cuisine: " << endl;
    getline(cin, selectedCuisine);


    selectedCuisine = toLower(selectedCuisine);

    int indices[20];
    int numDishes = listDishesByCuisine(dishes, dishCount, selectedCuisine, indices);

    if (numDishes == 0) {
        cout << "No dishes found for that cuisine." << endl;
        return 0;
    }


    int choice;
    cout << "Choose a dish number: " << endl;
    cin >> choice;

    if (choice < 1 || choice > numDishes) {
        cout << "Invalid selection." << endl;
        return 0;
    }

   
    Dish& selectedDish = dishes[indices[choice - 1]];
    cout << ""Dish Details" << endl;
    showDishDetails(selectedDish);

    delete[] dishes; 
    return 0;
}


string toLower(string s) {
    for (char& c : s) c = tolower(c);
    return s;
}


int loadData(Dish* dishes, int maxSize) {
    ifstream file("foods.txt");
    if (!file) return 0;

    string line;
    int count = 0;

    while (getline(file, line) && count < maxSize) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        dishes[count].cuisine = toLower(line.substr(0, p1));
        dishes[count].name = line.substr(p1 + 1, p2 - p1 - 1);
        dishes[count].calories = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        dishes[count].cost = stod(line.substr(p3 + 1, p4 - p3 - 1));
        dishes[count].instructions = line.substr(p4 + 1);

        count++;
    }

    return count;
}


void listCuisines(Dish* dishes, int count) {
    cout << "Available cuisines:" << endl;
    string printed[20];
    int printedCount = 0;

    for (int i = 0; i < count; i++) {
        bool alreadyListed = false;
        for (int j = 0; j < printedCount; j++) {
            if (printed[j] == dishes[i].cuisine)
                alreadyListed = true;
        }

        if (!alreadyListed) {
            printed[printedCount++] = dishes[i].cuisine;
            cout << " - " << dishes[i].cuisine << endl;
        }
    }
}


int listDishesByCuisine(Dish* dishes, int count, const string& cuisine, int* indices) {
    cout << "Dishes available:" << endl;
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (dishes[i].cuisine == cuisine) {
            indices[found] = i;
            cout << (found + 1) << ". " << dishes[i].name << endl;
            found++;
        }
    }

    return found;
}


void showDishDetails(Dish& d) {
    cout << "Dish: " << d.name << endl;
    cout << "Calories: " << d.calories << endl;
    cout << "Estimated Cost: $" << d.cost << endl;
    cout << "Instructions: " << d.instructions << endl;
}