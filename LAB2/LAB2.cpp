#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ArithmeticCoding {
public:
    struct Symbol {
        char value;
        double left;
        double right;
        double probability;
    };

    vector<Symbol> buildSymbolTable(const string& input) {
        vector<Symbol> symbols;
        for (char c : input) {
            bool found = false;
            for (Symbol& symbol : symbols) {
                if (symbol.value == c) {
                    symbol.probability += 1.0;
                    found = true;
                    break;
                }
            }
            if (!found) {
                symbols.push_back({ c, 0.0, 0.0, 1.0 });
            }
        }

        double left = 0.0;
        for (Symbol& symbol : symbols) {
            symbol.probability /= input.length();
            symbol.left = left;
            symbol.right = left + symbol.probability;
            left = symbol.right;
        }

        return symbols;
    }

    double encode(const string& input, const vector<Symbol>& symbolTable) {
        double left = 0.0;
        double right = 1.0;

        for (char c : input) {
            for (const Symbol& symbol : symbolTable) {
                if (symbol.value == c) {
                    double range = right - left;
                    right = left + range * symbol.right;
                    left = left + range * symbol.left;
                    break;
                }
            }
        }

        return (left + right) / 2.0;
    }

    string decode(double code, const vector<Symbol>& symbolTable, int length) {
        string result;

        for (int i = 0; i < length; ++i) {
            for (const Symbol& symbol : symbolTable) {
                if (code >= symbol.left && code < symbol.right) {
                    result += symbol.value;
                    code = (code - symbol.left) / (symbol.right - symbol.left);
                    break;
                }
            }
        }

        return result;
    }
};

int main() {
    ArithmeticCoding ac;

    cout << "Enter text: ";
    string input;
    getline(cin, input);

    vector<ArithmeticCoding::Symbol> symbolTable = ac.buildSymbolTable(input);

    double encodedValue = ac.encode(input, symbolTable);
    cout << "Encoded value: " << encodedValue << endl;

    string decodedString = ac.decode(encodedValue, symbolTable, input.length());
    cout << "Decoded string: " << decodedString << endl;

    return 0;
}