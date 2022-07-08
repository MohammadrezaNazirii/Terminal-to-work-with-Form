#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "myHeader.h"

int main() {
    system("cls");
    while (1){
        print_main_menu();
        char c = getchar();
        emptyBuffer();
        if(c == '1'){
            while(1){
                system("cls");
                print_design_menu();
                c = getchar();
                emptyBuffer();
                if (c == '1' || c == '2') {
                    int x, y;
                    char name[100], name_for_print[100];
                    if (c == '1'){//New
                        system("cls");
                        while (1) {
                            system("cls");
                            printf("Please enter a name for your form... ");
                            scanf("%s", name);
                            strcpy(name_for_print, name);
                            emptyBuffer();
                            strcat(name, ".txt");
                            if (!exist_file(name))
                                break;
                            else {
                                printf("You have a form with this name!\nDo you want to rewrite it?\nType 1 if you want to rewrite it or type any character to enter new name\n");
                                c = getchar();
                                emptyBuffer();
                                if (c == '1')
                                    break;
                            }
                        }
                        printf("Please enter dimensions of form separated by space(First number for width and Second number for height)... ");
                        scanf("%d %d", &x, &y);
                        emptyBuffer();
                        allocate_lines(x, y);
                        initialize_lines(x, y);
                        save_file(name, x, y);
                    }else{//Edit
                        system("cls");
                        while(1){
                            system("cls");
                            printf("Please enter the name of your form... ");
                            scanf("%s", name);
                            strcpy(name_for_print, name);
                            emptyBuffer();
                            strcat(name, ".txt");
                            if(exist_file(name))
                                break;
                            else {
                                printf("Can't find form with this name.\nTry again!");
                                Sleep(2500);
                            }
                        }
                    }
                    while (1){
                        read_file(name, &x, &y);
                        system("cls");
                        print_lines(y, name_for_print);
                        print_designNew_menu();
                        c = getchar();
                        emptyBuffer();
                        char label[100];
                        int xx, yy, width, height, len;
                        if(c == '1'){
                            get_data_from_user(1, &xx, &yy, &width, &height, label);
                            len = strlen(label);
                            if(check_validity(xx, yy, width, height, len, 1))
                                print_textbox(xx, yy, width, height, label);
                            else
                                write_error();
                        }else if(c == '2'){
                            get_data_from_user(0, &xx, &yy, &width, &height, label);
                            len = strlen(label);
                            if(check_validity(xx, yy, width, height, len, 0))
                                print_label(xx, yy, label);
                            else
                                write_error();
                        }else if(c == '3'){

                        }else if(c == '4'){

                        }else if(c == '5'){
                            break;
                        }else{
                            invalid_input();
                        }
                        save_file(name, x, y);
                    }
                }
                else if (c == '3') {
                    system("cls");
                    break;
                } else {
                    invalid_input();
                }
            }
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
