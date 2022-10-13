#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cmath"

/**
 * This section implements a serie of struct and functions to manipulate expected errors.
*/

/**
 * Implements a simple struct to manipulate errors.
*/
struct error {
  char *message;  // Stores a description of one error.
};

/**
 * Returns a new error with the description string as a value that satisfies error.
*/
error * errorf(const char *message) {
  error *e = new error;
  strcpy(e->message, message);

  return e;
}

/**
 * Prints the error description and stop the current process with a failure exit code.
 * Fatal is equivalent to Print() followed by a call to Exit(EXIT_FAILURE)
*/
void fatal(error *err) {
  if (err != NULL) {
    printf("ERROR: %s", err->message);
    exit(EXIT_FAILURE);
  }
}

/**
 * This section implements util functions to make tipicals manipulates of strings and chars.
*/

/**
 * Returns true if the char is a Latin alphabetic's lowercase. Otherwise, returns false.
*/
bool isLowercase(char value) {
  return value >= 'a' && value <= 'z';
}

/**
 * Returns true if the char is a Latin alphabetic's uppercase. Otherwise, returns false.
*/
bool isUppercase(char value) {
  return value >= 'A' && value <= 'Z';
}

/**
 * Returns the lowercase version of the received token if it is a character from the Latin alphabet.
 * Otherwise, it returns the same token unchanged.
*/
char lowercase(char value) {
  if ( isUppercase(value) ) {
    return value + ('a' - 'A');
  }

  return value;
}

/**
 * This section contains structure definitions to handle the character's frequency list of a message.
 * The structure corresponds to a singly linked list.
 * Additional the reference to the head, the list contains a reference to the tail to easily append elements.
*/

/**
 * Data struct to store one character frecuency and his replacement.
*/
struct charFreqData {
  char token;        // The character from message to decrypt.
  char replacement;   // The character to replace int the original message.
  int frequency;           // How often the token appears in the message.
};

/**
 * Models a element the character's frequency list.
 * Wraps a character frecuency data model.
*/
struct charFreqNode {
  charFreqNode *next;     // Points the next element in the list. Or NULL if is the last element.
  charFreqData data;      // Stores the element value. Models the data about the character's frequency.
};

/**
 * Data struct to instance a character's frequency list.
*/
struct charFreqList {
  charFreqNode *head;    // References to the first element in the list. Values NULL if the list is empty.
  charFreqNode *tail;     // References to the last element in the list. Values NULL if the list is empty.
                      // It's equal the first element if the list contains one element.
};

/**
 * Next section contains the operations to manipualte the list previously defined.
*/

/**
 * Appends a new element in the list.
 * Returns an error if the list isn't initialized.
*/
error* charFreqList_Append(charFreqList *list, char token, int frequency, char replacement) {
  // Validates the list is initialized.
  if (list == NULL) {
    return errorf("failed to append a new symbol because list is empty");
  }

  // Instance an new element and loaded it.
  charFreqNode *newNode = new charFreqNode;
  newNode->data.token = token;
  newNode->data.frequency = frequency;
  newNode->data.replacement = replacement;

  // List empty.
  if ( list->head == NULL ){
    list->head = newNode;
    list->tail = list->head;
    return NULL;
  }

  // Translate the last reference at the new element.
  list->tail->next = newNode;
  list->tail = list->tail->next;

  return NULL;
}

/**
 * Order the list of decreasing way.
 * Returns an error if the list isn't initialized or it hasn't nothing to order.
*/
error *charFreqList_SortDescending(charFreqList *list) {

  if (list == NULL || list->head == NULL) {
    return errorf("could not possible order a empty freq list");
  }

  charFreqNode *iter = list->head;
  while ( iter != NULL ) {

    charFreqNode *next = iter->next;
    while (next != NULL) {
      if ( next->data.frequency > iter->data.frequency ) {
        charFreqData tmp = next->data;
        next->data = iter->data;
        iter->data = tmp;
      }
      next = next->next;
    }

    iter = iter->next;
  }

  return NULL;
}

/**
 * Search the first element that match with the token passed by the parameter and returns it.
 * if no match is found, returns NULL.
 * if the list isn't initilized or is empty, returns NULL.
*/
charFreqNode *charFreqList_GetElementByToken(charFreqList *list, char token) {
  if (list == NULL || list->head == NULL) {
    return NULL;
  }

  charFreqNode *iter = list->head;
  do {
    if (iter->data.token == token){
      return iter;
    }

    iter = iter->next;
  } while (iter != NULL);

  return NULL;
}

