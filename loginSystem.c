#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int user_id = 0;

struct user
{
    char id[50];
    char name[12];
    char username[15];
    char email[30];
    char mobile_no[11];
    char password[11];
}current_user;


int validate(struct user active_user)
{
    FILE *lc = fopen("lc.txt", "r");
    char content[100];
    
    while(fgets(content,100,lc) != NULL)
        {   
            
            int word_count = 1;

            char email[30], password[11],name[12],id[100],username[15],mobile_no[11];
            char *token = strtok(content,",");
            while(token != NULL)
            {   if(word_count == 1)
                    strcpy(id,token);
                if(word_count == 2)
                    strcpy(username,token);
                if(word_count == 3)
                    strcpy(name,token);
                if(word_count == 4)
                    strcpy(email,token);
                if(word_count == 5)
                    strcpy(mobile_no,token);
                if(word_count == 6)
                    strcpy(password,token);

                token = strtok(NULL,",");
                word_count++;
            }
            
            password[strlen(password)-1] = '\0';

            if(strcmp(active_user.email,email) == 0 && strcmp(active_user.password,password) == 0)
            {
                
                strcpy(current_user.id,id);
                strcpy(current_user.username,username);
                strcpy(current_user.name,name);
                strcpy(current_user.mobile_no,mobile_no);

                return 1;

            }
        }
        return 0;
}

char *AcceptParticularInput(char input_type)
{
    //using getch() from compare the character enterd and then display it on the screen

    char character_input = getch();
    static char word[50];

    word[0] = '\0';
    int index = 0;
    
    while (character_input != 13)
    {   
        // erasing the previous character when back space is pressed
        if (character_input == 8 && strlen(word) != 0)
        {
            printf("\b");
            printf(" ");
            printf("\b");
            index--;
        }

        // check if ctrl+c is pressed then stop the program
        if (character_input == 3)
        {
            printf("\nQuitting......\n");

            if (strlen(word) != 0)
                word[index] = '\0';
            printf("%s %d", word, strlen(word));
            exit(1);
        }

         // only form the word when the entered character is an alphabet or spacebar
        if (input_type == 'C')
        {
            if ((character_input >= 65 && character_input <= 95) || (character_input >= 97 && character_input <= 122) || character_input == 32)
            {
                word[index++] = character_input;
                printf("%c", character_input);
            }
        }

        // only form the word when the entered character is a number
        if (input_type == 'N')
        {
            if (character_input >= 48 && character_input <= 57)
            {
                word[index++] = character_input;
                printf("%c", character_input);
            }
        }

        // only form the word when the entered character is an alphabet , dot(.), comma(,) or '@'
        if (input_type == 'M')
        {
            if ((character_input >= 65 && character_input <= 95) || (character_input >= 97 && character_input <= 122) || (character_input >= 48 && character_input <= 57) || character_input == 46 || character_input == 64)
            {
                word[index++] = character_input;
                printf("%c", character_input);
            }
        }
        
        character_input = getch();
    }
    word[index++] = '\0';
    return word;
}

void login()
{
    char *input;

    printf("==========Enter Your Login Details=========");
    printf("Email : ");
    input = AcceptParticularInput('M');
    strcpy(current_user.email,input);

    printf("\nPassword : ");
    input = AcceptParticularInput('M');
    strcpy(current_user.password,input);


    if(validate(current_user))
        printf("\n==========Welcome to you account %s===========",current_user.name);
    else
        printf("Incorrect email id Or password :(");
}


struct user AcceptNewAccountDetails()
{
    struct user new;
    char *input;
    
    printf("========Enter your details========.\n");
    
    // new.id[0] = 1+'0';
    // new.id[1] = '\0';

    printf("Name : ");
    input = AcceptParticularInput('C');
    strcpy(new.name,input);

    printf("\nUsername : ");
    input = AcceptParticularInput('M');
    strcpy(new.username,input);
    // fflush(stdin);
    // gets(new.username);
    
    printf("\nMobile No. : ");
    input = AcceptParticularInput('N');
    strcpy(new.mobile_no,input);

    printf("\nEmail : ");
    input = AcceptParticularInput('M');
    strcpy(new.email,input);

    printf("\nPassword : ");
    input = AcceptParticularInput('M');
    strcpy(new.password,input);

    return new;
}

// void createFileIfNotExists()
// {
//     FILE *lc = fopen("lc.txt", "r");
//     if (lc == NULL)
//     {   
//         lc = fopen("lc.txt","w");
//         fputs("id,username,name,email,mobile,password",lc);
//         fputc('\n',lc);
//         fclose(lc);
//     }
//     else
//         fclose(lc);
// }

// int findMatch(char content[])
// {
//     /**/
// }

int checkIfAccountExists(struct user newUser)
{
    
    FILE *lc = fopen("lc.txt", "r");
    if (lc == NULL)
    {   
        lc = fopen("lc.txt","a+");
        fputs("id,username,name,email,mobile,passwor",lc);
        fputc('\n',lc);
        fclose(lc);
    }

    char c;
    char content[100] = ""; 
   
    while ((c = fgetc(lc)) != EOF && (c = fgetc(lc)) != '\n');
 
    printf("\n");

    //reading lines from the file and extracting each words from that and comparing with email
    
    int i = 0,found=0;
    while ((c = fgetc(lc)) != EOF)
    {   
        if (c == '\n')
        {   
            printf("%s",content);
            char *token = strtok(content, ",");

            int word_count = 1;
            while(token != NULL)
            {   
                printf("\nWord count = %d and file email = %s  entered email = %s \n",word_count,token,newUser.email);

                if(word_count == 4 && strcmp(token,newUser.email) == 0)
                {
                    found = 1;
                    return found;
                }
                if(word_count == 1)
                    user_id = atoi(token);
                token = strtok(NULL,",");
                word_count++;

            }
            i = 0;
            continue;
        }
        
        content[i++] = c;
    }
    fclose(lc);
    return found;
   
}

void createAccount()
{
    struct user newUser = AcceptNewAccountDetails();

    if(checkIfAccountExists(newUser))
    {   
        printf("\nAccount already exists with these email !!!.");
    }
    else
    {   
        FILE *f = fopen("lc.txt","a");
        
        char new_data[100];

        user_id += 1;

        // storing integer as a string
        sprintf(newUser.id,"%d",user_id);

        //combining all the info of the new user and storing it in the file

        // strcat(new_data,newUser.id);
        strcpy(new_data,newUser.id);
        strcat(new_data,",");
        
        strcat(new_data,newUser.username);
        strcat(new_data,",");

        strcat(new_data,newUser.name);
        strcat(new_data,",");

        strcat(new_data,newUser.email);
        strcat(new_data,",");

        strcat(new_data,newUser.mobile_no);
        strcat(new_data,",");

        strcat(new_data,newUser.password);
        
        fputs(new_data,f);
        fputc('\n',f);

        fclose(f);
        printf("\nYour account has been successfully created !!!\n");
    }
}

int main()
{
    //createFileIfNotExists();
    int choice;
    printf("1 > To Login.\n2 > Create Account.\n ");
    printf("Enter choice : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:;
        createAccount();
        break;
    }
}
