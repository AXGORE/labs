#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int enter_str(char** osn_str, char* vsp_str, int* size) {
    int q = 0;
    int n = 1;
    *osn_str = (char*)malloc(1 * sizeof(char));
    while (1) {
        n = scanf("%9[^\n]s", vsp_str);
        if (n == EOF) { return 1; }
        if (n == 0) { return 0; }
        *size += 10;
        *osn_str = (char*)realloc(*osn_str, *size * sizeof(char));
        strcpy(*(osn_str)+q, vsp_str);
        q += 9;
    }
}

void get_word(char** str, int* i, char** l_word) {
    while (((*str)[*i] == ' ' || (*str)[*i] == '\t' || ((*str)[*i] != '1' && (*str)[*i]!='0')) && (*i<strlen(*str))) { *i += 1; }
    if (*i == strlen(*str)) { return; }
    int q = 0;
    int n = 1;
    char*   word = (char*)calloc(n , sizeof(char));
    while ((*str)[*i] != ' ' && (*str)[*i] != '\t' && *i < strlen(*str)) {
        while ((*str)[*i] != ' ' && (*str)[*i] != '\t' && ((*str)[*i] != '1' && (*str)[*i] != '0') && (*i < strlen(*str))) { *i += 1; }
        if ((*str)[*i] == ' ' || (*str)[*i] == '\t' || *i == strlen(*str)) { break; }
            word = (char*)realloc(word, n * sizeof(char));
            strncpy(word+q, &(*str)[*i], 1);
           // *word = (char*)realloc(*word, n * sizeof(char));
            q++;
            *i +=1; 
            n++;
           // printf("\n%d", n);
    }
    *l_word = (char*)calloc(n, sizeof(char));
    strncpy(*l_word, &(word)[0], n-1);
   // *l_word[n - 1] = '\0';
    free(word);
}

void bit(char** word) {	
    if (*word == NULL) { return; }
    int i = 0;
    int num_1 = 0;
    while (i < strlen(*word)) {
        if ((*word)[i] == '1') { num_1++;}
        i++;
    }
    *word = (char*)realloc(*word, (i+3) * sizeof(char));
    if (num_1 % 2 == 0) { 
        (*word)[i] = '0';
        (*word)[i + 1] = '\0';
    }
    else { (*word)[i] = '1';
           (*word)[i + 1] = '\0';
    }
}

void ch(char** osn_str,char** last_str) {
   // char* str = NULL;
    //char* vsp_str=NULL;
    int i=0;
    int n = 0;
    int q = 0;
    int f = 2;
    while (i < strlen(*osn_str)) {
        char* str = NULL;
        get_word(osn_str, &i, &str);  
        bit(&str);
        if (str == NULL) {
            if (n == 0) {
                printf("Try something else");
                return;
            }
            (*last_str)[n - f + 1] = '\0';
            break;
        }
        *last_str = (char*)realloc(*last_str, (strlen(str)+2 + n) * sizeof(char));
        strcpy(*(last_str)+q, str);
        i ++; 
        n = strlen(str) + 2 + n;
        if (i < strlen(*osn_str)) { (*last_str)[n - f] = ' '; }
        q = q + strlen(str) + 1;
        f++;
        free(str);
    }
    if (n == 0) { printf("Try something else"); }
    else
    printf("New line:%s", *last_str);

}

int main(){
    char* osn_str = NULL;
    char* last_str = NULL;
    int size = 0;
    char vsp_str[10];
    int k = 0, r = 0;
    //printf("%d          %d", osn_str, &osn_str);
    while (r != 1) {
        printf("Enter line:");
        r = enter_str(&osn_str, vsp_str, &size);
        if (r != 1) {
            ch(&osn_str, &last_str);
            printf("\n");
            while (getchar() != '\n');
        }
    }
    free(osn_str);
    free(last_str);

    return 0;
}