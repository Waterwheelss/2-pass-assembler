#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Global variables
 */

FILE *input_file, *intermediate_file, *symtab; // for pass 1.
char LABEL[10], OPCODE[10], OPERAND[10];       // Variables for input.
int LOCCTR;                                    // Variables for intermediate file.
char CODE[10], MNEMONIC[10];                   // Variables for optab.

/**
 * Pass 1 functions
 */

void pass1();                // pass1 function
void lineHandler();          // Get current line LABEL, OPCODE and OPERAND.
void insertToIntermediate(); // Insert current LABEL, OPCODE, OPERAND and LOCCTR to intermediate file.

/**
 * Pass 2 functions
 */

void pass2(); // pass2 function (not complete yet);

/**
 * Debug functions
 */
void printCurrentLine();

void main()
{
    /**
     * Pass 1.
     */

    // Open input file
    input_file = fopen("input.txt", "r");
    if (!input_file)
    {
        printf("Unable to open input file.");
        exit(1);
    }

    // Open pass 1 output file (intermediate file)
    intermediate_file = fopen("intermediate_file.txt", "w");
    if (!intermediate_file)
    {
        printf("Unable to open intermediate file.");
        exit(1);
    }

    // Exec pass 1 function
    pass1();
}

void pass1()
{
    char line[100];
    char copy_line[100];

    // Handle first line of the input
    fgets(line, sizeof(line), input_file);
    lineHandler(line);

    // If OPCODE is "START"
    if (!strcmp(OPCODE, "START"))
    {
        LOCCTR = atoi(OPERAND);
        fprintf(intermediate_file, "%X %s %s %s", LOCCTR, LABEL, OPCODE, OPERAND);

        // Go to next line
        fgets(line, sizeof(line), input_file);
    }
    lineHandler(line);
    fgets(line, sizeof(line), input_file);
    lineHandler(line);

    // Loop until hit OPCODE is "END"
    // while(strcmp(OPCODE, "END")){

    // }
    printCurrentLine();
}

/**
 * Process input line and get label, opcode and operand.
 */
void lineHandler(char *line)
{
    char string[100], *temp;

    // Clear current line variables when this function is called.
    LABEL[0] = '\0';
    OPCODE[0] = '\0';
    OPERAND[0] = '\0';

    /**
     * ==========Get label==========
     */

    // Copy line
    strcpy(string, line);

    // Check if there are symbol in the label field.
    if (string[0] != '\t')
    {
        // Get label
        temp = strtok(string, "	");

        // Save as current LABEL
        strcpy(LABEL, temp);

        // Get next, (+1 is \t)
        line = line + strlen(LABEL) + 1;
        strcpy(string, line);
    }
    else
    {
        // Get next
        line++;
        strcpy(string, line);
    }

    /**
     * ==========Get OPCODE==========
     */
    temp = strtok(string, "	");

    // Save as current OPCODE
    strcpy(OPCODE, temp);

    line = line + strlen(OPCODE) + 1;
    strcpy(string, line);

    /**
     * ==========Get OPERAND==========
     */

    // Check if there are operand (not space nor break)
    if (string[0] != '\t' || string[0] != '\n')
    {
        temp = strtok(string, " ");
        strcpy(OPERAND, temp);
    }
}

/**
 * Debug functions
 */

/**
 * Print current line
 */
void printCurrentLine()
{
    printf("LABLE: %s\n", LABEL);
    printf("OPCODE: %s\n", OPCODE);
    printf("OPERAND: %s\n", OPERAND);
    printf("LOCCTR: %d\n", LOCCTR);
}