#include <stdio.h>
#include <stdlib.h>

/* Structures */
struct counts {
    int retVal;     //
    int bytes;      // Number of bytes in file
    int words;      // Number of words in file
    int newlines;   // Number of lines in file
};

/* Helper Function Declarations */
void usage(char *programName);
struct counts readFile(char *filename, int fromStdIn);


/* Main */
int main(int argc, char *argv[]) {
    /* Initialize */
    struct counts output;
    int fromFile = 0;
    
    /* Parse command line args */
    switch (argc) {
        case 1:     // Read from stdin
            output = readFile("", 1);
            fromFile = 0;
            break;
        case 2:     // Read from file
            output = readFile(argv[1], 0);
            fromFile = 1;
            break;
        default:
            printf("ERROR - INVALID NUMBER OF ARGUMENTS - <%d>\n",argc-1);
            usage(argv[0]);
            exit(1);
            break;
    }
    
    /* Verify Successful Analysis */
    if (output.retVal < 0) {
        printf("ERROR ANALYZING INPUT <%d>\n",output.retVal);
        exit(1);
    }
    
    /* Report File Data */
    printf("%d %d %d %s\n",output.newlines, output.words, output.bytes, fromFile?argv[1]:"");
    
    /* Return */
    return 0;
}

/* Helper Function Definitions */
void usage(char *programName) {
    printf("%s - print newline, word, and byte counts for a file\n",programName);
    printf("USAGE:\n");
    printf("\t%s\t\t- Compute from text typed to stdin\n",programName);
    printf("\t%s FILENAME\t- Compute FILENAME\n",programName);
}
struct counts readFile(char *filename, int fromStdIn) {
    /* Initialize */
    struct counts output;   // Init output struct
    output.retVal = 0;
    output.bytes = 0;
    output.words = 0;
    output.newlines = 0;
    int inWord = 0;         // State Variable
    FILE *fd;               // File Descriptor
    char curChar = ' ';     // Current Character
    
    /* Get File Descriptor */
    if (fromStdIn) {
        fd = stdin;
    } else {
        fd = fopen(filename,"r");
        if (!fd) {
            printf("ERROR OPENING FILE <%s>\n",filename);
            output.retVal = -1;
            return output;
        }
    }
    
    /* Analyze File */
    do {
        // Get Next Character
        curChar = getc(fd);
        
        // Parse char and increment output as appropriate
        switch (curChar) {
            case EOF:               // EOF - Exit on next loop through
                break;
            case '\n':              // Newline - Incr newlines, bytes
                                    //      Set inWord->0
                output.newlines++;
                inWord = 0;
                output.bytes ++;
                break;
            case ' ':               // Whitespace - Incr bytes
            case '\t':              //      Set inWord->0
            case '\r':
                inWord = 0;
                output.bytes ++;
                break;
            default:                // All other chars - Incr words, bytes
                                    //      Set inWord->1
                if (!inWord) {
                    output.words++;
                }
                inWord = 1;
                output.bytes ++;
                break;
        }
    } while(curChar != EOF);
    
    
    /* Close File (if necessary) */
    if (!fromStdIn) {
        char tmp = fclose(fd);
        if (tmp != 0) {
            printf("ERROR CLOSING FILE <%s>\n",filename);
            output.retVal = -2;
            return output;
        }
    }
    
    
    /* Return */
    return output;
}












