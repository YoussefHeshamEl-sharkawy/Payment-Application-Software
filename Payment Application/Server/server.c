#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "server.h"

extern ST_accountsDB_t accountsDB[255] = { {5000.0, RUNNING, "12345678912345671"} , {9000.0, RUNNING, "12345678912345672"} 
                                         , {10000.0, BLOCKED, "12345678912345673"}  ,{4000.0, BLOCKED, "12345678912345674"} };

extern ST_transaction_t transactions[255] = {0};
extern ST_transaction_t transactions2[255] = { 0 };

ST_cardData_t cardData1 = { "youssef hesham ahmed" , "12345678912345671" , "05/23" };
ST_cardData_t cardData2 = { "youssef hesham ahmed" , "12345678912345679" , "05/23" };
ST_cardData_t cardData3 = { "youssef hesham ahmed" , "12345678912345673" , "05/23" };

EN_cardError_t cardErrorName , cardErrorPan , cardErrorDate;
ST_terminalData_t terminalData1 = {1000.0 , 100000.00  , "10/10/2022"};
ST_terminalData_t terminalData2 = { 7000.0 , 100000.00  , "10/10/2022" };
ST_terminalData_t terminalData3 = { 8000.0 , 100000.00  , "10/10/2022" };

EN_terminalError_t terminalErrorDate, terminalErrorExpired , terminalErrorMaxAmount , terminalErrorAmount;

ST_accountsDB_t accountRefrence;
ST_accountsDB_t accountRefrence1 = { 5000.0, RUNNING, "12345678912345671" } ;
ST_accountsDB_t accountRefrence2 = { 10000.0, BLOCKED, "12345678912345673" } ;

EN_serverError_t serverError, serverError2, serverError3;

float maxAmount = 100000.00;

ST_transaction_t transData1 , transData2 , transData3 , transData4 , transData5 , transData6;

EN_transState_t transState;

void printEnumServer(EN_serverError_t serverError) {
	switch (serverError) {
	case SERVER_OK: printf("SERVER_OK\n"); break;
	case SAVING_FAILED: printf("SAVING_FAILED\n"); break;
	case TRANSACTION_NOT_FOUND: printf("TRANSACTION_NOT_FOUND\n"); break;
	case ACCOUNT_NOT_FOUND: printf("ACCOUNT_NOT_FOUND\n"); break;
	case LOW_BALANCE: printf("LOW_BALANCE\n"); break;
	case BLOCKED_ACCOUNT: printf("BLOCKED_ACCOUNT\n"); break;
	default: break;


	}

}

void printEnumAccountstate(EN_accountState_t accountstate) {
	switch (accountstate) {
	case RUNNING: printf("RUNNING\n"); break;
	case BLOCKED: printf("BLOCKED\n"); break;
	default: break;


	}

}
void printEnumTransState(EN_transState_t transState) {
	switch (transState) {
	case APPROVED: printf("APPROVED\n"); break;
	case DECLINED_INSUFFECIENT_FUND: printf("DECLINED_INSUFFECIENT_FUND\n"); break;
	case DECLINED_STOLEN_CARD: printf("DECLINED_STOLEN_CARD\n"); break;
	case FRAUD_CARD: printf("FRAUD_CARD\n"); break;
	case INTERNAL_SERVER_ERROR: printf("INTERNAL_SERVER_ERROR\n"); break;
	default: break;
	}

}



EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	for (int i = 0; i < 255; i++) {
		if (!(strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber)))
		{
			accountRefrence->balance = accountsDB[i].balance;
			accountRefrence->state = accountsDB[i].state;
			strcpy_s(accountRefrence->primaryAccountNumber , 20 ,  accountsDB[i].primaryAccountNumber);
			return SERVER_OK;
		}

	}
	return ACCOUNT_NOT_FOUND;


}

void isValidAccountTest(void) {
	printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : isValidAccount \n");
	printf("Test Case 1: account with pan number available in Data base\n");
	printf("Input Data: CardData1 with PAN : 12345678912345671 \n");
	printf("Expected Result: SERVER_OK \n");
	serverError = isValidAccount(&cardData1, &accountRefrence);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);

	printf("Test Case 2: account with pan number not available in the Data base\n");
	printf("Input Data: CardData2 with PAN : 12345678912345679 \n");
	printf("Expected Result: ACCOUNT_NOT_FOUND \n");
	serverError = isValidAccount(&cardData2, &accountRefrence);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);
	


}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == 1)
		return BLOCKED_ACCOUNT;
	else 
		return SERVER_OK;

}

