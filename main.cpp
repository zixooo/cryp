#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        cerr << "Error: Use three parameters\n";
        return 5;
    }
    const string mode(argv[1]); // Режим работы
    const string file_name(argv[2]); // Имя файла

    if (mode == "encryption") {
        // Режим шифрование
        cout << "Input message:";
        string message;
        getline(cin, message);
        cout << " " << endl;
        cout << "Input key:";
        int key;
        cin >> key;
        const char *data = message.data();
        size_t size = message.size();
        vector<char> bytes(size);
        for (int i = 0; i < size; i++) {
            bytes[i] = data[i];
        }
        srand(key);
        ofstream outFile;
        outFile.open(file_name, ios::binary);
        outFile.clear();
        for (int i = 0; i < bytes.size(); ++i) {
            unsigned int gamma = rand();
            unsigned int r = (static_cast<unsigned int>(bytes[i])) ^ gamma;
            unsigned int enc_block =
                    (r >> 4) | ((r << 4) & 0xFF);
            char r1 = enc_block;
            outFile.write(&r1, sizeof(r1));
        }
        outFile.close();

    } else if (mode == "decryption") {
        // Режим расшифрования
        string key;
        cout << "Enter a key: ";
        getline(cin, key);
        unsigned int s_key = 0;
        for (char j: key) s_key += static_cast<unsigned int>(j);
        srand(s_key);
        cout << "Decrypted string: ";
        ifstream out;
        out.open(file_name, ios::binary);
        vector<unsigned char> encryptedData((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
        out.close();
        for (unsigned char i: encryptedData) {
            auto r2 = static_cast<unsigned int>(i);
            r2 = (((r2 << 4) & 0xFF | (r2 >> 4) & 0xFF) ^ rand()) & 0xFF;
            cout << static_cast<char>(r2);
        }
        out.close();
    }
    return 0;
}
