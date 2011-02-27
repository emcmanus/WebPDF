#include "AS3.h"

#include "fitz.h"
#include "mupdf.h"
#include "pdfapp.h"

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "webpdf.h"


// 
// Main
// 

int main(int argc, char **argv)
{
	// Create callbacks
	AS3_Val setupMethod = AS3_Function(NULL, f_setup);
	AS3_Val tickMethod = AS3_Function(NULL, f_tick);
	AS3_Val quitApplicationMethod = AS3_Function(NULL, f_teardown);
	
  AS3_Val libPDF = AS3_Object(
		"setup:AS3ValType, tick:AS3ValType, quit:AS3ValType", 
		setupMethod, tickMethod, quitApplicationMethod
	);
    
	AS3_Release( setupMethod );
	AS3_Release( tickMethod );
	AS3_Release( quitApplicationMethod );
	
  AS3_LibInit(libPDF);
	
	return (0);
}






static pdfapp_t gapp;


// 
// AS3 Callbacks
// 

AS3_Val f_setup (void *data, AS3_Val args)
{
  pdfapp_init(&gapp);
  
  gapp.scrw = 300;
	gapp.scrh = 800;
	gapp.zoom = 100.0;
	gapp.pageno = 1;
	
  pdfapp_open(&gapp, "pdfBytes");
  
  return AS3_Int(0);
}

AS3_Val f_tick (void *data, AS3_Val args)
{
  // Blit
  
  return AS3_Int(0);
}

AS3_Val f_teardown (void *data, AS3_Val args)
{
  pdfapp_close(&gapp);
  
  return AS3_Int(0);
}