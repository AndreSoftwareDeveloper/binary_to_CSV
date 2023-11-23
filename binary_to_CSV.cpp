#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>

using namespace std;

struct Record { // TODO check if unsigned is necessary
    uint16_t A;
    char B;
    uint8_t C;
    uint32_t D;
    float E;
    uint64_t F; // TODO Bit field
    uint8_t G : 7;
};

int main() {
    ifstream input("input.bin", ios::binary);

    if (!input.is_open()) {
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    ofstream output("output.csv");
    output << "A,D,E,G" << endl;

    Record record;
    while (input.peek() != EOF) {     
        input.read(reinterpret_cast<char*>(&record.A), sizeof(record.A));
        input.read(&record.B, sizeof(record.B));
        input.read(reinterpret_cast<char*>(&record.C), sizeof(record.C));
        input.read(reinterpret_cast<char*>(&record.D), sizeof(record.D));
        input.read(reinterpret_cast<char*>(&record.E), sizeof(record.E));
        input.read(reinterpret_cast<char*>(&record.F), sizeof(record.F));

        record.G = static_cast<uint8_t>((record.F >> 10) & 0x7F);

        output << record.A << "," << record.D << ","
            << fixed << setprecision(9) << record.E << "," << static_cast<int>(record.G) << endl;
    }

    input.close();
    output.close();

    cout << "The operation was completed successfully. Results saved to output.csv" << endl;
    return 0;
}
