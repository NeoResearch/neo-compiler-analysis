#include<iostream>
#include "Scanner++/Scanner.h"
#include<vector>
#include<sstream>

using namespace std;
using namespace scannerpp;

typedef unsigned char byte;

// type 1 (PUSH): PUSH00, PUSH01, ...
// type 2 arithmetic
// type 3 jumps (JMP...)
// type 4....
int opcodeCategory(byte op) {

}

enum OpType{
   PUSHBYTES, PUSHDATA, x, unknown
};

struct OpPack {
   OpPack(byte _op, OpType _type, int _size = 1, string _rest="") :
       op(_op), type(_type), size(_size), rest(_rest)
   {
   }
   byte op;      // hex code
   OpType type;  // opcode type
   string rest;  // opcode parameters
   int size;     // size in bytes (including parameters)
   friend ostream& operator<<(ostream& os, const OpPack& opk){
       os << "(" << unsigned(opk.op) << ";" << opk.type << ";" << opk.size << /*";" << opk.rest <<*/ ")";
       return os;
   }
};

int toDigit(char c) {
    if(c == 'a')
       return 10;
    else if(c == 'b')
       return 11;
    else if(c == 'c')
       return 12;
    else if(c == 'd')
       return 13;
    else if(c == 'e')
       return 14;
    else if(c == 'f')
       return 15;
    else {
       string s;
       s += c;
       return atoi(s.c_str());
    }
}

byte toHex(string opcode) {
    return toDigit(opcode[0])*16 + toDigit(opcode[1]);
}

