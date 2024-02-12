#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>
#include "eocdr.h"
#include "cfh.h"

int main(int argc, char** argv)
{
    if(argc != 2){
        fprintf(stderr, "Wrong args num\n");
        exit(EXIT_FAILURE);
    }
    FILE* file;
    file = fopen(argv[1], "rb");
    if(file){
        struct stat buf;                                                                                 //структура стат дла считывания размера
        if(!fstat(fileno(file), &buf)){
            uint8_t* source = (uint8_t*) malloc(buf.st_size);                                           // выделяем память
            if(source){
                int num;
                num = fread(source, sizeof(uint8_t), buf.st_size, file);                                 // читаем в выделенную память наш файл
                if(num == buf.st_size){
                    struct eocdr EOC;
                    if(fine_ecodr(&EOC, source, buf.st_size)){                                           // ищем сигнатуру EOCD
                        struct cfh CFH;
                        size_t offset = buf.st_size - EOC.comment_len - EOCDR_BASE_SZ - EOC.cd_size;    //вручную определил смещение, EOC.cd_offset не работала
                        printf("Number of files in zip: %d\n", EOC.disk_cd_entries);                    // выводим количество файлов в zip архиве 
                        for(size_t i = 0; i < EOC.disk_cd_entries; i++){
                            if(read_cfh(&CFH, source, buf.st_size, &offset)){                           // читаем одну центральную зараз 
                                printf("File %ld name: %s\n", i+1, CFH.name);                           // Выводим имя файла из центральной, иначе ошибка
                            } else{
                                fprintf(stderr, "Error while reading cfh\n");
                                free(source);
                                fclose(file);  
                                exit(EXIT_FAILURE);
                            }
                        }
                        free(source);
                        fclose(file);                                                                   // Закрываем считывание из файла, освобождаем файловый поток
                    } else{
                        fprintf(stderr, "It is not a zip file\n");                                      // Выводим сообщение об ошибке для каждого случия в поток ошибок
                        free(source); 
                        fclose(file);  
                        exit(EXIT_FAILURE);
                    }
                } else{
                    fprintf(stderr, "Failed to read %ld times from the file\n", buf.st_size);
                    free(source);
                    fclose(file);  
                    exit(EXIT_FAILURE);
                }
            } else{
                fprintf(stderr, "Memory has not been allocated\n");
                fclose(file);  
                exit(EXIT_FAILURE);
            }
        } else{
            fprintf(stderr, "Wrong file descriptor\n");
            fclose(file);  
            exit(EXIT_FAILURE);
        }
    } else{
        fprintf(stderr, "File can not be opened\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}


//  if(argc != 4)
//     {
//         if(argc == 2){
//             if(strcmp(argv[1], "--help") == 0){
//                 puts("Help argument invoked. This tool translates from different encodings to UTF-8");
//                 puts("Use first arg for a source file");
//                 puts("Use second arg for an encoding type: CP-1251 | KOI8-R | ISO-8859-5");
//                 puts("Use third arg for a target file");
//                 exit(EXIT_SUCCESS);
//             }
//         }
//         fprintf(stderr, "Wrong args num\n");
//         exit(EXIT_FAILURE);
//     }