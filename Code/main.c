#include <stdlib.h>
#include <stdio.h>

/* --Le--nommage--de--certaines--valeurs------------------------------------- */

#define VALUE 0
#define COUNT ( Size + 1 )

/* --Les--constantes--de--compilation---------------------------------------- */

#define Max_size_bloc 5
#define Max_size ( Max_size_bloc * Max_size_bloc )
#define Size ( Size_bloc * Size_bloc )

/* --Les--variables--globales------------------------------------------------ */

int Size_bloc ;
int Sudoku[ Max_size + 1 ][ Max_size + 1 ][ Max_size + 2 ] ;
int * Lines[ Max_size + 1 ][ Max_size + 1 ] ;
int * Columns[ Max_size + 1 ][ Max_size + 1 ] ;
int * Blocs[ Max_size + 1 ][ Max_size + 1 ] ;
int Optimise_one , Optimise_two ;

char Transcode[ 16 + 1 ]
= { ' ' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
    'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' } ;

char Transcode_ext[ 25 + 1 ]
= { ' ' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' ,
    'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' } ;

/* --Quelques--exemples--pour--le--test-------------------------------------- */

#include "grids.c"

/* --Les--prototypes--des--fonctions--fournies------------------------------- */

void setup_Lines_Columns_Blocs ( void ) ;
void fill_squares_line ( int * squares[ ] , int li ) ;
void fill_squares_column ( int * squares[ ] , int co ) ;
void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co ) ;
void optimise ( void ) ;
int fill_and_count_squares_Sudoku ( int value_list[ ] ) ;
int main ( void ) ;

/* --Les--prototypes--des--fonctions--a--fournir----------------------------- */

void print_Sudoku ( void ) ;
void fill_possibilities ( void ) ;
int optimise_possibilities ( int * squares[ ] ) ;
int back_track ( int squares_filled ) ;

/* --Les--fonctions--fournies------------------------------------------------ */

void setup_Lines_Columns_Blocs ( void ){
      int i ;
      for ( i = 1 ; i <= Size ; i++ ){
          fill_squares_line( Lines[ i ] , i ) ;
          fill_squares_column( Columns[ i ] , i ) ;
          fill_squares_bloc( Blocs[ i ] ,
                              1 + ( i - 1 ) / Size_bloc * Size_bloc ,
                              1 + ( i - 1 ) % Size_bloc * Size_bloc ) ;
          }
      }

