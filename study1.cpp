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
   PUSHBYTES, PUSHDATA, PUSHCONST, NOP, JUMP, CALL, APPCALL, SYSCALL, TAILCALL, ALTSTACK, RET, XSTACK, STACK, STRING, BITS, ARITHMETIC, COMPARE, MINMAXINT, SHA, HASH, SIG, ARRAY, STRUCT, EXCEPTION, unknown
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

int groupCount(vector<OpPack> vop, OpType type) {
  int count = 0;
  for(unsigned i=0; i<vop.size(); i++)
    if(vop[i].type == type)
      count++;
  return count;
}

int groupSumParam(vector<OpPack> vop, OpType type) {
  int sum = 0;
  for(unsigned i=0; i<vop.size(); i++)
    if(vop[i].type == type)
      sum+=vop[i].size;
  return sum;
}

void printLineCount(vector<OpPack> vop) {
  cout << "PUSHBYTES\t" << groupCount(vop, OpType::PUSHBYTES) << "\t";
  cout << "PUSHDATA\t" << groupCount(vop, OpType::PUSHDATA) << "\t";
  cout << "PUSHCONST\t" << groupCount(vop, OpType::PUSHCONST) << "\t";
  cout << "NOP\t" << groupCount(vop, OpType::NOP) << "\t";
  cout << "JUMP\t" << groupCount(vop, OpType::JUMP) << "\t";
  cout << "CALL\t" << groupCount(vop, OpType::CALL) << "\t";
  cout << "APPCALL\t" << groupCount(vop, OpType::APPCALL) << "\t";
  cout << "SYSCALL\t" << groupCount(vop, OpType::SYSCALL) << "\t";
  cout << "TAILCALL\t" << groupCount(vop, OpType::TAILCALL) << "\t";
  cout << "ALTSTACK\t" << groupCount(vop, OpType::ALTSTACK) << "\t";
  cout << "RET\t" << groupCount(vop, OpType::RET) << "\t";
  cout << "XSTACK\t" << groupCount(vop, OpType::XSTACK) << "\t";
  cout << "STACK\t" << groupCount(vop, OpType::STACK) << "\t";
  cout << "STRING\t" << groupCount(vop, OpType::STRING) << "\t";
  cout << "BITS\t" << groupCount(vop, OpType::BITS) << "\t";
  cout << "ARITHMETIC\t" << groupCount(vop, OpType::ARITHMETIC) << "\t";
  cout << "COMPARE\t" << groupCount(vop, OpType::COMPARE) << "\t";
  cout << "MINMAXINT\t" << groupCount(vop, OpType::MINMAXINT) << "\t";
  cout << "SHA\t" << groupCount(vop, OpType::SHA) << "\t";
  cout << "HASH\t" << groupCount(vop, OpType::HASH) << "\t";
  cout << "SIG\t" << groupCount(vop, OpType::SIG) << "\t";
  cout << "ARRAY\t" << groupCount(vop, OpType::ARRAY) << "\t";
  cout << "STRUCT\t" << groupCount(vop, OpType::STRUCT) << "\t";
  cout << "EXCEPTION\t" << groupCount(vop, OpType::EXCEPTION) << "\t";
  cout << "unknown\t" << groupCount(vop, OpType::unknown) << "\t";
  cout << "TOTAL\t" << vop.size() << endl;
}

