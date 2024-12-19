#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<queue>
#include<cmath>
#include<stack>

using namespace std;


class Register {
    private:
        long long value = 0;

    public:
        Register() = default;

        long long get_value() {
            return value;
        }

        void set_value(long long num) {
            value = num;
        }
};


class CPU {
    private:
        Register A = Register();   
        Register B = Register();   
        Register C = Register();   
        string program;
        long long instruct_ptr = 0;

        long long get_combo(long long num) {
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

        void adv(long long operand) {
            operand = get_combo(operand);
            A.set_value(A.get_value() >> operand);
        }

        void bxl(long long operand) {
            B.set_value(B.get_value() ^ operand);
        }

        void bst(long long operand) {
            operand = get_combo(operand);
            B.set_value(operand & 7);
        }

        void jnz(long long operand) {
            if (A.get_value() != 0) {
                instruct_ptr = operand;
            }
        }

        void bxc(long long operand) {
            B.set_value(B.get_value() ^ C.get_value());
        }

        void out(long long operand) {
            operand = get_combo(operand);
            rval += '0' + (operand & 7);
        }

        void bdv(long long operand) {
            operand = get_combo(operand);
            B.set_value(A.get_value() >> operand);
        }

        void cdv(long long operand) {
            operand = get_combo(operand);
            C.set_value(A.get_value() >> operand);
        }

        static constexpr void (CPU::*opcodes[8])(long long operand) = {&CPU::adv, &CPU::bxl, &CPU::bst, &CPU::jnz, &CPU::bxc, &CPU::out, &CPU::bdv, &CPU::cdv};
        
    public:
        string rval;
        CPU(long long vA, long long vB, long long vC, string pProgram) {
            A.set_value(vA);
            B.set_value(vB);
            C.set_value(vC);
            program = pProgram;
        }

        stack<pair<long long, long long>> order; 

        void cycle() {
            while (instruct_ptr < program.size()) {
                void (CPU::*toexe)(long long operand) = (opcodes[stoi(program.substr(instruct_ptr++, 1))]);
                (this->*toexe)(stoi(program.substr(instruct_ptr++, 1)));
            }
        }
};


int main() {
    ifstream data("input.txt");

    string line;
    smatch foundnum;

    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    long long vA = stoi(foundnum[0]);
    
    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    long long vB = stoi(foundnum[0]);
    
    getline(data, line);
    regex_search(line, foundnum, regex("[0-9]+"));
    long long vC = stoi(foundnum[0]);

    getline(data, line);
    getline(data, line);
    string program;
    string::const_iterator start = line.cbegin();
    while (regex_search(start, line.cend(), foundnum, regex("[0-9]+"))) {
        program += foundnum[0];
        start = foundnum.suffix().first;
    }
    // CPU cpu = CPU(aval + n, vB, vC, program);
    //             cpu.cycle();

    vector<long long> torun = {0};
    for (long long i = program.size() - 1; i >= 0; i--) {
        vector<long long> temp = torun;
        torun.clear();
        for (const auto& aval : temp) {
            for (long long n = 0; n < 8; n++) {
                CPU cpu = CPU(aval + n, vB, vC, program);
                cpu.cycle();
                if (cpu.rval == program.substr(i, program.size() - i)) {
                    torun.push_back((aval + n) * 8);
                    if (i == 0) {
                        cout << aval + n << '\n';
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