void fill_squares_line ( int * squares[ ] , int li ){
      int co , index = 1 ;
      for ( co = 1 ; co <= Size ; co++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
     }

void fill_squares_column ( int * squares[ ] , int co ){
      int li , index = 1 ;
      for ( li = 1 ; li <= Size ; li++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
      }

void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co ){
      int offset_li , offset_co , index = 1 ;
      for ( offset_li = 0 ; offset_li < Size_bloc ; offset_li++ )
          for ( offset_co = 0 ; offset_co < Size_bloc ; offset_co++ )
              squares[ index++ ] = Sudoku[ base_li + offset_li ][ base_co + offset_co ] ;
      }

void optimise ( void ){
      int i , iterate ;
      do {iterate = 0 ;
          for ( i = 1 ; i <= Size ; i++ )
              {iterate = optimise_possibilities ( Lines[ i ] ) ;
               iterate = optimise_possibilities ( Columns[ i ] ) || iterate ;
               iterate = optimise_possibilities ( Blocs[ i ] ) || iterate ;
              }
         }
      while ( iterate ) ;
      }

int fill_and_count_squares_Sudoku ( int value_list[ ] ){
  int li , co , value , index = 0 , sum = 0 ;
  for ( li = 1 ; li <= Size ; li++ )
     for ( co = 1 ; co <= Size ; co++ ){
          value = value_list[ index ++ ] ;
          Sudoku[ li ][ co ][ VALUE ] = value ;
          if ( value )
             sum++ ;
         }
 return( sum ) ;
}

int main ( void ){
   int solution_found , number_squares ;
   Size_bloc = 5 ;
   setup_Lines_Columns_Blocs( ) ;
   Optimise_one = 1 ;
   Optimise_two = 1 ;
   number_squares = fill_and_count_squares_Sudoku( Grid_twenty_five_1 ) ;
   print_Sudoku( ) ;
   solution_found = back_track( number_squares ) ;
   if ( solution_found ){
       (void)printf( "\nNous avons trouvé la solution :\n\n" ) ;
       print_Sudoku( ) ;
      }
   else
      (void)printf( "\nNous n'avons pas trouvé de solution.\n" ) ;
   (void)printf( "Bye !" ) ;
   return( 0 ) ;
}

/* --Les--autres--prototypes------------------------------------------------- */
/* Fonctions d'impression */
void print_star_line(void);
void print_dash_line(void);
void print_line(int);

/* Fonctions pour les possibilités */
void initialize_possibilities(int*);

/* Fonctions auxiliaires du back_track */
int* search_less_possibilities_cell( void );

/* --La--fonction--d--impression--------------------------------------------- */
void print_Sudoku ( void ){
  int i, j;
  int counter = 1;
  // Boucle sur le nombre de blocs
  for(i = 0; i < Size_bloc; i++){
    print_star_line();
    // Boucle sur le nombre de lignes par blocs
    for(j = 0; j < Size_bloc; j++){
      print_line(counter);
      if(j < Size_bloc -1)
        print_dash_line();
      counter++;
    }
  }
  print_star_line();
}

/* Les fonctions auxiliaires de print_Sudoku */
void print_star_line(void){
  int i;
  for(i = 0; i < Size; i++){
    printf("***");
  }
  printf("*\n");
}

void print_dash_line(void){
  int i, j;
  // Boucle pour le nombre de blocs.
  for(i = 0; i < Size_bloc; i++){
    printf("*");
    // Boucle pour le nombre d'élément dans un bloc
    for(j = 0; j < Size_bloc; j++){
      printf("--");
      // Condition pour éviter de mettre un + en trop
      if(j < Size_bloc-1)
        printf("+");
    }
  }
  // On ferme la grille
  printf("*\n");
}

void print_line(int lineNumber){
  int i, j;
  int counter = 1; // Nous permet de garder la position sur la ligne
  // Boucle pour le nombre de blocs.
  for(i = 0; i < Size_bloc; i++){
    printf("*");
    // Boucle pour le nombre d'élément dans un bloc
    for(j = 0; j < Size_bloc; j++){
      if(*Sudoku[ lineNumber ][ counter ] != 0)
        printf("%2d", *Sudoku[ lineNumber ][ counter ]);
      else
        printf("  ");
      // Condition pour éviter de mettre un | en trop
      if(j < Size_bloc-1)
        printf("|");
      counter++;
    }
  }
  // On ferme la grille
  printf("*\n");
}

/* --Le--raisonnement--au--niveau--zero-------------------------------------- */

void fill_possibilities ( void ){
  int i, j;
  // Boucle sur les lignes
  for(i = 0; i < Size; i++){
    // Boucle sur les colonnes --> parcours de toutes les cases de la grille
    for(j = 0; j < Size; j++){
      // Test : Est-ce que la case a une valeur?
      if(Sudoku[i][j][0] == 0){
        // On initialise les valeurs possibles a 1
        initialize_possibilities( Sudoku[i][j] );
        // On regarde les valeurs sur la ligne, on enlève les valeurs présentes
      }
      // Alors : On passe a la suivante
      /* Sinon :
        -
        - On regarde les valeurs sur la ligne, on enlève les valeurs présentes
        - On fait pareil pour la colonne et le bloc*/
    }
  }
}

/* Les fonctions auxiliaires de fill_possibilities */
void initialize_possibilities( int* cell ){
  int i;
  // On initialise TOUTES les possibilités à 1
  for(i = 1; i <= Size; i++){
    cell[i] = 1;
  }
  // On initialise le COUNT avec le nombre d'éléments
  cell[COUNT] = Size;
}

/* --Les--optimisations------------------------------------------------------ */

int optimise_possibilities ( int * squares[ ] ){

}

/* --Une--valeur--proposee--une--seule--fois--------------------------------- */
/* Les fonctions correspondant a la premiere optimisation */
/* --Deux--cases--a--possibilites--doubles----------------------------------- */
/* Les fonctions correspondant a la seconde optimisation */
/* --Le--back--track--------------------------------------------------------- */

int back_track ( int squares_filled ){
  int* cell;
  int i, result;
  // Si squares_filled == Size*Size, on retourne 1 : la grille est complète
  if(squares_filled == (Size * Size))
    return 1;
  // Sinon :
  else{
    // on calcule les possibilités pour les cases vides
    fill_possibilities();
    // on cherche la case vide ayant le moins de possibilités
    cell = search_less_possibilities_cell();
    // Si le nombre de possibilités de la cellule est 0 : alors on s'est trompé
    if(cell[COUNT] == 0)
      return 0;
    // Sinon on parcourt les différentes possibilités
    for(i = 1; i <= Size; i++){
      // On ne prend que les valeurs possibles
      if(cell[i] == 1){
        // On essaie avec la valeur i dans cette case
        cell[VALUE] = i;
        result = back_track( squares_filled +1 );
        // Si le résultat est vrai, alors on renvoie 1
        if(result == 1)
          return 1;
        // Sinon on remet la valeur à 0 et on change de valeur
        else {
          cell[VALUE] = 0;
          // TODO: Est-ce qu'on enlève la possibilité de i aussi? (cell[i] = 0?)
        }
      }
      // On essaie en sortant de la boucle au cas ou... TODO: vraiment utile?
      if(cell[VALUE] == 0)
        return 0;
    }
  }
}

/* Les fonctions auxiliaires de back_track */

int* search_less_possibilities_cell( void ){
  int i, j;
  // Variables temporaires pour le choix de la cellule
  int* temp_cell;
  int min_possibility_count = 10;

  for(i = 1; i <= Size; i++){
    for(j = 1; j <= Size; j++){
      if((*Sudoku[i][j] == 0) && (Sudoku[i][j][COUNT] < min_possibility_count)){
        temp_cell = Sudoku[i][j];
        min_possibility_count = temp_cell[COUNT];
      }
    }
  }
  return temp_cell;
}

/* -------------------------------------------------------------------------- */
