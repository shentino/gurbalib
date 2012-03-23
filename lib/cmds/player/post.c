void usage() {
   write("Usage: post [-h] SUBJECT\n");
   write("Post a message to a message board with subject SUBJECT.\n");
   write("It will then kick you into a simple editor so you can write your " +
      "message.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

private static mapping msg;
private static mapping subject;
private static mapping ob;

void main(string str) {

   if (!msg) {
      msg = ([]);
      subject = ([]);
      ob = ([]);
   }

   if (!str || str == "") {
      usage();
      return;
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      subject[this_player()->query_name()] = str;
   }

   ob[this_player()->query_name()] = this_environment()->present("board");
   if (!ob[this_player()->query_name()]) {
      write("Try writing a message at a message board.\n");
      return;
   }

   write(" \nPlease enter your text below.\n" +
      "'.' without quotes on a blank line to end. ~a to abort.\n" +
      "------------------------------------------------------------" +
      "------------------\n");
   this_player()->input_to_object(this_object(), "enter_line");
   this_player()->set_editing(1);
   msg[this_player()->query_name()] = "";
}

void enter_line(string line) {
   if (line != "." && line != "**" && line != "~a") {
      if (!msg[this_player()->query_name()]) {
	 msg[this_player()->query_name()] = line + "\n";
      } else {
	 msg[this_player()->query_name()] = msg[this_player()->query_name()] +
	    line + "\n";
      }
      this_player()->input_to_object(this_object(), "enter_line");
   } else {
      if (line == "~a") {
	 write(" \nMessage aborted.\n");
      } else {
	 ob[this_player()->query_name()]->add_message(this_player()->
	    query_name(), subject[this_player()->query_name()],
	    msg[this_player()->query_name()]);
	 write(" \nMessage posted.\n");
      }
      this_player()->set_editing(0);
      this_player()->write_prompt();
      this_environment()->tell_room(this_player(),
	 this_player()->query_Name() + " posts a new message.\n");
   }
}
