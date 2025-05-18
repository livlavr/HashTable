#ifndef LLISTDUMP_H_
#define LLISTDUMP_H_

LlistErrors        llistDump(LinkedList* llist);
LlistErrors        setDumpFile(LinkedList* llist);
inline LlistErrors processFilename(char* filename);

#endif
