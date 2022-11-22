#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "app.h"


ST_cardData_t cardData;
EN_cardError_t cardErrorName, cardErrorPan, cardErrorDate;
ST_terminalData_t terminalData;
EN_terminalError_t terminalErrorDate, terminalErrorExpired, terminalErrorSetMaxAmount, terminalErrorAmount , terminalErrorMaxAmount;
ST_accountsDB_t accountRefrence;
EN_serverError_t serverErrorValidAccount, serverError2, serverError3;
float maxAmountapp = 20000.00;
extern uint8_t flag = 0;

EN_transState_t transState;


void appStart(void) {
	
	cardErrorName = getCardHolderName(&cardData);
	printEnumString(cardErrorName);

	
	if (cardErrorName == WRONG_NAME || flag == 1 ) {
		printf("please re-enter the correct name \n");
		while (1) {
			
			cardErrorName = getCardHolderName(&cardData);
			
			if (cardErrorName == CARD_OK) {
				printEnumString(cardErrorName);
				break;
			}
		}

	}

	cardErrorDate = getCardExpiryDate(&cardData);
	printEnumString(cardErrorDate);
	if (cardErrorDate == WRONG_EXP_DATE) {
		printf("please re-enter the correct EXP date \n");
		while (1) {
			cardErrorDate = getCardExpiryDate(&cardData);
			if (cardErrorDate == CARD_OK) {
				printEnumString(cardErrorDate);
				break;
			}
		}

	}

	cardErrorPan = getCardPAN(&cardData);
	printEnumString(cardErrorPan);
	if (cardErrorPan == WRONG_PAN) {
		printf("please re-enter the correct PAN \n");
		while (1) {
			cardErrorPan = getCardPAN(&cardData);
			if (cardErrorPan == CARD_OK) {
				printEnumString(cardErrorPan);
				break;
			}
		}

	}



	terminalErrorDate = getTransactionDate(&terminalData);
	printEnumTerminal(terminalErrorDate);
	if (terminalErrorDate == WRONG_DATE) {
		printf("please re-enter the transaction date  \n");
		while (1) {
			terminalErrorDate = getTransactionDate(&terminalData);
			if (terminalErrorDate == TERMINAL_OK) {
				printEnumTerminal(terminalErrorDate);
				break;
			}
		}

	}

	terminalErrorExpired = isCardExpired(&cardData, &terminalData);
	if (terminalErrorExpired == EXPIRED_CARD) {
		printf("transaction couldn't be completed, the card is expired. ");
		return;
	}
	
	printEnumTerminal(terminalErrorExpired);
	terminalErrorAmount = getTransactionAmount(&terminalData);
	if (terminalErrorAmount == INVALID_AMOUNT) {
		printf("please enter a correct amount \n");
		while (1) {
			terminalErrorAmount = getTransactionAmount(&terminalData);
			if (terminalErrorAmount == TERMINAL_OK) {
				printEnumTerminal(terminalErrorAmount);
				break;
			}

		}
	}
	terminalErrorSetMaxAmount = setMaxAmount(&terminalData, maxAmountapp);
	printf(" terminal's Max amount = %f\n", terminalData.maxTransAmount);
	terminalErrorMaxAmount = isBelowMaxAmount(&terminalData);
	if (terminalErrorMaxAmount == EXCEED_MAX_AMOUNT) {
		printf("Declined amount exceeding limit.\n");
		return;
	}
	printEnumTerminal(terminalErrorMaxAmount);

	ST_transaction_t transData = { cardData , terminalData , APPROVED , 0 };
	transState = recieveTransactionData(&transData);

	if (transState == FRAUD_CARD) {
		printf(" couldn't find the account.\n Transaction declined fraud card.\n");
		return;
	}

	if (transState == DECLINED_STOLEN_CARD) {
		printf(" the account is blocked. \n Transaction declined stolen card.\n");
		return;
	}

	if (transState == DECLINED_INSUFFECIENT_FUND) {
		printf(" Declined insuffecient funds. \n");
		return;
	}

	if (transState == INTERNAL_SERVER_ERROR) {
		printf(" transaction wasn't completed, saving error. \n");
		return;
	}














	

}

//int main() {
//	
//		appStart();
//	
//}