OpPack getOpcode(string opcode, Scanner& scanner) {
   //cout << "process: " << opcode << endl;
   unsigned pvalue = toHex(opcode);
   cout << opcode << "["<<pvalue<<"] ";
   if (opcode == "00")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH0\t#An empty array of bytes is pushed onto the stack\n");
        return OpPack(0, OpType::PUSHBYTES);
   else if ((pvalue >= 1) && (pvalue <= 75)) {
            cout << "NEEDS MORE " << pvalue << " BYTES" << endl;
//            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHBYTES" + pvalue + "\t # ");
            OpPack opk(pvalue, OpType::PUSHBYTES);
            int i = 0;
            string spush = "";
            for (i = 0; i < pvalue; i++) {
                spush += scanner.nextChar();
                spush += scanner.nextChar();
                opk.size++;
            }
            opk.rest = spush;
            return opk;
            //$("#opcodes").text($("#opcodes").text() + " # 0x01-0x4B The next opcode bytes is data to be pushed onto the stack\n");
        }

        //else if(opcode == "01")
        // $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHBYTES1\t#0x01-0x4B The next opcode bytes is data to be pushed onto the stack\n");
        //else if(opcode == "4b")
        //  $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHBYTES75\t#\n");

        else if (opcode == "4c") {
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHDATA1\t#The next byte contains the number of bytes to be pushed onto the stack\n");
            OpPack opk(pvalue, OpType::PUSHDATA);
            int i = 0;
            string spush = "";
            for (i = 0; i < 1; i++) {
                spush += scanner.nextChar();
                spush += scanner.nextChar();
                opk.size++;
            }
            opk.rest = spush;
            return opk;
        }
        else if (opcode == "4d") {
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHDATA2\t#The next two bytes contain the number of bytes to be pushed onto the stack\n");
            OpPack opk(pvalue, OpType::PUSHDATA);
            int i = 0;
            string spush = "";
            for (i = 0; i < 2; i++) {
                spush += scanner.nextChar();
                spush += scanner.nextChar();
                opk.size++;
            }
            opk.rest = spush;
            return opk;
        }
        else if (opcode == "4e") {
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHDATA4\t#The next four bytes contain the number of bytes to be pushed onto the stack.\n");
            OpPack opk(pvalue, OpType::PUSHDATA);
            int i = 0;
            string spush = "";
            for (i = 0; i < 4; i++) {
                spush += scanner.nextChar();
                spush += scanner.nextChar();
                opk.size++;
            }
            opk.rest = spush;
            return opk;
        }
/*
        else if (opcode == "4f")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHM1\t#The number -1 is pushed onto the stack.\n");
        else if (opcode == "51")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH1\t# The number 1 is pushed onto the stack.\n");
        else if (opcode == "52")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH2\t# The number 2 is pushed onto the stack.\n");
        else if (opcode == "53")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH3\t# The number 3 is pushed onto the stack.\n");
        else if (opcode == "54")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH4\t# The number 4 is pushed onto the stack.\n");
        else if (opcode == "55")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH5\t# The number 5 is pushed onto the stack.\n");
        else if (opcode == "56")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH6\t# The number 6 is pushed onto the stack.\n");
        else if (opcode == "57")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH7\t# The number 7 is pushed onto the stack.\n");
        else if (opcode == "58")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH8\t# The number 8 is pushed onto the stack.\n");
        else if (opcode == "59")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH9\t# The number 9 is pushed onto the stack.\n");
        else if (opcode == "5a")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH10\t# The number 10 is pushed onto the stack.\n");
        else if (opcode == "5b")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH11\t# The number 11 is pushed onto the stack.\n");
        else if (opcode == "5c")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH12\t# The number 12 is pushed onto the stack.\n");
        else if (opcode == "5d")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH13\t# The number 13 is pushed onto the stack.\n");
        else if (opcode == "5e")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH14\t# The number 14 is pushed onto the stack.\n");
        else if (opcode == "5f")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH15\t# The number 15 is pushed onto the stack.\n");
        else if (opcode == "60")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH16\t# The number 16 is pushed onto the stack.\n");
        else if (opcode == "61")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNOP\t# Does nothing.\n");
        else if (opcode == "62") {
            $("#opcodes").text($("#opcodes").text() + opcode + "\tJMP\t# ");
            var nparfunc = "" + hexavm[0] + hexavm[1];
            hexavm = hexavm.substr(2, hexavm.length);
            $("#opcodes").text($("#opcodes").text() + nparfunc + "\n");
        }
        else if (opcode == "63") {
            $("#opcodes").text($("#opcodes").text() + opcode + "\tJMPIF\t# ");
            var nparfunc = "" + hexavm[0] + hexavm[1];
            hexavm = hexavm.substr(2, hexavm.length);
            $("#opcodes").text($("#opcodes").text() + nparfunc + "\n");
        }
        else if (opcode == "64") {
            $("#opcodes").text($("#opcodes").text() + opcode + "\tJMPIFNOT\t# ");
            var nparfunc = "" + hexavm[0] + hexavm[1];
            hexavm = hexavm.substr(2, hexavm.length);
            $("#opcodes").text($("#opcodes").text() + nparfunc + "\n");
        }
        else if (opcode == "65")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tCALL\t# \n");
        else if (opcode == "66")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tRET\t# \n");
        else if (opcode == "67")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tAPPCALL\t# \n");
        else if (opcode == "68") {
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSYSCALL\t# ");
            var nparfunc = "" + hexavm[0] + hexavm[1];
            hexavm = hexavm.substr(2, hexavm.length);
            fvalue = parseInt(nparfunc, 16);
            sfunc = "";
            var i = 0;
            for (i = 0; i < fvalue; i++) {
                var codepush = "" + hexavm[0] + hexavm[1];
                hexavm = hexavm.substr(2, hexavm.length);
                var cvalue = String.fromCharCode(parseInt(codepush, 16));
                sfunc += cvalue;
                if (sfunc == "Neo.Storage")
                    $("#cbx_storage")[0].checked = true;
                $("#opcodes").text($("#opcodes").text() + cvalue);
            }
            $("#opcodes").text($("#opcodes").text() + "\n");
        }
        else if (opcode == "69")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tTAILCALL\t# \n");
        else if (opcode == "6a")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDUPFROMALTSTACK\t# \n");
        else if (opcode == "6b")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tTOALTSTACK\t# Puts the input onto the top of the alt stack. Removes it from the main stack.\n");
        else if (opcode == "6c")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tFROMALTSTACK\t# Puts the input onto the top of the main stack. Removes it from the alt stack.\n");
        else if (opcode == "6d")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tXDROP\t# \n");
        else if (opcode == "72")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tXSWAP\t# \n");
        else if (opcode == "73")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tXTUCK\t# \n");
        else if (opcode == "74")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDEPTH\t# Puts the number of stack items onto the stack.\n");
        else if (opcode == "75")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDROP\t# Removes the top stack item.\n");
        else if (opcode == "76")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDUP\t# Duplicates the top stack item.\n");
        else if (opcode == "77")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNIP\t# Removes the second-to-top stack item.\n");
        else if (opcode == "78")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tOVER\t# Copies the second-to-top stack item to the top.\n");
        else if (opcode == "79")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPICK\t# The item n back in the stack is copied to the top.\n");
        else if (opcode == "7a")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tROLL\t# The item n back in the stack is moved to the top.\n");
        else if (opcode == "7b")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tROT\t# The top three items on the stack are rotated to the left.\n");
        else if (opcode == "7c")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSWAP\t# The top two items on the stack are swapped.\n");
        else if (opcode == "7d")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tTUCK\t# The item at the top of the stack is copied and inserted before the second-to-top item.\n");
        else if (opcode == "7e")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tCAT\t# Concatenates two strings.\n");
        else if (opcode == "7f")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSUBSTR\t# Returns a section of a string.\n");
        else if (opcode == "80")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tLEFT\t# Keeps only characters left of the specified point in a string.\n");
        else if (opcode == "81")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tRIGHT\t# Keeps only characters right of the specified point in a string.\n");
        else if (opcode == "82")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSIZE\t# Returns the length of the input string.\n");
        else if (opcode == "83")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tINVERT\t# Flips all of the bits in the input.\n");
        else if (opcode == "84")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tAND\t# Boolean and between each bit in the inputs.\n");
        else if (opcode == "85")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tOR\t# Boolean or between each bit in the inputs.\n");
        else if (opcode == "86")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tXOR\t# Boolean exclusive or between each bit in the inputs.\n");
        else if (opcode == "87")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tEQUAL\t# Returns 1 if the inputs are exactly equal, 0 otherwise.\n");
        else if (opcode == "8b")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tINC\t# 1 is added to the input.\n");
        else if (opcode == "8c")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDEC\t# 1 is subtracted from the input.\n");
        else if (opcode == "8d")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSIGN\t# \n");
        else if (opcode == "8f")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNEGATE\t# The sign of the input is flipped.\n");
        else if (opcode == "90")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tABS\t# The input is made positive.\n");
        else if (opcode == "91")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNOT\t# If the input is 0 or 1, it is flipped. Otherwise the output will be 0.\n");
        else if (opcode == "92")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNZ\t# Returns 0 if the input is 0. 1 otherwise.\n");
        else if (opcode == "93")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tADD\t# a is added to b.\n");
        else if (opcode == "94")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSUB\t# b is subtracted from a.\n");
        else if (opcode == "95")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tMUL\t# a is multiplied by b.\n");
        else if (opcode == "96")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tDIV\t# a is divided by b.\n");
        else if (opcode == "97")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tMOD\t# Returns the remainder after dividing a by b.\n");
        else if (opcode == "98")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSHL\t# Shifts a left b bits, preserving sign.\n");
        else if (opcode == "99")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSHR\t# Shifts a right b bits, preserving sign.\n");
        else if (opcode == "9a")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tBOOLAND\t# If both a and b are not 0, the output is 1. Otherwise 0.\n");
        else if (opcode == "9b")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tBOOLOR\t# If a or b is not 0, the output is 1. Otherwise 0.\n");
        else if (opcode == "9c")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNUMEQUAL\t# Returns 1 if the numbers are equal, 0 otherwise.\n");
        else if (opcode == "9e")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNUMNOTEQUAL\t# Returns 1 if the numbers are not equal, 0 otherwise.\n");
        else if (opcode == "9f")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tLT\t# Returns 1 if a is less than b, 0 otherwise.\n");
        else if (opcode == "a0")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tGT\t# Returns 1 if a is greater than b, 0 otherwise.\n");
        else if (opcode == "a1")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tLTE\t# Returns 1 if a is less than or equal to b, 0 otherwise.\n");
        else if (opcode == "a2")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tGTE\t# Returns 1 if a is greater than or equal to b, 0 otherwise.\n");
        else if (opcode == "a3")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tMIN\t# Returns the smaller of a and b.\n");
        else if (opcode == "a3")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tMIN\t# Returns the smaller of a and b.\n");
        else if (opcode == "a4")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tMAX\t# Returns the larger of a and b.\n");
        else if (opcode == "a5")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tWITHIN\t# Returns 1 if x is within the specified range (left-inclusive), 0 otherwise.\n");
        else if (opcode == "a7")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSHA1\t# The input is hashed using SHA-1.\n");
        else if (opcode == "a8")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSHA256\t# The input is hashed using SHA-256.\n");
        else if (opcode == "a9")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tHASH160\t# The input is hashed using HASH160.\n");
        else if (opcode == "aa")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tHASH256\t# The input is hashed using HASH256.\n");
        else if (opcode == "ac")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tCHECKSIG\t# \n");
        else if (opcode == "ae")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tCHECKMULTISIG\t# \n");
        else if (opcode == "c0")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tARRAYSIZE\t# \n");
        else if (opcode == "c1")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPACK\t# \n");
        else if (opcode == "c2")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tUNPACK\t# \n");
        else if (opcode == "c3")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tPICKITEM\t# \n");
        else if (opcode == "c4")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tSETITEM\t# \n");
        else if (opcode == "c5")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNEWARRAY\t# \n");
        else if (opcode == "c6")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tNEWSTRUCT\t# \n");
        else if (opcode == "c8")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tAPPEND\t# \n");
        else if (opcode == "c9")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tREVERSE\t# \n");
        else if (opcode == "ca")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tREMOVE\t# \n");
        else if (opcode == "f0")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tTHROW\t# \n");
        else if (opcode == "f1")
            $("#opcodes").text($("#opcodes").text() + opcode + "\tTHROWIFNOT\t# \n");
        else {
            $("#opcodes").text($("#opcodes").text() + opcode + "\t???\t# \n");
        }
*/
    else {

        return OpPack(toHex(opcode), OpType::unknown);
     }
}


