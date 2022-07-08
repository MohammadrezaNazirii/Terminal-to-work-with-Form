char** lines;

void emptyBuffer(){
    char c;
    while (1){
        c = getchar();
        if(c == '\n')
            break;
    }
}

void print_main_menu(){
    printf("Welcome to Form-Creator!\n");
    printf("1.Design From\n2.Complete Designed Forms\n3.Exit\n");
    printf("What do you want to do? ");
}

void invalid_input(){
    printf("Invalid Input!!!\n");
    Sleep(1500);
}

void print_design_menu(){
    printf("1.New\n2.Edit\n3.Back/Exit\n");
    printf("What do you want to do? ");
}

int exist_file(char* name){
    FILE* f = fopen(name, "r");
    if(f == NULL)
        return 0;
    fclose(f);
    return 1;
}

void allocate_lines(int x, int y){
    lines = (char**) malloc(y*sizeof(char*));
    for(int i=0;i<y;i++)
        lines[i] = (char*) malloc((x+2) * sizeof(char));
}

char* create_line(int x, int mode){
    char* arr = malloc((x+1) * sizeof(char));
    if(mode == 0){
        arr[0] = 'x';
        for(int i=1;i<x-1;i++)
            strcat(arr, "=");
        arr[x-1] = 'x';
        arr[x] = '\n';
        arr[x+1] = '\0';
    }else{
        arr[0] = '|';
        for(int i=1;i<x-1;i++)
            strcat(arr, " ");
        arr[x-1] = '|';
        arr[x] = '\n';
        arr[x+1] = '\0';
    }
    return arr;
}

void initialize_lines(int x, int y){
    for(int i=0;i<y;i++){
        if (i == 0 || i == y-1){
            strcpy(lines[i], create_line(x, 0));
        }else{
            strcpy(lines[i], create_line(x, 1));
        }
    }
}

void save_file(char* name, int x, int y){
    FILE* f = fopen(name, "w");
    fprintf(f, "%d  %d\n", x, y);
    for(int i=0;i<y;i++)
        fprintf(f, "%s", lines[i]);
    fclose(f);
}