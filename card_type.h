/*
  Nathaniel Collier
  9/1/2007
  This code was origionaly backported from java code I wrote
*/
#include <string>
#include <sstream>

using namespace std;

#ifndef CARD_TYPE_H
#define CARD_TYPE_H





class card_type
{
   private:

	 bool visible;

	 int x; // graphical display x pos
	 int y; // graphical display y pos

   public:
     int value; // how much is the card worth in points
     int suit; // heart diamond spade club
     int face; // king queen jack 1 2 3 4 5 6 7 8 9 10
     string name; // "King of Hearts"
     string abv_name;
     int index;
     int pos;


     card_type(int value_, int suit_, int face_, string name_, string abv_name_, int index_);
     card_type( const card_type& temp );
	 card_type();
     ~card_type();
     char face_to_char( int face_i );
     string face_to_string( int face_i );
     string suit_to_string( int suit );
     char suit_to_char( int suit_i );
     char convert_suit_to_symbol( char suit );
     string color_abv_name( string abv_name );
     card_type create_card( int suit, int face );
     string get_card_text();

};


//////////// Private Functions //////////////




//////////// Public Functions ///////////////



card_type::card_type()
{
  value = 0;
  suit = 0;
  face = 0;
  name = "blank";
  abv_name = "blank";
  index = 0;
}

card_type::card_type(int value_, int suit_, int face_, string name_, string abv_name_, int index_) 
{     
   value = value_;
   suit = suit_;
   face = face_;
   name = name_;
   abv_name = abv_name_;
   index = index_;  
}
    
card_type::card_type( const card_type& temp )
{
      value = temp.value;
      suit = temp.suit;
      face = temp.face;
      name = temp.name;
      abv_name = temp.abv_name;
      index = temp.index;
      x = temp.x;
      y = temp.y;
      visible = temp.visible;     
}

card_type::~card_type()
{

}

    /* 
     *  converts an integer to the face character
     */
    char card_type::face_to_char( int face_i )
    {
      char face_ch = 'X';
      
       switch( face_i )
       {
           case 1: face_ch = 'A'; break;
           case 2: face_ch = '2'; break;
           case 3: face_ch = '3'; break;
           case 4: face_ch = '4'; break;
           case 5: face_ch = '5'; break;
           case 6: face_ch = '6'; break;
           case 7: face_ch = '7'; break;
           case 8: face_ch = '8'; break;
           case 9: face_ch = '9'; break;
           case 10: face_ch = 'T'; break;
           case 11: face_ch = 'J'; break;
           case 12: face_ch = 'Q'; break;
           case 13: face_ch = 'K'; break;
           case 14: face_ch = 'J'; break;
       }
       
       return face_ch;
    }
    
    /*
     * Takes a face 1-4 and converts it to a string
     */
    string card_type::face_to_string( int face_i )
    {
      string face_str;
      switch( face_i )
       {
           case 1: face_str = "Ace"; break;
           case 2: face_str = "Two"; break;
           case 3: face_str = "Three"; break;
           case 4: face_str = "Four"; break;
           case 5: face_str = "Five"; break;
           case 6: face_str = "Six"; break;
           case 7: face_str = "Seven"; break;
           case 8: face_str = "Eight"; break;
           case 9: face_str = "Nine"; break;
           case 10: face_str = "Ten"; break;
           case 11: face_str = "Jack"; break;
           case 12: face_str = "Queen"; break;
           case 13: face_str = "King"; break;
           case 14: face_str = "Joker"; break;
       }
      return face_str;
    }
    

    /*
     *  Takes a suite 1-4 and turns it into a string
     */
    string card_type::suit_to_string( int suit )
    {
       string text;
       
       switch( suit )
       {
           case 1: text = "Heart"; break;
           case 2: text = "Diamond"; break;
           case 3: text = "Spade"; break;
           case 4: text = "Club"; break;
       }
      return text;
    }
    
    /*
     *  Takes a suite 1-4 and turns it into a character
     */
    char card_type::suit_to_char( int suit_i )
    {
      char suit = 'X';
      
      switch( suit_i )
      {
          case 1: suit = 'H'; break;
          case 2: suit = 'D'; break;
          case 3: suit = 'S'; break;
          case 4: suit = 'C'; break;
      }
      return suit;
    }
    
    
   /*
    char_change
	receives a char and changes it to
	a symbol using a code
	Only used in the console based version of this program
	This function is mostly hear for historical reasons
   */
    char card_type::convert_suit_to_symbol( char suit )
    {
      char symbol;
      
      switch( suit ) 
      {
         case 'H': symbol = (char)259; break;
         case 'D': symbol = (char)260; break;
         case 'C': symbol = (char)261; break;
         case 'S': symbol = (char)262; break;
         case 'O': symbol = (char)257; break;
         case 'T': symbol = (char)258; break;
         default: symbol = suit; break;
      }
      return symbol;  
    }
    
    /*
     *  Takes a non colorized abreviated name and inserts the 
     *  proper color codes for the abreviated name
     */
    string card_type::color_abv_name( string abv_name )
    {
        string new_abv;
        char suit;
        char face;
        
        // the abv_name has quotes at positions 0 and 3
        cout << "abv_name before color:  " << abv_name ;
        suit = abv_name[1];
        face = abv_name[0];
        
        char symbol_suite = convert_suit_to_symbol( suit );
        
        switch( face )
        {
           case 'A': new_abv += "&r"; break;
           case 'K': 
           case 'Q':
           case 'J': new_abv += "&C"; break;
           case '8': new_abv += "&G"; break;
           default: new_abv += "&c"; break;
        }
        new_abv += face;
   
        switch( suit )
        {
           case 'H': 
           case 'D': new_abv += "&R"; break; // red
           case 'S':
           case 'C': new_abv += "&W"; break; // black
           default: break; // don't want any coloring right now on special cards
        } 
        new_abv += suit;
        
        return new_abv;
    }
    
    /*
     *  Generates a card based on the type which is the 'face' of the card
     *       2 - 10 Jack Queen King Ace Joker etc...
     *  The suit which can be a 
     *       1 - Heart
     *       2 - Diamond
     *       3 - Spade
     *       4 - Club
     */
    card_type card_type::create_card( int suit, int face )
    {
       card_type card(-1,-1,-1,"-1","-1",-1);
       string suit_str = suit_to_string( suit );
       string face_str = face_to_string( face);
       string abv_name =  "" + face_to_char( face ) + suit_to_char( suit ) ;
       string name =  face_to_string( face ) + " of " + suit_to_string( suit ) ;      
       /*
        *  The below lines that are commented out are left in for backwards compatibility
        *  with the load from file function since it leaves the quote characters in the string
        *  when it parses them
        */

       
       card.suit = suit;
       card.face = face;
       
       if( face == 8 )
       {
          card.value = 50;
       }
       else
       {
           card.value = face;
       }
       
       card.abv_name = abv_name;
       
       
       
       card.name = name;
       
       card.index = 0;
       
       cout << card.get_card_text();
       
       return card;
    }
    
    
    string card_type::get_card_text()
    {
        stringstream text;
        
        text  <<  "\nSuit= " << suit_to_string( suit ) <<
                 "\nFace= " << face_to_string( face ) <<
                 "\nAbvname= " << abv_name <<
                 "\nName= " << name <<
                 "\nValue= " << value <<
                 "\nIndex= " << index <<
                 "\nFace= " << face <<
                 "\nSuit= " << suit;
        return text.str();
    }









#endif



