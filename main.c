#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "myHeader.h"

int main() {
    system("cls");
    while (1){
        print_main_menu();
        char c = getchar();
        emptyBuffer();
        if(c == '1'){

        }
        else if(c == '2'){

        }
        else if(c == '3'){
            printf("Good Luck!");
            break;
        }else{
            system("cls");
            invalid_input();
        }
    }
    return 0;
}