void isBlockedAccountTest(void) {
	printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : isBlockedAccount \n");
	printf("Test Case 1: providing refrence account with running status\n");
	printf("Input Data: accountrefrence1 \n");
	printf("Expected Result: SERVER_OK \n");
	serverError = isBlockedAccount( &accountRefrence1);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);

	printf("Test Case 2: providing refrence account with Blocked status\n");
	printf("Input Data: accountrefrence2 \n");
	printf("Expected Result: BLOCKED_ACCOUNT \n");
	serverError = isBlockedAccount(&accountRefrence2);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);



}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (termData->transAmount > accountRefrence->balance)
		return LOW_BALANCE;
	else
		return SERVER_OK;

}

void isAmountAvailableTest(void) {
	printf("Tester Name: Youssef Hesham Elsharkawy \n Function Name : isAmountAvailable \n");
	printf("Test Case 1: transaction's amount is available\n");
	printf("Input Data:terminalData1 & accountrefrence1 \n");
	printf("Expected Result: SERVER_OK \n");
	serverError = isAmountAvailable(&terminalData1,&accountRefrence1);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);

	printf("Test Case 2: transaction's amount is not available\n");
	printf("Input Data: terminalData2 & accountrefrence1 \n");
	printf("Expected Result: LOW_BALANCE \n");
	serverError = isAmountAvailable(&terminalData2 , &accountRefrence1);// calling the actual function with the above input data
	printf("Actual Result:");
	printEnumServer(serverError);

}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	static uint32_t  seqNum = 100;
	static  uint8_t transNum = 0;
	if (transNum > 255) {
		return SAVING_FAILED;
	}
	else {
		transData->transactionSequenceNumber = seqNum;
		transactions[transNum] = *transData;
		seqNum += 1;
		transNum += 1;
		
		listSavedTransactions();
		return SERVER_OK;
	}
}

void saveTransactionTest(void) {
	EN_serverError_t error;
	printf("Tester Name: Youssef Hesham Elsharkawy \nFunction Name : saveTransaction \n");
	printf("Test Case 1: account doesnt exist\n");
	printf("Input Data:transData2\n");
	printf("Expected Result: FRAUD_CARD \n");
	transState = recieveTransactionData(&transData2);
	error = saveTransaction(&transData2);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 2: INSUFFECIENT FUND\n");
	printf("Input Data:transData3\n");
	printf("Expected Result: DECLINED_INSUFFECIENT_FUND \n");
	transState = recieveTransactionData(&transData3);
	error = saveTransaction(&transData3);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 3: Blocked account\n");
	printf("Input Data:transData4\n");
	printf("Expected Result: DECLINED_STOLEN_CARD \n");
	transState = recieveTransactionData(&transData4);
	error = saveTransaction(&transData4);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 4: Approved transaction\n");
	printf("Input Data:transData1\n");
	printf("Expected Result: APPROVED \n");
	transState = recieveTransactionData(&transData1);
	error = saveTransaction(&transData1);
	printf("Actual Result:");
	printEnumTransState(transState);
}


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	EN_serverError_t error;
	error = isValidAccount(&transData->cardHolderData, &accountRefrence);
	if (error == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		//error = saveTransaction(transData);
		return FRAUD_CARD;
	}
	error = isBlockedAccount(&accountRefrence);
	if (error == BLOCKED_ACCOUNT) {
		transData->transState = DECLINED_STOLEN_CARD;
		//error = saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}
	error = isAmountAvailable(&transData->terminalData, &accountRefrence);
	if (error == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		//error = saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	for (int i = 0; i < 255; i++) {
		if (!(strcmp(transData->cardHolderData.primaryAccountNumber, accountsDB[i].primaryAccountNumber)))
		{
			accountsDB[i].balance -= transData->terminalData.transAmount;
			printf("new balance = %f\n", accountsDB[i].balance);	
		}
	}
	transData->transState = APPROVED;
	//error = saveTransaction(transData);
	if (error == SAVING_FAILED) {
		transData->transState = INTERNAL_SERVER_ERROR;
		//error = saveTransaction(transData);
		return INTERNAL_SERVER_ERROR;
	}

	return APPROVED;

}
void recieveTransactionDataTest(void) {
	printf("Tester Name: Youssef Hesham Elsharkawy \nFunction Name : recieveTransactionData \n");
	printf("Test Case 1: account doesnt exist\n");
	printf("Input Data:transData2\n");
	printf("Expected Result: FRAUD_CARD \n");
	transState = recieveTransactionData(&transData2);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 2: INSUFFECIENT FUND\n");
	printf("Input Data:transData3\n");
	printf("Expected Result: DECLINED_INSUFFECIENT_FUND \n");
	transState = recieveTransactionData(&transData3);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 3: Blocked account\n");
	printf("Input Data:transData4\n");
	printf("Expected Result: DECLINED_STOLEN_CARD \n");
	transState = recieveTransactionData(&transData4);
	printf("Actual Result:");
	printEnumTransState(transState);
	printf("-------------------------------------------\n");
	printf("Test Case 4: Approved transaction\n");
	printf("Input Data:transData1\n");
	printf("Expected Result: APPROVED \n");
	transState = recieveTransactionData(&transData1);
	printf("Actual Result:");
	printEnumTransState(transState);
}






