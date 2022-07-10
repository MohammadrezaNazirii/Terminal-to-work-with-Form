#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "myHeader.h"
#include "third_phase.h"

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
                    int x, y, flag_new, index;
                    char name[100], name_for_print[100];
                    if (c == '1'){//New
                        system("cls");
                        flag_new = 1;
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
                                printf("You have a form with this name!\nDo you want to rewrite it?\nType 'y' if you want to rewrite it or type any character to enter new name\n");
                                c = getchar();
                                emptyBuffer();
                                if (c == 'y')
                                    break;
                            }
                        }
                        printf("Please enter dimensions of form separated by space(First number for width and Second number for height)... ");
                        scanf("%d %d", &x, &y);
                        emptyBuffer();
                        allocate_lines(x, y);
                        initialize_lines(x, y);
                        save_file(name, x, y, 1);
                    }else{//Edit
                        system("cls");
                        flag_new = 0;
                        while(1){
                            system("cls");
                            printf("Please enter the name of your form... ");
                            scanf("%s", name);
                            strcpy(name_for_print, name);
                            emptyBuffer();
                            strcat(name, ".txt");
                            if(exist_file(name))
                                break;
                            else
                                print_fileNotFound_error();
                        }
                    }
                    while (1){
                        if(flag_new)
                            read_file(name, &x, &y, 0);
                        else
                            read_file(name, &x, &y, 1);
                        system("cls");
                        print_lines(y, name_for_print);
                        print_designNew_menu();
                        c = getchar();
                        emptyBuffer();
                        char label[100], selected_label[100];
                        int xx, yy, width, height, len;
                        if(c == '1'){
                            get_data_from_user(1, &xx, &yy, &width, &height, label);
                            len = strlen(label);
                            if(check_inputs(x, y, xx, yy, len, width, height, 1)){
                                out_of_range_input();
                                continue;
                            }
                            if(check_validity(xx, yy, width, height, len, 1)) {
                                labels[nLabels++].have_textbox = 1;
                                print_textbox(xx, yy, width, height, label);
                            }
                            else
                                write_error();
                        }else if(c == '2'){
                            get_data_from_user(0, &xx, &yy, &width, &height, label);
                            len = strlen(label);
                            if(check_inputs(x, y, xx, yy, len, 0, 0, 0)){
                                out_of_range_input();
                                continue;
                            }
                            if(check_validity(xx, yy, width, height, len, 0)) {
                                labels[nLabels++].have_textbox = 0;
                                print_label(xx, yy, label);
                            }
                            else
                                write_error();
                        }else if(c == '3'){
                            print_removeLabel_menu(selected_label);
                            index = find_label(selected_label);
                            if(index >= 0){
                                if(labels[index].have_textbox) {
                                    find_start_of_textbox(&labels[index], &xx, &yy);
                                    find_textbox_dimensions(xx, yy, &width, &height);
                                    remove_textbox(xx, yy, width, height);
                                }
                                remove_label(labels[index].x, labels[index].y, strlen(labels[index].str));
                                remove_label_from_struct(index);
                            }else
                                print_labelNotFound_error();
                        }
                        else if(c == '4'){
                            break;
                        }else{
                            invalid_input();
                        }
                        save_file(name, x, y, 0);
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
            int x, y, xx, yy, width, height;
            char name[100], name_for_print[100], textbox_str[100], temp[100];
            textbox_str[0] = '\0';
            while(1){
                system("cls");
                printf("Enter the name of the form you want to complete... ");
                scanf("%s", name);
                strcpy(name_for_print, name);
                emptyBuffer();
                strcat(name, ".txt");
                if(exist_file(name))
                    break;
                else
                    print_fileNotFound_error();
            }
            read_file(name, &x, &y, 1);
            print_lines(y, name_for_print);
            print_buttons();
            print_menu();
            int i=0;
            while (1){
                if(labels[i].have_textbox){
                    printf("'-':previous  '+':next  '1'to'5':buttons  string:Fill TextBox  '0':back\n");
                    //print label
                    printf("Label: %s\n", labels[i].str);
                    c = getchar();
                    if (c == '-') {
                        i--;
                        if (i == 0)
                            i = nLabels - 1;
                    } else if (c == '+') {
                        i++;
                        if (i == nLabels)
                            i = 0;
                    } else if (c == '0') {
                        break;
                    } else if (c == '1') {

                    } else if (c == '2') {

                    } else if (c == '3') {

                    } else if (c == '4') {

                    } else if (c != ' ') {//matne TextBox ro migire.
                        gets(temp);
                        strncat(textbox_str, &c, 1);
                        strcat(textbox_str, temp);
                        find_start_of_textbox(&labels[i], &xx, &yy);
                        find_textbox_dimensions(xx, yy, &width, &height);
                        if(strlen(textbox_str) <= width*height){
                            strcpy(labels[i].str_textbox, textbox_str);
                        }else{
                            printf("Your text is too large for this TextBox.");
                            Sleep(1500);
                        }
                    }
                }else
                    i++;
            }
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
