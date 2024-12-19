#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<queue>
#include<cmath>

using namespace std;


class Register {
    private:
        int value = 0;

    public:
        Register() = default;

        int get_value() {
            return value;
        }

        void set_value(int num) {
            value = num;
        }
};


class CPU {
    private:
        Register A = Register();   
        Register B = Register();   
        Register C = Register();   
        vector<short> program;
        int instruct_ptr = 0;

        int get_combo(short num) {
            switch (num) {
                case 0:
                case 1:
                case 2:
                case 3:
                    return num;
                    break;
                
                case 4:
                    return A.get_value();
                    break;

                case 5:
                    return B.get_value();
                    break;

                case 6:
                    return C.get_value();
                    break;
                
                default:
                    throw runtime_error("This operand is reserved or not valid");
                    break;
            }
        }

        void adv(short operand) {
            operand = get_combo(operand);
            A.set_value(A.get_value() >> operand);
        }

        void bxl(short operand) {
            B.set_value(B.get_value() ^ operand);
        }

        void bst(short operand) {
            operand = get_combo(operand);
            B.set_value(operand & 7);
        }

        void jnz(short operand) {
            if (A.get_value() != 0) {
                instruct_ptr = operand;
            }
        }

        void bxc(short operand) {
            B.set_value(B.get_value() ^ C.get_value());
        }

        void out(short operand) {
            operand = get_combo(operand);
            cout << (operand & 7) << ',';
        }

        void bdv(short operand) {
            operand = get_combo(operand);
            B.set_value(A.get_value() >> operand);
        }

        void cdv(short operand) {
            operand = get_combo(operand);
            C.set_value(A.get_value() >> operand);
        }

        static constexpr void (CPU::*opcodes[8])(short operand) = {&CPU::adv, &CPU::bxl, &CPU::bst, &CPU::jnz, &CPU::bxc, &CPU::out, &CPU::bdv, &CPU::cdv};
        
    public:
        CPU(int vA, int vB, int vC, vector<short> pProgram) {
            A.set_value(vA);
            B.set_value(vB);
            C.set_value(vC);
            program = pProgram;
        }

        void cycle() {
            while (instruct_ptr < program.size()) {
                void (CPU::*toexe)(short operand) = (opcodes[program[instruct_ptr++]]);
                (this->*toexe)(program[instruct_ptr++]);
            }
        }
};


int main() {
    ifstream data("input.txt");

    string line;
    smatch foundnum;

    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    int vA = stoi(foundnum[0]);
    
    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    int vB = stoi(foundnum[0]);
    
    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    int vC = stoi(foundnum[0]);

    getline(data, line);
    getline(data, line);
    vector<short> program;
    string::const_iterator start = line.cbegin();
    while (regex_search(start, line.cend(), foundnum, regex("[0-9]+"))) {
        program.push_back((short)stoi(foundnum[0]));
        start = foundnum.suffix().first;
    }

    CPU cpu = CPU(vA, vB, vC, program);
    cpu.cycle();

    return 0;
}