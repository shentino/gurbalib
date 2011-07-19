inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^end of the tunnel.%^RESET%^" );
  set_long( "You are at the end of a small tunnel.  There is a large " +
     "red button here.");
  set_exits( ([ 
	       "north" : "/domains/newbie/rooms/fighting",
	       "out" : "/domains/newbie/rooms/tree",
  ]) );
  add_item("button", "A giant red BUTTON!\nIt is glowing and says PRESS ME!");
  add_room_command("push", "do_push");
}

int do_push(string arg) {
   if (arg == "button") {
      if( this_player()->is_completed_quest("NewbieVille")) {
          write("The button is already depressed.\n");
      } else {
         this_player()->add_completed_quest("NewbieVille");
         write("Congradulations!!! You have just completed the NewbieVille " +
           "Quest.\n");
      }
   } else {
      write("Push what?");
   }
}