void listSavedTransactions(void) {
	for (int i = 0; i < strlen(transactions); i++) {
		if (transactions[i].transactionSequenceNumber == 0) {
			break;
		}
		printf("##########################\n");
		printf("Transaction Sequence Number = %d\n", transactions[i].transactionSequenceNumber);
		printf("Transaction Date :");
		puts(transactions[i].terminalData.transactionDate);
		printf("Transaction Amount: %f\n" , transactions[i].terminalData.transAmount);
		printf("Transaction State :");
		printEnumTransState(transactions[i].transState);
		printf("Terminal Max Amount : %f\n", transactions[i].terminalData.maxTransAmount);
		printf("cardholder name:");
		puts(transactions[i].cardHolderData.cardHolderName);
		printf("PAN:");
		puts(transactions[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:");
		puts(transactions[i].cardHolderData.cardExpirationDate);
		printf("##########################\n");


	}

}
void listSavedTransactions2(void) {
	for (int i = 0; i < strlen(transactions2); i++) {
		if (transactions2[i].transactionSequenceNumber == 0) {
			break;
		}
		printf("##########################\n");
		printf("Transaction Sequence Number = %d\n", transactions2[i].transactionSequenceNumber);
		printf("Transaction Date :");
		puts(transactions2[i].terminalData.transactionDate);
		printf("Transaction Amount: %f\n", transactions2[i].terminalData.transAmount);
		printf("Transaction State :");
		printEnumTransState(transactions2[i].transState);
		printf("Terminal Max Amount : %f\n", transactions2[i].terminalData.maxTransAmount);
		printf("cardholder name:");
		puts(transactions2[i].cardHolderData.cardHolderName);
		printf("PAN:");
		puts(transactions2[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date:");
		puts(transactions2[i].cardHolderData.cardExpirationDate);
		printf("##########################\n");


	}

}

void listSavedTransactionsTest(void) {
	printf("Tester Name: Youssef Hesham Elsharkawy \nFunction Name : listSavedTransactions \n");
	listSavedTransactions2();
}

int main() {
	transData1.cardHolderData = cardData1;
	transData1.terminalData = terminalData1;

	transData2.cardHolderData = cardData2;
	transData2.terminalData = terminalData2;

	transData3.cardHolderData = cardData1;
	transData3.terminalData = terminalData2;

	transData4.cardHolderData = cardData3;
	transData4.terminalData = terminalData2;

	transactions2[0].cardHolderData = cardData1;
	transactions2[0].terminalData = terminalData1;
	transactions2[0].transactionSequenceNumber = 999;
	transactions2[0].transState = APPROVED;

	transactions2[1].cardHolderData = cardData2;
	transactions2[1].terminalData = terminalData2;
	transactions2[1].transactionSequenceNumber = 1000;
	transactions2[1].transState = FRAUD_CARD;


	
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	//recieveTransactionDataTest();
	//saveTransactionTest();
	listSavedTransactionsTest();

}
