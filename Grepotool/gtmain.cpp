#include <QDebug>

#include <GtApp.h>



/*! Load all GT-Libs and launch GT 
*/
int launchGT (int argc, char**argv) {

	GtApp app (argc, argv);

	// app.createRelease ();

	return app.startGrepotool ();
}

/*! Create a release
*/
int releaseGT (int argc, char**argv) {

	GtApp app (argc, argv);

	return app.createRelease ();
}


/*! Notifies GT to pop to front by incrementing the contents 
of a shared memory segment.
*/
int notifyGT (QSharedMemory * m) {

	if (! m->lock () ) {
					
		qDebug ("No access to shared memory segment");

		return -1;
	}

	// increment the contents of m

	int * d = (int *) m->data();

	++(*d);

	m->unlock();

	return 0;
}





int main (int argc, char ** argv) 
{
	int retval = 0;

	bool do_release = false;
	bool do_help = false;

	for (int i= 1; i < argc; ++i) {
		if ( QString (argv[i]) == "-release") do_release = true;
		if ( QString (argv[i]) == "-r") do_release = true;
		if ( QString (argv[i]) == "-help") do_help = true;
		if ( QString (argv[i]) == "-?") do_help = true;
	}

	if (do_release) {
		return releaseGT (argc,argv);
	}


	QSharedMemory m ("Grepotool");

	if(m.create (10, QSharedMemory::ReadWrite)) {
	
		qDebug ("success we're the only instance - launching GT...");
		
		if (! m.lock () ) {

			qDebug ("No access to shared memory segment");

			return -1;
		}
		
		// initialize shared memory to 0

		int * d = (int *) m.data();

		*d = 0;

		m.unlock();
				
		try {

			retval = launchGT ( argc, argv );

		} catch (...) {

			qDebug ("Exception caught");

			// TODO: add exception handling or a stack dump ...

			retval = -1;
		}

	} else {

		if ( m.attach () ) {

			qDebug ("Success we're the second instance - notifying GT to pop to front");

			retval = notifyGT ( &m );
			
		} else {

			qDebug ("Attach failed ");

			retval = -1;
		}
		
	}
	
	return retval;

}