vector<OpPack> str_opcodes(Scanner& scanner) {
   vector<OpPack> vs;
   while(scanner.hasNext()) {
     string ops;
     ops += scanner.nextChar();
     ops += scanner.nextChar();
     vs.push_back(getOpcode(ops, scanner));
   }
   return vs;
}


void study1(string filebase) {
    stringstream spython;
    spython << "Samples/"+ filebase << ".py.avmhex";
    stringstream scs;
    scs << "Samples/" + filebase << ".cs.avmhex";

    cout << "open: " << spython.str() << endl;
    Scanner scanFilePy(new File(spython.str()));
    vector<OpPack> vop_py = str_opcodes(scanFilePy);
    for(unsigned i=0; i<vop_py.size(); i++)
       cout << vop_py[i] << " ";
    cout << endl;

    cout << "open: " << scs.str() << endl;
    Scanner scanFileCs(new File(scs.str()));
    vector<OpPack> vop_cs = str_opcodes(scanFileCs);

    cout << "RESULT1\tpy\t" << vop_py.size() << "\tcs\t" << vop_cs.size() << endl;

}


int main() {

   string filelist="filelist.txt";

   Scanner scanner(new File(filelist));

   while(scanner.hasNext()) {
      string path = scanner.nextLine();
      cout << path << endl;
      study1(path);
   }

   cout << "Program finished sucessfully!" << endl; 
   return 0;
}
