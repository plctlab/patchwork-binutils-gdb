/* Example of writing diagnostics as SARIF to a file.  */

#include "libdiagnostics.h"

/*
_________111111111122
123456789012345678901
PRINT "hello world!";
*/
const int line_num = __LINE__ - 2;

int
main ()
{
  FILE *outfile = fopen ("test.txt", "w");
  if (!outfile)
    return -1;

  diagnostic_manager *diag_mgr = diagnostic_manager_new ();

  diagnostic_manager_add_sarif_sink (diag_mgr, outfile,
				     DIAGNOSTIC_SARIF_VERSION_2_1_0);

  const diagnostic_file *file = diagnostic_manager_new_file (diag_mgr, __FILE__, "c");
  diagnostic_location_t loc_start
    = diagnostic_manager_new_location_from_file_line_column (diag_mgr, file, line_num, 8);
  diagnostic_location_t loc_end
    = diagnostic_manager_new_location_from_file_line_column (diag_mgr, file, line_num, 19);
  diagnostic_location_t loc_range
    = diagnostic_manager_new_location_from_range (diag_mgr,
						  loc_start,
						  loc_start,
						  loc_end);

  diagnostic *d = diagnostic_begin (diag_mgr,
				    DIAGNOSTIC_LEVEL_ERROR);
  diagnostic_set_location (d, loc_range);
  
  diagnostic_finish (d, "can't find %qs", "foo");

  diagnostic_manager_release (diag_mgr);

  fclose (outfile);

  return 0;
};
