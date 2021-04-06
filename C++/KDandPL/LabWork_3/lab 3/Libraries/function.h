//
//  function.h
//  lab 3
//
//  Created by Belousov Ilya on 10/2/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#ifndef function_h
#define function_h

char *itoa(int number, char *destination, int base) {
  int count = 0;
  do {
    int digit = number % base;
    destination[count++] = (digit > 9) ? digit - 10 +'A' : digit + '0';
  } while ((number /= base) != 0);
    
  destination[count] = '\0';
  int i;
  for (i = 0; i < count / 2; ++i) {
    char symbol = destination[i];
    destination[i] = destination[count - i - 1];
    destination[count - i - 1] = symbol;
  }
  return destination;
}

#endif /* function_h */
