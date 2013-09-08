inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: add_bonus [-h] STATNAME" });
   lines += ({ " " });
   lines += ({ "Increase your bonus to stat STATNAME by 1." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "See also:" });
   lines += ({ "\tadd_base, query_base_max, score, stats" });

   this_player()->more(lines);
}

static void main(string statname) {

   if (!statname || (statname == "")) {
      usage();
      return;
   }

   if (sscanf(statname, "-%s", statname)) {
      usage();
      return;
   }

   this_player()->add_bonus_stat(statname, 1);
   write("done!\n");
}
