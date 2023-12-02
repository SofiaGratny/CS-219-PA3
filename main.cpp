#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <bitset>
#include <vector>
using namespace std;

//cmds
vector<uint32_t> initRegs();
uint32_t loadHex(string);
int findReg(string);
string printRegs(uint32_t[]);
string trim(string);

//arithmetic operations
void ADD(string, string, string);
void AND(string, string, string);
void ORR(string, string, string);
void SUB(string, string, string);
void XOR(string, string, string);
//adjusting operations
void ASR(string, string, string);
void LSR(string, string, string);
void LSL(string, string, string);
//movement operation
void MOV(string, string);


int main() {
    uint32_t registers[8] = {0,0,0,0,0,0,0,0};
    ifstream file;
    ofstream outfile;
    string line, a, b, c, d;
    file.open("Programming-Project-3.txt");
    outfile.open("output.txt");
    //after initialization of the file

    if (file.is_open()) {
        while (getline(file, line)) { // loop through
            stringstream s(line);
            while (s >> a) {
                int res = 0, op1 = 0, op2 = 0;
                uint32_t hex = 0;
                //movement operation
                if (a.compare("MOV")==0 || a.compare("mov")==0) {
                    s >> b; s >> c; 
                    //cout << "BRUH" << endl;
                    res = findReg(b); hex = loadHex(trim(c));
                    registers[res] = hex;
                    outfile << a << " " << b << " " << c << endl << printRegs(registers) << endl;
                } else {
                    //adjusting operations
                    s >> b; s >> c; s >> d;
                    res = findReg(b); op1 = findReg(c); op2 = findReg(d);
                    if (a.compare("ASR")==0 || a.compare("asr")==0) {
                        hex = loadHex(trim(d));
                        registers[res] = (registers[op1]>>hex);
                    } else if (a.compare("LSR")==0 || a.compare("lsr")==0) {
                        hex = loadHex(trim(d));
                        registers[res] = (registers[op1]>>hex);
                    } else if (a.compare("LSL")==0 || a.compare("lsl")==0) {
                        hex = loadHex(trim(d));
                        registers[res] = (registers[op1]<<hex);
                    }

                    //arithmetic operations
                    if (a.compare("ADD")==0 || a.compare("add")==0) {
                        registers[res] = registers[op1]+registers[op2];
                    } else if (a.compare("AND")==0 || a.compare("and")==0) {
                        registers[res] = (registers[op1]&registers[op2]);
                    } else if (a.compare("ORR")==0 || a.compare("orr")==0) {
                        registers[res] = (registers[op1]|registers[op2]);
                    } else if (a.compare("SUB")==0 || a.compare("sub")==0) {
                        registers[res] = registers[op1]-registers[op2];
                    } else if (a.compare("XOR")==0 || a.compare("xor")==0) {
                        registers[res] = (registers[op1]^registers[op2]);
                    }
                    outfile << a << " " << b << " " << c << " " <<  d << endl << printRegs(registers) << endl;
                }
            }
        }
    }
    file.close();
    outfile.close();
    return 0;
}

string trim(string a) {
    string b;
    stringstream s;
    for (int i = 1; i < a.length(); i++) {
        s << a[i];
    }
    s >> b;
    return b;
}

string printRegs(uint32_t r[]) {
    string b, c, d;
    for (int i = 0; i < 8; i++) {
        stringstream s;
        b = "Register [" + to_string(i) + "] ";
        s << hex << r[i]; 
        s >> c;
        b = b + " {" + c + "}\n";
        d = d + b;
    }
    cout << d << endl;
    return d;
}

int findReg(string in) {
    int a = int(in[1]) - 48;
    return a;
}

vector<uint32_t> initRegs() {
    return {0, 0, 0, 0, 0, 0, 0, 0};
}

uint32_t loadHex(string Hex) {
    uint32_t bin1;
    stringstream ss; //stringstream for dynamic stuff makes hex conversion really easy

    ss << hex << Hex;
    ss >> bin1;

    return bin1; // returns the hex value given in the form of uint32_t
}