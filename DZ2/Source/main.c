#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static  char * W1251[128] =  {   "Ђ", "Ѓ", "‚", "ѓ", "„", "…", "†", "‡", "€", "‰", "Љ",
                                 "‹", "Њ", "Ќ", "Ћ", "Џ", "ђ", "‘", "’", "“", "”", "•",
                                 "–", "—", "", "™", "љ", "›", "њ", "ќ", "ћ", "џ", 
                                 " ", "Ў", "ў", "Ј", "¤", "Ґ", "¦", "§", "Ё", "©", "Є",
                                 "«", "¬", "", "®", "Ї", "°", "±", "І", "і", "ґ", "µ",
                                 "¶", "·", "ё", "№", "є", "»", "ј", "Ѕ", "ѕ", "ї", "А",
                                 "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й", "К", "Л", 
                                 "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц",
                                 "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я", "a", "б",
                                 "в", "г", "д", "е", "ж", "з", "и", "й", "к", "л", "м",
                                 "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч",
                                 "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};

static  char * koi8_r[128] = {"─", "│", "┌", "┐", "└", "┘", "├", "┤", "┬", "┴", "┼",
                                  "▀", "▄", "█", "▌", "▐", "░", "▒", "▓", "⌠", "■", "∙",
                                  "√", "≈", "≤", "≥", " ", "⌡", "°", "²", "·", "÷", "═", 
                                  "║", "╒", "ё", "╓", "╔","╕", "╖", "╗", "╘", "╙", "╚",
                                  "╛", "╜", "╝", "╞", "╟", "╠", "╡", "Ё", "╢", "╣", "╤",
                                  "╥", "╦", "╧", "╨", "╩", "╪", "╫", "╬", "©", "ю", "а",
                                  "б", "ц", "д", "е", "ф", "г", "х", "и", "й", "к", "л", 
                                  "м", "н", "о", "п", "я", "р", "с", "т", "у", "ж", "в",
                                  "ь", "ы", "з", "ш", "э", "щ", "ч", "ъ", "Ю", "А", "Б",
                                  "Ц", "Д", "Е", "Ф", "Г", "Х", "И", "Й", "К", "Л", "М",
                                  "Н", "О", "П", "Я", "Р", "С", "Т", "У", "Ж", "В", "Ь",
                                  "Ы", "З", "Ш", "Э", "Щ", "Ч", "Ъ"};


        static  char * iso[128] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                  " ", "Ё", "Ђ", "Ѓ","Є", "Ѕ", "І", "Ї", "Ј", "Љ", "Њ", "Ћ", "Ќ", 
                                  "", "Ў", "Џ", "А", "Б", "В", "Г", "Д",
                                  "Е", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П",
                                  "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", 
                                  "Ы", "Ь", "Э", "Ю", "Я", "а", "б", "в", "г", "д", "е",
                                  "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р",
                                  "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы",
                                  "ь", "э", "ю", "я", "№", "ё", "ђ", "ѓ", "є", "ѕ", "і",
                                  "ї", "ј", "љ", "њ", "ћ", "ќ", "§", "ў", "џ"};                                  





int main(int argc, char** argv)
{   
    
    if(argc != 4)
    {
        if(argc == 2){
            if(strcmp(argv[1], "--help") == 0){
                puts("Help argument invoked. This tool translates from different encodings to UTF-8");
                puts("Use first arg for a source file");
                puts("Use second arg for an encoding type: CP-1251 | KOI8-R | ISO-8859-5");
                puts("Use third arg for a target file");
                exit(EXIT_SUCCESS);
            }
        }
        fprintf(stderr, "Wrong args num\n");
        exit(EXIT_FAILURE);
    }

    FILE* source_f = fopen(argv[1], "r");
    if(!source_f)
    {
        fprintf(stderr, "Source file can not be open for reading\n");
        exit(EXIT_FAILURE);
    }

    FILE* target_f = fopen(argv[3], "w");
    if(!target_f)
    {
        fprintf(stderr, "Target file can not be open for writing\n");
       exit(EXIT_FAILURE);
    }

    if(strcmp(argv[2], "CP-1251") == 0)
    {
        unsigned char ch;
        while(fscanf(source_f, "%c", &ch) != EOF){
            if(ch >= 128){
                fprintf(target_f, "%s", W1251[ch - 128]);
            } else{
                fprintf(target_f, "%c", ch);
            }
        }
    } else if(strcmp(argv[2], "KOI8-R") == 0){
        unsigned char ch;
        while(fscanf(source_f, "%c", &ch) != EOF){
            if(ch >= 128){
                fprintf(target_f, "%s",koi8_r[ch - 128]);
            }
            else{
                fprintf(target_f, "%c", ch);
            }
        }
    } else if(strcmp(argv[2], "ISO-8859-5") == 0){
        unsigned char ch;
        while(fscanf(source_f, "%c", &ch) != EOF){
            if(ch >= 128){
                fprintf(target_f,"%s", iso[ch - 128]);
            } else{
                fprintf(target_f, "%c", ch);
            }
        }
    } else{
        fprintf(stderr, "Wrong encoding argument value");
        fclose(source_f);
        fclose(target_f);
        exit(EXIT_FAILURE);
    }

    fclose(source_f);
    fclose(target_f);
    return 0;
}