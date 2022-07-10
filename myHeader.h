char** lines;

typedef struct {
    int x;
    int y;
    char str[100];
    int have_textbox;
    char str_textbox[100];
}label;

label labels[100];
int nLabels=0;

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

void save_file(char* name, int x, int y, int mode){
    FILE* f;
    f = fopen(name, "r+");
    if (f == NULL || mode == 1) {
        fclose(f);
        f = fopen(name, "w");
    }
    fprintf(f, "%d  %d\n", x, y);
    for(int i=0;i<y;i++)
        fprintf(f, "%s", lines[i]);
    if (mode == 0){
        fprintf(f, "\n%d\n", nLabels);
        for(int i=0;i<nLabels;i++)
            fprintf(f, "%d %d %s %d %s\n", labels[i].x, labels[i].y, labels[i].str, labels[i].have_textbox, labels[i].str_textbox);
    }
    fclose(f);
}

void read_file(char* name, int* x, int* y, int mode){
    FILE* f = fopen(name, "r");
    fscanf(f, "%d  %d\n", x, y);
    allocate_lines(*x, *y);
    for(int i=0;i<*y;i++)
        fgets(lines[i], *x+2, f);
    if(mode == 1){
        fscanf(f, "%d", &nLabels);
        for(int i=0;i<nLabels;i++){
            fscanf(f, "%d %d %s %d %s", &labels[i].x, &labels[i].y, labels[i].str, &labels[i].have_textbox, labels[i].str_textbox);
        }
    }
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

int print_label(int x, int y, const char l[]){
    labels[nLabels-1].x = x;
    labels[nLabels-1].y = y;
    strcpy(labels[nLabels-1].str, l);
    strcpy(labels[nLabels-1].str_textbox, ".");
    int i=0;
    for(;l[i] != '\0';i++){
        lines[y][x+i] = l[i];
    }
    return x+i;
}

void print_textbox(int x, int y, int w, int h, const char l[]){
    int newX = print_label(x, y, l);
//    lines[y][newX] = ':';
    for(int i=newX;i<newX+w+2;i++){
        if (i == newX || i == newX+w+1)
            lines[y-1][i] = 'x';
        else
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
        if (i == newX || i == newX+w+1)
            lines[y+h][i] = 'x';
        else
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

void find_textbox_dimensions(int x, int y, int* w, int* h){
    *w = 0;
    *h = 0;
    for(int i=x+1;lines[y][i] != 'x';i++)
        (*w)++;
    for(int i=y+1;lines[i][x] != 'x';i++)
        (*h)++;
}

void remove_label(int x, int y, int len){
    for(int i=0;i<len;i++)
        lines[y][x+i] = ' ';
}

void remove_textbox(int x, int y, int w, int h){
    for(int i=y;i<y+h+2;i++){
        for(int j=x;j<x+w+2;j++)
            lines[i][j] = ' ';
    }
}

int check_inputs(int x, int y, int xx, int yy, int len, int w, int h, int mode){
    if(mode == 1) {
        if ((xx > 0) && (yy > 0) && ((xx + len + w + 2) < x) && ((yy + h + 1) < y))
            return 0;
    }else{
        if ((xx > 0) && (yy > 0) && ((xx + len) < x) && (yy < y))
            return 0;
    }
    return 1;
}

void out_of_range_input(){
    printf("Inputs Out Of Range!!!\n");
    Sleep(1500);
}

void find_start_of_textbox(label* label, int* x, int* y){
    *x = (label->x) + (int)strlen(label->str);
    *y = (label->y) - 1;
}
