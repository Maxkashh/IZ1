#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <malloc.h>

typedef struct
{
    const char* name;
    const  char* open_tag;
    const  char* close_tag;
    char** atributes;

}HTMLTag;
int col = 0;
bool choice;

bool isTag_open()
{
    char choice;
    printf("%s\n", "Do u have close tag?  Y/n");
    scanf("%c", &choice);
    return (choice == 'y' || choice == 'Y');

}


char* get_tag()
{
    char temp[1000];
    printf("%s", "Enter HTML tag:");
    gets(temp);
    //scanf("%s",temp);
    int length = strlen(temp);
    char* newstr;
    newstr = (char*)malloc(length + 1);
    if (newstr != NULL) {
        strcpy(newstr, temp);
        int count = 0;
        for (int i = 0; i < length; i++)
        {
            if (newstr[i] == '<' || newstr[i] == '>') { count++; }

        }


        while ((newstr[0] != '<' || newstr[length - 1] != '>' || count < 2 || count>2 || length <= 2))
        {

            printf("%s", "Error! This is not a HTML tag , check your tag again!\n");
            printf("%s", "Enter HTML tag:\n");
            gets(temp);
            strcpy(newstr, temp);
            int length = strlen(temp);
            // strcpy(newstr, temp);
            count = 0;
            for (int i = 0; i < length; i++)
            {
                if (newstr[i] == '<' || newstr[i] == '>') { count++; }

            }
            if (newstr[0] == '<' && newstr[length - 1] == '>' && count == 2 && length > 2) { break; }


        }
        return newstr;
    }
    else printf("%s", "Sorry!Dont have memory!");
}
char* get_name(const char* string)
{
    int length = strlen(string);
    char* name;
    name = (char*)malloc(length + 1);
    if (name != NULL) {
        strcpy(name, string);
        for (int j = 0, i = 1; i < length - 1; j++, i++)
        {
            name[j] = string[i];
        }
        name[strlen(name) - 2] = 0;



        return name;
    }
    else printf("%s", "Sorry!Dont have memory!");
}
char* get_closeTag(const char* string)
{


    int length = strlen(string);

    char* close;
    close = (char*)malloc(length + 2);
    if (close != NULL) {
        strcpy(close, string);
        for (int i = 0; i < length + 2; i++)
        {
            close[i] = string[i];
        }

        int pos = 2;
        char x = '/';
        for (int i = length + 2; i >= pos; i--)

            close[i] = close[i - 1];



        // вставить х в поз

        close[pos - 1] = x;

        return close;
    }

    else printf("%s", "Sorry!Dont have memory!");
}
//void printTag(const char* tag, const char* name, const char* close, const char** atributes, int n)
//
//{
//    printf("%s\n", "Name:");
//    printf("%s\n", name);
//
//    printf("%s\n", "Open tag:");
//    printf("%s\n", tag);
//
//    printf("%s\n", "Close tag:");
//    printf("%s\n", close);
//    printf("%s\n", "Atributes:");
//    for (int i = 0; i <= n; i++)
//    {
//        printf("%s\n\t", atributes[i]);
//        printf("\n");
//    }
//}
//void printTag2(const char* tag, const char* name, const char* close)
//
//{
//    printf("%s\n", "Name:");
//    printf("%s\n", name);
//
//    printf("%s\n", "Open tag:");
//    printf("%s\n", tag);
//
//    printf("%s\n", "Close tag:");
//    printf("%s\n", close);
//    printf("%s\n", "Atributes:");
//    printf("%s\n", "None");
//}

void printObj(HTMLTag* obj)
{
    printf("%s\n", "Name:");
    printf("%s\n", obj->name);

    printf("%s\n", "Open tag:");
    printf("%s\n", obj->open_tag);

    printf("%s\n", "Close tag:");
    printf("%s\n", obj->close_tag);

    printf("%s\n", "Atributes:");

    for (int i = 0; i <= col; i++)
    {
        printf("%s\n\t", obj->atributes[i]);
        printf("\n");
    }


    //col = 0;

}


const char** get_atribut(int n)
{


    char** strings = (char**)malloc(sizeof(char*) * n);
    if (strings != NULL) {
        for (int i = 0; i <= n; i++)
            strings[i] = (char*)malloc(sizeof(char*) * n);

        //char* strP[10];
        // char** strP = (char**)malloc(sizeof(char*) * n);
        int i;
        printf("%s\n", "Enter atributes of this tag:");
        for (i = 0; i <= n; i++) {
            gets(strings[i]);
            //strP[i] = &strings[i][0];
        }





        return strings;
    }
    else printf("%s", "Sorry!Dont have memory for object!");
}

HTMLTag* init(const char* tag)
{
    HTMLTag* obj;
    obj = malloc(sizeof(HTMLTag));
    if (obj != NULL) {
        obj->open_tag = tag;
        obj->name = get_name(obj->open_tag);
        choice = isTag_open();
        if (choice) { obj->close_tag = get_closeTag(obj->open_tag); }
        else
        {

            obj->close_tag = "None";

        }

        obj->atributes = NULL;
        printf("%s\n", "Enter count of atributes:");

        scanf("%d", &col);
        obj->atributes = get_atribut(col);





        return obj;
    }
    else printf("%s", "Sorry!Dont have memory for object!");

}
void deleteMemory(HTMLTag* obj)
{
    if (choice) { free(obj->close_tag); }


    free(obj->name);
    free(obj->open_tag);
    //free(obj->atributes);

    for (int i = 0; i < 3; i++)
    {
        free(obj->atributes[i]);
    }




    free(obj);
}
