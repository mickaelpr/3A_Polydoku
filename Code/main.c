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
/* Ce sont les proptotypes des autres fonctions que vous introduisez. */
/* --La--fonction--d--impression--------------------------------------------- */

void print_Sudoku ( void )
     {
      /* ... */
     }

/* Les fonctions auxiliaires de print_Sudoku */
/* --Le--raisonnement--au--niveau--zero-------------------------------------- */

void fill_possibilities ( void )
     {
      /* ... */
     }

/* Les fonctions auxiliaires de fill_possibilities */
/* --Les--optimisations------------------------------------------------------ */

int optimise_possibilities ( int * squares[ ] )
    {
     /* ... */
    }

/* --Une--valeur--proposee--une--seule--fois--------------------------------- */
/* Les fonctions correspondant a la premiere optimisation */
/* --Deux--cases--a--possibilites--doubles----------------------------------- */
/* Les fonctions correspondant a la seconde optimisation */
/* --Le--back--track--------------------------------------------------------- */

int back_track ( int squares_filled )
    {
     /* ... */
    }

/* Les fonctions auxiliaires de back_track */
/* -------------------------------------------------------------------------- */