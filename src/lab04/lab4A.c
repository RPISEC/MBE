/*
 *   Format String Lab - A Problem
 *   gcc -z execstack -z relro -z now -o lab4A lab4A.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BACKUP_DIR "./backups/"
#define LOG_FILE "./backups/.log"

void
log_wrapper(FILE *logf, char *msg, char *filename)
{
    char log_buf[255];
    strcpy(log_buf, msg);
    snprintf(log_buf+strlen(log_buf), 255-strlen(log_buf)-1/*NULL*/, filename);
    log_buf[strcspn(log_buf, "\n")] = '\0';
    fprintf(logf, "LOG: %s\n", log_buf);
}

int
main(int argc, char *argv[])
{
    char ch = EOF;
    char dest_buf[100];
    FILE *source, *logf;
    int target = -1;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
    }

    // Open log file
    logf = fopen(LOG_FILE, "w");
    if (logf == NULL) {
        printf("ERROR: Failed to open %s\n", LOG_FILE);
        exit(EXIT_FAILURE);
    }

    log_wrapper(logf, "Starting back up: ", argv[1]);

    // Open source
    source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open dest
    strcpy(dest_buf, BACKUP_DIR);
    strncat(dest_buf, argv[1], 100-strlen(dest_buf)-1/*NULL*/);
    target = open(dest_buf, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);
    if (target < 0) {
        printf("ERROR: Failed to open %s%s\n", BACKUP_DIR, argv[1]);
        exit(EXIT_FAILURE);
    }

    // Copy data
    while( ( ch = fgetc(source) ) != EOF)
        write(target, &ch, 1);

    log_wrapper(logf, "Finished back up ", argv[1]);

    // Clean up
    fclose(source);
    close(target);

    return EXIT_SUCCESS;
}
