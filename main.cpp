#include <bits/stdc++.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#define InputFile "gift1.in"
#define OutputFile "gift1.out"

using namespace std;

ifstream input(InputFile);                         // Input file
ofstream output(OutputFile, std::ofstream::trunc); // Output file
int np;      // Non-deterministic polynomial
string text; // Text content of a single line (during read operation)
unordered_map<string, int>
    umap; // HashMap (unstructured) for storing names with id

struct CashRegister {
  char name[14];
  int money;
};

struct ShareCounter {
  int totalAmount;
  int totalRecievers;
};

// Function which handles money transfer
void giverFunction(int amount, int receivers, CashRegister cashRegister[],
                   string giverName) {

  int shareAmount, leftovers;

  std::cout << endl << giverName << " is transferring money....";

  // Return if Amount and Reciever is 0
  if (!amount && !receivers) {
    std::cout << endl << "Skipping money transfer for " << giverName << endl;
    return;
  }

  shareAmount = amount / receivers;
  leftovers = amount % receivers;

  // Allocate amount to receivers
  for (int i = 0; i < receivers; i++) { // o(n)
    getline(input, text);
    std::cout << endl << "Receiver -> " << text;
    cashRegister[umap[text]].money =
        cashRegister[umap[text]].money + shareAmount;
  }

  // Adding money for givers
  cashRegister[umap[giverName]].money =
      cashRegister[umap[giverName]].money - amount + leftovers;
}

// Getting Amount and Receiver count
ShareCounter getSharingDetails(string str) {
  ShareCounter shareCounter;
  for (int i = 0; i < str.length(); i++) { // o(n)
    if (str[i] == ' ') {
      shareCounter.totalAmount = stoi(str.substr(0, i));
      shareCounter.totalRecievers = stoi(str.substr(i, str.length() - 1));
    }
  }
  return shareCounter;
}

int main() {
  string giverName;
  getline(input, text);
  np = stoi(text);
  if (np < 2 || np > 10) {
    std::cout << "NP should be between 2-10";
    exit(0);
  }
  CashRegister cashRegister[np];

  std::cout << "Cash Register Generated..." << endl;
  for (int i = 0; i < np; i++) { // o(n)
    getline(input, text);
    strcpy(cashRegister[i].name, text.c_str());
    cashRegister[i].money = 0;

    // Adding data to hashmap
    umap[text.c_str()] = i;
  }

  // Giving money to recievers - o(n)
  while (getline(input, text)) {
    giverName = text;
    getline(input, text);
    ShareCounter result = getSharingDetails(text);
    giverFunction(result.totalAmount, result.totalRecievers, cashRegister,
                  giverName);
  }

  // Writing to output file o(n)
  for (int i = 0; i < np; i++) {
    output << cashRegister[i].name << " " << cashRegister[i].money << endl;
  }

  std::cout << endl << "Output file has been generated...";
  exit(0);
}