void printLineSumParam(vector<OpPack> vop) {
  cout << "PUSHBYTES\t" << groupSumParam(vop, OpType::PUSHBYTES) << "\t";
  cout << "PUSHDATA\t" << groupSumParam(vop, OpType::PUSHDATA) << "\t";
  cout << "PUSHCONST\t" << groupSumParam(vop, OpType::PUSHCONST) << "\t";
  cout << "NOP\t" << groupSumParam(vop, OpType::NOP) << "\t";
  cout << "JUMP\t" << groupSumParam(vop, OpType::JUMP) << "\t";
  cout << "CALL\t" << groupSumParam(vop, OpType::CALL) << "\t";
  cout << "APPCALL\t" << groupSumParam(vop, OpType::APPCALL) << "\t";
  cout << "SYSCALL\t" << groupSumParam(vop, OpType::SYSCALL) << "\t";
  cout << "TAILCALL\t" << groupSumParam(vop, OpType::TAILCALL) << "\t";
  cout << "ALTSTACK\t" << groupSumParam(vop, OpType::ALTSTACK) << "\t";
  cout << "RET\t" << groupSumParam(vop, OpType::RET) << "\t";
  cout << "XSTACK\t" << groupSumParam(vop, OpType::XSTACK) << "\t";
  cout << "STACK\t" << groupSumParam(vop, OpType::STACK) << "\t";
  cout << "STRING\t" << groupSumParam(vop, OpType::STRING) << "\t";
  cout << "BITS\t" << groupSumParam(vop, OpType::BITS) << "\t";
  cout << "ARITHMETIC\t" << groupSumParam(vop, OpType::ARITHMETIC) << "\t";
  cout << "COMPARE\t" << groupSumParam(vop, OpType::COMPARE) << "\t";
  cout << "MINMAXINT\t" << groupSumParam(vop, OpType::MINMAXINT) << "\t";
  cout << "SHA\t" << groupSumParam(vop, OpType::SHA) << "\t";
  cout << "HASH\t" << groupSumParam(vop, OpType::HASH) << "\t";
  cout << "SIG\t" << groupSumParam(vop, OpType::SIG) << "\t";
  cout << "ARRAY\t" << groupSumParam(vop, OpType::ARRAY) << "\t";
  cout << "STRUCT\t" << groupSumParam(vop, OpType::STRUCT) << "\t";
  cout << "EXCEPTION\t" << groupSumParam(vop, OpType::EXCEPTION) << "\t";
  cout << "unknown\t" << groupSumParam(vop, OpType::unknown) << "\t";
  cout << "TOTAL\t";
  int sum = 0;
  for(unsigned i=0; i<vop.size(); i++)
    sum += vop[i].size;
  cout << sum << endl;
}

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
   //cout << opcode << "["<<pvalue<<"] ";
   if (opcode == "00")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSH0\t#An empty array of bytes is pushed onto the stack\n");
        return OpPack(0, OpType::PUSHBYTES);
   else if ((pvalue >= 1) && (pvalue <= 75)) {
            //cout << "NEEDS MORE " << pvalue << " BYTES" << endl;
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
            string spush = "";
            for (int i = 0; i < 1; i++) {
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
        else if (opcode == "4f")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPUSHM1\t#The number -1 is pushed onto the stack.\n");
            return OpPack(pvalue, OpType::PUSHCONST);
        else if ((pvalue >= 81) && (pvalue <= 96))
            return OpPack(pvalue, OpType::PUSHCONST);
            /*
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
            */
        else if (opcode == "61")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNOP\t# Does nothing.\n");
            return OpPack(pvalue, OpType::NOP);
        else if ((opcode == "62") || (opcode == "63") || (opcode == "64")) {
          OpPack opk(pvalue, OpType::JUMP);
          string spush = "";
          for (int i = 0; i < 1; i++) {
              spush += scanner.nextChar();
              spush += scanner.nextChar();
              opk.size++;
          }
          opk.rest = spush;
          return opk;
          //  $("#opcodes").text($("#opcodes").text() + opcode + "\tJMP\t# ");
          //  var nparfunc = "" + hexavm[0] + hexavm[1];
          //  hexavm = hexavm.substr(2, hexavm.length);
          //  $("#opcodes").text($("#opcodes").text() + nparfunc + "\n");
        }
        /*
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
        */
        else if (opcode == "65")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tCALL\t# \n");
            return OpPack(pvalue, OpType::CALL);
        else if (opcode == "66")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tRET\t# \n");
            return OpPack(pvalue, OpType::RET);
        else if (opcode == "67")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tAPPCALL\t# \n");
            return OpPack(pvalue, OpType::APPCALL);
        else if (opcode == "68") {
            OpPack opk(pvalue, OpType::SYSCALL);
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSYSCALL\t# ");
            //var nparfunc = "" + hexavm[0] + hexavm[1];
            //hexavm = hexavm.substr(2, hexavm.length);
            ///fvalue = parseInt(nparfunc, 16);
            //sfunc = "";
            string spush = "";
            spush += scanner.nextChar();
            spush += scanner.nextChar();
            opk.size++;
            unsigned num = toHex(spush);
            //var i = 0;
            for (int i = 0; i < num; i++) {
                //var codepush = "" + hexavm[0] + hexavm[1];
                //hexavm = hexavm.substr(2, hexavm.length);
                //var cvalue = String.fromCharCode(parseInt(codepush, 16));
                //sfunc += cvalue;
                spush += scanner.nextChar();
                spush += scanner.nextChar();
                opk.size++;
                //if (sfunc == "Neo.Storage")
                //    $("#cbx_storage")[0].checked = true;
                //$("#opcodes").text($("#opcodes").text() + cvalue);
            }
            //$("#opcodes").text($("#opcodes").text() + "\n");
            opk.rest = spush;
            return opk;
        }
        else if (opcode == "69")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tTAILCALL\t# \n");
            return OpPack(pvalue, OpType::TAILCALL);
        else if (opcode == "6a")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDUPFROMALTSTACK\t# \n");
            return OpPack(pvalue, OpType::ALTSTACK);
        else if (opcode == "6b")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tTOALTSTACK\t# Puts the input onto the top of the alt stack. Removes it from the main stack.\n");
            return OpPack(pvalue, OpType::ALTSTACK);
        else if (opcode == "6c")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tFROMALTSTACK\t# Puts the input onto the top of the main stack. Removes it from the alt stack.\n");
            return OpPack(pvalue, OpType::ALTSTACK);
        else if (opcode == "6d")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tXDROP\t# \n");
            return OpPack(pvalue, OpType::XSTACK);
        else if (opcode == "72")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tXSWAP\t# \n");
            return OpPack(pvalue, OpType::XSTACK);
        else if (opcode == "73")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tXTUCK\t# \n");
            return OpPack(pvalue, OpType::XSTACK);
        else if (opcode == "74")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDEPTH\t# Puts the number of stack items onto the stack.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "75")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDROP\t# Removes the top stack item.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "76")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDUP\t# Duplicates the top stack item.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "77")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNIP\t# Removes the second-to-top stack item.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "78")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tOVER\t# Copies the second-to-top stack item to the top.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "79")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPICK\t# The item n back in the stack is copied to the top.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "7a")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tROLL\t# The item n back in the stack is moved to the top.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "7b")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tROT\t# The top three items on the stack are rotated to the left.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "7c")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSWAP\t# The top two items on the stack are swapped.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "7d")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tTUCK\t# The item at the top of the stack is copied and inserted before the second-to-top item.\n");
            return OpPack(pvalue, OpType::STACK);
        else if (opcode == "7e")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tCAT\t# Concatenates two strings.\n");
            return OpPack(pvalue, OpType::STRING);
        else if (opcode == "7f")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSUBSTR\t# Returns a section of a string.\n");
            return OpPack(pvalue, OpType::STRING);
        else if (opcode == "80")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tLEFT\t# Keeps only characters left of the specified point in a string.\n");
            return OpPack(pvalue, OpType::STRING);
        else if (opcode == "81")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tRIGHT\t# Keeps only characters right of the specified point in a string.\n");
            return OpPack(pvalue, OpType::STRING);
        else if (opcode == "82")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSIZE\t# Returns the length of the input string.\n");
            return OpPack(pvalue, OpType::STRING);
        else if (opcode == "83")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tINVERT\t# Flips all of the bits in the input.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "84")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tAND\t# Boolean and between each bit in the inputs.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "85")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tOR\t# Boolean or between each bit in the inputs.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "86")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tXOR\t# Boolean exclusive or between each bit in the inputs.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "87")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tEQUAL\t# Returns 1 if the inputs are exactly equal, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "8b")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tINC\t# 1 is added to the input.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "8c")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDEC\t# 1 is subtracted from the input.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "8d")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSIGN\t# \n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "8f")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNEGATE\t# The sign of the input is flipped.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "90")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tABS\t# The input is made positive.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "91")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNOT\t# If the input is 0 or 1, it is flipped. Otherwise the output will be 0.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "92")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNZ\t# Returns 0 if the input is 0. 1 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "93")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tADD\t# a is added to b.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "94")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSUB\t# b is subtracted from a.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "95")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tMUL\t# a is multiplied by b.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "96")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tDIV\t# a is divided by b.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "97")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tMOD\t# Returns the remainder after dividing a by b.\n");
            return OpPack(pvalue, OpType::ARITHMETIC);
        else if (opcode == "98")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSHL\t# Shifts a left b bits, preserving sign.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "99")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSHR\t# Shifts a right b bits, preserving sign.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "9a")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tBOOLAND\t# If both a and b are not 0, the output is 1. Otherwise 0.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "9b")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tBOOLOR\t# If a or b is not 0, the output is 1. Otherwise 0.\n");
            return OpPack(pvalue, OpType::BITS);
        else if (opcode == "9c")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNUMEQUAL\t# Returns 1 if the numbers are equal, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "9e")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNUMNOTEQUAL\t# Returns 1 if the numbers are not equal, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "9f")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tLT\t# Returns 1 if a is less than b, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "a0")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tGT\t# Returns 1 if a is greater than b, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "a1")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tLTE\t# Returns 1 if a is less than or equal to b, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "a2")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tGTE\t# Returns 1 if a is greater than or equal to b, 0 otherwise.\n");
            return OpPack(pvalue, OpType::COMPARE);
        else if (opcode == "a3")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tMIN\t# Returns the smaller of a and b.\n");
            return OpPack(pvalue, OpType::MINMAXINT);
        else if (opcode == "a4")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tMAX\t# Returns the larger of a and b.\n");
            return OpPack(pvalue, OpType::MINMAXINT);
        else if (opcode == "a5")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tWITHIN\t# Returns 1 if x is within the specified range (left-inclusive), 0 otherwise.\n");
            return OpPack(pvalue, OpType::MINMAXINT);
        else if (opcode == "a7")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSHA1\t# The input is hashed using SHA-1.\n");
            return OpPack(pvalue, OpType::SHA);
        else if (opcode == "a8")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSHA256\t# The input is hashed using SHA-256.\n");
            return OpPack(pvalue, OpType::SHA);
        else if (opcode == "a9")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tHASH160\t# The input is hashed using HASH160.\n");
            return OpPack(pvalue, OpType::HASH);
        else if (opcode == "aa")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tHASH256\t# The input is hashed using HASH256.\n");
            return OpPack(pvalue, OpType::HASH);
        else if (opcode == "ac")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tCHECKSIG\t# \n");
            return OpPack(pvalue, OpType::SIG);
        else if (opcode == "ae")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tCHECKMULTISIG\t# \n");
            return OpPack(pvalue, OpType::SIG);
        else if (opcode == "c0")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tARRAYSIZE\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c1")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPACK\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c2")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tUNPACK\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c3")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tPICKITEM\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c4")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tSETITEM\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c5")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNEWARRAY\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c6")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tNEWSTRUCT\t# \n");
            return OpPack(pvalue, OpType::STRUCT);
        else if (opcode == "c8")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tAPPEND\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "c9")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tREVERSE\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "ca")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tREMOVE\t# \n");
            return OpPack(pvalue, OpType::ARRAY);
        else if (opcode == "f0")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tTHROW\t# \n");
            return OpPack(pvalue, OpType::EXCEPTION);
        else if (opcode == "f1")
            //$("#opcodes").text($("#opcodes").text() + opcode + "\tTHROWIFNOT\t# \n");
            return OpPack(pvalue, OpType::EXCEPTION);
        else {
            //$("#opcodes").text($("#opcodes").text() + opcode + "\t???\t# \n");
            return OpPack(pvalue, OpType::unknown);
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
    int countpybytes = 0;
    for(unsigned i=0; i<vop_py.size(); i++) {
       //cout << vop_py[i] << " ";
       countpybytes += vop_py[i].size;
    }
    //cout << endl;


    cout << "open: " << scs.str() << endl;
    Scanner scanFileCs(new File(scs.str()));
    vector<OpPack> vop_cs = str_opcodes(scanFileCs);
    int countcsbytes = 0;
    for(unsigned i=0; i<vop_cs.size(); i++) {
       //cout << vop_cs[i] << " ";
       countcsbytes += vop_cs[i].size;
    }
    //cout << endl;

    cout << "RESULT_COUNT\tpy\t" << vop_py.size() << "\tcs\t" << vop_cs.size() << "\tratio\t" << vop_cs.size()/double(vop_py.size()) << endl;
    cout << "RESULT_SUMPARAMS\tpy\t" << countpybytes << "\tcs\t" << countcsbytes   << "\tratio\t" << countcsbytes/double(countpybytes) << endl;

    cout << "GROUP_COUNT_PY\t";
    printLineCount(vop_py);
    cout << "GROUP_COUNT_CS\t";
    printLineCount(vop_cs);

    cout << "GROUP_SUMPARAM_PY\t";
    printLineSumParam(vop_py);
    cout << "GROUP_SUMPARAM_CS\t";
    printLineSumParam(vop_cs);
}


int main() {

   string filelist="filelist2.txt";

   Scanner scanner(new File(filelist));

   while(scanner.hasNext()) {
      string path = scanner.nextLine();
      cout << path << endl;
      study1(path);
   }

   cout << "Program finished sucessfully!" << endl;
   return 0;
}
