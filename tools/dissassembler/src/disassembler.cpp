#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

void DissassembleChip8Op(uint8_t *codebuffer, int pc)
{
	uint8_t *code = &codebuffer[pc];
	uint8_t firstNbr = (code[0] >> 4);

	printf("%04x %02x %02x ", pc, code[0],code[1]);
	switch (firstNbr) {
		case 0x00: printf(" not handled yet"); break;
		case 0x01: printf(" not handled yet"); break;
		case 0x02: printf(" not handled yet"); break;
		case 0x03: printf(" not handled yet"); break;
		case 0x04: printf(" not handled yet"); break;
		case 0x05: printf(" not handled yet"); break;
		case 0x06: printf(" not handled yet"); break;
		case 0x07: printf(" not handled yet"); break;
		case 0x08: printf(" not handled yet"); break;
		case 0x09: printf(" not handled yet"); break;
		case 0x0a: printf(" not handled yet"); break;
		case 0x0b: printf(" not handled yet"); break;
		case 0x0c: printf(" not handled yet"); break;
		case 0x0d: printf(" not handled yet"); break;
		case 0x0e: printf(" not handled yet"); break;
		case 0x0f: printf(" not handled yet"); break;
			
	}
}

int main(int argc, char** argv)
{
	ifstream inFile(argv[1], ios_base::in | ios_base::ate | ios_base::binary);
	if(inFile.fail())
	{
		cout << "Error Opening file: " << argv[1] << endl;
		exit(-1);
	}
	unsigned int pc = 0x200;
	unsigned int size = inFile.tellg(); 
	std::vector<unsigned char> v;

	v.reserve(size + 0x200);
	v.insert(v.begin(),
			istream_iterator<unsigned char>(inFile),
			istream_iterator<unsigned char>());


	inFile.seekg(0,ios::beg);
	inFile.close();
	


	while(pc < (size + 0x200))
	{
		DissassembleChip8Op(&v[0],pc);
		pc += 2;
		cout << endl;
	}

	return 0;
}
