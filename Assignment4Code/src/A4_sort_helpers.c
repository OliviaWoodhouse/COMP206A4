#include "A4_sort_helpers.h"

// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
    for (int i = 1; i< MAX_NUMBER_LINES && text_array[i][0] != '\0'; i++) {
      int j = i;
      while (j>0) {
          if (strcmp(text_array[j-1], text_array[j]) > 0) {
              char temp[MAX_LINE_LENGTH];
              strcpy(temp, text_array[j-1]);
              strcpy(text_array[j-1], text_array[j]);
              strcpy(text_array[j], temp);
          }
          j--;
      }
    }
    
   /* for (int k = 0; k < MAX_NUMBER_LINES && text_array[k][0] != '\0'; k++) {
        printf("%s", text_array[k]);
    }*/
}

sem_t *sem_array[27];

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    sem_unlink("A4a");
    sem_array[0] = sem_open("A4a", O_CREAT, 0666, 1);
    sem_unlink("A4b");
    sem_array[1] = sem_open("A4b", O_CREAT, 0666, 0);
    sem_unlink("A4c");
    sem_array[2] = sem_open("A4c", O_CREAT, 0666, 0);
    sem_unlink("A4d");
    sem_array[3] = sem_open("A4d", O_CREAT, 0666, 0);
    sem_unlink("A4e");
    sem_array[4] = sem_open("A4e", O_CREAT, 0666, 0);
    sem_unlink("A4f");
    sem_array[5] = sem_open("A4f", O_CREAT, 0666, 0);
    sem_unlink("A4g");
    sem_array[6] = sem_open("A4g", O_CREAT, 0666, 0);
    sem_unlink("A4h");
    sem_array[7] = sem_open("A4h", O_CREAT, 0666, 0);
    sem_unlink("A4i");
    sem_array[8] = sem_open("A4i", O_CREAT, 0666, 0);
    sem_unlink("A4j");
    sem_array[9] = sem_open("A4j", O_CREAT, 0666, 0);
    sem_unlink("A4k");
    sem_array[10] = sem_open("A4k", O_CREAT, 0666, 0);
    sem_unlink("A4l");
    sem_array[11] = sem_open("A4l", O_CREAT, 0666, 0);
    sem_unlink("A4m");
    sem_array[12] = sem_open("A4m", O_CREAT, 0666, 0);
    sem_unlink("A4n");
    sem_array[13] = sem_open("A4n", O_CREAT, 0666, 0);
    sem_unlink("A4o");
    sem_array[14] = sem_open("A4o", O_CREAT, 0666, 0);
    sem_unlink("A4p");
    sem_array[15] = sem_open("A4p", O_CREAT, 0666, 0);
    sem_unlink("A4q");
    sem_array[16] = sem_open("A4q", O_CREAT, 0666, 0);
    sem_unlink("A4r");
    sem_array[17] = sem_open("A4r", O_CREAT, 0666, 0);
    sem_unlink("A4s");
    sem_array[18] = sem_open("A4s", O_CREAT, 0666, 0);
    sem_unlink("A4t");
    sem_array[19] = sem_open("A4t", O_CREAT, 0666, 0);
    sem_unlink("A4u");
    sem_array[20] = sem_open("A4u", O_CREAT, 0666, 0);
    sem_unlink("A4v");
    sem_array[21] = sem_open("A4v", O_CREAT, 0666, 0);
    sem_unlink("A4w");
    sem_array[22] = sem_open("A4w", O_CREAT, 0666, 0);
    sem_unlink("A4x");
    sem_array[23] = sem_open("A4x", O_CREAT, 0666, 0);
    sem_unlink("A4y");
    sem_array[24] = sem_open("A4y", O_CREAT, 0666, 0);
    sem_unlink("A4z");
    sem_array[25] = sem_open("A4z", O_CREAT, 0666, 0);
    sem_unlink("A4finalize");
    sem_array[26] = sem_open("A4finalize", O_CREAT, 0666, 0);
    remove("temp_file.txt");
    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   
int process_by_letter( char* input_filename, char first_letter ){
    
    sem_wait(sem_array[first_letter-'a']);
    //sprintf( buf, "This process will sort the letter %c.\n",  first_letter );
    read_by_letter(input_filename, first_letter);
    sort_words();
    //write(1,buf,strlen(buf));
    FILE *file;
    if (first_letter == 'a') {
        file = fopen("temp_file.txt", "w");
    } 
    else{
        file = fopen ("temp_file.txt", "a");
    }
    for (int i=0; text_array[i][0] != '\0' && i <MAX_NUMBER_LINES; i++) {
        fputs(text_array[i], file);
    }
    fclose(file);

    if (first_letter == 'z') {
        sem_post(sem_array[26]);
    } else {
        sem_post(sem_array[(first_letter - 'a') +1]);
    }
    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    sem_wait(sem_array[26]);
    FILE *file;
    file = fopen("temp_file.txt", "r");
    int i = 0;
    
    while (fgets(text_array[i],MAX_LINE_LENGTH, file)) {
        i++;
    }
    
    i = 0;
    while (text_array[i][0]!='\0') {
        sprintf(buf, "%s", text_array[i]);
        write(1, buf, strlen(buf));
        i++;
    }
    fclose(file);
    sprintf(buf, "Sorting complete!\n");
    write(1, buf, strlen(buf));
    sem_close(sem_array[0]);
    return 0;
}
