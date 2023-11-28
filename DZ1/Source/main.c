#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>
#include "eocdr.h"
#include "cfh.h"

int main(int argc, char** argv)
{
    if(argc == 2){
        FILE* file;
        file = fopen(argv[1], "rb");
        if(file){
            struct stat buf;    //структура стат дла считывания размера
            bool result;
            result = fstat(fileno(file), &buf);
            if(!result){
                struct eocdr EOC;
                uint8_t* source = (uint8_t*) malloc(buf.st_size);   // выделяем память
                fread(source, buf.st_size, 1, file);                // читаем в выделенную память наш файл
                result = fine_ecodr(&EOC, source, buf.st_size);     // ищем сигнатуру EOCD
                if(result){
                    struct cfh CFH;
                    size_t offset = buf.st_size - EOC.comment_len - EOCDR_BASE_SZ - EOC.cd_size;    //вручную определил смещение, EOC.cd_offset не работала
                    printf("Number of files in zip: %d\n", EOC.disk_cd_entries);                    // выводим количество файлов в zip архиве 
                    for(size_t i = 0; i < EOC.disk_cd_entries; i++){
                        result = read_cfh(&CFH, source, buf.st_size, &offset);          // читаем одну центральную зараз 
                        if(result){
                            printf("File %ld name: %s\n", i+1, CFH.name);           // Выводим имя файла из центральной, иначе ошибка
                        } else{
                            fprintf(stderr, "Error while reading cfh\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    fclose(file);       // Закрываем считывание из файла, освобождаем файловый поток
                } else{
                    fprintf(stderr, "It is not a zip file\n");         // Выводим сообщение об ошибке для каждого случия в поток ошибок 
                    exit(EXIT_FAILURE);
                }
            } else{
                fprintf(stderr, "Wrong file descriptor\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "File can not be opened\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Wrong args num\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}