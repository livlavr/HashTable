#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "llistErrors.h"
#include "custom_asserts.h"
#include "llist.h"
#include "llistDump.h"

static const size_t SIZE_OF_BUFFER = 40;

LlistErrors llistDump(LinkedList* llist) {
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);

    FILE* dump_file = fopen("Dump-source/dump.dot", "w");

    warning(dump_file, LINKED_LIST_FILE_OPEN_ERROR);

    //Header of graphviz file
    fprintf(dump_file, "digraph llist{\nsplines=ortho;\nrankdir=HR;\nnodesep=0.4;"
                       "\nnode [shape=record, fontname=\"Arial\"];\n"
                       "edge [style=bold, color=\"#009700:black;0.001\", weight=10, penwidth=2.5, "
                       "arrowsize=0.4];\n");

    //Output zero index (service element)
    fprintf(dump_file, "0 ");
    fprintf(dump_file, "[style = \"filled, rounded\", fillcolor=\"#1fcbf2\", label=\" {index = %d | data = %s | next = %d | prev = %d}\" ];\n", 0, llist->data[0].key, llist->next[0], llist->prev[0]);

    //Output all other elements
    int i = 1;
    for(i = 1; i < llist->capacity; i++) {
        fprintf(dump_file, "%d ", i);
        fprintf(dump_file, "[style = \"filled, rounded\", fillcolor=\"#f2291f\", label=\" {index = %d | data = %s | next = %d | prev = %d}\" ];\n", i, llist->data[i].key, llist->next[i], llist->prev[i]);
    }

    //Output size of linked-list
    fprintf(dump_file, "size ");
    fprintf(dump_file, "[style = \"filled, rounded\", fillcolor=\"#ffe41f\", label=\" {size = %d}\" ];\n", llist->size);

    //Output first free cell
    fprintf(dump_file, "free [style = \"filled, rounded\", fillcolor=\"#26e5a2\", label=\"free = %d\" ];\n", llist->free);

    //Change color of all free elements to green
    i = llist->free;
    int count_elements = 0;
    while(i != 0) {
        if(count_elements >= llist->capacity) {
            color_printf(RED_COLOR, BOLD, "ERROR: too many iterations in Dump\n");
            color_printf(RED_COLOR, BOLD, "Probably you did invalid operation (Used bad index for example)\n");

            warning(count_elements < llist->capacity, LINKED_LIST_PROGRAM_ERROR);
        }
        fprintf(dump_file, "%d ", i);
        fprintf(dump_file, "[style = \"filled, rounded\", fillcolor=\"#26e5a2\"];\n");

        i = llist->next[i];
        count_elements++;
    }

    //Set rank
    fprintf(dump_file, "{ rank = same; ");
    for(i = 0; i < llist->capacity; i++) {
        fprintf(dump_file, "%d; ", i);
    }
    fprintf(dump_file, "}\n");

    //Set "next" relations (green arrows)
    fprintf(dump_file, "free->%d;\n", llist->free);
    for(i = 0; i < llist->capacity; i++) {
        if(i && llist->next[i]) {
            fprintf(dump_file, "%d->%d;\n", i, llist->next[i]);
        }
    }
    fprintf(dump_file, "0->%d;\n", llist->next[0]);
    fprintf(dump_file, "%d->0;\n", llist->prev[0]);

    //Change arrows color
    fprintf(dump_file, "edge [style=bold, color=\"#891728:black;0.001\", weight=0, penwidth=2.5, arrowsize=0.4];\n");

    //Set "prev" relations (red arrows)
    i = 0;
    count_elements = 0;
    do {
        if(count_elements >= llist->capacity) {
            color_printf(RED_COLOR, BOLD, "ERROR: too many iterations in Dump\n");
            color_printf(RED_COLOR, BOLD, "Probably you did invalid operation (Used bad index for example)\n");

            warning(count_elements < llist->capacity, LINKED_LIST_PROGRAM_ERROR);
        }
        fprintf(dump_file, "%d->%d;\n", i, llist->prev[i]);
        i = llist->prev[i];
        count_elements++;
    } while(i != 0);

    fprintf(dump_file, "}\n");

    fclose(dump_file);

    char system_duffer[100] = "";
    strcat(system_duffer, "dot -Tpng Dump-source/dump.dot -o ");
    strcat(system_duffer, llist->dump_file);

    int system_status = system(system_duffer);
    warning(system_status != -1, LINKED_LIST_PROGRAM_ERROR);

    return LINKED_LIST_SUCCESS;
}

LlistErrors setDumpFile(LinkedList* llist)
{
    warning(llist, LINKED_LIST_NULL_PTR_ERROR);

    char *buffer = (char*)calloc(SIZE_OF_BUFFER, sizeof(char));
    warning(buffer, LINKED_LIST_ALLOCATION_ERROR);

    time_t my_time          = time(NULL);
    char*  time             = ctime(&my_time);
    time[strlen(time) - 1]  = '\0';
    size_t time_char_length = strlen(time) - 1;
    const char *folder_name = "Llist-dumps/";

    int system_status = system("mkdir -p Llist-dumps");
    warning(system_status != -1, LINKED_LIST_PROGRAM_ERROR);

    strcpy(buffer, folder_name);
    strncpy(buffer + strlen(folder_name), time, time_char_length);
    strcat(buffer, ".png");

    processFilename(buffer);

    llist->dump_file = buffer;

    return LINKED_LIST_SUCCESS;
}

inline LlistErrors processFilename(char* filename) {
    warning(filename, LINKED_LIST_NULL_PTR_ERROR);

    char* filename_ptr = filename;
    filename_ptr = strchr(filename_ptr, ' ');
    while(filename_ptr != NULL)
    {
        *filename_ptr = '_';
        filename_ptr  = strchr(filename_ptr, ' ');
    }

    return LINKED_LIST_SUCCESS;
}
