char unused[] = "x--------x";
char used[] = "x========x";

label selected_labels[100];
int nSelectedLabels=0;

char completed_forms[100][100];
int nCompletedForms = 0;

void print_buttons(){
    printf("%s  %s  %s  %s\n", unused, unused, unused, unused);
    printf("|1.ADD   |  |2.Find  |  |3.Edit  |  |4.Remove|\n");
    printf("%s  %s  %s  %s\n", unused, unused, unused, unused);
}

void print_ADD(){
    printf("%s\n", used);
    printf("|1.ADD   |\n");
    printf("%s\n", used);
    printf("Enter a name for this completed form... ");
}

void print_Find(){
    printf("%s  %s  %s\n", used, unused, unused);
    printf("|1.Find  |  |2.Edit  |  |3.Remove|\n");
    printf("%s  %s  %s\n", used, unused, unused);
    printf("What do you want to do? ");
}

void print_Edit(){
    printf("%s  %s\n", used, unused);
    printf("|1.Edit  |  |2.OK    |\n");
    printf("%s  %s\n", used, unused);
}

void print_Remove(){
    printf("%s\n", used);
    printf("|1.Remove|\n");
    printf("%s\n", used);
}

void print_menu(){
    printf("You can select a button for an action,\n");
    printf("or enter '-', for previous and '+', for next component,\n");
    printf("or you can enter 0 in every steps for back to previous step.\n");
    printf("Note: When you are on a component, if enter something, it will go to its TextBox.\n");
}

void fill_textbox(int xx, int yy, int w, int h, const char str[]){
    int n=0;
    for(int i=yy+1;i<yy+h+1;i++){
        for(int j=xx+1;j<xx+w+1;j++){
            if(str[n] != '\0')
                lines[i][j] = str[n++];
            else
                lines[i][j] = '~';
        }
    }
}

void make_completed_name(char* completed_name, const char* name){
    strcat(completed_name, name);
    strcat(completed_name, "/");
    char temp[100];
    gets(temp);
    strcat(completed_name, temp);
    strcat(completed_name, ".txt");
}

void preMenu_find(){
    emptyBuffer();
    system("cls");
    printf("You should complete TextBoxes in last menu that you want to search in completed forms.\n");
    printf("If you didn't complete TextBoxes in last menu, go back and fill them.\n");
    printf("Do you want to continue?(y/n) ");
}

void preMenu_edit(){
    emptyBuffer();
    system("cls");
    print_Edit();
    printf("Enter the name of completed form that you want to edit... ");
}

void preMenu_remove(){
    emptyBuffer();
    system("cls");
    print_Remove();
    printf("Enter the name of completed form that you want to remove... ");
}

void fill_selected_labels(){
    for(int i=0;i<nLabels;i++)
        if(strcmp(labels[i].str_textbox, "."))
            selected_labels[nSelectedLabels++] = labels[i];
}

void get_completed_form_names(char* name){
    char path[100] = "./";
    strcat(path, name);
    int n=0;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(n>1)
                strcpy(completed_forms[nCompletedForms++], dir->d_name);
            n++;
        }
        closedir(d);
    }
}