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