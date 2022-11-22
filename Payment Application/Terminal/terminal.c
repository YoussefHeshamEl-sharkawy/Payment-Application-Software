#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<stdint.h>
#include <string.h>
#include <ctype.h>
#include "terminal.h"

ST_cardData_t cardData = {"youssef hesham ahmed" ,"1234567891234567", "05/23"  };
EN_cardError_t cardError;
ST_terminalData_t terminalData;
EN_terminalError_t terminalError, terminalError2, terminalError3;
float maxAmount1 = -20000.00;
float maxAmount2 = 20000.00;

void printEnumTerminal(EN_terminalError_t terminalError) {
    switch (terminalError) {
    case TERMINAL_OK: printf(" TERMINAL_OK\n"); break;
    case WRONG_DATE: printf(" WRONG_DATE\n"); break;
    case EXPIRED_CARD: printf(" EXPIRED_CARD\n"); break;
    case INVALID_CARD: printf(" INVALID_CARD\n"); break;
    case INVALID_AMOUNT: printf(" INVALID_AMOUNT\n"); break;
    case EXCEED_MAX_AMOUNT: printf(" EXCEED_MAX_AMOUNT\n"); break;
    case INVALID_MAX_AMOUNT: printf(" INVALID_MAX_AMOUNT\n"); break;
    default: break;
    }
}


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    printf("Please enter the transactions date: ");
    char trial[20] = { 0 };
    fgets(trial, 20, stdin);
    fflush(stdin);
    if (trial[10] != '\n') {
        trial[10] = '\0';
        return WRONG_DATE;
    }
    else {
        strcpy(termData->transactionDate, trial);
        termData->transactionDate[10] = '\0';
    }
    if (strlen(termData->transactionDate) == 10) {
        if (termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/') {
            for (int i = 0; i < 10; i++) {
                if (i == 2 || i==5 ) {
                    
                }
                else if (!(isdigit(termData->transactionDate[i]))) {
                    return WRONG_DATE;
                }
            }

            return TERMINAL_OK;
        }
        else
            return WRONG_DATE;

    }
    else
        return WRONG_DATE;

}

void getTransactionDateTest(void) {

    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionDate \n");
    printf("Test Case 1: wrong format less than 10 char\n");
    printf("Input Data: 10/10/22 \n");
    printf("Expected Result: WRONG_DATE \n");
    terminalError = getTransactionDate(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionDate \n");
    printf("Test Case 2: wrong format more than 10 char\n");
    printf("Input Data: 10/10/20212 \n");
    printf("Expected Result: WRONG_DATE \n");
    terminalError = getTransactionDate(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionDate \n");
    printf("Test Case 3: 10 char but not in dd/mm/yyyy format\n");
    printf("Input Data: 10/10-2022 \n");
    printf("Expected Result: WRONG_DATE \n");
    terminalError = getTransactionDate(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionDate \n");
    printf("Test Case 4: 10 char but containg a letter\n");
    printf("Input Data: 10/i0/2022 \n");
    printf("Expected Result: WRONG_DATE \n");
    terminalError = getTransactionDate(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionDate \n");
    printf("Test Case 5: 10 char in correct format\n");
    printf("Input Data: 10/10/2022 \n");
    printf("Expected Result: TERMINAL_OK \n");
    terminalError = getTransactionDate(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);


}

    //mm/yy
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
    uint8_t month = 0;
    uint8_t year = 0;
    if (cardData->cardExpirationDate[3] > termData->transactionDate[8]) {
        year = 1;
    }
    else
    {
        if ((cardData->cardExpirationDate[3] == termData->transactionDate[8]) && (cardData->cardExpirationDate[4] > termData->transactionDate[9])) {
            year = 1;
        }

    }
    if (cardData->cardExpirationDate[0] > termData->transactionDate[3]) {
        month = 1;
    }
    else
    {
        if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) {
            month = 0;
        }
        else {
             if (cardData->cardExpirationDate[1] > termData->transactionDate[4]) {
            month = 1;
             }
        }
    }

  
    if ((year) || (month && !year))
        return TERMINAL_OK;
    else
        return EXPIRED_CARD;
}

void isCardExpriedTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : isCardExpried \n");
    printf("Test Case 1: card exp. date is 05/23\n");
    printf("Input Data: 10/10/2023 \n");
    printf("Expected Result: EXPIRED_CARD \n");
    terminalError = getTransactionDate(&terminalData);
    terminalError = isCardExpired(&cardData , &terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : isCardExpried \n");
    printf("Test Case 2: card exp. date is 05/23\n");
    printf("Input Data: 10/10/2022 \n");
    printf("Expected Result: TERMINAL_OK \n");
    terminalError = getTransactionDate(&terminalData);
    terminalError = isCardExpired(&cardData, &terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("please enter the transaction amount : ");
    scanf_s("%f", &termData->transAmount);
    if (termData->transAmount <= 0) {
        termData->transAmount = 0;
        return INVALID_AMOUNT;
    }
    else
        return TERMINAL_OK;
}

void getTransactionAmountTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionAmount \n");
    printf("Test Case 1: negative number\n");
    printf("Input Data: -1000 \n");
    printf("Expected Result: INVALID_AMOUNT \n");
    terminalError = getTransactionAmount(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : getTransactionAmount \n");
    printf("Test Case 2: positive number\n");
    printf("Input Data: 1000 \n");
    printf("Expected Result: TERMINAL_OK \n");
    terminalError = getTransactionAmount(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
    if (maxAmount <= 0) {
        return INVALID_MAX_AMOUNT;
    }
    else {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }

}

void setMaxAmountTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : setMaxAmount \n");
    printf("Test Case 1: negative\n");
    printf("Input Data: -20000 \n");
    printf("Expected Result: INVALID_MAX_AMOUNT \n");
    terminalError = setMaxAmount(&terminalData , maxAmount1);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : isBelowMaxAmount \n");
    printf("Test Case 2: positive\n");
    printf("Input Data: 20000 \n");
    printf("Expected Result: TERMINAL_OK \n");
    terminalError = setMaxAmount(&terminalData , maxAmount2);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}

void isBelowMaxAmountTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : isBelowMaxAmount \n");
    printf("Test Case 1: higher than max amount\n");
    printf("Input Data: 30000 \n");
    terminalData.transAmount = 30000;
    printf("Expected Result: EXCEED_MAX_AMOUNT \n");
    terminalError = isBelowMaxAmount(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);

    printf("\nTester Name: Youssef Hesham Elsharkawy \n Function Name : isBelowMaxAmount \n");
    printf("Test Case 2: lower than the max amount\n");
    printf("Input Data: 5000 \n");
    terminalData.transAmount = 5000;
    printf("Expected Result: TERMINAL_OK \n");
    terminalError = isBelowMaxAmount(&terminalData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumTerminal(terminalError);
}




int main() {
//
//    //getTransactionDateTest();
//   // isCardExpriedTest();
//   // getTransactionAmountTest();
//    setMaxAmountTest();
//    isBelowMaxAmountTest();
//
//
    }
    
	
