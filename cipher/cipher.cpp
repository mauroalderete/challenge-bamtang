#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cmath"

const char *MESSAGE = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
const char *FREQLANG = "TEOAISRHNUCMDLGWFPYKJBVQX";

int count_digit(int number) {
   return int(log10(number) + 1);
}

void drawFreqLang(const char *freq, unsigned int offset) {

  unsigned int freqLen = strlen(freq);

  if (freqLen <= 0) {
    return;
  }

  unsigned int digits = count_digit(freqLen) + 1;

  char *indexLine = (char*) malloc(freqLen + (freqLen*digits));
  char *symbolLine = (char*) malloc(freqLen + (freqLen*digits));
  int idx;

  // build lines formatted
  sprintf(indexLine, "%d", offset);
  symbolLine[0] = freq[0];
  idx = 1;
  while (freq[idx] != '\0') {
    sprintf(indexLine, "%s %d", indexLine, idx + offset);

    int countSpaces = count_digit(idx + offset);
    char *spaces = (char*) malloc(countSpaces);
    for (unsigned int s=0; s<countSpaces-1 ; s++) {
      spaces[s] = ' ';
    }
    sprintf(symbolLine, "%s %c%s", symbolLine, freq[idx], spaces);

    idx++;
  }

  printf("%s\n", symbolLine);
  printf("%s\n", indexLine);
}

int strreplacement(char *dst, const char *src, char pattern, char target) {

  const int lenmsg = strlen(src);
  strcpy(dst, src);
  dst[lenmsg] = '\0';

  int i = 0;
  for (int idx = 0; idx < lenmsg; idx++) {
    if (dst[idx] == pattern) {
      i++;
      dst[idx] = target;
    }
  }

  return i;
}

char lowercase(char token) {
  if ( token >= 'A' && token <= 'Z' ) {
    return token + ('a' - 'A');
  }

  return token;
}

char isLowercase(char token) {
  return token >= 'a' && token <= 'z';
}

struct error {
  char *message;
};

error * errorf(const char *message) {
  error *e = new error;
  strcpy(e->message, message);

  return e;
}

struct freqData {
  char symbol;
  char replacement;
  int freq;
};

struct freqNode {
  freqNode *next;
  freqData data;
};

struct freqList {
  freqNode *start;
  freqNode *last;
};

error* append(freqList *list, char symbol, int freq) {
  if (list == NULL) {
    return errorf("failed to append a new symbol because list is empty");
  }

  freqNode *newNode = new freqNode;
  newNode->data.symbol = symbol;
  newNode->data.freq = freq;

  if ( list->start == NULL ){
    list->start = newNode;
    list->last = list->start;
    return NULL;
  }

  list->last->next = newNode;
  list->last = list->last->next;

  return NULL;
}

void show(freqList *list) {
  if (list == NULL || list->start == NULL) {
    return;
  }

  int pos = 0;
  freqNode *iter = list->start;
  while (iter != NULL){
    printf("%d => %c:%d\n", pos, iter->data.symbol, iter->data.freq);
    pos++;
    iter = iter->next;
  }
}

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

char *decryptMessage(const char *msg, const char *f) {

  freqList *msgList = new freqList;
  
  error *err = getFreqMessage(msgList, msg);
  if (err != NULL ) {
    printf("ERROR: %s", err->message);
    return NULL;
  }
  
  const int lenlang = strlen(f);
  const int lenmsg = strlen(msg);

  char *msgDecoded = (char *) malloc( lenmsg );
  strcpy(msgDecoded, msg);
  msgDecoded[lenmsg] = '\0';

  freqNode *iter = msgList->start;
  do {
    if (iter->data.freq - 1 >= lenlang) {
      iter = iter->next;
      continue;
    }

    char symbolDecoded = f[iter->data.freq - 1];
    strreplacement(msgDecoded, msgDecoded, iter->data.symbol, symbolDecoded);
    iter = iter->next;
  } while (iter != NULL);

  printf("freqLang:\n%s", f);
  printf("\n");
  show(msgList);
  printf("\n");
  printf("message encoded:\n%s\n", msg);
  printf("\n");
  printf("message decoded:\n%s\n", msgDecoded);
  return NULL;
}

int main() {
  freqList *lista = new freqList;

  error *err = NULL;

  err = getFreqMessage(lista, MESSAGE);
  if (err != NULL) {
    printf("ERROR: %s", err->message);
    return EXIT_FAILURE;
  }

  err = orderDecreasing(lista);
  if (err != NULL) {
    printf("ERROR: %s", err->message);
    return EXIT_FAILURE;
  }

  show(lista);

  drawFreqLang(FREQLANG, 1);

  //index token to decode
  freqNode *iter = lista->start;
  for (unsigned idx = 0; idx < strlen(FREQLANG) && iter != NULL; idx++) {
    iter->data.replacement = FREQLANG[idx];
    iter = iter->next;
  }

  //repalce
  char *buffer = (char*) malloc(strlen(MESSAGE));
  strcpy(buffer, MESSAGE);
  buffer[strlen(MESSAGE)] = '\0';

  freqNode *iter2 = lista->start;
  while (iter2 != NULL) {
    for (int idx = 0; idx < strlen(MESSAGE); idx++){
      if (lowercase(MESSAGE[idx]) == iter2->data.symbol) {
        if (isLowercase(MESSAGE[idx])) {
          buffer[idx] = lowercase(iter2->data.replacement);
        } else {
          buffer[idx] = iter2->data.replacement;
        }
        
      }
    }
    iter2 = iter2->next;
  }

  printf("message is:\n\n");
  printf("%s", buffer);

  // orderFreqList(lista);
  // show(lista);
  // decryptMessage(message, freqLang);
  return 0;
}