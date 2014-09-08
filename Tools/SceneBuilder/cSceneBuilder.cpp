/**
 ****************************************************************************************************
 * \file		cSceneBuilder.cpp
 * \brief		Implementation of cSceneBuilder class
 *
 * \date		1 February 2013
 * \author		Sherly Yunita \n
 *				Created \n
 *				\n\n
 ****************************************************************************************************
*/

#include "cSceneBuilder.h"

// Inherited Implementation
//=========================

bool cs6963::cSceneBuilder::Build_derived( const char* i_fileName_source, const char* i_fileName_target ) const
{
	// For now textures don't get "built";
	// instead, copy the source texture as-is to the target
	BOOL shouldFailIfDestinationFileAlreadyExists = FALSE;
	if ( CopyFile( i_fileName_source, i_fileName_target, shouldFailIfDestinationFileAlreadyExists ) == TRUE )
	{
		return true;
	}
	else
	{
		std::string errorMessage = std::string( "Couldn't copy " ) + i_fileName_source + " to " + i_fileName_target + ":  "
			+ GetLastWindowsError();
		FormatAndOutputErrorMessage( errorMessage );
		return false;
	}
}
