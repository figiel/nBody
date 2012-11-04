General
==============================

Before using this software, please read the licence provided in Licence.txt file.



Directory structure
==============================

\Bin
	All output binaries including itermediate and executable files.

\Projects
	Directory containing all available project for different programming
	environments. Each project must be delivered in separate subdirectory that
	contains all files including makefiles engaged with specific environment.

\Projects\VC2010
	Project for VC++ 2010 Express (Architectures: WIN32, x86 for Debug
	and Release).

\Source
	Directory containing all source codes including header files.

\Source\Environment\
	Directory containing all source codes including header files engaged with
	specific programming environment.

\Source\Environment\VC2010
	Source codes related to VC++ 2010 Express programming environment FOR WIN32
	and x64 Windows architectures.

\Source\Skeleton
	Directory contains CSkeleton class definition. This class is interface
	between environment specific source code and the rest of application
	sources. This is also a skeletion that manages all other sources like
	graphics, physics or world management and other components initialization.

\Source\Math
	Directory contains all mathematical algorythms like numerical analysis,
	shared by other modules.

\Source\World
	Source implements world constraints and initial structure.

\Source\Physics
	Source implements all body interactions.

\Source\Graphics
	Source implements graphics rendering in OpenGL.