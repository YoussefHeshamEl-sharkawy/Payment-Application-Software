
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "card.h"
ST_cardData_t cardData;
EN_cardError_t cardError, cardError2;




EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
  
    printf("Please enter the name of the card holder:");
    gets(cardData->cardHolderName);
    fflush(stdin);
    if (strlen(cardData->cardHolderName) < 24 && strlen(cardData->cardHolderName) > 19) {
        for (int i = 0; i < strlen(cardData->cardHolderName); i++) {
            if (!isalpha(cardData->cardHolderName[i]) && !(cardData->cardHolderName[i] == ' '))
                return WRONG_NAME;
        }
        return CARD_OK;
    }
    else
        return WRONG_NAME;
}

void getCardHolderNameTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : getCardHolderName \n");
    printf("Test Case 1: \n");
    printf("Input Data: Youssef hesham ahmed abdalla \n");
    printf("Expected Result: WRONG_NAME \n");
    cardError = getCardHolderName(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);
    
    printf("Test Case 2: \n");
    printf("Input Data: Youss1f hesham ahm1d \n");
    printf("Expected Result: WRONG_NAME \n");
    cardError = getCardHolderName(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);
   
    printf("Test Case 3: \n");
    printf("Input Data: Youssef hesham\n");
    printf("Expected Result: WRONG_NAME \n");
    cardError = getCardHolderName(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);
   
    printf("Test Case 4: \n");
    printf("Input Data: Youssef hesham ahmed\n");
    printf("Expected Result: CARD_OK \n");
    cardError = getCardHolderName(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    printf("Please enter the expiry date of the card : ");
    char trial[20];
    fgets(trial , 10, stdin);
    fflush(stdin);
  // puts(trial);
    //printf("%d %d\n", strlen(trial) , trial[5]);
    if (trial[5] != '\n') {
        
        return WRONG_EXP_DATE;
    }
    else {
        trial[5] = '\0';
        strcpy(cardData->cardExpirationDate, trial);
        cardData->cardExpirationDate[5] = '\0';
    }
        
    if (strlen(cardData->cardExpirationDate) == 5) {
        if (cardData->cardExpirationDate[2] == '/') {
            for (int i = 0; i < 5; i++) {
                char x = cardData->cardExpirationDate[i];
                if (i == 2) {
                    
                }
                else if (!(x >= 48 && x <= 57)) {
               
                    return WRONG_EXP_DATE;
                }
            }
            return CARD_OK;
        }
        else
         
            return WRONG_EXP_DATE;
    }
   else
        return WRONG_EXP_DATE;
}

void getCardExpiryDateTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : getCardExpiryDate \n");
    printf("Test Case 1: \n");
    printf("Input Data: 1/2\n");
    printf("Expected Result: WRONG_EXP_DATE \n");
    cardError = getCardExpiryDate(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 2: \n");
    printf("Input Data: i1/02\n");
    printf("Expected Result: WRONG_EXP_DATE \n");
    cardError = getCardExpiryDate(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 3: \n");
    printf("Input Data: 12-22\n");
    printf("Expected Result: WRONG_EXP_DATE \n");
    cardError = getCardExpiryDate(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 4: \n");
    printf("Input Data: 12/2011\n");
    printf("Expected Result: WRONG_EXP_DATE \n");
    cardError = getCardExpiryDate(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 5: \n");
    printf("Input Data: 12/23\n");
    printf("Expected Result: CARD_OK \n");
    cardError = getCardExpiryDate(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    printf("please enter the card's PAN number : ");
    gets(cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber) <= 19 && strlen(cardData->primaryAccountNumber) >= 16) {
        for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
            if (!isdigit(cardData->primaryAccountNumber[i]))
                return WRONG_NAME;
        }

        return CARD_OK;
    }


    else
        return WRONG_PAN;
}

void getCardPANTest(void) {
    printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : getCardPAN \n");
    printf("Test Case 1: pan number too big\n");
    printf("Input Data: 123456789123456789123456789\n");
    printf("Expected Result: WRONG_PAN \n");
    cardError = getCardPAN(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 2: pan too small \n");
    printf("Input Data: 123456789\n");
    printf("Expected Result: WRONG_PAN \n");
    cardError = getCardPAN(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 3: pan containg a letter\n");
    printf("Input Data: 123456789123456y1234567\n");
    printf("Expected Result: WRONG_PAN \n");
    cardError = getCardPAN(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

    printf("Test Case 4: correct pan\n");
    printf("Input Data: 1234567891234567\n");
    printf("Expected Result: CARD_OK \n");
    cardError = getCardPAN(&cardData);// calling the actual function with the above input data
    printf("Actual Result:");
    printEnumString(cardError);

}

void printEnumString(EN_cardError_t cardError) {
    switch (cardError) {
    case CARD_OK: printf("CARD_OK\n"); break;
    case WRONG_NAME: printf("WRONG_NAME\n"); break;
    case WRONG_PAN: printf("WRONG_PAN\n"); break;
    case WRONG_EXP_DATE: printf("WRONG_EXP_DATE\n"); break;
    default: break;


    }

}




//int main() {
//     //getCardHolderNameTest();
//   //getCardExpiryDateTest();
//     // getCardPANTest();
//
//
//}