/**
 * Allows increasing the count of appearances of a token passed.
 * Search the token and increase its frequency in 1.
 * If the element there isn't in the list then,
 * it appends this and set its frequency in 1 and its replacement token in char(0).
 * Returns an error if the list isn't initialized.
*/
error* charFreqList_IncreaseFrequency(charFreqList *list, char token) {
  if (list == NULL) {
    return errorf("failed to inc freq because list is empty");
  }

  charFreqNode *foundNode = charFreqList_GetElementByToken(list, token);
  if (foundNode == NULL){
    error *err = charFreqList_Append(list, token, 1, 0);
    if (err != NULL) {
      return err;
    }

    return NULL;
  }

  foundNode->data.frequency++;

  return NULL;
}

/**
 * Refill a new character's frequency list from a message passed by parameters.
 * Only map the tokens that match with the letter of the Latin alphabet (a-z).
 * It does not distinguish between uppercase and lowercase.
 * Store all tokens in lowercase.
 * Any token that does not match the letter of the Latin alphabet (a-z) will be stored unchanged.
 * Returns an error if the list isn't initialized.
*/
error *charFreqList_RefillFromMessage(charFreqList *list, const char *msg) {

  const int len = strlen(msg);

  if ( list == NULL) {
    return errorf("list is required");
  }

  for (int idx = 0; idx < len ; idx++) {
    if ( (msg[idx] < 'a' || msg[idx] > 'z') && (msg[idx] < 'A' || msg[idx] > 'Z') ) {
      continue;
    }

    char token = lowercase(msg[idx]);

    error *err = charFreqList_IncreaseFrequency(list, token);
    if (err != NULL) {
      return err;
    }
  }

  return NULL;
}

/**
 * This section contains the primitives to handle decryption process.
*/

/**
 * Populates a character frequency list with the tokens that should be used to replace in the message.
 * It takes an ordered list and assigns the token to replace based on the token position in a language character frequency table.
 * 
 * For example, if we take the ordered frequency list "XYZ" and a lang table "ABCDE", then,
 * the first element on the list 'X' must be replaced with the first token in the lang table,
 * in this case, 'A'.
 * 
 * This function allows the relationship between both tokens and stores them in the list.
*/
void charFreqList_PopulateWithReplacementTokens(charFreqList *list, const char *tableLang) {
  charFreqNode *iter = list->head;
  for (unsigned idx = 0; idx < strlen(tableLang) && iter != NULL; idx++) {
    iter->data.replacement = tableLang[idx];
    iter = iter->next;
  }
}

/**
 * Takes a list the character's frecuency populate with his respectives replacement tokens
 * and decode a message passed by parameters.
*/
char *decodeMessage(charFreqList *list, const char* message) {
  char *decoded = (char*) malloc(strlen(message));
  strcpy(decoded, message);
  decoded[strlen(message)] = '\0';

  charFreqNode *iter2 = list->head;
  while (iter2 != NULL) {
    // With each item listed I loop through the entire message...
    for (int idx = 0; idx < strlen(message); idx++){

      // looking for matching tokens to replace.
      if (lowercase(message[idx]) == iter2->data.token) {

        // I replace maintaining the lower or upper case of the original message.
        if (isLowercase(message[idx])) {
          decoded[idx] = lowercase(iter2->data.replacement);
        } else {
          decoded[idx] = iter2->data.replacement;
        }
      }
    }
    iter2 = iter2->next;
  }

  return decoded;
}

/**
 * Recives a string message and a language character frequency table
 * and returns the message decrypted.
 * If an error is found then end the process inmeditly.
*/
char *decryptMessage(const char *message, const char *tableLang) {

  // Instances a new list to store the character frequencies.
  charFreqList *list = new charFreqList;
  error *err = NULL;
  
  // Fill the list with the character frequencies from a message.
  err = charFreqList_RefillFromMessage(list, message);
  fatal(err);

  // Sorts the list in descending way. The tokens most frequent will be first.
  err = charFreqList_SortDescending(list);
  fatal(err);

  // Indexes the list with the language character frequency table
  charFreqList_PopulateWithReplacementTokens(list, tableLang);

  // Uses the language character frequency table to decode the message.
  char *messageDecoded = decodeMessage(list, message);

  return messageDecoded;
}

int main() {
  const char *message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
  const char *freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";

  char *decripted = decryptMessage(message, freqLang);

  printf("%s", decripted);

  printf("\n"); //prettier outlet

  exit(EXIT_SUCCESS);
}