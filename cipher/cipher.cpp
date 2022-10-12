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
bool isLowercase(char token) {
  return token >= 'a' && token <= 'z';
}

/**
 * Returns true if the char is a Latin alphabetic's uppercase. Otherwise, returns false.
*/
bool isUppercase(char token) {
  return token >= 'A' && token <= 'Z';
}

/**
 * Returns the lowercase version of the received token if it is a character from the Latin alphabet.
 * Otherwise, it returns the same token unchanged.
*/
char lowercase(char token) {
  if ( isUppercase(token) ) {
    return token + ('a' - 'A');
  }

  return token;
}

/**
 * This section contains structure definitions to handle the character's frequency list of a message.
 * The structure corresponds to a singly linked list.
 * Additional the reference to the head, the list contains a reference to the tail to easily append elements.
*/

/**
 * Data struct to store one character frecuency and his replacement.
*/
struct freqData {
  char symbol;        // The character from message to decrypt.
  char replacement;   // The character to replace int the original message.
  int freq;           // How often the token appears in the message.
};

/**
 * Models a element the character's frequency list.
 * Wraps a character frecuency data model.
*/
struct freqNode {
  freqNode *next;     // Points the next element in the list. Or NULL if is the last element.
  freqData data;      // Stores the element value. Models the data about the character's frequency.
};

/**
 * Data struct to instance a character's frequency list.
*/
struct freqList {
  freqNode *start;    // References to the first element in the list. Values NULL if the list is empty.
  freqNode *last;     // References to the last element in the list. Values NULL if the list is empty.
                      // It's equal the first element if the list contains one element.
};

/**
 * Next section contains the operations to manipualte the list previously defined.
*/

/**
 * Appends a new element in the list.
 * The replacement value will starts empty.
 * Returns an error if the list isn't initialized.
*/
error* append(freqList *list, char symbol, int freq) {
  // Validates the list is initialized.
  if (list == NULL) {
    return errorf("failed to append a new symbol because list is empty");
  }

  // Instance an new element and loaded it.
  freqNode *newNode = new freqNode;
  newNode->data.symbol = symbol;
  newNode->data.freq = freq;
  newNode->data.replacement = 0;

  // List empty.
  if ( list->start == NULL ){
    list->start = newNode;
    list->last = list->start;
    return NULL;
  }

  // Translate the last reference at the new element.
  list->last->next = newNode;
  list->last = list->last->next;

  return NULL;
}

/**
 * Order the list of decreasing way.
 * Returns an error if the list isn't initialized or it hasn't nothing to order.
*/
error *orderDecreasing(freqList *list) {

  if (list == NULL || list->start == NULL) {
    return errorf("could not possible order a empty freq list");
  }

  freqNode *iter = list->start;
  while ( iter != NULL ) {

    freqNode *next = iter->next;
    while (next != NULL) {
      if ( next->data.freq > iter->data.freq ) {
        freqData tmp = next->data;
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
freqNode *getNodeBySymbol(freqList *list, char symbol) {
  if (list == NULL || list->start == NULL) {
    return NULL;
  }

  freqNode *iter = list->start;
  do {
    if (iter->data.symbol == symbol){
      return iter;
    }

    iter = iter->next;
  } while (iter != NULL);

  return NULL;
}

/**
 * Allows increasing the count of appearances of a token passed.
 * Search the token and increase its frequency in 1.
 * If the element there isn't in the list then, it appends this and set its frequency in 1.
 * Returns an error if the list isn't initialized.
*/
error* incFreq(freqList *list, char symbol) {
  if (list == NULL) {
    return errorf("failed to inc freq because list is empty");
  }

  freqNode *foundNode = getNodeBySymbol(list, symbol);
  if (foundNode == NULL){
    error *err = append(list, symbol, 1);
    if (err != NULL) {
      return err;
    }

    return NULL;
  }

  foundNode->data.freq++;

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
error *getFreqMessage(freqList *list, const char *msg) {

  const int len = strlen(msg);

  if ( list == NULL) {
    return errorf("list is required");
  }

  for (int idx = 0; idx < len ; idx++) {
    if ( (msg[idx] < 'a' || msg[idx] > 'z') && (msg[idx] < 'A' || msg[idx] > 'Z') ) {
      continue;
    }

    char token = lowercase(msg[idx]);

    error *err = incFreq(list, token);
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
void indexToken(freqList *list, const char *itable) {
  freqNode *iter = list->start;
  for (unsigned idx = 0; idx < strlen(itable) && iter != NULL; idx++) {
    iter->data.replacement = itable[idx];
    iter = iter->next;
  }
}

/**
 * Takes a list the character's frecuency populate with his respectives replacement tokens
 * and decode a message passed by parameters.
*/
char *decodeMessage(freqList *list, const char* message) {
  char *buffer = (char*) malloc(strlen(message));
  strcpy(buffer, message);
  buffer[strlen(message)] = '\0';

  freqNode *iter2 = list->start;
  while (iter2 != NULL) {
    for (int idx = 0; idx < strlen(message); idx++){
      if (lowercase(message[idx]) == iter2->data.symbol) {
        if (isLowercase(message[idx])) {
          buffer[idx] = lowercase(iter2->data.replacement);
        } else {
          buffer[idx] = iter2->data.replacement;
        }
        
      }
    }
    iter2 = iter2->next;
  }

  return buffer;
}

/**
 * Recives a string message and a language character frequency table
 * and returns the message decrypted.
 * If an error is found then end the process inmeditly.
*/
char *decryptMessage(const char *message, const char *f) {

  freqList *list = new freqList;
  error *err = NULL;
  
  err = getFreqMessage(list, message);
  fatal(err);

  err = orderDecreasing(list);
  fatal(err);

  indexToken(list, f);

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