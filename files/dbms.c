#include "dbms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function prototype for Task 1. See handout for details.
 */
int db_show_row(const struct db_table *db, unsigned int row){
  if(row > db->rows_used){
    return 0;
  }

  struct album *aPointer = db->table;
  struct album a1 = *(aPointer + row);

  if(aPointer + row != NULL){
    printf("%6lu:", a1.id);

    if(strlen(a1.title) > 20){
      printf("%.20s:", a1.title);
    }else{
      printf("%20s:", a1.title);
    }

    if(strlen(a1.artist) > 20){
      printf("%.20s:", a1.artist);
    }else{
      printf("%20s:", a1.artist);
    }

    printf("%4hu \n", a1.year);
    return 1;
  }
  return 0;

}

/**
 * Function prototype for Task 2. See handout for details.
 */
int db_add_row(struct db_table *db, struct album *a){
  if(db == NULL){return 0;}
  // add record if there is no space left
  if(db->rows_used == db->rows_total){
    struct album *a1 = (struct album *) realloc (db->table, sizeof(struct album) * (db->rows_total + 5));
    if(a1 == NULL){return 0;} // memory allocation failed
    db->table = a1;
    // add in the new row
    db->table[db -> rows_used] = *a;
    db->rows_used = db -> rows_used + 1;
    db->rows_total = db -> rows_total + 5;
  }else if(db->rows_used < db->rows_total){
    //memory is still available
    db->table[db -> rows_used] = *a;
    db->rows_used = db -> rows_used + 1;
  }else{
    printf("Error with rows_total and rows_used");
    return 0;
  }
  return 1;
}

/**
 * Function prototype for Task 3. See handout for details.
 */
int db_remove_row(struct db_table *db, unsigned long id){
  if(db == NULL){return 0;}

  int successful = 0;  // boolean - if it removed the rows_used
  for(int i = 0; i < db->rows_used; i++){

    // if it is the row that we want to delete
    unsigned long albumId = db->table[i].id;
    if(id == albumId){
      for(int j = i + 1; j < db->rows_used; j++){
        db->table[j-1] = db->table[j]; // shift all rows up by one
      }
      db->rows_used = db->rows_used - 1;
      successful = 1;

      // If there is 5 unused rows, remove them
      int rows_left = db->rows_total - db->rows_used;
      if(rows_left >= 5){
        struct album *free = (struct album *) realloc (db->table, sizeof(struct album) * (db->rows_total - 5));
        if(free == NULL){return 0;} // if the realloc
        db->table = free;
        db->rows_total = db->rows_total - 5;
      }
    }
  }
  return successful;

}
