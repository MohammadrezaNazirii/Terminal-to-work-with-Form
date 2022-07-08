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

void read_file(char* name, int* x, int* y){
    FILE* f = fopen(name, "r");
    fscanf(f, "%d  %d\n", x, y);
    allocate_lines(*x, *y);
    for(int i=0;i<*y;i++)
        fgets(lines[i], *x+2, f);
    fclose(f);
}

void print_lines(int y, char* name){
    printf("Form : %s\n", name);
    for(int i=0;i<y;i++){
        for(int j=0;lines[i][j] != '\0';j++){
            if(lines[i][j] == '~')
                putchar(' ');
            else
                putchar(lines[i][j]);
        }
    }
}

void print_designNew_menu(){
    printf("1.Create TextBox(each TextBox should have Label)        2.Create Label        3.Remove TextBox        4.Remove Label        5.Back/Exit\n");
    printf("What do you want to do? ");
}

void get_data_from_user(int mode, int* xx, int* yy, int* w, int* h, char l[]){
    if (mode == 1)
        printf("Enter a Label for TextBox: ");
    else if (mode == 0)
        printf("Enter Label: ");
    gets(l);
    printf("Enter the coordinates(first x and then y): ");
    scanf("%d %d", xx, yy);
    emptyBuffer();
    if (mode == 1){
        printf("Enter width and height of TextBox separated by space: ");
        scanf("%d %d", w, h);
        emptyBuffer();
    }
}

int print_label(int x, int y, const char label[]){
    int i=0;
    for(;label[i] != '\0';i++){
        lines[y][x+i] = label[i];
    }
    return x+i;
}

void print_textbox(int x, int y, int w, int h, const char label[]){
    int newX = print_label(x, y, label);
//    lines[y][newX] = ':';
    for(int i=newX;i<newX+w+2;i++){
        lines[y-1][i] = '-';
    }
    for(int j=0;j<h;j++){
        for (int i = newX; i < newX + w + 2; i++) {
            if(i == newX || i == newX+w+1){
                lines[y+j][i] = '|';
            }else
                lines[y+j][i] = '~';
        }
    }
    for(int i=newX;i<newX+w+2;i++){
        lines[y+h][i] = '-';
    }
}

int check_validity(int x, int y, int w, int h, int len, int mode){
    for(int i=x;i<x+len;i++){
        if(lines[y][i] != ' ')
            return 0;
    }
    if(mode == 1){
        for(int i=-1;i<h+1;i++){
            for(int j=x+len;j<x+len+w+2;j++){
                if(lines[y+i][j] != ' ')
                    return 0;
            }
        }
    }
    return 1;
}

void write_error(){
    printf("Error: Your request cannot be fulfilled, because this place is already occupied.\nPlease try again\n");
    Sleep(1500);
}