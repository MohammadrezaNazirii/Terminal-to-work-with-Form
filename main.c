#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <sys/stat.h>
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
            int x, y, xx, yy, width, height, flag_pos, flag_neg;
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
            int i=0;
            while (1){
                if(labels[i].have_textbox){
                    system("cls");
                    print_lines(y, name_for_print);
                    print_buttons();
                    print_menu();
                    printf("'-':previous  '+':next  '1'to'4':buttons  string:Fill TextBox  '0':back\n");
                    printf("Label: %s\n", labels[i].str);
                    c = getchar();
                    if (c == '-') {
                        emptyBuffer();
                        flag_pos = 0;
                        flag_neg = 1;
                        i--;
                        if (i == -1)
                            i = nLabels - 1;
                    } else if (c == '+') {
                        emptyBuffer();
                        flag_pos = 1;
                        flag_neg = 0;
                        i++;
                        if (i == nLabels)
                            i = 0;
                    } else if (c == '0') {
                        emptyBuffer();
                        system("cls");
                        break;
                    } else if (c == '1') {
                        emptyBuffer();
                        system("cls");
                        print_lines(y, name_for_print);
                        print_ADD();
                        mkdir(name_for_print);
                        char completed_name[20] = "./";
                        make_completed_name(completed_name, name_for_print);
                        if(!exist_file(completed_name))
                            save_file(completed_name, x, y, 0);
                        else{
                            printf("You have a form with this name!\nDo you want to rewrite it?\nType 'y' if you want to rewrite it or type any character to try again.\n");
                            c = getchar();
                            emptyBuffer();
                            if (c == 'y')
                                save_file(completed_name, x, y, 0);
                        }
                    } else if (c == '2') {
                        emptyBuffer();
                    } else if (c == '3') {
                        emptyBuffer();
                        system("cls");
                        print_Edit();
                        printf("Enter the name of completed form that you want to edit... ");
                        char completed_name[20] = "./";
                        make_completed_name(completed_name, name_for_print);
                        if(exist_file(completed_name)){
                            read_file(completed_name, &x, &y, 1);
                        } else {
                            print_fileNotFound_error();
                            continue;
                        }
                        while(1){
                            if(labels[i].have_textbox){
                                system("cls");
                                print_lines(y, completed_name);
                                print_Edit();
                                printf("'-':previous  '+':next  '1'to'2':buttons  string:Fill TextBox  '0':back\n");
                                printf("Label: %s\n", labels[i].str);
                                c = getchar();
                                if (c == '-') {
                                    emptyBuffer();
                                    flag_pos = 0;
                                    flag_neg = 1;
                                    i--;
                                    if (i == -1)
                                        i = nLabels - 1;
                                } else if (c == '+') {
                                    emptyBuffer();
                                    flag_pos = 1;
                                    flag_neg = 0;
                                    i++;
                                    if (i == nLabels)
                                        i = 0;
                                } else if (c == '0') {
                                    emptyBuffer();
                                    system("cls");
                                    break;
                                } else if (c == '2'){
                                    emptyBuffer();
                                    save_file(completed_name, x, y, 0);
                                    break;
                                } else if (c != ' ') {//matne TextBox ro migire.
                                    textbox_str[0] = '\0';
                                    gets(temp);
                                    strncat(textbox_str, &c, 1);
                                    strcat(textbox_str, temp);
                                    find_start_of_textbox(&labels[i], &xx, &yy);
                                    find_textbox_dimensions(xx, yy, &width, &height);
                                    if(strlen(textbox_str) > width*height){
                                        printf("Your text is too large for this TextBox.");
                                        Sleep(1500);
                                    }else{
                                        strcpy(labels[i].str_textbox, textbox_str);
                                        fill_textbox(xx, yy, width, height, textbox_str);
                                    }
                                }
                            }else{
                                if(flag_pos) {
                                    i++;
                                    if (i == nLabels)
                                        i = 0;
                                }
                                if(flag_neg){
                                    i--;
                                    if (i == -1)
                                        i = nLabels-1;
                                }
                            }
                        }
                    } else if (c == '4') {
                        emptyBuffer();
                        system("cls");
                        print_Remove();
                        printf("Enter the name of completed form that you want to remove... ");
                        char completed_name[20] = "./";
                        make_completed_name(completed_name, name_for_print);
                        if(exist_file(completed_name)){
                            read_file(completed_name, &x, &y, 1);
                        } else {
                            print_fileNotFound_error();
                            continue;
                        }
                        remove(completed_name);
                    } else if (c != ' ') {//matne TextBox ro migire.
                        textbox_str[0] = '\0';
                        gets(temp);
                        strncat(textbox_str, &c, 1);
                        strcat(textbox_str, temp);
                        find_start_of_textbox(&labels[i], &xx, &yy);
                        find_textbox_dimensions(xx, yy, &width, &height);
                        if(strlen(textbox_str) > width*height){
                            printf("Your text is too large for this TextBox.");
                            Sleep(1500);
                        }else if(strcmp(labels[i].str_textbox, ".")){
                            printf("This TexBox is already filled.");
                            Sleep(1500);
                        }else{
                            strcpy(labels[i].str_textbox, textbox_str);
                            fill_textbox(xx, yy, width, height, textbox_str);
                        }
                    }
                }else {
                    if(flag_pos) {
                        i++;
                        if (i == nLabels)
                            i = 0;
                    }
                    if(flag_neg){
                        i--;
                        if (i == -1)
                            i = nLabels-1;
                    }
                }
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
