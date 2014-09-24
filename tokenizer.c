/* sexpr_tokenizer.c
 * retrieves tokens from line of input
 *
 * possible tokens:
 * -integer
 * -floating point
 * -string
 * -left parenthesis
 * -right parenthesis
 */

#include <stdio.h> //printf
#include <stdlib.h> //atoi, atof
#include <string.h> //strchr
#include <ctype.h> //isspace, isdigit, isalpha

#define MAXLINE 1024
#define MAXSTRING 300

char line_buffer[MAXLINE];
int idx;

long int token_int;
double token_double;
char token_string[MAXSTRING];

int is_atomic(char c)
{
   if (!(isspace(c)) && !(isdigit(c)) && (c != '[') && (c != ']') && (c != '(') && (c != ')')
         && (c != '.') && (c != '\"'))
      return 1;
   return 0;
}

int is_numeric(char c)
{
   if (isdigit(c) || (c == '.') || (c == 'e') || (c == 'E'))
      return 1;
   return 0;
}

int get_token()
{
   char num_buffer[20];
   int i; //num_buffer

   while (line_buffer[idx] != '\n') {
      if (isspace(line_buffer[idx]))
         idx++;

      else if (isdigit(line_buffer[idx]) || (line_buffer[idx] == '-') || (line_buffer[idx] == '+')) {
         i = 0;
         while(is_numeric(line_buffer[idx]))
            num_buffer[i++] = line_buffer[idx++];
         num_buffer[i] = '\0';

         if (strchr(num_buffer, '.') != NULL) {
            token_double = atof(num_buffer);
            return 2; //signals floating point token found
         }

         else {
            token_int = atoi(num_buffer);
            return 1; //signals integer token found
         }
      }

      else if (is_atomic(line_buffer[idx])) {
         i = 0;
         while (is_atomic(line_buffer[idx]) || isdigit(line_buffer[idx])) 
            token_string[i++] = line_buffer[idx++];
         
         token_string[i] = '\0';
         return 3; //signals atom token found
      }

      else if (line_buffer[idx] == '\"') {
         i = 0;
         idx++;
         while (line_buffer[idx] != '\"')
            token_string[i++] = line_buffer[idx++];
         token_string[i] = '\0';
         idx++;
         return 4; //signals string token found
      }

      else if (line_buffer[idx] == '(') {
         idx++;
         return 5; //signals left parenthesis found
      }

      else if (line_buffer[idx] == ')') {
         idx++;
         return 6; //signals right parenthesis found
      }

      else if (line_buffer[idx] == '[') {
         idx++;
         return 7; //signals left square bracket found
      }

      else if (line_buffer[idx] == ']') {
         idx++;
         return 8; //signals right square bracket found
      }

      else if (line_buffer[idx] == '.') {
         idx++;
         return 9; //signals dot found
      }
   }

   return 0; //signals no token found/end of line
}
