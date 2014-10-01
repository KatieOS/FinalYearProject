#include "GamePluginPCH.h"
#include "save.h"
#include "BaseEntity.hpp"
#include "Player.h"
#include "VisionSerializer.h"
//#include "GameManager.h"

#define ARCHIVE_START_TAG "SERIALIZE_API_SAMPLE"
#define ARCHIVE_END_TAG   "END_OF_ARCHIVE"
#define SAVEGAME_NAME     "SaveGames/save%1d.gam"
Save::Save()
	 :m_iCurrentMap(0)
    , m_fInfoTime(0.0f)
    , m_bSavePending(false)
    , m_iGameNum(1)
{

}


// ---------------------------------------------------------------------------------
// Method: ResetWorld
// Notes: This function is used by the LoadGame function to get rid of all
//        serializeable entities.
// ---------------------------------------------------------------------------------


void Save::SaveMe()
{
	

	 hkvVec3 m_sPosition;
	 hkvMat3 m_rotationMatrix;
  // open file and create archive
  IVFileOutStream *pOutStream = Vision::File.Create( "test.sav");
 // if (!pOutStream) Vision::Error.FatalError("Couldn't create file!");

  VArchive ar( "test.sav", pOutStream, Vision::GetTypeManager() );

  // write archive version number
  ar << Vision::GetArchiveVersion();

  // write other data
  //write position
  

  // close archive and file
  ar.Close();
  pOutStream->Close();

}
void Save::Load()
{
	// open file and create archive
  IVFileInStream *pInStream = Vision::File.Open( "test.sav");
  //if (!pInStream) Vision::Error.FatalError("Couldn't open file!");

  VArchive ar( "test.sav", pInStream, Vision::GetTypeManager() );

  // read and set archive version number
  int iLoadingVersion;
  ar >> iLoadingVersion;
  ar.SetLoadingVersion(iLoadingVersion);

  // check whether Vision can use this archive version
  if (! Vision::IsValidArchive(ar))
  {
   // Vision::Error.FatalError("Incompatible archive version!");
    ar.Close();
    pInStream->Close();
    return;
  }

  // read other data

  // close archive and file
  ar.Close();
  pInStream->Close();

}

